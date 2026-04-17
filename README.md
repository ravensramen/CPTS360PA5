Sydnee Boothby
CPTS 360
04/17

This program simulates how web browsers communicate with servers using http.
Practicing networking and socketing concepts. Takes in 2 port address and establishes a socket connection

How to Run:
gcc main.c functions.c -o proxy OR make
./proxy 8080

Run cmd in another terminal: (setup a request)
curl -x localhost:8080 http://example.com (had to install curl)

//Terminal will return the html content of example.com

To-do:
- Clean up code + little more testing...