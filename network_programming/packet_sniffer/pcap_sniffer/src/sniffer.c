#include <sniffer.h>
#include <packet_handling.h>
#include <stdlib.h>
#include <stdio.h>
#include <pcap/pcap.h>      /* libpcap */
#include <string.h>         /* strcmp */
#include <arpa/inet.h>      /* inet_ntoa */

// TODO: add a brief description for each function

int main(int argc, char const *argv[]) {
    char const *dev;                /* device to sniff on */
    pcap_t *handle;                 /* session handle */
    char errbuf[PCAP_ERRBUF_SIZE];  /* error string */
    char filter_exp[] = "tcp src port 443"; /* filter expression */
    struct bpf_program fp;          /* compiled filter expression */
    bpf_u_int32 mask;               /* netmask of the sniffing device */
    bpf_u_int32 net;                /* IP of the sniffing device */
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

    pcap_loop(handle, PKT_COUNT, gotPacket, (u_char *)&pkt_count);

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

/** print_usage
 * argv - command line arguments
 */
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
