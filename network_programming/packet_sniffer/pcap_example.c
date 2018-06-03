#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <string.h>
#include <string.h>
#include <net/if.h>

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
                strcpy(dev, argv[i]);
            else
            {
                printf("ERROR: '-i' option requires an argument [device]\n");
                exit(1);
            }
        }
    }
    if(dev)
        printf("Device: %s\n", dev);
    return 0;
}
