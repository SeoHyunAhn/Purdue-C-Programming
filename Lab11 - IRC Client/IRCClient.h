#ifndef IRC_CLIENT_H
#define IRC_CLIENT_H

#define MAX_MESSAGES 100
#define MAX_MESSAGE_LEN 300
#define MAX_RESPONSE (20 * 1024)
using namespace std;
#include <vector>

void add_user();
void printUsage();
extern    char * host;
    extern char * user;
    extern char * password;
    extern char * sport;
    extern int port;
extern char *roomName;
extern char response[MAX_RESPONSE];
extern vector <std::string> userinRoom;
extern vector <std::string> roomList;
extern vector <std::string> getmessages;
#endif
