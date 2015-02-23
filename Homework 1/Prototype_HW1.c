/*
* 공학전자계산 2014년 겨울계절학기 
* 권대욱 2009190021 UIC 국제학과
*
* 2015년 1월 3일 토요일에 Visual Studio 2010 으로 작성하였습니다.
* 본 프로그램은 두개의 정수: X, Y (Y는 0이 아닌) 와 a, s, m, d 중 하나의 문자를 argument 로 받은 후
* 적절한 값을 double 형태로 출력해 줍니다.
* 문자값에 a 를 입력한 경우 X + Y 의,
* 문자값에 s 를 입력한 경우 X - Y 의,
* 문자값에 m 를 입력한 경우 X * Y 의,
* 문자값에 d 를 입력한 경우 X / Y 의 결과값을 출력해 주게 됩니다.
*
* 적절한 값을 입력하지 않을 시에는 에러메세지와 함께 프로그램이 종료됩니다.
* X, Y 값이 정수가 아닌 값이 입력됬을 경우 별도의 에러메세지 없이 프로그램이 종료됩니다.
*/

#include <stdio.h>    // 라이브러리 등록 및 함수 프로토타입 선언
#include <math.h>

double add (int x, int y);
double subtract (int x, int y);
double multiply (int x, int y);
double divide (int x, int y);
double print_result (double z);


int main(void)    // 메인함수 시작
{
	// 변수선언
	int x, y, invalid=0;
	char comp;
	double result;

	// 변수설명 및 입력
	printf("You need to type two integers X, Y and a character\n"
		"First, decide which operation to conduct by choosing one of the following characters:\n"
		"If you type \"a\", then we will compute X + Y \n"
		"If you type \"s\", then we will compute X - Y \n"
		"If you type \"m\", then we will compute X * Y \n"
		"If you type \"d\", then we will compute X / Y \n");
	printf("What is your choice?> ");
	scanf("%c", &comp);
	printf("\nNow, give us the first integer X> ");
	scanf("%d", &x);

	if (comp=='d'){    // 문자에 d 를 선택한 경우 나눠주는 정수는 0이 아닌 정수를 입력하도록 안내문 출력
		printf("Type the second \"NONZERO\" integer Y> ");
	}
	else{
		printf("Type the second integer Y> ");
	}
	scanf("%d", &y);

	// 입력한 자료를 바탕으로 함수를 이용한 결과값 계산 시행 
	if (comp=='a'){
		result=add(x,y);
	}
	else if (comp=='s'){
		result=subtract(x,y);
	}
	else if (comp=='m'){
		result=multiply(x,y);
	}
	else if (comp=='d'){
		if(y==0){
		printf("\nIf you choose to divide, Y must be a nonzero integer");    // 나누는 숫자가 0일 경우 에러메세지 출력 
		invalid=1;    // 그리고 invalid 값 변형하여 아래 입력값이 잘못되었다는 메세지도 함께출력
		}
		else{
		result=divide(x,y);    // 나누는 숫자가 0 이 아닐 경우 정상적으로 연산 
		}
	}
	else{
		invalid=1;
	}

	if (invalid==1){    // 입력된 문자가 a, s, m, d 중 하나가 아닐 시,
		printf("\nYou did not follow the input directions properly,\n"
			"Please run the program again.\n");    // 에러메세지 출력 후 메인함수 종료
	}
	else{
		print_result(result);    // 입력된 문자에 이상이 없을 경우 함수를 이용한 결과값 출력 시행 
		printf("\n\nThank you for using this program.\nSee you next time ^.^\n\n");    // 감사메시지 출력 후 메인함수 종료
	}

	// 메인함수 종료
	return 0;
}


// 필요한 함수 정의
double add (int x, int y){
	return (double) (x+y);
}

double subtract (int x, int y){
	return (double) (x-y);
}

double multiply (int x, int y){
	return (double) (x*y);
}

double divide (int x, int y){
	return (double)x / (double)y;
}

double print_result (double z){
	printf("\n>>>> The result of the operation is: %.4lf", z);    // 함수가 실행되면 계산결과를 출력
	return 0.0;    // 0.0 리턴값은 화면에 표시되지 않을 것이며, 단순히 문법을 맞추기 위해 존재
}
