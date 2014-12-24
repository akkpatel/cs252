
const char * usage =
"                                                               \n"
"daytime-server:                                                \n"
"                                                               \n"
"Simple server program that shows how to use socket calls       \n"
"in the server side.                                            \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   daytime-server <port>                                       \n"
"                                                               \n"
"Where 1024 < port < 65536.             \n"
"                                                               \n"
"In another window type:                                       \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where daytime-server  \n"
"is running. <port> is the port number you used when you run   \n"
"daytime-server.                                               \n"
"                                                               \n"
"Then type your name and return. You will get a greeting and   \n"
"the time of the day.                                          \n"
"                                                               \n";
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
int QueueLength = 25;

// Processes time request
void processTimeRequest( int socket );
void maps(char* path, char* newPath, int socket);
bool endsWith(char* path, char * ending);
char* writeHeader(int fd, char* path);
int mystrLen(char* s);
void dispatchHTTP(int fd);
void* loopthread(int masterSocket);
void createThreadForEachRequest(int masterSocket);
void poolOfThreads(int masterSocket);
void poolOfProcesses(int masterSocket);
void newPool(int masterSocket);
void poolSlave(int masterSocket);
void forkServer(int masterSocket);

extern "C" void killzombie(int temp){
	while((waitpid(-1, NULL, WNOHANG)) > 0);
}

int
main( int argc, char ** argv )
{
  int port;
  int fFlag = 0;
  int tFlag = 0;
  int pFlag = 0;
  // Print usage if not enough arguments
 // printf("in the main\n");
  if ( argc < 2 ) {
   port = 3131;
  }

  // Get the port from the arguments
  if(argc == 2){
	port = atoi( argv[1] );
	if(port == 0){
		char * temp = argv[1];
		if(strcmp(temp,"-f") == 0){
		fFlag = 1;
		}
		if(strcmp(temp, "-t")==0){
			tFlag = 1;
		}
		if(strcmp(temp, "-p")==0){
			pFlag = 1;
		}
		port = 3131;	
	}
	//printf("port %d  fFlag %d    tFlag %d    pFlag %d\n",port, fFlag, tFlag, pFlag);
	//printf("port %d\n", port);
  }
  if(argc > 2){
	char* temp = argv[1];
	port = atoi(argv[2]);
	if(strcmp(temp,"-f") == 0){
		fFlag = 1;
	}
	if(strcmp(temp, "-t")==0){
		tFlag = 1;
	}
	if(strcmp(temp, "-p")==0){
		pFlag = 1;
	}
	printf("temp %s   port %d  fFlag %d    tFlag %d    pFlag %d\n", temp, port, fFlag, tFlag, pFlag);
  }
  if(port <= 1024 || port >= 65536){
	printf("port is either <= 1024 or >= 65536\n");
	printf("Run the code again, with a port between 1024 and 65536\n");
	exit(0);
  }
  
  // Set the IP address and port for this server
  struct sockaddr_in serverIPAddress; 
  memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
  serverIPAddress.sin_family = AF_INET;
  serverIPAddress.sin_addr.s_addr = INADDR_ANY;
  serverIPAddress.sin_port = htons((u_short) port);
  
  // Allocate a socket
  int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
  if ( masterSocket < 0) {
    perror("socket");
    exit( -1 );
  }

  // Set socket options to reuse port. Otherwise we will
  // have to wait about 2 minutes before reusing the sae port number
  int optval = 1; 
  int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
		       (char *) &optval, sizeof( int ) );
   
  // Bind the socket to the IP address and port
  int error = bind( masterSocket,
		    (struct sockaddr *)&serverIPAddress,
		    sizeof(serverIPAddress) );
  if ( error ) {
    perror("bind");
    exit( -1 );
  }
  
  // Put socket in listening mode and set the 
  // size of the queue of unprocessed connections
  error = listen( masterSocket, QueueLength);
  if ( error ) {
    perror("listen");
    exit( -1 );
  }
  if(pFlag){
	printf("in pFlag\n");
	newPool(masterSocket);
  }
  	struct sigaction signalAction;
	signalAction.sa_handler = killzombie;
	sigemptyset(&signalAction.sa_mask);
	signalAction.sa_flags = SA_RESTART;
	int newError = sigaction(SIGCHLD, &signalAction, NULL );
	if ( newError ) 
	{
		perror( "sigaction" );
		exit( -1 );
	}
  if(fFlag){
	printf("inside fFlag\n");
	forkServer(masterSocket);
	printf("outside fFlag\n");
  }
  if(tFlag){
	printf("inside tFlag\n");
	createThreadForEachRequest(masterSocket);
	printf("called the function\n");
  }else{
	printf("in else\n");
	  while ( 1 ) {

	    // Accept incoming connections
	    struct sockaddr_in clientIPAddress;
	    int alen = sizeof( clientIPAddress );
	    int slaveSocket = accept( masterSocket,
				      (struct sockaddr *)&clientIPAddress,
				      (socklen_t*)&alen);


		    if ( slaveSocket < 0 ) {
		      perror( "accept" );
		      exit( -1 );
		    }

		    // Process request.
		    processTimeRequest( slaveSocket );

		    // Close socket
		    close( slaveSocket );
	  }
   }
  
}

void
processTimeRequest( int fd )
{
  // Buffer used to store the name received from the client
  const int MaxName = 1024;
  char name[ MaxName + 1 ];
  int nameLength = 0;
  int n;
  int length = 0;
  int gotGet = 0;
  int gotDoc = 0;
  char* docPath = 0;
  char* curr_string = (char*)malloc(sizeof(char));

  // Currently character read
  unsigned char newChar;

  // Last character read
  unsigned char oldChar;

  //
  // The client should send <name><cr><lf>
  // Read the name of the client character by character until a
  // <CR><LF> is found.
  //
   printf("I am in proccesTimeReques\n");
  while (n = read( fd, &newChar, sizeof(newChar))) {
//	printf("In n %d\n", n);

//	printf("newchar=%c\n",newChar);

	if (gotGet) {
		length++;
		curr_string[length-1] = newChar;
		printf("curr_string is now %s\n", curr_string);
	}

	if(newChar == ' '){
		if(!gotGet){
			gotGet = 1;
		}
		else if (!gotDoc){
			docPath = (char*)malloc(length*sizeof(char));
			curr_string[length] = 0;
			strcpy(docPath, curr_string);
			docPath[length] = 0;
			gotDoc = 1;
		}
	}
	else if(newChar == '\n' && oldChar == '\r'){
		printf("crlf found\n");
		break;
	}

	oldChar = newChar;

  }
  char* newPath = (char*)malloc(sizeof(char*));
  for(int xx = 0; xx<strlen(docPath)-1; xx++){
	newPath[xx] = docPath[xx];
  }

  printf("docpath=%s\n", docPath);
  int i = strlen(docPath);
  maps(docPath, newPath, fd);
}


void 
maps(char* path, char* newPath, int socket){
  /* Creating a path*/
  printf("path in maps %s\n", path);
  char* cwd = (char*)malloc(sizeof(char)*256);
  cwd = getcwd(cwd, 256);
  char* temp = "/http-root-dir/htdocs";
  char* toFile = (char*)malloc((strlen(cwd)+strlen(path)+strlen(temp)+15)*sizeof(char));
  int pathlen = strlen(path);
  printf("i %d\n",pathlen);
  if(pathlen == 2){
	  if(strcmp(path, "/")){
		printf("path == /\n");
		strcat(toFile, cwd);
		strcat(toFile, temp);
		strcat(toFile, "/index.html");
  	  }
  }else{
	printf("in else\n");
	strcat(toFile, cwd);
	strcat(toFile, temp);
	strcat(toFile, newPath);

  }
  printf("toFile %swer\n", toFile);

/* Created a Path to the file*/
/*now will use that path to write the file back to header*/

 printf("path in write %s\n", toFile);
 char* server = "CS252/lab5"; 
 char* contentType = (char*) malloc(20*sizeof(char));
 if(endsWith(toFile, ".html") || endsWith(toFile, ".html/")){
	printf("inside .html\n");
	strcpy(contentType, "text/html"); 
 }else if(endsWith(toFile, ".gif") || endsWith(toFile, ".gif/")){
	printf("inside .gif\n");
	strcpy(contentType, "image/gif");
 }else{
	printf("inside else in writeHeader\n");
	strcpy(contentType, "text/plain");
 }
 printf("path before open %sasdasd\n", toFile);
 int file = open(toFile, O_RDONLY);
 printf("file %d\n", file);
 const char *protocol = "HTTP/1.1";
  const char *space = " ";
const char *clrf = "\r\n";
 if( file > 0 ){
    write(socket, protocol, strlen(protocol));
    write(socket, space, 1);
    write(socket, "200", 3);
    write(socket, space, 1);
    write(socket, "Document", 8);
    write(socket, space, 1);
    write(socket, "Follows", 7);
    write(socket, clrf, 2);
    write(socket, "Server:", 7);
    write(socket, space, 1);
    write(socket, server, strlen(server));
    write(socket, clrf, 2);
    write(socket, "Content-type:", 13);
    write(socket, space, 1);
    write(socket, contentType, strlen(contentType));
    write(socket, clrf, 2);
    write(socket, clrf, 2);
    //return;
    char c;
    int count;

	 char w_buf[1000];
	int length = 0;
    while(count = read(file, &c, 1))
    {
	w_buf[length] = c;
	length++;
	
	if (length==1000){
	     if(write(socket, w_buf, 1000) != 1000){
		perror("write");
	     }
	     length = 0;
	}
    }
    if(write(socket, w_buf, length) != length){
	perror("write");
    }
    write(socket, "\0", 1);
    close(file);
 }else{
	printf("in else\n");
    const char *notFound = "404 File not Found";
    write(socket, protocol, strlen(protocol));
    write(socket, space, 1);
    write(socket, "404", 3);
    write(socket, "File", 4);
    write(socket, "Not", 3);
    write(socket, "Found", 5);
    write(socket, clrf, 2);
    write(socket, "Server:", 7);
    write(socket, space, 1);
    write(socket, server, strlen(server));
    write(socket, clrf, 2);
    write(socket, "Content-type:", 13);
    write(socket, space, 1);
    write(socket, contentType, strlen(contentType));
    write(socket, clrf, 2);
    write(socket, clrf, 2);
    write(socket, notFound, strlen(notFound));

 }
}


int mystrLen(char* s) {
  /* FILL IN HERE */
   int len;
    for (len = 0; *s != '\0'; s++,len++){
	}
    return len;
}

/*Checks if the end contains something like .html, .gif etc.*/

bool endsWith(char* path, char * ending){
//	printf("in endswith\n");
	int pathLen = strlen(path);
//	printf("len %d\n", strlen(path));
//	printf("ending %s\n", ending);
	int j = 0;
	for(int i = 0; i < strlen(path); i++){
		if(path[i] == '.'){
//			printf("i %d\n", i);
			j = i;
			break;	
		}
	}
//	printf("j %d    path[i] %c\n", j, path[66]);
	int k = 0;
	for(int z = j; z < (pathLen); z++){
//		printf("inside second for\n");
		if(path[z] != ending[k]){
//			printf("in else\n");
			return false;
		}else{
//			printf("path[i] %c    ending[k] %c\n", path[z], ending[k]);
		}
		k++;
	}
//	printf("ending\n");
	return true;
}


void dispatchHTTP(int fd){
	processTimeRequest(fd);
	close(fd);
}

void createThreadForEachRequest(int masterSocket){
    while(1){
	    // Accept incoming connections
	struct sockaddr_in clientIPAddress;
	int alen = sizeof( clientIPAddress );
	int slaveSocket = accept( masterSocket,
		         (struct sockaddr *)&clientIPAddress,
		         (socklen_t*)&alen);
	printf("inside tFlag\n");
	if ( slaveSocket < 0 ) {
	      perror( "accept" );
	      exit( -1 );
	}
	if(slaveSocket >= 0){
		printf("slaveSocket is >0 in tFlag\n");
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		pthread_create(&thread, &attr, (void * (*)(void*))dispatchHTTP, (void*)slaveSocket);
		printf("exiting slaveSocket is >0\n");
	}
	printf("Going outside tflag\n");
    }

}

void poolOfThreads(int masterSocket){
	pthread_t thread[4];
	for(int i = 0; i < 4; i++){
		pthread_create(&thread[i], NULL, (void * (*)(void*))loopthread, (void*)masterSocket);
	}
	loopthread(masterSocket);
	printf("going inside poolOfProcess\n");
	poolOfProcesses(masterSocket);
	printf("outside of process\n");
}
void poolOfProcesses(int masterSocket){
	for(int i =0; i <4; i++){
		int pid = fork();
		if(pid == 0){
			loopthread(masterSocket);
		}
	}
	loopthread(masterSocket);
}

void newPool(int masterSocket){
	pthread_t tid[5];
	for(int i = 0; i <5; i++){
		 pthread_attr_t attr;
     		 pthread_attr_init( &attr );
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    		 pthread_create(&tid[i], &attr,(void *(*)(void *))poolSlave,(void *)masterSocket);
	}
	pthread_join(tid[0], NULL);
}

void poolSlave(int masterSocket){
	pthread_mutex_t mutex;
	while(1){
		printf("looping thread\n");
		pthread_mutex_lock(&mutex);
		struct sockaddr_in clientIPAddress;
  		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);
		sleep(20);
		if ( slaveSocket < 0 ) {
		      perror( "accept" );
		      exit( -1 );
		}
		pthread_mutex_unlock(&mutex);
		if(slaveSocket >= 0){
			dispatchHTTP(slaveSocket);
		}
	}
}
void* loopthread(int masterSocket){
pthread_mutex_t mutex;
	while(1){
		printf("looping thread\n");
		pthread_mutex_lock(&mutex);
		struct sockaddr_in clientIPAddress;
  		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);
		if ( slaveSocket < 0 ) {
		      perror( "accept" );
		      exit( -1 );
		}
		pthread_mutex_unlock(&mutex);
		if(slaveSocket >= 0){
			dispatchHTTP(slaveSocket);
		}
	}
}

void forkServer(int masterSocket){
	while(1){
		struct sockaddr_in clientIPAddress;
  		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);
		//sleep(10);
		if ( slaveSocket < 0 ) {
		      perror( "accept" );
		      exit( -1 );
		}
		if(slaveSocket >= 0){
			int ret = fork();
			if(ret == 0){
				dispatchHTTP(slaveSocket);
				exit(0);
			}
			close(slaveSocket);
		}
	}

}

