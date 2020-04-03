#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 2345

int main(void)
{
  int sockfd,newsockfd;
  struct sockaddr_in addr;
  int addr_len = sizeof(struct sockaddr_in);
  char msgbuf[1024];/*发送和接收缓冲区*/
  if((sockfd = socket(PF_INET,SOCK_STREAM,0))<0)
    {
      perror("socket created error!");
      exit(1);      
    }
  else
    {
      printf("socket created successed\n");
      printf("socket id:%d\n",sockfd);
    }
  bzero(&addr,sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port =htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);/*IP本机*/
  if(bind(sockfd,(struct sockaddr *)(&addr),sizeof(struct sockaddr))<0)
    {
      perror("bind error\n");
      exit(1);
    }
  else
    {
      printf("bind success!\n");
      printf("local port:%d\n",addr.sin_port);
    }

  if(listen(sockfd,5)<0)/*调用listen函数监听端口号，能同时处理最大连接数5*/
    {
      perror("listen error");
      exit(1);
    }
  else
    {
      
      printf("local ip:%d/n",addr.sin_addr.s_addr);
      
      printf("local port:%d/n",addr.sin_port);
      printf("listenning>>>\n");

      
     }
  if((newsockfd = accept(sockfd,(struct sockaddr *)(&addr),&addr_len))<0)/*调用接受连接请求*/
    {
      perror("accept error\n");
    }
    else
      {
	printf("connect %s/n",inet_ntoa(addr.sin_addr));
	if(read(newsockfd,msgbuf,sizeof(msgbuf))<=0)
	  {
	    perror("read error");
	  }
	else
	  printf("message:\n%s \n",msgbuf);
      }

     
  return 0;
  
}
