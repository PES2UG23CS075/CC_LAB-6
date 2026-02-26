#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

int main() {
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);
    
    while(true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        std::string response_body = "Served by backend: " + std::string(hostname) + "\n";
        std::string response = "HTTP/1.1 200 OK\r\nContent-Length: " + 
                               std::to_string(response_body.size()) + 
                               "\r\nContent-Type: text/plain\r\n\r\n" + response_body;
        send(client_fd, response.c_str(), response.size(), 0);
        close(client_fd);
    }
    return 0;
}
