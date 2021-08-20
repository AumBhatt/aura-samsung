# <p align="center"><img width="200" src="test/1280px-Samsung_Logo.svg.png"/> <img width="50" src="test/samsung-smart-tv-logo.png"/>  + <img width="70" src="test/Tizen-Pinwheel-On-Dark-RGB.png"/></p>

###### <p align="center">`**This is not the final code.`</p>
#### Note: For compiling Tizen or Legacy OS programs on ARM based systems, use the makefile
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
Test server: ```server/server_ws.js``` (written in Node.js)
## 2. Legacy
###### file → `legacy/lgy.cpp`
##### Compilation:
```bash
g++ -o lgy lgy.cpp -lpthread
```
##### Program Usage:
```
Note:
  If using test server: PORT = temp_port (set by default).
  If testing with actual TV: PORT = 55000 (predefined CONST as '#define HOST_PORT' in source file).
```
```bash
./lgy <host_ip> <host_port> <tv_model> <remote_ip> <remote_mac> <command>
```
Test server: ```server/server_lgy.js``` (written in Python 3)
###### References:
Main: https://github.com/Ape/samsungctl <br>
> Legacy OS:
> ###### 1] https://gist.github.com/danielfaust/998441
> ###### 2] http://sc0ty.pl/2012/02/samsung-tv-network-remote-control-protocol/ 
> Tizen OS:
> ###### 1] https://github.com/vrachieru/samsung-tv-api
