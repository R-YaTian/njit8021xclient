/* File: ip.c
 * ----------
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef WIN32
#include <winsock2.h>
#include "pcaphelper.h"
#else
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

void GetIpFromDevice(uint8_t ip[4], const char DeviceName[])
{
#if defined(WIN32)
	//struct hostent* hn = NULL;
	//char HostName[255];

	//gethostname(HostName, sizeof(HostName));	// 获得本机主机名.   

	//hn = gethostbyname(HostName);	//根据本机主机名得到本机ip   
	//memcpy(ip, ((struct in_addr *)hn->h_addr_list[0]), 4);

	/* get the devices list */

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *devList;
	pcap_if_t *dev;
	if (pcap_findalldevs(&devList, errbuf) == -1)
	{
		fprintf(stderr, "There is a problem with pcap_findalldevs: %s\n", errbuf);
		return -1;
	}

	/* scan the list for a suitable device to capture from */
	for (dev = devList; dev != NULL; dev = dev->next)
	{
		if (strcmp(dev->name, DeviceName) == 0)
		{
			pcap_addr_t *a;
			for (a = dev->addresses; a; a = a->next)
			{
				// scan for IPv4 address by libpcap/winpcap.
				if (a->addr->sa_family == AF_INET)
				{
					ip[0] = ((struct sockaddr_in *)a->addr)->sin_addr.S_un.S_un_b.s_b1;
					ip[1] = ((struct sockaddr_in *)a->addr)->sin_addr.S_un.S_un_b.s_b2;
					ip[2] = ((struct sockaddr_in *)a->addr)->sin_addr.S_un.S_un_b.s_b3;
					ip[3] = ((struct sockaddr_in *)a->addr)->sin_addr.S_un.S_un_b.s_b4;
					return;
				}
			}
		}
	}
	pcap_freealldevs(devList);
#else
	int fd;
	struct ifreq ifr;

	assert(strlen(DeviceName) <= IFNAMSIZ);

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	assert(fd>0);

	strncpy(ifr.ifr_name, DeviceName, IFNAMSIZ);
	ifr.ifr_addr.sa_family = AF_INET;
	if (ioctl(fd, SIOCGIFADDR, &ifr) == 0)
	{
		struct sockaddr_in *p = (void*) &(ifr.ifr_addr);
		memcpy(ip, &(p->sin_addr), 4);
	}
	else
	{
		// 查询不到IP时默认填零处理
		memset(ip, 0x00, 4);
	}

	close(fd);
#endif
}

