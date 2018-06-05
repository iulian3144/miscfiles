#include <stdlib.h>
#include <stdio.h>
#include <pcap/pcap.h>
#include <string.h>
#include <string.h>
#include<linux/if_ether.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
// #include <linux/if.h>


#define PCAP_BUF_SIZE   1518
#define PKT_COUNT       100

/* function prototypes */
void print_usage(char const *argv[]);
void listDevices();
void got_packet(u_char *args, const struct pcap_pkthdr *header,
    const u_char *packet);
void printData(const u_char *data, int size);


int main(int argc, char const *argv[]) {
    char const *dev;                /* device to sniff on */
    pcap_t *handle;                 /* session handle */
    char errbuf[PCAP_ERRBUF_SIZE];  /* error string */
    char filter_exp[] = "tcp src port 443"; /* filter expression */
    struct bpf_program fp;          /* compiled filter expression */
    bpf_u_int32 mask;               /* netmask of the sniffing device */
    bpf_u_int32 net;                /* IP of the sniffing device */
    struct pcap_pkthdr header;      /* header that pcap gives us */
    const u_char *packet;           /* actual packet */
    int promiscous = 0;
    const u_int pkt_count = 0;      /* packet count */
    struct pcap_stat statistics;


    /* define device */
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return(2);
    }

    int i;
    /* parse command line options */
    for(i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-i") == 0) {
            /* assign dev with the option's argument */
            if(argc > ++i) {
                dev = argv[i];
                continue;
            }
            else {
                fprintf(stderr,
                    "ERROR: '-i' option requires an argument [device]\n");
                print_usage(argv);
                exit(1);
            }
        }
        /* list devices */
        else if(strcmp(argv[i], "-D") == 0) {
            listDevices();
            return 0;
        }
        /* print program help/usage */
        else if(strcmp(argv[i], "-h") == 0) {
            print_usage(argv);
            return(0);
        }
    }

    if(pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Can't get netmask for device %s: %s\n", dev, errbuf);
        net = mask = 0;
    }

    printf("Listening on %s [filter: `%s`]\n", dev, filter_exp);
    handle = pcap_open_live(dev, PCAP_BUF_SIZE, promiscous, 1000, errbuf);
    if(handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return(2);
    }

    if(pcap_datalink(handle) != DLT_EN10MB) {
        fprintf(stderr, "Device %s doesn't provide Ethernet headers - not supported\n", dev);
        return(2);
    }

    if(pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter `%s`: %s\n", filter_exp,
            pcap_geterr(handle));
        return(2);
    }
    if(pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter `%s`: %s\n", filter_exp,
            pcap_geterr(handle));
        return(2);
    }

    /* grab a packet */
    // packet = pcap_next(handle, &header);
    /* print its length */
    // printf("Jacked a packet with length: [%d]\n", header.len);
    pcap_loop(handle, PKT_COUNT, got_packet, (u_char *)&pkt_count);

    /* get and print statistics */
    pcap_stats(handle, &statistics);
    fprintf(stderr, "%2u packets received by filter\n", statistics.ps_recv);
    fprintf(stderr, "%2u packets captured\n", pkt_count);
    fprintf(stderr, "%2u packets dropped by kernel\n", statistics.ps_drop);
    fprintf(stderr, "%2u packets dropped by interface\n", statistics.ps_ifdrop);
    /* close the session */
    pcap_close(handle);
    return 0;
}

void print_usage(char const *argv[]) {
    printf("Usage:\n");
    printf("\t%s [-i <device>] [-D]\n", argv[0]);
    printf("Options:\n");
    printf("\t-i <interface>  specify interface to listen on\n");
    printf("\t-B              list available interfaces\n");
}

void listDevices() {
    pcap_if_t *devices; /* pointer to interface list */
    pcap_if_t  *device;  /* pointer to interface */
    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&devices, errbuf) != 0) {
        printf("[ERROR] %s\n", errbuf);
    }

    int i = 1;
    for(device = devices; device != NULL; device = device->next) {
        char *ipaddr = NULL;        /* string ip address */
        pcap_addr_t *dev_addr;      /* pointer to device addresses */

        printf("%2d. %s", i, device->name);

        int j = 0;
        for(dev_addr = device->addresses;
            dev_addr != NULL;
            dev_addr = dev_addr->next) {
            if(dev_addr->addr->sa_family == AF_INET && dev_addr->addr &&
                dev_addr->netmask) {
                ipaddr = inet_ntoa(
                    ((struct sockaddr_in *)dev_addr->addr)->sin_addr);
                if(j++) printf(", %s", ipaddr);
                else    printf(" [%s", ipaddr);
            }
        }
        if(j) printf("]\n");
        else  printf("\n");
        i++;
    }
}

void got_packet(u_char *args, const struct pcap_pkthdr *header,
    const u_char *packet) {
    u_int *pkt_count = (u_int *)args;
    const struct ethhdr *ethh;  /* ethernet header */
    const struct iphdr *iph;    /* ip header offset */
    const struct tcphdr *tcph;  /* tcp header offset */
    u_int ip_ihl;               /* internet header length */
    u_int tcp_hlen;             /* tcp header length */
    u_int size_tcp;             /* tcp segment length */
    const char *payload;        /* payload offset */
    u_int size_payload;         /* payload size */
    struct in_addr saddr;       /* src address */
    struct in_addr daddr;       /* dst address */

    /* increase packet count */
    (*pkt_count)++;
    ethh = (struct ethhdr *)packet;
    iph  = (struct iphdr *)(packet + ETH_HLEN);
    ip_ihl = iph->ihl * 4;
    if(ip_ihl < 20) {
        fprintf(stderr, "Invalid Internet header length: %u bytes\n", ip_ihl);
        return;
    }
    if(iph->tot_len < ip_ihl) {
        fprintf(stderr, "Invalid IP packet size: tot_len smaller than ihl\n");
        return;
    }

    saddr.s_addr = iph->saddr;
    daddr.s_addr = iph->daddr;

    /* determine protocol */
    switch(iph->protocol) {
        case IPPROTO_TCP:
            printf("Protocol: TCP\n");
            break;
        case IPPROTO_UDP:
            printf("Protocol: UDP\n");
            return;
        case IPPROTO_ICMP:
            printf("Protocol: ICMP\n");
            return;
        case IPPROTO_IP:
            printf("Protocol: IP\n");
            return;
        default:
            printf("Protocol: unknown\n");
            return;
    }

    /* define tcp header offset */
    tcph = (struct tcphdr *)(packet + ETH_HLEN + ip_ihl);
    tcp_hlen = tcph->th_off * 4;
    if(tcp_hlen < 20) {
        fprintf(stderr, "Invalid TCP header length: %u bytes\n", tcp_hlen);
        return;
    }
    size_tcp = iph->tot_len - ip_ihl;
    if(size_tcp < tcph->th_off) {
        fprintf(stderr, "Invalid TCP packet size: size_tcp < th_off\n");
        return;
    }
    fprintf(stdout, "%15s:%-5d > ", inet_ntoa(saddr), ntohs(tcph->th_sport));
    fprintf(stdout, "%15s:%-5d [len: %4d]\n", inet_ntoa(daddr),
        ntohs(tcph->th_dport), header->len);
    payload = (u_char *)(packet + ETH_HLEN + ip_ihl + tcp_hlen);
    size_payload = ntohs(iph->tot_len) - (ip_ihl + tcp_hlen);

    if(size_payload > 0)
        printData(payload, size_payload);
}

void printData(const u_char *payload, int size_payload) {
    FILE *logfile = stdout;
    int i, j;
    for (i = 0; i < size_payload; i++) {
        // if one line of hex printing is complete...
        if ( i != 0 && i % 16 == 0) {
            fprintf(logfile, "         ");
            for (j = i - 16; j < i; j++) {
                // if its a number or alphabet
                if (payload[j] >= 32 && payload[j] <= 128)
                    fprintf(logfile, "%c", (unsigned char)payload[j]);
                else
                    fprintf(logfile, "."); // otherwise print a dot
            }
            fprintf(logfile, "\n");
        }

        if (i % 16 == 0)
            fprintf(logfile, "   ");
        fprintf(logfile, " %02X", (unsigned int)payload[i]);

        // print the last spaces
        if (i == size_payload - 1) {
            for (j = 0; j < 15 - i % 16; j++)
                fprintf(logfile, "   "); // extra spaces

            fprintf(logfile, "         ");

            for (j = i - i % 16; j <= i; j++) {
                if (payload[j] >= 32 && payload[j] <= 128)
                    fprintf(logfile, "%c", (unsigned char)payload[j]);
                else
                    fprintf(logfile, ".");
            }
            fprintf(logfile, "\n");
        }
    }
}
