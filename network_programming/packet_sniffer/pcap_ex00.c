#include <stdlib.h>
#include <stdio.h>
#include <pcap/pcap.h>
#include <string.h>
#include <string.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

/* function prototypes */
void usage(char const *argv[]);
void listDevices();

int main(int argc, char const *argv[])
{
    char dev[] = "eth0";

    int i;
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-i") == 0)
        {
            // assign dev with the next argument
            if(argc > ++i)
            {
                strcpy(dev, argv[i]);
                continue;
            }
            else
            {
                printf("ERROR: '-i' option requires an argument [device]\n");
                exit(1);
            }
        }
        // list devices
        if(strcmp(argv[i], "-D") == 0)
            listDevices();
    }
    if(dev)
        printf("Device: %s\n", dev);
    return 0;
}

void usage(char const *argv[])
{
    printf("Usage:\n");
    printf("\t%s [-i <device>] [-B]\n", argv[0]);
    printf("Options:\n");
    printf("\t-i <interface>  specify interface to listen on\n");
    printf("\t-B              list available interfaces\n");
}

void listDevices()
{
    pcap_if_t *devices, *device;
    char errbuf[PCAP_ERRBUF_SIZE];
    int ret;

    if(pcap_findalldevs(&devices, errbuf) != 0)
    {
        printf("[ERROR] %s\n", errbuf);
    }

    int i = 1;
    for(device = devices; devices != NULL; device = device->next)
    {
        struct sockaddr_in *addr = (struct sockaddr_in *)(device->addresses->addr);
        printf("%2d. %s [%s]\n", i, device->name, inet_ntoa(addr->sin_addr));
        i++;
    }
}
