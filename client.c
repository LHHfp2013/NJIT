#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#define PORT 5000
#define LENGTH 256
int main(int argc,char **argv[])
{
	int sockfd;
	int num;
	char revbuf[LENGTH];
	struct sockaddr_in remote_addr;
	if(argc!=2)
	{  printf("Usage:client HOST IP(ex:./client 192.168.0.94).\n");
	   return(0);
	}
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	{  printf("ERROR:Failed to obtain Socket Descriptor!\n");
	   return(0);
	}
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(PORT);
	inet_pton(AF_INET,argv[1],&remote_addr.sin_addr);
	bzero(&(remote_addr.sin_zero),8);
	if(connect(sockfd,(struct sockaddr*)&remote_addr,sizeof(struct sockaddr))==-1)
	{
		printf("ERROR:Failed to connect to thehost!\n");
		return(0);
	}
	else{
	  printf("OK:Have connected to the %s\n",argv[1]);}
	while(strcmp(revbuf,"exit")!=0)
	{
		bzero(revbuf,LENGTH);
		num = recv(sockfd,revbuf,LENGTH,0);
		switch(num)
		{    case -1:
				printf("ERROR:Receive string error!\n");
				close(sockfd);return(0);
			case 0:
				close(sockfd);return(0);
			default:
				printf("OK:Receive numbytes = %d\n",num);break;
		}
		revbuf[num] = '\0';
		printf("OK:Received string is:%s\n",revbuf);
	}
		close(sockfd);
		return(0);}
