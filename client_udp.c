#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 60000
#define MAX_BUF_SIZE 1024

int main(int argc,char **argv)
{
  
  int sockfd,addrlen,n;
  char buffer[MAX_BUF_SIZE];
  struct sockaddr_in addr;
  FILE *fp;
  addrlen=sizeof(struct sockaddr_in);
  bzero(&addr,addrlen);
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr("192.168.1.120");
  addr.sin_port=htons(PORT);
  sockfd=socket(AF_INET,SOCK_DGRAM,0);/*建立客户端socket*/
  if(sockfd<0)
    {
      fprintf(stderr,"socket error\n");
      exit(1);
    }


  while(1)
    {
      bzero(buffer,MAX_BUF_SIZE);
      fgets(buffer,MAX_BUF_SIZE,stdin);
      sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)(&addr),addrlen);
      printf("Client endpoint intput :%s\n",buffer);
      /*接收到的数据，打印*/
      n=recvfrom(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)(&addr),&addrlen);
      fprintf(stdout,"receive message:%s",buffer);
    }
  close(sockfd);
  exit(0);
}
