#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[])
{
	int sockid;
	sockid= socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family= AF_INET;
	servaddr.sin_port= htons(5500);
	servaddr.sin_addr.s_addr= INADDR_ANY;
	
	int reuse=1;
	setsockopt(sockid, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	
	bind(sockid, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	struct ip_mreq group;
	group.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
  	group.imr_interface.s_addr = inet_addr("9.5.1.1");
  	setsockopt(sockid, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));
  	
  	char data[10];
  	read(sockid, data, strlen(data));
  	
  	return 0;
  }
