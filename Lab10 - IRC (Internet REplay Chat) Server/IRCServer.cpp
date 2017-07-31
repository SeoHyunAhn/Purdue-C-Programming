
const char * usage =
"                                                               \n"
"IRCServer:                                                   \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   IRCServer <port>                                          \n"
"                                                               \n"
"Where 1024 < port < 65536.                                     \n"
"                                                               \n"
"In another window type:                                        \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server      \n"
"is running. <port> is the port number you used when you run    \n"
"daytime-server.                                                \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

#include "IRCServer.h"

int QueueLength = 5;
int
IRCServer::open_server_socket(int port) {
    
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
    
    return masterSocket;
}

void
IRCServer::runServer(int port)
{
    int masterSocket = open_server_socket(port);
    
    initialize();
    
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
        processRequest( slaveSocket );
    }
}

int
main( int argc, char ** argv )
{
    // Print usage if not enough arguments
    if ( argc < 2 ) {
        fprintf( stderr, "%s", usage );
        exit( -1 );
    }
    
    // Get the port from the arguments
    int port = atoi( argv[1] );
    
    IRCServer ircServer;
    
    // It will never return
    ircServer.runServer(port);
    
}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//   REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//   Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   REQUEST: CREATE-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LIST-ROOMS <USER> <PASSWD>\r\n
//   Answer: room1\r\n
//           room2\r\n
//           ...
//           \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
//   Answer: MSGNUM1 USER1 MESSAGE1\r\n
//           MSGNUM2 USER2 MESSAGE2\r\n
//           MSGNUM3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//

void
IRCServer::processRequest( int fd )
{
    // Buffer used to store the comand received from the client
    const int MaxCommandLine = 1024;
    char commandLine[ MaxCommandLine + 1 ];
    int commandLineLength = 0;
    int n;
    
    // Currently character read
    unsigned char prevChar = 0;
    unsigned char newChar = 0;
    
    //
    // The client should send COMMAND-LINE\n
    // Read the name of the client character by character until a
    // \n is found.
    //
    
    // Read character by character until a \n is found or the command string is full.
    while ( commandLineLength < MaxCommandLine &&
           read( fd, &newChar, 1) > 0 ) {
        
        if (newChar == '\n' && prevChar == '\r') {
            break;
        }
        
        commandLine[ commandLineLength ] = newChar;
        commandLineLength++;
        
        prevChar = newChar;
    }
    
    // Add null character at the end of the string
    // Eliminate last \r
    commandLineLength--;
    commandLine[ commandLineLength ] = 0;
    
    printf("RECEIVED: %s\n", commandLine);
    
    printf("The commandLine has the following format:\n");
    printf("COMMAND <user> <password> <arguments>. See below.\n");
    printf("You need to separate the commandLine into those components\n");
    printf("For now, command, user, and password are hardwired.\n");
    int i=0;
    char word[5][30];
    int length=strlen(commandLine);
    int j=0, k=0;
    while (i<length) {
        if (j==3) {
            word[3][k]=commandLine[i];
            k++;
        }
        if (commandLine[i]== ' ' &&j!=3) {
            word[j][k] = '\0';
            j++;
            k = 0;
            printf("SPACE\n");
        }else if (j!=3){
            printf("%c\n", commandLine[i]);
            word[j][k] = commandLine[i];
            k++;
        }
        
        i++;
    }
    word[j][k]='\0';
    const char * command = word[0];
    const char * user = word[1];
    const char * password = word[2];
    const char * args = "";
    if (j>=3){
        args=word[3];
    }
    
    
    
    printf("command=%s\n", command);
    printf("user=%s\n", user);
    printf( "password=%s\n", password );
    printf("args=%s\n", args);
    
    if (!strcmp(command, "ADD-USER")) {
        addUser(fd, user, password, args);
    }else if(!strcmp(command, "CREATE-ROOM")){
        createRoom(fd, user, password, args);
    }else if (!strcmp(command, "ENTER-ROOM")) {
        enterRoom(fd, user, password, args);
    }
    else if (!strcmp(command, "LEAVE-ROOM")) {
        leaveRoom(fd, user, password, args);
    }
    else if (!strcmp(command, "SEND-MESSAGE")) {
        sendMessage(fd, user, password, args);
    }
    else if (!strcmp(command, "LIST-ROOMS")) {
        listRoom(fd, user, password, args);
    }
    else if (!strcmp(command, "GET-MESSAGES")) {
        getMessages(fd, user, password, args);
    }
    else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
        getUsersInRoom(fd, user, password, args);
    }
    else if (!strcmp(command, "GET-ALL-USERS")) {
        getAllUsers(fd, user, password, args);
    }
    else if (!strcmp(command, "CHECK_PASS")) {
        checkPassword(fd, user, password);
    }
    else if (!strcmp(command, "LOGIN")) {
        login(fd, user, password);
    }
    else {
        const char * msg =  "UNKNOWN COMMAND\r\n";
        write(fd, msg, strlen(msg));
    }
    close(fd);
}
#define MAXWORD 200
char word[MAXWORD];
int wordLength;
char * IRCServer::nextword(FILE * fd) {
    int c;
    int i = 0;
    wordLength = 0;
    // While it is not EOF read char
    while ((c= fgetc(fd)) != EOF) {
        if (c == ' '|| c == '\n' || c == '\t'|| c == '\r') {
            if (wordLength > 0)
                return word;
        }
        else {
            word[i] = c;
            i++;
            word[i]='\0';
            wordLength++;
        }
    }
    if (wordLength > 0)
        return word;
    else
        return NULL;
}

int userCount = 0;
int messCount;
int roomCount;
const char * argsRoomName = (char *) malloc (100 * sizeof(char));
const char * currentMessage = (char *) malloc (1000 * sizeof(char));

struct userCheck {
    char * username;
    char * password;
    int rooms[50];
};

char username[100];
char password[100];

struct Rooms {
    char * users[100];
    char * roomName;
    char * messages[100];
    int userRoomCount;
    int cMessCount;
    int inside;
};
    char * roomyame[100];
   
int yamecount=0;
typedef Rooms Rooms;
Rooms * RoomArray;

typedef userCheck userCheck;
userCheck * userArray;




void
IRCServer::initialize()
{
    userCount=0;
    userArray = (userCheck * )malloc(100 * sizeof(userCheck));
    FILE *fp= fopen("password.txt", "wr");
    char * c = (char * )malloc(100*sizeof(char));
    int i=0;
    while ((c = nextword(fp))!='\0') {
        std::string sfromC(c);
        if (sfromC!="\n") {
            if (i==0 ) {
                userArray[userCount].username = strdup(c);
                i=1;
                continue;
            }
            else if(i==1){
                userArray[userCount].password = strdup(c);
                i=0;
                userCount++;
                continue;
            }
        }
        
    }
    
    roomCount =0;
    RoomArray = (Rooms *)malloc(100 * sizeof(Rooms));
    for (int j=0; j<100; j++) {
        for (int k=0; k<100; k++) {
            RoomArray[j].messages[k] = (char *)malloc(1000 *sizeof(char));
        }
    }
    
    fclose(fp);
    
}

bool
IRCServer::checkPassword(int fd, const char * user, const char * password) {
    // Here check the password
    
    int i = 0;
    char * nameCheck=strdup(user);
    char * passCheck=strdup(password);
    for (; i<userCount; i++) {
        printf("%s\n @@%s\n", userArray[i].username, userArray[i].password);
        if (strcmp(userArray[i].username, nameCheck) == 0 &&strcmp(userArray[i].password, password) ==0) {
            printf("Password is correct!\n");
            return true;
        }
    }
    return false;
}

void
IRCServer::login(int fd, const char * user, const char * password)
{
    // Here add a new user. For now always return OK.
    if (checkPassword(fd, user, password)) {
        const char * msg = "OK\r\n";
        write(fd, msg, strlen(msg));
        return;
    }
    
}



void
IRCServer::addUser(int fd, const char * user, const char * password, const char * args)
{
    // Here add a new user. For now always return OK.
    int temp  = 0;
    FILE * fp = fopen("password.txt", "w+");
    char * nameCheck = strdup(user);
    char * passCheck = strdup(password);
    int i=0;
    for (; i<userCount; i++) {
        printf("%s\n %s\n", userArray[i].username, nameCheck);
        if (strcmp(userArray[i].username, nameCheck) == 0) {
            temp = 1;
            break;
        }
    }
    if (temp !=1) {
        userArray[userCount].username= nameCheck;
        userArray[userCount].password= passCheck;
        userCount++;
        printf("%s\n ADD USER VERSION %s\n", userArray[userCount].username, userArray[userCount].password);
        fprintf(fp, "%s\n%s\n\n", nameCheck, passCheck);
        fclose(fp);
        const char *msg = "OK\r\n";
        write(fd, msg, strlen(msg));
        return;
    }
    else {
        const char * msg = "DENIED\r\n";
        write(fd, msg, strlen(msg));
        return;
    }
    
}

void IRCServer::createRoom(int fd, const char * user, const char * password, const char * args) {
    int temp =0;
    argsRoomName = strdup(args);
    
    if (checkPassword(fd, user, password)) {
        for (int i = 0; i < roomCount; i++) {
            if (!strcmp(RoomArray[i].roomName, argsRoomName)) {
                temp = 1;
                break;
            }
        }
        if (temp != 1) {
            RoomArray[roomCount].roomName = strdup(argsRoomName);
            roomCount++;
            roomyame[yamecount]=strdup(argsRoomName);
            yamecount++;
            const char * msg =  "OK\r\n";
            write(fd, msg, strlen(msg));
        } else {
            const char * msg = "DENIED\r\n";
            write(fd, msg, strlen(msg));
            return;
        }
    } else {
        const char * msg = "ERROR (Wrong password)\r\n";
        write(fd, msg, strlen(msg));
    }
}
void IRCServer::listRoom(int fd, const char * user, const char * password, const char * args){
    int i=0;
    for (; i<roomCount; i++) {
        char * msg=(char *) malloc (100 * sizeof(char));;
        strcpy(msg, RoomArray[i].roomName);
        strcat(msg, "\r\n");
        write(fd, msg, strlen(msg));
    }
    
}
void
IRCServer::enterRoom(int fd, const char * user, const char * password, const char * args)
{
    int roomPos =0;
    int flag = 0;
    int temp =0;
    char * message;
    int i=0;
    if (checkPassword(fd, user, password)) {
        for (; i < roomCount; i++) {
            if (!strcmp(RoomArray[i].roomName, argsRoomName)) {
                roomPos = i;
                temp = 1;
                break;
            }
        }
        if (temp == 0) {
            strcpy(message, "ERROR-NO Room\r\n");
            write(fd, message, strlen(message));
            return;
        }
        for (i = 0; i < RoomArray[roomPos].userRoomCount; i++) {
            if (!strcmp(user, RoomArray[roomPos].users[i])) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            RoomArray[roomPos].users[RoomArray[roomPos].userRoomCount] = strdup(user);
            RoomArray[roomPos].userRoomCount++;
            const char * msg =  "OK\r\n";
            write(fd, msg, strlen(msg));
        } else {
            const char * msg =  "Already inside\r\n";
            write(fd, msg, strlen(msg));
        }
    } else {
        const char * msg = "ERROR (Wrong password)\r\n";
        write(fd, msg, strlen(msg));
    }
}

void
IRCServer::leaveRoom(int fd, const char * user, const char * password, const char * args)
{
    int tempRoomPos = 0;
    int tempUserP = 0;
    int aflag = 0;
    int bflag = 0;
    int i=0;
    char * message = (char *) malloc (100 * sizeof(char));
    if (checkPassword(fd, user, password)) {
        for (; i < roomCount; i++) {
            if (!strcmp(RoomArray[i].roomName, argsRoomName)) {
                tempRoomPos = i;
                aflag = 1;
                break;
            }
        }
        if (aflag ==1) {
            i =0;
            for (; i < RoomArray[tempRoomPos].userRoomCount; i++) {
                if (!strcmp(RoomArray[tempRoomPos].users[i], user)) {
                    tempUserP = i;
                    bflag = 1;
                    break;
                }
            }
            if (bflag == 1) {
                int j=0;
                for (j = tempUserP; j < RoomArray[tempRoomPos].userRoomCount; j++) {
                    RoomArray[tempRoomPos].users[j] = RoomArray[tempRoomPos].users[j + 1];
                }
                RoomArray[tempRoomPos].userRoomCount--;
                const char * msg = "OK\r\n";
                write(fd, msg, strlen(msg));
            } else {
                strcpy(message, "ERROR (No user in room)");
                strcat(message, "\r\n");
                write(fd, message, strlen(message));
            }
        }
    } else {
        const char * msg = "ERROR (Wrong password)\r\n";
        write(fd, msg, strlen(msg));
    }
}

void makeString(char src[], int number){
    int i, sample, len = 0, n;
    n = number;
    if (n == 0) {
        src[len] = '0';
        src[len + 1] = '\0';
        return;
    }
    while (n != 0) {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++) {
        sample = number % 10;
        number = number / 10;
        src[len - (i + 1)] = sample + '0';
    }
    src[len] = '\0';
}

void
IRCServer::sendMessage(int fd, const char * user, const char * password, const char * args)
{
    
    int tempRoomPos = 0;
    int flag = 0;
    int  i=0;
    char * temp = (char *) malloc (1000 * sizeof(char));
    if (checkPassword(fd, user, password)) {
        std::string s_args(args);
        std::string my_room=s_args.substr(0, s_args.find(" "));
        string cMessage = s_args.substr(s_args.find(" ")+1);
        currentMessage=cMessage.c_str();
        
        for (; i < roomCount; ++i) {
            if (!strcmp(my_room.c_str(), RoomArray[i].roomName)) {
                tempRoomPos = i;
                flag = 1;
                break;
            }
        }
        
        int bflag = 0;
        for (int j = 0; j < RoomArray[tempRoomPos].userRoomCount; j++) {
            if (!strcmp(RoomArray[tempRoomPos].users[j], user)) {
                bflag = 1;
                break;
            }
        }
        if (bflag != 1) {
            const char * msg = "ERROR (user not in room)\r\n";
            write(fd, msg, strlen(msg));
            return;
        }
    
        
        if (RoomArray[tempRoomPos].cMessCount < 100) {
            string count = std::to_string(RoomArray[tempRoomPos].cMessCount);
            std::string ret_message(count +" "+user+" " +currentMessage);
             RoomArray[tempRoomPos].messages[RoomArray[tempRoomPos].cMessCount] = strdup(ret_message.c_str());
            RoomArray[tempRoomPos].cMessCount++;
            const char * msgs = "OK\r\n";
            write(fd, msgs, strlen(msgs));
        }
    }else{
        const char * msg = "ERROR (Wrong password)\r\n";
        write(fd, msg, strlen(msg));
    }
}

void
IRCServer::getMessages(int fd, const char * user, const char * password, const char * args)
{
    
    //string roomname = s_args(s_args.find(" ")+1);
    
    int tempRoomPos;
    int flag =0;
    int bflag = 0;
    int temp, i=0, j=0, k=0;
    char * message = (char *) malloc (1000 * sizeof(char));
    char * c;
    
    if (checkPassword(fd, user, password)) {
        for ( i = 0; i < roomCount; i++) {
            if (!strcmp(RoomArray[i].roomName, argsRoomName)) {
                tempRoomPos = i;
                printf("%d 12\n\n", i);
                std::string s_args(args);
                int num=stoi(s_args.substr(0, s_args.find(" ")));
                temp = num;
                flag = 0;
                break;
            }
        }
        for ( j = 0; j < RoomArray[tempRoomPos].userRoomCount; j++) {
            if (!strcmp(RoomArray[tempRoomPos].users[j], user)) {
                bflag = 1;
                //printf("%d @\n\n", RoomArray[tempRoomPos].userRoomCount);
                break;
            }
        }
        if (flag == 0) {
            if (bflag == 1) {
                int cflag = 0;
                for (j = temp+1; j < RoomArray[tempRoomPos].cMessCount; j++) {
                    cflag = 1;
                    strcpy(message, RoomArray[tempRoomPos].messages[j]);
                    strcat(message, "\r\n");
                    write(fd, message, strlen(message));
                    printf("%s", message);
                }
                if (cflag == 0) {
                    strcpy(message, "NO-NEW-MESSAGES\r\n");
                    write(fd, message, strlen(message));
                    return;
                }
                strcpy(message, "\r\n");
                write (fd, message, strlen(message));
            } else {
                const char * msg = "ERROR (User not in room)\r\n";
                write (fd, msg, strlen(msg));
                return;
            }
        }
    } else {
        const char * msg = "ERROR (Wrong password)\r\n";
        write(fd, msg, strlen(msg));
    }
    
}

void
IRCServer::getUsersInRoom(int fd, const char * user, const char * password, const char * args)
{
    int tempRoomPos;
    int flag = 0;
    if (checkPassword(fd, user, password)) {
        for (int i = 0; i < roomCount; i++) {
            if (!strcmp(RoomArray[i].roomName, argsRoomName)) {
                tempRoomPos = i;
                flag = 1;
                break;
            }
        }
        if (flag != 1) {
            return;
        }
        char * tempName = (char *) malloc (100 * sizeof(char));
        for (int j = 0; j < RoomArray[tempRoomPos].userRoomCount - 1; j++) {
            for (int k = j + 1; k < RoomArray[tempRoomPos].userRoomCount; k++) {
                if (strcmp(RoomArray[tempRoomPos].users[j], RoomArray[tempRoomPos].users[k]) > 0) {
                    tempName = strdup(RoomArray[tempRoomPos].users[j]);
                    RoomArray[tempRoomPos].users[j] = strdup(RoomArray[tempRoomPos].users[k]);
                    RoomArray[tempRoomPos].users[k] = strdup(tempName);
                }
            }
        }
        char * message = (char *) malloc (100 * sizeof(char));
        for (int i = 0; i < RoomArray[tempRoomPos].userRoomCount; i++) {
            strcpy(message, RoomArray[tempRoomPos].users[i]);
            strcat(message, "\r\n");
            write(fd, message, strlen(message));
        }
        strcpy(message, "\r\n");
        write(fd, message, strlen(message));
    } else {
        const char * msg = "ERROR (Wrong password)\r\n";
        write(fd, msg, strlen(msg));
    }
}

void
IRCServer::getAllUsers(int fd, const char * user, const char * password,const  char * args)
{
    char * temp = (char *)malloc(100 * sizeof(char));
    char order[userCount+1][30];
    if (checkPassword(fd, user, password)) {
        for (int i=0; i<userCount; i++) {
            for (int j=i+1; j<userCount; j++) {
                if (strcmp(userArray[i].username, userArray[j].username)>=1) {
                    temp =userArray[i].username;
                    userArray[i].username=userArray[j].username;
                    userArray[j].username=temp;
                    temp =userArray[i].password;
                    userArray[i].password=userArray[j].password;
                    userArray[j].password=temp;
                }
            }
        }
        for (int i=0; i<userCount; i++) {
            write(fd, userArray[i].username, strlen(userArray[i].username));
            write(fd, "\r\n", 2);
        }
        write(fd, "\r\n", 2);
        
    } else {
        const char * msg ="ERROR (Wrong password)\r\n";
        write(fd, msg, strlen(msg));
    }
    
}

