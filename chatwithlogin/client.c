/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>


int main(int argc,char *argv[]){
  int clientSocket;
  int i,r;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(atoi(argv[2]));
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero));

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof (serverAddr);
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
char buffer[1024];
char d[1024]="quit";
char buff[1024];
char opt[1024];
memset(buff,'\0',1024);
printf("Enter the username :");
fgets(buff,1024,stdin);
r=strlen(buff);
if(buff[r-1]=='\n')
buff[r-1]='\0';

send(clientSocket,buff,1024,0);
memset(buff,'\0',1024);
printf("Enter the password :");
fgets(buff,1024,stdin);
 r=strlen(buff);
if(buff[r-1]=='\n')
buff[r-1]='\0';

send(clientSocket,buff,1024,0);
memset(buff,'\0',1024);


int check=0;
int chec=0;
recv(clientSocket,&check,sizeof(check),0);

if(check==0)
{
printf("You are not registered with us please send the username and password\n");
chec=1;
while(chec==1)
{
memset(buff,'\0',1024);
printf("Enter the username :");
fgets(buff,1024,stdin);
r=strlen(buff);
if(buff[r-1]=='\n')
buff[r-1]='\0';
send(clientSocket,buff,1024,0);

memset(buff,'\0',1024);
printf("Enter the password :");
fgets(buff,1024,stdin);
 r=strlen(buff);
if(buff[r-1]=='\n')
buff[r-1]='\0';
send(clientSocket,buff,1024,0);

recv(clientSocket,&chec,sizeof(chec),0);
if(chec==1)
{
printf("This username is already taken.Please try with another username again.\n");
}
}
}

while(1)
{
  memset(buff,'\0',1024);
  printf("Currently logined users are :\n");
  int cou=0;
  while(recv(clientSocket,buff,1024,0)>0)
  {cou++;
    if(strcmp(buff,"stop")==0)
    break;
    if(strcmp(buff,"")!=0)
    printf("%d %s\n",cou,buff);
      memset(buff,'\0',1024);
  }
  printf("Enter yes for continue no for exit:");
  fgets(opt,1024,stdin);
  if(opt[strlen(opt)-1]=='\n')
  opt[strlen(opt)-1]='\0';
  int h=0;
 if(strcmp(opt,"no")==0)
 {
h=1;
   printf("Thank you.\n");
}
send(clientSocket,&h,sizeof(h),0);
if(h==1)
break;
printf("Recieved messages by you.\n");
cou=1;
while(recv(clientSocket,buff,1024,0)>0)
{
  if(strcmp(buff,"stop")==0)
  break;
  if(cou%2==1)
  {if(strcmp(buff,"")!=0)
  printf("%d %s\n",cou,buff);
}
else
{
if(strcmp(buff,"")!=0)
printf("%s\n",buff);
}
cou++;
    memset(buff,'\0',1024);
}
memset(buff,'\0',1024);
printf("Enter the receivers address type end for stopping receives :\n");
while(1)
{
fgets(buff,1024,stdin);
 r=strlen(buff);
if(buff[r-1]=='\n')
buff[r-1]='\0';
send(clientSocket,buff,1024,0);
if(strcmp(buff,"end")==0)
break;
memset(buff,'\0',1024);
}
printf("Enter the text :");
memset(buffer,'\0',1024);
fgets(buffer,1024,stdin);
int l;
l=strlen(buffer);
if(buffer[l-1]=='\n')
buffer[l-1]='\0';
send(clientSocket,buffer,1024,0);
check=0;
recv(clientSocket,&check,sizeof(check),0);
// printf("%s",buffer);
if(check==0)
printf("Reciever is not registered ..\n");
else
printf("Message has been send ...\n");
}
  return 0;
}
