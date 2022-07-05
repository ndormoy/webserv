#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include "colors.h"
#define PORT 8080

/*
	http://localhost:8080/ pour se connecter en local
	GET — Fetch a URL
	HEAD — Fetch information about a URL
	PUT — Store to an URL
	POST — Send form data to a URL and get a response back
	DELETE — Delete a URL GET and POST (forms) are commonly used
	for image: https://docs.microsoft.com/en-us/previous-versions/exchange-server/exchange-10/ms527550(v=exchg.10)?redirectedfrom=MSDN
	HTML EXAMPLE: https://www.w3schools.com/html/html_examples.asp
	HTML & CSS ANIMATION: https://blog.hubspot.com/website/css-animation-examples
	telnet localhost 8080

	Never use the GET method if you have password or other sensitive information to pass to the server.
	The GET method has size limitation and you can pass upto 1024 characters in a request string

	Le chemin virtuel (ou URI - Uniform Resource Identifier) ​​est similaire à un chemin que vous utiliseriez pour accéder à un document ou à une image ordinaire.
	 C'est-à-dire qu'il pointe le serveur vers le fichier qui contient le programme CGI que vous souhaitez exécuter.
	
	Dans l'encodage d'URL, il existe deux règles :
		Les espaces sont convertis en signes +.
		N'importe lequel des caractères peut être échappé en le transformant en une séquence sous la forme %xx ,
		 où x est un chiffre hexadécimal.
		 Par exemple, %21est un point d'exclamation.
	
	Si la méthode GET est utilisée, les données proviennent de la variable QUERY_STRING.
	Si la méthode POST est utilisée, ces informations sont envoyées à votre programme à l'aide de l'entrée standard.

	Les formulaires HTML qui utilisent la méthode POST envoient leurs informations codées à l'aide de l'entrée standard.
	 Vous pouvez utiliser la variable d'environnement CONTENT_LENGTH pour déterminer le nombre d'octets à lire.

	Chaque paire nom-valeur est un en-tête de protocole HTTP
	Cependant, si le serveur détecte des lignes d'en-tête impaires, 
	le serveur enregistre une erreur 500 et ne renvoie aucune donnée au client.
	 texte/html, texte/ plain, image/gif, image/jpeg, audio/basic

	Par exemple, les trois URI suivants sont équivalents :

   http://example.com:80/~smith/home.html
   http://EXAMPLE.com/%7Esmith/home.html
   http://EXEMPLE.com:/%7esmith/home.html

*/

std::string	find_path(char * buffer)
{
	std::string path = "";
	int i = 5;
	while (buffer[i] != ' ')
	{
		path += buffer[i];
		i++;
	}
	return path;

} 

// ATTENTION IL NE FAUT PAS LE PREMIER / DANS LE PATH
std::string	read_open(std::string path)
{
	//std::cout << BRED << path << CRESET << std::endl;
	std::string content = "";
	std::ifstream file(path.c_str());
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			content += line + "\n";
		}
		file.close();
	}
	else
	{
		content = "Error 404: File not found";
	}
	//std::cout << BRED << content << CRESET ;
	return content;
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    std::string tmp = "";
    // Only this line has been changed. Everything is same.
    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html;charset=UTF-8\nContent-Length: 1800\n\n";
    //std::string	hello = "HTTP/1.1 200 OK\nContent-Type: text/html;charset=UTF-8\nContent-Length: 1800\n\n<html>\n<body>\n\n<h2>HTML Buttons</h2>\n<p>HTML buttons are defined with the button tag:</p>\n\n<button>Click me</button>\n\n</body>\n</html>";
    //std::string	hello = "HTTP/1.1 200 OK\nContent-Type: text/plain;charset=UTF-8\nContent-Length: 12\n\nHello world!";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) // il faut que ca soit inf a 0 pour moi
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    //Permet de suprrinmer le In bind: Address already in use
	int nb = 1;
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &nb, sizeof(int)) == -1)
        exit(EXIT_FAILURE);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000); //BUG ici on utiliserai plustot recv ??
        printf("%s\n",buffer );
		tmp = hello;
		hello.append(read_open(find_path(buffer)));
        write(new_socket , hello.c_str() , strlen(hello.c_str())); //BUG ici on utiliserai plustot send ??
		std::cout << BRED << hello << CRESET << std::endl;
		hello = tmp;
        printf("------------------Hello message sent-------------------");
        close(new_socket);
    }
    return 0;
}
