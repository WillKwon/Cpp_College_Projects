/*
* 공학전자계산 과제3 , 2015년 1월 15일 
* 작성자: 국제학과 2009190021 권대욱 
*
* Visual Studio 2010 을 사용하여 작성되었음
*
* 프로그램 설명:
* 본 프로그램을 시작하면 빈 데이터베이스가 생성됩니다. 
* 첫번째 순서로 사용자는 가지고 있는 부품의 정보를 입력하게 됩니다. 
* 두번째 순서로 사용자는 부품번호를 입력하여 데이터베이스에 있는 해당 부품에 대한 정보를 출력할 수 있습니다. 
* 세번째 순서로 사용자는 부품번호를 입력한 후 해당 부품의 수량 및 가격을 변경할 수 있습니다.
* 네번째 순서로 사용자는 편집된 데이터베이스 전체를 부품번호 혹은 부품이름순으로 정렬된 형태로 출력할 수 있습니다. 
* 마지막으로 사용자는 현재 가지고 있는 모든 부품의 총 가치 (모든 부품의 수량*가격 의 합) 를 출력할 수 있습니다. 
*
* 주의사항:
* 첫번째단계에서 부품정보 입력 시 안내된 type의 정보를 입력하지 않고 다른 type을 입력하였다면 프로그램 오류가
* 나므로 종료 후 처음부터 다시 실행해 주시길 바랍니다.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
typedef struct { int number; char name[31]; int quantity; double price; }item;

item IN_DATA();    // Add Items to Database
int SEARCH_LOCATION(item database[], int no_of_items);    // Gives where the partnumber is located in the database
void SEARCH_DATA(int no_of_items, item database[]);    // Given the part number, print its information
item EDIT_DATA(int no_of_items, item database[]);    // Given the part number, edit its information
void PRINT_DATABASE();    // Print database sorted by part number or name
void SORT(item database[], int no_of_items, int choice);    // Used in PRINT_DATABASE()
int GETMIN(item database[], int fill, int n);    // Used in PRINT_DATABASE()
int GETMIN_NAME(item database[], int fill, int n);    // Used in PRINT_DATABASE()
int STRCMP(char const *a, char const *b);    // Used in PRINT_DATABASE()
void PRINT(item database[], int no_of_items);    // Used in PRINT_DATABASE()
void PRINT_TOTAL_VALUE(item database[], int no_of_items);    // Computes sum( quantity * price ) of all parts




////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//****  THE MAIN
/////////////////


int main(void){

	item database[100];// database 는 하나의 원소가 item 인 array
	int i=0, j=0, no_of_items, invalid=0;
	int num, location=-1, choice=0;
	item record;
	char response[15], cate[15];

	printf("* To use this program, you should first add items to the empty database\n"
		"* You can search, edit, and display your database by following our instructions\n"
		"* You can proceed to the next step by typing yes or no in each stage\n"
		"*******************************************************************************\n\n");

	//************************ STAGE 1 ************************//
	while(1){
		if(i >= 99){    // Error message if the database is full
			printf("ERROR: Your database is full");
			break;}

		printf("Do you want to add an item to the database? (Yes/No) ");
		scanf("%s",&response);
			
		if(response[0] =='Y' || response[0] == 'y'){
			record = IN_DATA();    // Fill up the database
			
			for(j=0; j <= i ; j++){
				if(database[j].number == record.number){
					location = j; break;}
			}
			if(location == -1)
				database[i] = record;			
			else
				printf("\nERROR: Same part number already exists in database \n");    // Error message if typed same part number
			i+=1;
		}
		else if (response[0] =='N' || response[0] =='n')
			break;
		else
			printf("Invalid input: type Yes or No \n");
	}
	no_of_items = i;
	printf("//// END of adding items to your database //// \n\n");


	//************************ STAGE 2 ************************//
	SEARCH_DATA(no_of_items, database); 


	//************************ STAGE 3 ************************//
	while(1){    // Ask part number // what you want to change
		printf("Do you want to edit an item? (Yes/No) ");
		scanf("%s",&response);

		if(response[0] =='N' || response[0] == 'n')
			break;
		
		else if (response[0] =='Y' || response[0] == 'y'){
			location = SEARCH_LOCATION(database, no_of_items); 

			if(location != -1){
				printf("Number  |             Name             |  Quantity  |  Price  |");    // Show information before asking for how to change
				printf("\n   %5.d %30s   %10.d   %8.2lf \n", database[location].number, database[location].name, database[location].quantity, database[location].price);
			
				while(1){
					printf("Type which category you want to modify (Quantity/Price) ");
					scanf("%s",&cate);    

					if(cate[0] =='Q' || cate[0] == 'q'){
						choice = 1;
						record = EDIT_DATA( database, location, choice );
						database[location] = record;
						break;}
					else if(cate[0] =='P' || cate[0] == 'p'){
						choice = 2;
						record = EDIT_DATA( database, location, choice );
						database[location] = record;
						break;}
					else
						printf("Invalid input: type Quantity or Price \n");}
			}
			else
				printf("Type part number does not exist in the database \n");    // Error message if the user tries to change none-existing part
		}
		else
			printf("Invalid input: type Yes or No \n");
	}
	printf("//// END of editing items //// \n\n");


	//************************ STAGE 4 ************************//
	PRINT_DATABASE(database, no_of_items );
	printf("//// END of displaying database //// \n\n");


	//************************ STAGE 5 ************************//
	PRINT_TOTAL_VALUE(database, no_of_items);
	printf("//// END of displaying total value //// \n\n");


	printf("*******************************************************************************\n"
		"\t  THIS IS THE END OF THE PROGRAM. THANK YOU FOR USING!  ^.^  \n\n");
	
	return 0;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//****  FUNCTIONS
/////////////////


item IN_DATA(void)   	
{
	item record={0};
	int len;

	while(1){
		printf("Please type the part number (in int): ");
		scanf("%d", &record.number);
		
		if( (1 <= record.number) && (record.number <= 1000) )
			break;
		else
			printf("ERROR: Part number should range from 1 to 1,000 \n");
	}

	while(1){
		printf("Please type the part name (in character string): ");
		scanf("%s",&record.name);
		len = strlen (record.name);

		if( (1 <= len) && (len <= 30) )
			break;
		else
			printf("ERROR: Part name be within 30 characters \n");
	}

	while(1){
		printf("Please type the part quantity (in int): ");
		scanf("%d", &record.quantity);

		if( (1 <= record.quantity) && (record.quantity <= 5000000) )
			break;
		else
			printf("ERROR: Part number should range from 1 to 5,000,000 \n");
	}

	while(1){
		printf("Please type the part price (in double): ");
		scanf("%lf", &record.price);
			
		if( (1 <= record.price) && (record.price <= 1000000) )
			break;
		else
			printf("ERROR: Part number should range from 1 to 1,000,000 \n");
	}

	return record;
}


int SEARCH_LOCATION(item database[], int no_of_items)    // part number 주면 그게 database의 몇번째에 있는지 알려줌, 없으면 없다고 말해줌
{
	int location = -1, i, num; 
	int found = -1;

	printf("Type the part number: ");
	scanf("%d",&num);

	for(i=0; i< no_of_items; i++){
		if(database[i].number == num){
			location = i;
			found = 1;
			break;}
	}

	return location;
}


void SEARCH_DATA(int no_of_items, item database[])    
{
	int num, i, location, found=0;
	char response[10];

	while(1){
		printf("Do you want to search for an item? (Yes/No) ");
		scanf("%s",&response);
		
		if(response[0] =='Y' || response[0] == 'y'){
		location = SEARCH_LOCATION(database, no_of_items);
			
			if(location != -1){
				printf("Number  |             Name             |  Quantity  |  Price  |");
				printf("\n   %5.d %30s   %10.d   %8.2lf \n", database[location].number, database[location].name, database[location].quantity, database[location].price);}
			else
				printf("Typed part number does not exist \n");    // Error message if part does not exist
		}
				
		else if (response[0] =='N' || response[0] =='n')
			break;
		else
			printf("Invalid input: type Yes or No \n");
	}
	printf("//// END of searching items //// \n\n");

	return;
}


item EDIT_DATA( item database[], int location, int choice )     
{
	int nquantity;
	double nprice;
	item new_record;

	new_record = database[location];

	if (choice == 1){    // Change quantity

		while(1){
			printf("Type changes (in/decrease) in quantity: ");
			scanf("%d", &nquantity);
			
			if( (1 <= new_record.quantity + nquantity) && (new_record.quantity + nquantity <= 5000000) ){
				new_record.quantity = new_record.quantity + nquantity;
				break;}
			else
				printf("INVALID CHANGE: the quantity should range from 1 to 5,000,000 \n");    // Error message for values out of range
		}
	}
	else{    // Change Price
		while(1){
			printf("Type changes (in/decrease) in price: ");
			scanf("%lf", &nprice);
			
			if( (1 <= new_record.price + nprice) && (new_record.price + nprice <= 1000000) ){
				new_record.price = new_record.price + nprice;
				break;}
			else
				printf("INVALID CHANGE: the price should range from 1 to 1,000,000 \n");    // Error message for values out of range
		}
	}

	return new_record;
}


void PRINT_DATABASE(item database[], int no_of_items )
{
	char response[15];
	int sort;

	while(1){
		printf("Do you want to display your database? (Yes/No) ");    // Ask if sort by part number or part name
		scanf("%s", &response);

		if(response[0] =='Y' || response[0] == 'y'){
			while(1){
				printf("Type '1' to sort by part number or Type '2' to sort by part name: ");
				scanf("%d", &sort);

				if( sort == 1){
					SORT(database, no_of_items, sort);
					PRINT(database, no_of_items);
					break;}
				else if( sort == 2){
					SORT(database, no_of_items, sort);
					PRINT(database, no_of_items);
					break;}
				else 
					printf("Invalid input: type '1' or '2'");}
		}
		else if (response[0] =='N' || response[0] =='n')
			break;
		else
			printf("Invalid input: type Yes or No \n");
	}

	return;
}


void PRINT(item database[], int no_of_items)
{
	int i; 

	printf("Number  |             Name             |  Quantity  |  Price  |");
	for(i = 0; i < no_of_items; i++){
		printf("\n   %5.d %30s   %10.d   %8.2lf", database[i].number, database[i].name, database[i].quantity, database[i].price);}
	printf("\n");

	return;
}


void SORT(item database[], int no_of_items, int choice)
{
	int fill, mindex;
	item temp;

	if(choice == 1){    // Choice 1: sort by part number
		for(fill=0; fill < no_of_items - 1 ; fill++){
			mindex = GETMIN_NUMBER(database, fill, no_of_items - 1);
			if (fill != mindex){
				temp = database[mindex];
				database[mindex] = database[fill];
				database[fill] = temp;}
		}
	}
	else{    // Choice 2: sort by part name
		for(fill=0; fill < no_of_items - 1 ; fill++){
			mindex = GETMIN_NAME(database, fill, no_of_items - 1);
			if (fill != mindex){
				temp = database[mindex];
				database[mindex] = database[fill];
				database[fill] = temp;}
		}
	}
}


int GETMIN_NUMBER(item database[], int fill, int n)
{
	int i=0, temp = fill;

	for(i=fill+1 ; i<= n; i++){
		if( database[temp].number > database[i].number )
			temp= i;
	}

	return temp;
}


int GETMIN_NAME(item database[], int fill, int n)
{
	int i=0, temp = fill;

	for(i=fill+1 ; i<= n; i++){
		if( STRCMP(database[temp].name, database[i].name) )
			temp= i;
	}

	return temp;
}


int STRCMP(char const *a, char const *b)    // Change characters into lowercase and then compare
{
	int d, res;

	for (;; a++, b++) {
        d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            if( d > 0)
				return res = 1;
			else
				return res = 0;
    }
}


void PRINT_TOTAL_VALUE(item database[], int no_of_items)
{
	int i;
	char response[15];
	double value;

	while(1){
		printf("Do you want to see the total value of your parts in the database?(Yes/No) ");
		scanf("%s", &response);

		if(response[0] =='Y' || response[0] == 'y'){
		value = 0;
			for(i = 0; i < no_of_items; i++){
				value = value + database[i].quantity * database[i].price;}
			printf("The total value of your parts is: %.2lf \n", value);
		}
		else if (response[0] =='N' || response[0] =='n')
			break;
		else
			printf("Invalid input: type Yes or No \n");
	}

	return;
}