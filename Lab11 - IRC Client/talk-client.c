
#include <time.h>
#include <curses.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

#include "IRCClient.h"

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LEN 300
#define MAX_RESPONSE (20 * 1024)

vector <std::string> userinRoom;
vector <std::string> roomList;
vector <std::string> getmessages;

char * host;
char * user;
char * password;
char * sport;
int port;
char response[MAX_RESPONSE];
char * roomName;
char * recentMessage;

//string userNameArray[50];

int lastMessage = 0;

int open_client_socket(char * host, int port) {
	// Initialize socket address structure
	struct  sockaddr_in socketAddress;
	
	// Clear sockaddr structure
	memset((char *)&socketAddress,0,sizeof(socketAddress));
	
	// Set family to Internet 
	socketAddress.sin_family = AF_INET;
	
	// Set port
	socketAddress.sin_port = htons((u_short)port);
	
	// Get host table entry for this host
	struct  hostent  *ptrh = gethostbyname(host);
	if ( ptrh == NULL ) {
		perror("gethostbyname");
		exit(1);
	}
	
	// Copy the host ip address to socket address structure
	memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);
	
	// Get TCP transport protocol entry
	struct  protoent *ptrp = getprotobyname("tcp");
	if ( ptrp == NULL ) {
		perror("getprotobyname");
		exit(1);
	}
	
	// Create a tcp socket
	int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	
	// Connect the socket to the specified server
	if (connect(sock, (struct sockaddr *)&socketAddress,
		    sizeof(socketAddress)) < 0) {
		perror("connect");
		exit(1);
	}
	
	return sock;
}

int sendCommand(char * host, int port, char * command, char * user,
		char * password, char * args, char * response) {
	int sock = open_client_socket( host, port);

	// Send command
	write(sock, command, strlen(command));
	write(sock, " ", 1);
	write(sock, user, strlen(user));
	write(sock, " ", 1);
	write(sock, password, strlen(password));
	write(sock, " ", 1);
	write(sock, args, strlen(args));
	write(sock, "\r\n",2);

	// Keep reading until connection is closed or MAX_REPONSE
	int n = 0;
	int len = 0;
	while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
		len += n;
	}

	printf("response:%s\n", response);

	close(sock);
}

void printUsage()
{
	printf("Usage: talk-client host port user password\n");
	exit(1);
}

void add_user() {
	// Try first to add user in case it does not exist.
    //char response[ MAX_RESPONSE ];
    
    sendCommand(host, port, (char*)"ADD-USER", user, password, (char *)"", response);
	if (!strcmp(response,"OK\r\n")) {
		printf("User %s added\n", user);
        userinRoom.push_back(user);
    }else{
        printf("User %s already logged in\n", user);
    }
}
void create_room(){
    sendCommand(host, port, (char*)"CREATE-ROOM", user, password, roomName, response);
    if (!strcmp(response,"OK\r\n")) {
        printf(" %s created a room called %s\n", user, roomName);
        roomList.push_back(roomName);
    }else{
        printf(" %s room's not created\n", user);
    }
}
void check_password(){
    sendCommand(host, port, (char*)"LOGIN", user, password, (char *)"", response);
    if (strcmp(response, "OK\r\n") == 0) {
        printf("%s @@\n", response);
    }
}

void enter_room() {

    sendCommand(host, port, (char*)"ENTER-ROOM", user, password, roomName, response);
    if (!strcmp(response,"OK\r\n")) {
        printf(" %s entered a room called %s\n", user, roomName);
        roomList.push_back(roomName);
    }else{
        printf(" %s room's not enter\n", user);
        printf(" %s \n", response);
    }
}

void leave_room() {
    sendCommand(host, port, (char*)"LEAVE-ROOM", user, password, roomName, response);
    if (!strcmp(response,"OK\r\n")) {
        printf(" %s left a room called %s\n", user, roomName);
    }else{
        printf(" %s room's not leave\n", user);
        printf(" %s \n", response);
    }
}

void get_messages(int num) {
    //   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
    //   Answer: MSGNUM1 USER1 MESSAGE1\r\n
    //           MSGNUM2 USER2 MESSAGE2\r\n
    //           MSGNUM3 USER2 MESSAGE2\r\n
    //           ...\r\n
    //           \r\n
    //
    char * tempArgs = (char *)malloc(sizeof(char) * 500);
    strcpy(tempArgs, "-1");
    strcat(tempArgs, " ");
    strcat(tempArgs, roomName);
    sendCommand(host, port, (char*)"GET-MESSAGES", user, password, tempArgs, response);
    
}

void send_message(char * msg) {
    //   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
    char * tempArgs = (char *)malloc(sizeof(char) * 500);
    strcpy(tempArgs, msg);
    strcat(tempArgs, " ");
    strcat(tempArgs, roomName);
    sendCommand(host, port, (char*)"SEND-MESSAGE", user, password, tempArgs, response);
    if (!strcmp(response,"OK\r\n")) {
        printf(" %s sent a meessage called %s in %s\n", user, msg, roomName);
        getmessages.push_back(msg);
    }else{
        printf(" %s room's not created\n", user);
        printf(" %s \n", response);
    }
}

void print_users_in_room() {
    //REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
    int i=0;
    char * temp;
    sendCommand(host, port, (char*)"GET-USERS-IN-ROOM", user, password, roomName, response);
}

void print_room() {
    //   Request: LIST-ROOMS <USER> <PASSWD>\r\n
    //   Answer: room1\r\n
    //           room2\r\n
    //           ...
    //           \r\n
    int i=0;
    char * temp;
    sendCommand(host, port, (char*)"LIST-ROOMS", user, password, roomName, response);
    printf(" %s @@\n", response);
}

void printPrompt() {
	printf("talk> ");
	fflush(stdout);
}

void printHelp() {
	printf("Commands:\n");
	printf(" -who   - Gets users in room\n");
	printf(" -users - Prints all registered users\n");
	printf(" -help  - Prints this help\n");
	printf(" -quit  - Leaves the room\n");
	printf("Anything that does not start with \"-\" will be a message to the chat room\n");
}

void * getMessagesThread(void * arg) {
	// This code will be executed simultaneously with main()
	// Get messages to get last message number. Discard the initial Messages
	
	while (1) {
		// Get messages after last message number received.

		// Print messages

		// Sleep for ten seconds
		usleep(2*1000*1000);
	}
}

void startGetMessageThread()
{
	pthread_create(NULL, NULL, getMessagesThread, NULL);
}
