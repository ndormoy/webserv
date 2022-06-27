#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>

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
*/


int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Only this line has been changed. Everything is same.
    std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html;charset=UTF-8\nContent-Length: 1800\n\n";
    //char *hello = "HTTP/1.1 200 OK\nContent-Type: text/html;charset=UTF-8\nContent-Length: 1800\n\n<html>\n<body>\n\n<h2>HTML Buttons</h2>\n<p>HTML buttons are defined with the button tag:</p>\n\n<button>Click me</button>\n\n</body>\n</html>";
    //char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain;charset=UTF-8\nContent-Length: 12\n\nHello world!";
    
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
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
		hello.append(buffer);
        write(new_socket , hello.c_str() , strlen(hello.c_str()));
        printf("------------------Hello message sent-------------------");
        close(new_socket);
    }
    return 0;
}