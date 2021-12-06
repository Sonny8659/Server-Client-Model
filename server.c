#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "220.149.128.100"
#define SERV_PORT   4530
#define BACKLOG     10

#define INIT_MSG    "==============\nHello! I'm P2P File Sharing Server... \nPlease, LOG-IN!=========================\n"
#define USER1_ID     "user1"
#define USER1_PW     "passwd1"
#define USER2_ID     "user2"
#define USER2_PW     "passwd2"

int main(void)
{
    /* listen on sock_fd, new connection on new_fd */
    int sockfd, new_fd;

    // my address information, address where i run this program
    struct sockaddr_in my_addr;

    // remote address information
    struct sockaddr_in their_addr;
    unsigned int sin_size;

    // buffer
    int rcv_byte;
    char buf[512];

    char id[20];
    char pw[20];

    char msg[512];

    int val = 1;

    // socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("Server-socket() error lol!");
        exit(1);
    }
    else printf("Server-socket() sockfd id OK...\n");

    // host byte order
    my_addr.sin_family = AF_INET;

    // short, network byte order
    my_addr.sin_port = htons(SERV_PORT);
    // my_addr.sin_addr.s_addr = inet_addr(SERV_IP)
    my_addr.sin_addr.s_addr = INADDR_ANY;

    // zero the rest of the struct
    memset(&(my_addr.sin_zero), 0, 8);

    // to prevent 'Adress already in use...' 
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val)) < 0) {
        perror("setsockopt");
        close(sockfd);
        return -1;
    }

    // bind
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("Server-bine() error lol!");
        exit(1);
    }
    else printf("Server-bind() is OK...\n");

    // listen
    if(listen(sockfd, BACKLOG) == -1)
    {
        PERROR("listen() error lol!");
        exit(1);
    }
    else printf("listen() is OK...\n\n");

    // ...other codes to read the received data....
    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

    // send INIT_MSG
    send(new_fd, INIT_MSG, strlen(INIT_MSG) + 1, 0);

    close(new_fd);
    close(sockfd);

    return 0;

}