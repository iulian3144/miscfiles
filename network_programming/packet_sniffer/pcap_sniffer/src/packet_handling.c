#include <packet_handling.h>
#include <netinet/ip.h>         /* iphdr */
#include <netinet/tcp.h>        /* tcphdr */
#include <linux/if_ether.h>     /*ethhdr */
#include <arpa/inet.h>          /* inet_ntoa */

// TODO: add a brief description for each function

void gotPacket(u_char *args, const struct pcap_pkthdr *header,
    const u_char *packet) {
    u_int *pkt_count = (u_int *)args;
    const struct iphdr *iph;    /* ip header offset */
    const struct tcphdr *tcph;  /* tcp header offset */
    u_int ip_ihl;               /* internet header length */
    u_int tcp_hlen;             /* tcp header length */
    u_int size_tcp;             /* tcp segment length */
    const u_char *payload;      /* payload offset */
    u_int size_payload;         /* payload size */
    struct in_addr saddr;       /* src address */
    struct in_addr daddr;       /* dst address */

    /* increase packet count */
    (*pkt_count)++;
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
