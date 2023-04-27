FROM gcc:latest

WORKDIR /app

COPY bmi_server.c .

RUN gcc -o bmi_server bmi_server.c

EXPOSE 8000

CMD ["./bmi_server"]