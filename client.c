#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sockey.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "220.149.128.100"
#define SERV_PORT   4530

/*=================================socket structures============================================*/
struct sockaddr {
    u_char      sa_len;
    u_short     sa_family       // address family. AF_xxx
    char        sa_data[14];    // 14 bytes of protocol address
};

struct sockaddr_in {
    u_char      sin_len;
    u_short     sin_family;
    u_short     sin_port;
    struct      in_addr sin_addr;
    char        sin_zero[8];
};

struct in_addr {
    union {
        struct { u_char s_b1, s_b2, s_b3, s_b4;} S_un_b;    //4바이트
        struct { u_short s_w1, s_w2; } S_un_w;              //4바이트
        u_long S_addr;  // 4바이트
    }S_un;
};
/*========================================end====================================================*/

int main(int argc, char *argv [  ])
{
    int sockfd; // will hold the destination addr
    struct sockaddr_in dest_addr;

    int rcv_byte;
    char buf[512];

    char id[20];
    char pw[20];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Client-socket() error lol!");
        exit(1);
    }
    else printf("Client-socket() sockfd id OK...\n");

    // host byte order
    dest_addr.sin_family = AF_INET;

    // short, network byte order
    dest_addr.sin_port = htons(SERV_PORT);
    dest_addr.sin_addr.s_addr = inet_addr(SERV_IP);

    memset(&(dest_addr.sin_zero),0,8);

    //connect
    if(connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Client-connect() error lol!");
        exit(1);
    }
    else printf("Client-connect() is OK...\n\n");

    // receive INIT_MSG
    rcv_byte = recv(sockfd, buf, sizeof(buf), 0);
    printf("%s\n", buf);

    close(sockfd);


    return 0;
}