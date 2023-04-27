#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8000
#define BUFFER_SIZE 4096

float berechne_bmi(float gewicht, float groesse_m) {
  return gewicht / (groesse_m * groesse_m);
}

void einstufung_bmi(float bmi, char *result) {
  if (bmi < 18.5) {
    sprintf(result, "Ihr BMI ist %.2f, Sie sind damit untergewichtig.\n", bmi);
  } else if (bmi >= 18.5 && bmi <= 24.9) {
    sprintf(result, "Ihr BMI ist %.2f, Sie sind damit im Normalbereich.\n", bmi);
  } else {
    sprintf(result, "Ihr BMI ist %.2f, Sie sind damit übergewichtig.\n", bmi);
    }
  }

  int main() {
    int server_fd, client_fd, addrlen;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket creation failed");
      exit(EXIT_FAILURE);
        }

        server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(PORT);

        if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
          exit(EXIT_FAILURE);
        }

        if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
          exit(EXIT_FAILURE);
        }

        while (1) {
        addrlen = sizeof(client_addr);

        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addrlen);
        if (client_fd < 0) {
            perror("Accept failed");
          exit(EXIT_FAILURE);
            }

            memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE);

        float gewicht, groesse_cm, groesse_m;
        sscanf(buffer, "GET /?gewicht=%f&groesse=%f", &gewicht, &groesse_cm);
        groesse_m = groesse_cm / 100;

        float bmi = berechne_bmi(gewicht, groesse_m);
        char result[100];
        einstufung_bmi(bmi, result);

        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE,
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%s",
                 strlen(result), result);

        send(client_fd, response, strlen(response), 0);

        close(client_fd);
    }

    return 0;
}