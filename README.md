# <p align="center"><img width="200" src="test/1280px-Samsung_Logo.svg.png"/> <img width="50" src="test/samsung-smart-tv-logo.png"/>  + <img width="70" src="test/Tizen-Pinwheel-On-Dark-RGB.png"/></p>

###### <p align="center">`**This is not the final code.`</p>
## 1. Tizen
###### file → `tizen/tz.cpp`
##### Compilation:
```bash
g++ -o tz tz.cpp -lpthread
```
##### Program Usage:
`Note: Only ip of the TV needed. Port is already set to 8001 as given in references.`
```bash
./tz <host> <port> <remote-name> <command>
```
###### References:
>Legacy OS: https://github.com/enen92/flask-samsung <br>
>Tizen OS: https://github.com/vrachieru/samsung-tv-api
