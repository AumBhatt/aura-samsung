# <p align="center"><img width="200" src="test/1280px-Samsung_Logo.svg.png"/> <img width="50" src="test/samsung-smart-tv-logo.png"/>  + <img width="70" src="test/Tizen-Pinwheel-On-Dark-RGB.png"/></p>

###### <p align="center">`**This is not the final code.`</p>
## 1. Tizen
###### file → `tizen/tz.cpp`
##### Compilation:
```bash
g++ -o tz tz.cpp -lpthread
```
##### Program Usage:
#### `Note: PORT = 8001 -> Already set....`
```bash
./tz <host> <remote-name> <command>
```
###### References:
> Main: https://github.com/Ape/samsungctl
><br>
> Legacy OS:
> - https://github.com/enen92/flask-samsung
> - http://sc0ty.pl/2012/02/samsung-tv-network-remote-control-protocol/ 
> <br>
> Tizen OS:
> - https://github.com/vrachieru/samsung-tv-api
