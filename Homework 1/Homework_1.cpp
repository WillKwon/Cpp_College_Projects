/*
* Scientific Computing: Homework 1
* Written using Visual Studio 2010
* 
* This program requires two ints and a char as inputs
* and returns a double as an output
*
* Type two ints for the values of X and Y
* Type a to compute X + Y
* Type s to compute X - Y
* Type m to compute X * Y
* Type d to compute X / Y
*
*
* Daewook Kwon: will.dw.kwon@gmail.com
*/

#include <iostream>
#include <math.h>

using namespace std;
void Intro(char* compute, int* X, int* Y);
double Compute(char compute, int X, int Y);
void print_result (double result);


int main()
{
	char compute,
		*computep = &compute;
	int X, Y,
		*Xp = &X,
		*Yp = &Y;
	double result;

	Intro(computep, Xp, Yp);
	result = Compute(compute, X, Y);
	print_result (result);

	return 0;
}


// Procedures
void Intro(char* compute, int* X, int* Y){
	cout << "You need to type two integers X, Y and a character\n" 
		<< "First, decide which operation to conduct by choosing one of the following characters:\n"
		<< "If you type \"a\", then we will compute X + Y \n"
		<< "If you type \"s\", then we will compute X - Y \n"
		<< "If you type \"m\", then we will compute X * Y \n"
		<< "If you type \"d\", then we will compute X / Y \n" << endl;
	cout << "What is your choice?: ";
		
	while(true){		
		cin >> *compute;
		if(!(*compute == 'a' || *compute == 's' || *compute == 'm' || *compute == 'd'))
			cout << "Invalid input! Type again: ";
		else
			break;
	}

	cout << "Now type the first integer X: ";
	cin >> *X;
	cout << "Type the second integer Y: ";
	while(true){
		cin >> *Y;
		if (*compute == 'd'){
			if(*Y == 0){
				cout << "The second int cannot be 0 if you have chosen to \"divide\"!" << endl;
				cout << "Please try again: ";}
			else 
				return;
		}
		else
			return;			
	}
}


double Compute(char compute, int X, int Y){
	double result;

	switch(compute){
		case 'a':
			result = X + Y;
			break;
		case 's':
			result = X - Y;
			break;
		case 'm':
			result = X * Y;
			break;
		case 'd':
			result = X / Y;
			break;
	}

	return result;
}


void print_result (double result){
	cout << ">>>> The result of your operation is: " << result << endl;
}
