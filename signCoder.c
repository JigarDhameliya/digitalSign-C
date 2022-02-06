#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "math.h"

/*
Name: Jigar Mukeshbhai Dhameliya
COMP2401
Goal: To make a scrolling sign abd doing some bit manipulation
*/
#define MAX_MESSAGE_SIZE  100

/*
This function filters the input by
-Converting all lower case to upper case
-replacing non integers with period
*/
void filterInput(char theArray[],int numOfCharToDisplay){
	int p=0;
	for(int i=0;i<numOfCharToDisplay;i++){
		p = theArray[i];
		if(!((p==46) || (p>64 && p<91) || (p>96 && p<123)))
			theArray[i] = ' ';
		if(p>96 && p<123){
			theArray[i] = p-32;
		}
	}
}

//This function sets the whole array to 0. Using this we can
//ignore explicitly adding the padding when manipulating the array for vertical.
void fillWithZero(unsigned char theArray[],int n){
	for(int i=0;i<n;i++){
		theArray[i] = 0;
	}
}

/*
This function is used to manipulate the bytes of horizontal array so it can be used to print elements
Vertically
First the input array is converted to binary and each 1 or 0 is stored in as one array.
Then the elements are selected accordingly to make it able to print vertically
*/
void bitManipulation(unsigned char theArray[]){
	int convert[8][8];
  for(int i=0;i<8;i++){
    int n = theArray[i];
    for (int j=7; j>=0; j--) {
      if (n%2 != 0) {
        convert[i][j] = 1;
        n = (int)(n/2);
      }
      else {
        convert[i][j] = 0;
        n = (int)(n/2);
      }
    }
  }
  for(int k=0;k<8;k++){
    int x=0;
    for(int l=0;l<8;l++){
       x += convert[7-l][7-k]*pow(2,l);
    }
    theArray[k] = x;
  }
}

/*
This function is used to fill the display array with appropriate elements from the AtoZ array
The AtoZ array is a 2D array that stores each characters 8 bytes which are used to print them
*/
void fillDisplayArrayHorizontal(char theArray[],int numOfCharToDisplay, unsigned char theDisplayArray[]){
	unsigned char AtoZ[28][8] = {{128,252,146,17,146,252,128,0},{129,255,137,137,141,138,112,0},{60,66,129,129,129,66,231,0},{129,255,129,129,129,66,60,0},{129,255,137,137,137,129,195,0},{129,255,145,17,57,1,7,0},{60,66,129,153,137,137,123,0},{129,255,137,8,137,255,129,0},{129,129,129,255,129,129,129,0},{112,72,129,129,127,1,1,0},{129,255,137,8,149,227,129,0},{129,255,129,128,128,128,192,0},{129,255,130,12,130,255,129,0},{129,255,130,12,145,255,129,0},{60,66,129,129,129,66,60,0},{129,255,137,9,9,9,6,0},{62,65,65,225,65,65,62,0},{129,255,137,25,169,201,134,0},{230,73,137,137,137,146,103,0},{3,1,129,255,129,1,3,0},{1,127,129,128,129,127,1,0},{1,63,65,128,65,63,1,0},{1,127,129,112,129,127,1,0},{129,195,165,24,165,195,129,0},{1,7,137,240,137,7,1,0},{195,161,145,137,137,133,195,0},{192,192,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
	for(int i=0;i<numOfCharToDisplay;i++){
		int tempChar = theArray[i];
		for(int j=0;j<8;j++){
			if(tempChar == 32)
				theDisplayArray[(i*8)+j] = AtoZ[27][j];
			else if(tempChar == 46)
				theDisplayArray[(i*8)+j] = AtoZ[26][j];
			else
				theDisplayArray[(i*8)+j] = AtoZ[tempChar-65][j];
		}
  }
}

/*
This is a similar function as to the fillDisplayArrayHorizontal, the differece is that before adding
the appropriate elements it manipulates them and then adds them. It also leaves a blank row between
for proper readability
*/
void fillDisplayArrayVertical(char theArray[],int numOfCharToDisplay, unsigned char theDisplayArray[]){
	unsigned char AtoZ[28][8] = {{128,252,146,17,146,252,128,0},{129,255,137,137,141,138,112,0},{60,66,129,129,129,66,231,0},{129,255,129,129,129,66,60,0},{129,255,137,137,137,129,195,0},{129,255,145,17,57,1,7,0},{60,66,129,153,137,137,123,0},{129,255,137,8,137,255,129,0},{129,129,129,255,129,129,129,0},{112,72,129,129,127,1,1,0},{129,255,137,8,149,227,129,0},{129,255,129,128,128,128,192,0},{129,255,130,12,130,255,129,0},{129,255,130,12,145,255,129,0},{60,66,129,129,129,66,60,0},{129,255,137,9,9,9,6,0},{62,65,65,225,65,65,62,0},{129,255,137,25,169,201,134,0},{230,73,137,137,137,146,103,0},{3,1,129,255,129,1,3,0},{1,127,129,128,129,127,1,0},{1,63,65,128,65,63,1,0},{1,127,129,112,129,127,1,0},{129,195,165,24,165,195,129,0},{1,7,137,240,137,7,1,0},{195,161,145,137,137,133,195,0},{192,192,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
	for(int i=0;i<numOfCharToDisplay;i++){
		int tempChar = theArray[i];
		unsigned char bitToManipulate[8] = {0,0,0,0,0,0,0,0};
		for(int j=0;j<8;j++){
			if(tempChar == 32)
				bitToManipulate[j] = AtoZ[27][j];
			else if(tempChar == 46)
				bitToManipulate[j] = AtoZ[26][j];
			else
				bitToManipulate[j] = AtoZ[tempChar-65][j];
		}
		bitManipulation(bitToManipulate);
		for(int k=0;k<8;k++){
			theDisplayArray[(i*9)+k] = bitToManipulate[k];
		}
	}
}

/*
This is the main function.
It takes in 3 inputs
-> orientation = anything except 'V' would result in Horizontal orientation
-> Max number of chars at a time on the screen = anything less than pne is one and
anything greater than 12 is 12.
-> display message = It takes input iteratively with get chars
After taking input all the functions are called accordingly.
*/
int main() {
	char orientation;
	printf("Enter the orientation for your scrolling sign: ");
	orientation = getchar();
	while(getchar() != '\n');
	int n=0;
	printf("Enter the max number of alphabets you want to display at once: ");
	scanf("%d",&n);
	while(getchar() != '\n');
	if(n<0)
		n=1;
	else if(n>12)
		n=12;
	char displayArray[MAX_MESSAGE_SIZE];
	int numOfCharToDisplay=0;
	printf("Input the message you want to display ");
	for(int i=0;i<MAX_MESSAGE_SIZE;i++){
		char c1 = getchar();
		if(c1 != '\n'){
			displayArray[numOfCharToDisplay] = c1;
			numOfCharToDisplay++;
		}
		else
			break;
	}

	filterInput(displayArray,numOfCharToDisplay);
	if(orientation =='V'){
		int arrayElements = (numOfCharToDisplay+n)*9;
		unsigned char theDisplayArray[arrayElements];
		fillWithZero(theDisplayArray,arrayElements);
		fillDisplayArrayVertical(displayArray,numOfCharToDisplay,theDisplayArray);
		initializeWindow(VERTICAL,n);
		displaySign(theDisplayArray,sizeof(theDisplayArray));
		closeWindow();
	}
	else{
		int arrayElements = (numOfCharToDisplay+n)*8;
		unsigned char theDisplayArray[arrayElements];
		fillWithZero(theDisplayArray,arrayElements);
		fillDisplayArrayHorizontal(displayArray,numOfCharToDisplay,theDisplayArray);
		initializeWindow(HORIZONTAL,n);
		displaySign(theDisplayArray,sizeof(theDisplayArray));
		closeWindow();
	}
}
