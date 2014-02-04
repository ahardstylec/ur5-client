#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <sched.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../libs/interrupt_utils.h"
#include "../libs/base_utils.h"
#include <pthread.h>
#include <stdbool.h>

bool exit_program = false;
pthread_mutex_t quit_programm_mutex =PTHREAD_MUTEX_INITIALIZER;


int main(int argc, char **argv){
    int sockfd, portno, n;
    struct sockaddr_in serveraddr;

    char * ip_string="";
    char *garbage=NULL;
    bzero(&serveraddr, sizeof(serveraddr));

    if (argc != 3) {
        fprintf(stderr,"usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    ip_string = argv[1];
    if(inet_aton(ip_string, &serveraddr.sin_addr) == 0){
        printf("ip address not valid");
        exit(1);
    }

    portno = (int) strtol(argv[2], &garbage, 10);
    printf("Start UR5 Client\n");

    setup_sigint();
    setup_sigpipe();

    /* build the server's Internet address */
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(portno);
    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        printf("failed\n");
        error("ERROR opening socket");
        exit(1);
    }

    char *buff[sizeof(PVAPacket)];
    int connect_error=0;
    while(connect_error<3 && (exit_program != true)){
        printf("connecting to server %s:%d...", ip_string, portno);
        fflush(stdout);
        if (connect(sockfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr)) < 0){
            connect_error++;
            printf("error: can't connect to server!(%d times)..try again in 2 seconds..\n", connect_error);
            fflush(stdout);
            continue;
        }
        printf("suceess\n");

        while(exit_program != true){

            n = recv(sockfd, &servo_packet, sizeof(servo_packet),0);
            if(n<1){
                connect_error++;

                // --- TODO routine if connection is lost
                break;
            }
            if(n != sizeof(PPacket))

            //--------------------- do something with the data ----------------------





            //-----------------------------------------------------------------------

            /* send the message line to the server */
            if (send(sockfd, (char *) &pva_packet, sizeof(pva_packet), 0) < 0){
                puts("connection to server lost");
                connect_error++;
                break;
            }
        }
    }
    connect_error >2 ? printf("cant connect to server!(tried %d times) ..abort!\n",connect_error) :
                       puts("disconnected from server");

    close(sockfd);
    return 0;
}
