This is absolutely useless and just a proof of concept that I made in one of my programming lessons

1. ```docker build -t bmi_server .```
2. ```docker run -d -p 8000:8000 --name bmi_server_container bmi_server```
3. ```curl "http://localhost:8000/?gewicht=90&groesse=171"```