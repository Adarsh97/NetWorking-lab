#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>


int main(int argc,char *argv[])
{
char buffer[1024];
int oldsocket;
oldsocket=socket(PF_INET,SOCK_STREAM,0);
struct sockaddr_in server;
server.sin_family=AF_INET;
server.sin_port=htons(atoi(argv[2]));
server.sin_addr.s_addr=inet_addr(argv[1]);
memset(server.sin_zero,'\0',sizeof(server.sin_zero));
socklen_t h;
h=sizeof(server);
connect(oldsocket,(struct sockaddr*)&server,h);

int n,i;
printf("Enter the number of elements:");
scanf("%d",&n);
send(oldsocket,&n,sizeof(int),0);
int a[n];
for(i=0;i<n;i++)
scanf("%d",&a[i]);
send(oldsocket,&a,sizeof(int)*n,0);
recv(oldsocket,&a,sizeof(int)*n,0);
printf("Sorted array is :\n");
for(i=0;i<n;i++)
printf("%d ",a[i]);
printf("\n");
return 0;
}
