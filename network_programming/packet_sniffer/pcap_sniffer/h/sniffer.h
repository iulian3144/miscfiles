#ifndef _SNIFFER_H
#define _SNIFFER_H

#define PCAP_BUF_SIZE   1518
#define PKT_COUNT       100

/* function prototypes */
void print_usage(char const *argv[]);
void listDevices();

#endif /* _SNIFFER_H */
