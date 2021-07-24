# <p align="center"><img width="250" src="test/1280px-Samsung_Logo.svg.png"/></p>

###### <p align="center">`**This is not the final code.`</p>
## 1. Tizen
###### file → `tizen/tz.cpp`
##### Compilation
```bash
g++ -o tz tz.cpp -lpthread
```
##### Program Run
`Note: Only ip of the TV needed. Port is already set to 8001 as given in references.`
```bash
./tz <host> <port> <remote-name> <command>
```
###### References:
>Legacy OS: https://github.com/enen92/flask-samsung <br>
>Tizen OS: https://github.com/vrachieru/samsung-tv-api
