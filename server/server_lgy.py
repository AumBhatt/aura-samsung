#!/usr/bin/env python3

import socket
import os
from time import sleep

clear = lambda: os.system('clear')
clear()

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 3000        # Port to listen on (non-privileged ports are > 1023)

def mySocket():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        print("\n-----------------------------------", "\nListening py3 @http://127.0.0.1:" + str(PORT), "\n-----------------------------------")
        s.listen()
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(data, type(data))
            print(" > Client Disconncted")
    mySocket()
mySocket()