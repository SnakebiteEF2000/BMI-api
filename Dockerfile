FROM nginx:alpine

RUN apk add --no-cache build-base

WORKDIR /app

COPY bmi_server.c .

RUN gcc -o bmi_server bmi_server.c

RUN rm /etc/nginx/conf.d/default.conf

COPY nginx.conf /etc/nginx/conf.d

COPY index.html /usr/share/nginx/html

EXPOSE 80 8000

CMD ["sh", "-c", "./bmi_server & nginx -g 'daemon off;'"]
