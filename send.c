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
	servaddr.sin_addr.s_addr= inet_addr("255.1.1.1");
	
	char loop=0;
	setsockopt(sockid, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loop, sizeof(loop));
	
	struct in_addr localInterface;
	localInterface.s_addr= inet_addr("9.5.1.1");
	setsockopt(sockid, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));
	
	char buff[]="hello";
	sendto(sockid, buff, strlen(buff), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	return 0;
}
	
