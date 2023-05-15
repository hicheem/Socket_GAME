# Socket GAME
## Game of guessing number with socket and multithreading
The server is implemented in C : to compile gcc -o server c_server.c -lpthread -lws2_32 (note that: -lpthread need to be add as library for multithreading , and -lws2_32 for sockets)

The client : 
* C client : to compile gcc -o c_client c_client.c -lpthread -lws2_32
* Java Client : to compile javac java_client.class , to exe : java java_client

---

**© 2023 Written by Hichem FARAOUN. All rights reserved.**
