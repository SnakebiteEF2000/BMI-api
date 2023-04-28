#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUFFER_SIZE 2048

double calculate_bmi(double weight, double height) {
  double height_in_meters = height / 100.0;
  return weight / (height_in_meters * height_in_meters);
}

const char *classify_bmi(double bmi) {
  if (bmi < 18.5) {
    return "Untergewicht";
  } else if (bmi >= 18.5 && bmi <= 24.9) {
    return "Normalgewicht";
  } else {
    return "Übergewicht";
    }
  }

  int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    double weight, height;
    double bmi;
    char response[BUFFER_SIZE];
    const char *classification;

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
      exit(EXIT_FAILURE);
        }

        // Bind the socket to the IP address and port
    address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
      exit(EXIT_FAILURE);
        }

        // Listen for connection requests
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
      exit(EXIT_FAILURE);
        }

        while (1) {
        // Accept a connection
          if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        // Read the input from the client
        read(new_socket, buffer, BUFFER_SIZE);
        sscanf(buffer, "GET /bmi?weight=%lf&height=%lf", &weight, &height);

        // Calculate the BMI and classify it
        bmi = calculate_bmi(weight, height);
        classification = classify_bmi(bmi);

        // Send the response with Access-Control-Allow-Origin header
        snprintf(response, BUFFER_SIZE, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nAccess-Control-Allow-Origin: *\r\n\r\nBMI: %.2f, Einstufung: %s", bmi, classification);
        send(new_socket, response, strlen(response), 0);
        close(new_socket);
        }

    return 0;
}