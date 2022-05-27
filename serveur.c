// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1, read_size;
    int addrlen = sizeof(address);
    // char *hello = "Hello from server";

    // Creer socket (domaine, type, protocole)
    // AF_INET:internet; SOCK_STREAM:Mode connecté;0:protocole par défaut;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // utilisation de l’adresse IP de la machine
    address.sin_port = htons(8080);       // choix d’un numéro de port si 0 == port non utilisé

    // spécification de l'adresse locale
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // Entrer dans un mode d’écoute
    // 5= le nombre maximal de demandes de connexion autorisées dans la file
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // le nombre maximal de demandes de connexion autorisées dans la file
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        char client_message[2000] = {0};
        read_size = recv(new_socket, client_message, 2000, 0);
        if (read_size == -1)
        {
            perror("recv failed");
        }
        else if (read_size == 0)
        {
            printf("error readsize");
            // closing the connected socket
            close(new_socket);
            // closing the listening socket
            //SHUT_RDWR:reception et émission interdite
            shutdown(server_fd, SHUT_RDWR);
            return 0;
        }
        puts(client_message);
        write(new_socket, client_message, strlen(client_message));
        if(strstr(client_message,"bye")!=0){
            // closing the connected socket
            close(new_socket);
            // closing the listening socket
            //SHUT_RDWR:reception et émission interdite
            shutdown(server_fd, SHUT_RDWR);
            return 0;
        }
    }
}
