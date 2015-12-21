#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 7890 // The port users will be connecting to

int send_string(int sockfd, unsigned char *buffer) {
  int sent_bytes, bytes_to_send;
  bytes_to_send = strlen(buffer);
  while(bytes_to_send > 0)
  {
    sent_bytes = send(sockfd, buffer, bytes_to_send, 0);
    if(sent_bytes == -1)
      return 0; // Return 0 on send error.
      // Networking 209
    bytes_to_send -= sent_bytes;
    buffer += sent_bytes;
  }
  return 1; // Return 1 on success.
}


/* This function accepts a socket FD
* buffer. It will receive from the
* sequence in seen. The EOL bytes are read from the socket, but
* the destination buffer is terminated before these bytes.
* Returns the size of the read line (without EOL bytes). */
int recv_line(int sockfd, unsigned char *dest_buffer) {
  #define EOL "\r\n" // End-of-line byte sequence
  #define EOL_SIZE 2
  unsigned char *ptr;
  int eol_matched = 0;
  ptr = dest_buffer;

  while(recv(sockfd, ptr, 1, 0) == 1) { // Read a single byte.
    if(*ptr == EOL[eol_matched]) { // Does this byte match terminator? eol_matched++;
      if(eol_matched == EOL_SIZE) { // If all bytes match terminator,
        *(ptr+1-EOL_SIZE) = '\0'; // terminate the string.
        return strlen(dest_buffer); // Return bytes received
      }
    } else { eol_matched = 0;
    }
    ptr++; // Increment the pointer to the next byter.
  }
  return 0; // Didn't find the end-of-line characters.
}



int main(void) {

int sockfd, new_sockfd; // Listen on sock_fd, new connection on new_fd struct sockaddr_in host_addr, client_addr;

// My address information socklen_t sin_size;
int recv_length=1, yes=1;

char buffer[1024];
if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)


host_addr.sin_family = AF_INET; // Host byte order
host_addr.sin_port = htons(PORT); // Short, network byte order
host_addr.sin_addr.s_addr = 0; // Automatically fill with my IP. memset(&(host_addr.sin_zero), '\0', 8); // Zero the rest of the struct.
if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
  fatal("binding to socket");
if (listen(sockfd, 5) == -1)
  fatal("listening on socket");

  while(1) { // Accept loop.
    sin_size = sizeof(struct sockaddr_in);
    new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size); if(new_sockfd == -1)
    fatal("accepting connection");
    printf("server: got connection from %s port %d\n",
    inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port)); send(new_sockfd, "Hello, world!\n", 13, 0);
    recv_length = recv(new_sockfd, &buffer, 1024, 0);
    while(recv_length > 0) {
      printf("RECV: %d bytes\n", recv_length); dump(buffer, recv_length);
      recv_length = recv(new_sockfd, &buffer, 1024, 0);
    }
    close(new_sockfd);
  }
  return 0;
}
