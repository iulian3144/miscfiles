#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h> /* for catching signals */
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <errno.h>

typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;

#ifndef RECV_BUFSIZE
#define RECV_BUFSIZE 65536
#endif

void sigint_handler(int sig);
void processPacket(unsigned char *buffer, int size);
void printTCPPacket(unsigned char *buffer, int size);
void printData(unsigned char *data, int size);
int sockFd;
unsigned int packetCount = 0;

int main(int argc, char *argv[])
{
    int status;
    sockaddr_t saddr;
    int saddr_size;
    int data_size;
    unsigned char *buffer = (unsigned char *)malloc(RECV_BUFSIZE);
    char iface[IFNAMSIZ] = "eth0";

    // parse cmd arguments
    int i;
    for(i = 1; i < argc; i++)
    {
        // interface name
        if(strcmp(argv[i], "-i") == 0)
        {
            i++;
            strcpy(iface, argv[i]);
            iface[strlen(argv[i])] = 0;
        }
    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        printf("\nCan't catch SIGINT!\n");

    // create a raw socket that should sniff
    sockFd = socket(
                 PF_INET,        // family - IPv4 protocols
                 SOCK_RAW,       // type - TCP (SOCK_DGRAM = UDP)
                 IPPROTO_TCP     // protocol
             );
    status = setsockopt(sockFd, SOL_SOCKET, SO_BINDTODEVICE, iface,
        strlen(iface));

    if(status != 0)
    {
        printf("[setsockopt] [ERROR %d] (%s) '%s'\n", errno, iface,
            strerror(errno));
        exit(1);
    }


    while (1)
    {
        saddr_size = sizeof(saddr);
        // receive packet
        // printf("receiving... ");
        data_size = recvfrom(sockFd, buffer, RECV_BUFSIZE, 0, &saddr,
                             &saddr_size);
        // printf("done [data_size]\n");
        if (data_size < 0)
        {
            printf("[recvfrom] error!\n");
            return 1;
        }
        packetCount++;
        printf("\rpacket count: %3d", packetCount);
        // processPacket(buffer, data_size);
    }

    status = close(sockFd);
    printf("Finished\n");
    return status;
}

void processPacket(unsigned char *buffer, int size)
{
    struct iphdr *iph = (struct iphdr *)buffer;

    switch (iph->protocol)
    {
    case 1: // ICMP protocol
        break;
    case 2: // IGMP protocol
        break;
    case 6: // TCP protocol
        printTCPPacket(buffer, size);
        break;
    case 17: // UDP protocol
        break;
    }
}

void printTCPPacket(unsigned char *buffer, int size)
{
    unsigned short iphdrlen;
    struct iphdr *iph   = (struct iphdr *)buffer;
    iphdrlen = iph->ihl * 4; // ihl is the length of the header in multiples of
    // 4 bytes
    struct tcphdr *tcph = (struct tcphdr *)(buffer + iphdrlen);

    fprintf(stdout, "SRC_port: %5u; DST_port: %5u\n",
            ntohs(tcph->source), ntohs(tcph->dest));
    fprintf(stdout, "Data Payload\n");
    printData(buffer + iphdrlen + tcph->doff * 4,
              size - tcph->doff * 4 - iphdrlen);
}

void printData(unsigned char *data, int size)
{
    FILE *logfile = stdout;
    int i, j;
    for (i = 0; i < size; i++)
    {
        // if one line of hex printing is complete...
        if ( i != 0 && i % 16 == 0)
        {
            fprintf(logfile, "         ");
            for (j = i - 16; j < i; j++)
            {
                // if its a number or alphabet
                if (data[j] >= 32 && data[j] <= 128)
                    fprintf(logfile, "%c", (unsigned char)data[j]);
                else
                    fprintf(logfile, "."); // otherwise print a dot
            }
            fprintf(logfile, "\n");
        }

        if (i % 16 == 0)
            fprintf(logfile, "   ");
        fprintf(logfile, " %02X", (unsigned int)data[i]);

        if (i == size - 1) // print the last spaces
        {
            for (j = 0; j < 15 - i % 16; j++)
                fprintf(logfile, "   "); // extra spaces

            fprintf(logfile, "         ");

            for (j = i - i % 16; j <= i; j++)
            {
                if (data[j] >= 32 && data[j] <= 128)
                    fprintf(logfile, "%c", (unsigned char)data[j]);
                else
                    fprintf(logfile, ".");
            }
            fprintf(logfile, "\n");
        }
    }
}

void sigint_handler(int sig)
{
    int status;
    printf("\nSIGINT caught, exiting gracefully...\n");
    printf("packet count: %u\n", packetCount);
    status = close(sockFd);

    exit(status);
}
