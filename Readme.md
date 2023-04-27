# BMI calculator

## This project is a simple BMI calculator API and web frontend implemented using a C-based server and Nginx, running in a Docker container. It calculates and classifies a user's BMI based on their weight and height inputs.
1. `git clone https://github.com/SnakebiteEF2000/BMI-api.git`
2. `cd BMI-api`
3. `docker build -t nginx_bmi_server .`
4. `docker run -d -p 80:80 -p 8000:8000 --name nginx_bmi_server_container nginx_bmi_server`

Navigate to `http://localhost`

Test API with (example data:weight= 90kg & height= 171 cm):
`curl "http://localhost:8000/bmi?weight=90&height=171"`

## This is absolutely useless and just a proof of concept that I made in one of my programming lessons