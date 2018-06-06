#ifndef _PACKET_HANDLING_H
#define _PACKET_HANDLING_H

#include <pcap/pcap.h>

/* function prototypes */
void gotPacket(u_char *args, const struct pcap_pkthdr *header,
    const u_char *packet);
void printData(const u_char *data, int size);
#endif /* _PACKET_HANDLING_H */
