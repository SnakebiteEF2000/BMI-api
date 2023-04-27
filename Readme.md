This is absolutely useless and just a proof of concept that I made in one of my programming lessons

1. ```git clone https://github.com/SnakebiteEF2000/BMI-api.git```
2. ```docker build -t bmi_server .```
3. ```docker run -d -p 8000:8000 --name bmi_server_container bmi_server```
4. ```curl "http://localhost:8000/?gewicht=90&groesse=171"```