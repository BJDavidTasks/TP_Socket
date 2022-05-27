// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char message[2000] = {0};
    char server_reply[2000] = {0};
    // char *hello = "Hello from client";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Connect to remote server
    if ((client_fd = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    puts("Connected\n");
    do
    {
        memset(message, '\0', sizeof(message));
        memset(server_reply, '\0', sizeof(server_reply));
        printf("\n Enter un message : ");
        //scanf("%s", message);
        gets(message);
        // Send some data
        if (send(sock, message, strlen(message), 0) < 0)
        {
            puts("message non envoyé");
            //return 1;
        }

        // Receive a reply from the server
        if (recv(sock, server_reply, 2000, 0) < 0)
        {
            puts("erreur reception");
            break;
        }

        // if (strcmp(server_reply,"bye")==0)
        // {
        //     // closing the connected socket
        //     close(client_fd);
        // }
        printf("reponse serveur : %s \n", server_reply);
    } while (strstr(server_reply, "bye") == 0);
    close(client_fd);
    return 0;

}
