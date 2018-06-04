#include <stdlib.h>
#include <stdio.h>
#include <pcap/pcap.h>
#include <string.h>
#include <string.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
// #include <linux/if.h>


#define PCAP_BUF_SIZE   1518
#define SIZE_ETHERNET   14

/* function prototypes */
void print_usage(char const *argv[]);
void listDevices();
void got_packet(u_char *args, const struct pcap_pkthdr *header,
    const u_char *packet);
void printTCPPacket(const u_char *buffer, int size);

int main(int argc, char const *argv[])
{
    char const *dev;                /* device to sniff on */
    pcap_t *handle;                 /* session handle */
    char errbuf[PCAP_ERRBUF_SIZE];  /* error string */
    char filter_exp[] = "port 443"; /* filter expression */
    struct bpf_program fp;          /* compiled filter expression */
    bpf_u_int32 mask;               /* netmask of the sniffing device */
    bpf_u_int32 net;                /* IP of the sniffing device */
    struct pcap_pkthdr header;      /* header that pcap gives us */
    const u_char *packet;           /* actual packet */
    u_int pkt_count = 1;            /* sniffed packets count */

    /* define device */
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL)
    {
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return(2);
    }

    int i;
    /* parse command line options */
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-i") == 0)
        {
            /* assign dev with the option's argument */
            if(argc > ++i)
            {
                dev = argv[i];
                continue;
            }
            else
            {
                fprintf(stderr,
                    "ERROR: '-i' option requires an argument [device]\n");
                print_usage(argv);
                exit(1);
            }
        }
        /* list devices */
        else if(strcmp(argv[i], "-D") == 0)
        {
            listDevices();
            return 0;
        }
        /* print program help/usage */
        else if(strcmp(argv[i], "-h") == 0)
        {
            print_usage(argv);
            return(0);
        }
    }

    if(pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
    {
        fprintf(stderr, "Can't get netmask for device %s: %s\n", dev, errbuf);
        net = mask = 0;
    }

    printf("Listening on %s [filter: `%s`]\n", dev, filter_exp);
    handle = pcap_open_live(dev, PCAP_BUF_SIZE, 1, 1000, errbuf);
    if(handle == NULL)
    {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return(2);
    }

    if(pcap_datalink(handle) != DLT_EN10MB)
    {
        fprintf(stderr, "Device %s doesn't provide Ethernet headers - not supported\n", dev);
        return(2);
    }

    if(pcap_compile(handle, &fp, filter_exp, 0, net) == -1)
    {
        fprintf(stderr, "Couldn't parse filter `%s`: %s\n", filter_exp,
            pcap_geterr(handle));
        return(2);
    }
    if(pcap_setfilter(handle, &fp) == -1)
    {
        fprintf(stderr, "Couldn't install filter `%s`: %s\n", filter_exp,
            pcap_geterr(handle));
        return(2);
    }

    /* grab a packet */
    // packet = pcap_next(handle, &header);
    /* print its length */
    // printf("Jacked a packet with length: [%d]\n", header.len);
    pcap_loop(handle, 10, got_packet, (u_char *)&pkt_count);

    /* close the session */
    pcap_close(handle);
    return 0;
}

void print_usage(char const *argv[])
{
    printf("Usage:\n");
    printf("\t%s [-i <device>] [-D]\n", argv[0]);
    printf("Options:\n");
    printf("\t-i <interface>  specify interface to listen on\n");
    printf("\t-B              list available interfaces\n");
}

void listDevices()
{
    pcap_if_t *devices, *device;
    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&devices, errbuf) != 0)
    {
        printf("[ERROR] %s\n", errbuf);
    }

    int i = 1;
    for(device = devices; device != NULL; device = device->next)
    {
        char *ipaddr = NULL;
        pcap_addr_t *dev_addr;

        printf("%2d. %s", i, device->name);

        int j = 0;
        for(dev_addr = device->addresses;
            dev_addr != NULL;
            dev_addr = dev_addr->next)
        {
            if(dev_addr->addr->sa_family == AF_INET && dev_addr->addr &&
                dev_addr->netmask)
            {
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
    const u_char *packet)
{
    // printf("[%2u] Got packet [len: %d]\n", (*(uint *)args)++, header->len);
    printTCPPacket(packet, header->len);
}

void printTCPPacket(const u_char *buffer, int size)
{

    unsigned short iphdrlen;
    struct iphdr *iph   = (struct iphdr *)(buffer + SIZE_ETHERNET);
    iphdrlen = iph->ihl * 4; // ihl is the length of the header in multiples of
    struct in_addr saddr = {iph->saddr};
    struct in_addr daddr = {iph->daddr};
    u_int size_tcp;

    // 4 bytes
    struct tcphdr *tcph = (struct tcphdr *)(buffer + iphdrlen);

    size_tcp = tcph->th_off*4;
    if(size_tcp < 20)
    {
        fprintf(stderr, "Invalid TCP header length: %u bytes\n", size_tcp);
        return;
    }

    fprintf(stdout, "%s:%d > %s:%d\n",
        inet_ntoa(saddr),
        ntohs(tcph->th_sport),
        inet_ntoa(daddr),
        ntohs(tcph->th_dport));
}
