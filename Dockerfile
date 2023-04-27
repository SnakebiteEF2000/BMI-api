# Use Nginx base image
FROM nginx:alpine

# Install build tools and remove cache
RUN apk add --no-cache build-base

# Set the working directory for the BMI API
WORKDIR /app

# Copy the bmi_server.c file
COPY bmi_server.c .

# Compile the BMI API
RUN gcc -o bmi_server bmi_server.c

# Remove the default Nginx configuration
RUN rm /etc/nginx/conf.d/default.conf

# Add a new Nginx configuration
COPY nginx.conf /etc/nginx/conf.d

# Copy the index.html file to the Nginx public directory
COPY index.html /usr/share/nginx/html

# Expose the ports for the webserver and the BMI API
EXPOSE 80 8000

# Run the BMI API and Nginx simultaneously
CMD ["sh", "-c", "./bmi_server & nginx -g 'daemon off;'"]
