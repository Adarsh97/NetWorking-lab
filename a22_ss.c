/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>

int counter=0;
int a[100];
char b[15][1024];
int counter1=0;
int counter2=0;

void* func(void* arg);

int main(int argc,char *argv[]){
  int welcomeSocket, newSocket;
  char mssg[50];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
int p;
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(atoi(argv[2]));
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof (serverAddr.sin_zero));

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
int yes=1;
 setsockopt(welcomeSocket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");
pthread_t tid;
int pid;
  /*---- Accept call creates a new socket for the incoming connection ----*/
while(1)
{

  addr_size = sizeof (serverStorage);
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
  if(newSocket <0)
  {
    printf("error in accepting ....\n");
    return 0;
  }
if(pid=pthread_create(&tid,NULL,func,(void*)&newSocket)<0)
{
  printf("error in thread ...\n");
  return 0;
}

}
return 0;
}



void* func(void* arg)
{
  int indi;
  int count1,count,j;
int i,k=0,w,l;
int flag=0;
int new ;
int *y=(int*)arg;
int newSocket=*y;

FILE *fp;

char username[1024];
char password[1024];
char e[1024];
char f[1024];
char buffer[1024];
char buffer1[1024];
char buffer2[1024];
char buffer3[1024];
char buffer4[1024];
char newl[1024]="\n";
char mssg[1024];
memset(buffer,'\0',1024);
memset(buffer1,'\0',1024);
 int x=recv(newSocket,buffer,1024,0);
 x=recv(newSocket,buffer1,1024,0);
if(x<=0)
{
printf("error in reading ...\n");
return 0;
}

fp=fopen("register.txt","a+");
fclose(fp);
fp=fopen("login.txt","a+");
fclose(fp);
fp=fopen("message.txt","a+");
fclose(fp);
fp=fopen("register.txt","r");
k=0;
while(!feof(fp))
{
fgets(username,1024,fp);
fgets(password,1024,fp);
l=strlen(username);
if(username[l-1]=='\n')
username[l-1]='\0';
l=strlen(password);
if(password[l-1]=='\n')
password[l-1]='\0';
if((strcmp(username,buffer)==0)&&(strcmp(password,buffer1)==0))
{
k=1;
}
}
fclose(fp);
if(k==1)
{
  fp=fopen("login.txt","a");
  fputs(buffer,fp);
  fputs(newl,fp);
  fclose(fp);
}
send(newSocket,&k,sizeof(k),0);
if(k==0)
{
while(1)
{
fp=fopen("register.txt","r");
flag=0;
recv(newSocket,e,1024,0);
recv(newSocket,f,1024,0);
strcpy(buffer,e);
while(!feof(fp))
{
  fgets(username,1024,fp);
  fgets(password,1024,fp);
  l=strlen(username);
  if(username[l-1]=='\n')
  username[l-1]='\0';
  l=strlen(password);
  if(password[l-1]=='\n')
  password[l-1]='\0';
if(strcmp(e,username)==0)
{
  flag=1;
}
}
fclose(fp);
send(newSocket,&flag,sizeof(flag),0);
if(flag==0)
{
  fp=fopen("register.txt","a");
fputs(e,fp);
fputs(newl,fp);
fputs(f,fp);
fputs(newl,fp);
fclose(fp);
fp=fopen("login.txt","a");
fputs(e,fp);
fputs(newl,fp);
fclose(fp);
break;
}
}
}
while(1)
{
fp=fopen("login.txt","r");
count1=0;
while(!feof(fp))
{
  count1++;
  indi=0;
  fgets(username,1024,fp);
  l=strlen(username);
  for(j=0;j<counter;j++)
  {
    if(a[j]==count1)
    {
      indi=1;
      break;
    }
  }
  if(username[l-1]=='\n')
  username[l-1]='\0';
  if(indi!=1)
  send(newSocket,username,1024,0);
  memset(username,'\0',1024);
}
fclose(fp);
char endmssg[1024]="stop";
send(newSocket,endmssg,1024,0);
fp=fopen("message.txt","r");
while(!feof(fp))
{
  fgets(username,1024,fp);
  l=strlen(username);
  if(username[l-1]=='\n')
  username[l-1]='\0';
  fgets(buffer1,1024,fp);
  l=strlen(buffer1);
  if(buffer1[l-1]=='\n')
  buffer1[l-1]='\0';
  fgets(buffer2,1024,fp);
  l=strlen(buffer2);
  if(buffer2[l-1]=='\n')
  buffer2[l-1]='\0';
  if(strcmp(buffer,buffer1)==0)
  {
    send(newSocket,username,1024,0);
    send(newSocket,buffer2,1024,0);
  }

}
send(newSocket,endmssg,1024,0);
fclose(fp);

int checker=0;
int ender =0;
recv(newSocket,&ender,sizeof(ender),0);
if(ender==1)
{
  count=0;
  fp=fopen("login.txt","r");
  while(!feof(fp))
  {
    count++;
    fgets(username,1024,fp);
    l=strlen(username);
    if(username[l-1]=='\n')
    username[l-1]='\0';
    if(strcmp(username,buffer)==0)
    {
      a[counter++]=count;
    //  break;
    }

  }
  fclose(fp);
break;
}
counter1=0;
while(1)
{
x=recv(newSocket,buffer3,1024,0);
if(x==0)
break;
if(strcmp(buffer3,"end")==0)
break;
strcpy(b[counter1],buffer3);
counter1++;
}
x=recv(newSocket,buffer4,1024,0);
counter2=0;
while(counter2<counter1)
{
fp=fopen("login.txt","r");
 checker=0;
while(!feof(fp))
{
  fgets(buffer1,1024,fp);
  l=strlen(buffer1);
  if(buffer1[l-1]=='\n')
  buffer1[l-1]='\0';
  if(strcmp(b[counter2],buffer1)==0)
  {
    checker=1;
  }
}
// send(newSocket,&checker,sizeof(checker),0);
fclose(fp);
fp=fopen("message.txt","a");
if(checker==1)
{
  fputs(buffer,fp);
  fputs(newl,fp);
  fputs(b[counter2],fp);
  fputs(newl,fp);
  fputs(buffer4,fp);
  fputs(newl,fp);
}
fclose(fp);
counter2++;
}
send(newSocket,&checker,sizeof(checker),0);
}
}
