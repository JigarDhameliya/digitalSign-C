# digitalSign-C

This program will get a message from the user and have it displayed in the form of Digital Sign.
The code for drawing and displaying the sign has been implemented already, so you won’t have to do that. 
However, if you need to prepare the message to be sent to that sign as an array of bytes. Where each letter
isidivide into 64 parts and each part represents a yes or no. That is how it will produce the red and 
black digital sign.

-> To run this program 
gcc -o signCoder signCoder.c display.c.
