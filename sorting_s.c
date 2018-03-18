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
int oldsocket,newsocket;
oldsocket=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server,client;
struct sockaddr_storage storage_server;
server.sin_family=AF_INET;
server.sin_port=htons(atoi(argv[2]));
server.sin_addr.s_addr=inet_addr(argv[1]);
bind(oldsocket,(struct sockaddr*)&server,sizeof(server));
if(listen(oldsocket,5)==0)
printf("listening\n");
else
printf("error in listening\n");
socklen_t h;
h=sizeof(client);
newsocket=accept(oldsocket,(struct sockaddr*)&client,&h);
int k,t,i,j;
recv(newsocket,&k,sizeof(int),0);
// printf("%d\n",k);
int a[k];
recv(newsocket,&a,sizeof(int)*k,0);
for(i=0;i<k;i++)
{
for(j=i+1;j<k;j++)
{
if(a[i]>a[j])
{
t=a[j];
a[j]=a[i];
a[i]=t;
}
}
}
for(i=0;i<k;i++)
printf("%d ",a[i]);
printf("\n");
send(newsocket,&a,sizeof(int)*k,0);
close(newsocket);

return 0;
}
