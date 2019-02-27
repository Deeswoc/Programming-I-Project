//Daniel Nelson
//1705813

//The next two lines are Visual Studio specific
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#define HEADERSIZE 500 //Size of the Header String
#define PASSWORD "12345678" //Password string for the project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Counters
int AConCount = 0, BConCount = 0, CConCount = 0, totalMinRent = 0, purchaseCount = 0, donationCount = 0;

/*
	String Key
	Condition
		a - excellent
		b - fair
		c - good

	Rental Fee Table
	Excellent   -   20%
	Fair        -   15%
	Good        -    8%
*/

//datatype made to store the record of a book
struct Book {
	char ISBN[7];
	char condition;
	int purchaseAmt;
};

//decaring a function that returns a new book
struct Book makeBook(
	char mISBN[6],
	char mcondition,
	int mpurchaseAmt
);

//Function Definitions
int rentAmount(struct Book b);
int addBooks();
void menu();
void displayLogs();
void updateBookLog();
char *conditionOut(char key);
int password(char *somthing);

//recordManipulation
struct Book record[11]; //Storage
int bookCount = 0; //Number of books in entered

int main() {
	if(password(PASSWORD) == 0)//If password returns 0 that means the correct password was entered within the minimum number of tries and the user has been granted access
	menu();
	return 0;
}

//function to return a book with the data the user entered
struct Book makeBook(
	char mISBN[6],
	char mcondition,
	int mpurchaseAmt
) {
	struct Book newBook;
	strcpy(newBook.ISBN, mISBN);
	newBook.condition = mcondition;
	newBook.purchaseAmt = mpurchaseAmt;
	return newBook;
}

//function to return the rent amount of a record
int rentAmount(struct Book b) {
	switch (b.condition)
	{
	case 'a': {return b.purchaseAmt*0.2; }
	case 'b': {return b.purchaseAmt*0.15; }
	case 'c': {return b.purchaseAmt*0.08; }
	default:
		break;
	}	
}

//function for the main menu of the program
void menu() {
	int choice;
	do {
		system("cls");
		system("color 07");
		printf("Enter the Number for the menu option\n");
		printf("1 - Add Books\n");
		printf("2 - Update Books\n");
		printf("3 - Display Book Logs\n");
		printf("0 - Exit\n");
		do {
			if (scanf("%d", &choice) != 1) {
				printf("Invalid Selection\n");
				choice = -1;
				while (getchar() != '\n');//takes characters from the buffer until a \n is recieved
			}
			else if (choice > 3 || choice < 0) {
				printf("Invalid Selection\n");
				choice = -1;
			}
			//choice is set to -1 to ensure the loop starts over if wrong data is entered
		} while (choice > 3 || choice < 0);

		while (getchar() != '\n');
		switch (choice) {
		case 1: {
			addBooks();//starts the function to add a new book
			break;
		}
		case 2: {
			updateBookLog();//starts the function to update an existing book
			break;
		}
		case 3: {
			displayLogs();// displays the records of the books entered in the system and various tallies
			break;
		}
		}
	} while (choice!=0); //the menu will run until the user exits
}

int addBooks() {
	const int purchaseAmtUpperLimit = 3000, purchaseAmtLowerLimit = 0;
	system("color 70");
	char ISBN[7];
	char condition;
	int len;
	int purchaseAmt;
	double purchaseAmtTemp;
	do {
		if (bookCount != 10) {//Stops the program from exceeding the limit of 10 books
			printf("UTECH Book Inventory Tracker\n-----------------------------------------------------------------------------------------------------------\n");
			do {
				printf("Enter ISBN (Enter \"XXX\" to Stop)\n");
				fgets(ISBN, 7, stdin);
				if (!strchr(ISBN, '\n')) while (fgetc(stdin) != '\n');
				len = strlen(ISBN);
				if (ISBN[len - 1] == '\n') ISBN[len - 1] = '\0';

				if ((atoi(ISBN)) == 0 && strcmp("xxx", strlwr(ISBN)) != 0 ){
					printf("You must use a number\n");
				}
			} while ((atoi(ISBN)) == 0 && strcmp("xxx", strlwr(ISBN)) != 0);

			//compares the lowercase of ISBN with the string "xxx" and if the are the same the program skips adding a book
			if (!strcmp("xxx", strlwr(ISBN)) == 0) {
				bookCount++;
				printf("What is the condition of the book\n");
				printf("A - Excellent\n");
				printf("B - Fair\n");
				printf("C - Good\n");
				do {
					condition = getchar();//reads the character the user enters as their selection from the buffer
					if (condition != '\n') while (getchar() != '\n');//runs the buffer cleaning code mentioned previously if the condition value isn't '\n'
					condition = tolower(condition);//makes the condition lowercase
					if (strchr("abc", condition) == NULL) {//checks if condition is in the string "abc"
						if (condition == '\n') {
							printf("No Input Entered\n");
						}
						else {
							printf("Invalid Selection\n");
						}
						//pauses the program
						system("pause");
						//Remove Lines
						printf("\33[2K");
						printf("\033[A");
						printf("\33[2K");
						printf("\033[A");
						printf("\33[2K");
						printf("\033[A");
						printf("\33[2K");
					}

				} while (strchr("abc", condition) == NULL);
				printf("Enter the purchase amount. \n");
				do {

					if (scanf("%lf", &purchaseAmtTemp) != 1) {//if no value is assigned to purchaseAmtTemp
						purchaseAmtTemp = -1;
						while (getchar() != '\n');
						printf("Input invalid\n");
					}
					else if (purchaseAmtTemp > purchaseAmtUpperLimit || purchaseAmtTemp <= purchaseAmtLowerLimit) printf("Input out of range\n");

				} while (purchaseAmtTemp > purchaseAmtUpperLimit || purchaseAmtTemp <= purchaseAmtLowerLimit);
				purchaseCount++;
				purchaseAmt = purchaseAmtTemp * 100;
				//create a struct of Book type called b using the funciton
				struct Book b = makeBook(ISBN, condition, purchaseAmt);
				totalMinRent += rentAmount(b);//adds the calculated rent of the new book to the total rent
				switch (b.condition) {//decision involving the condition value of Book b
				case 'a': {
					AConCount++;
					break; }
				case 'b': {
					BConCount++;
					break; }
				case 'c': {
					CConCount++;
					break; }
				}
				//tallies are incremented appropriately
				fflush(stdin); //flush input buffer
				fflush(stdout); //flush output buffer 
				record[bookCount - 1] = b;//sets the record at array index
				while (getchar() != '\n');
				system("cls");
			}
		}
		else {
			printf("Book Limit Reached\n");
			strcpy(ISBN, "xxx");//sets the ISBN to "xxx" so the loop breaks
		}
	} while (!strcmp("xxx", strlwr(ISBN)) == 0);//loop will continue until a capital/common or any combination of both for "xxx" is entered
}

void updateBookLog() {
	char src[11];//What is used to search for the book
	int out = -1;//Controller for the loop
	int found = -1;//Determine if book was found
	char YN;
	do {
		printf("Enter the ISBN of the book to update\n");
		fgets(src, 10, stdin);
		if (!strchr(src, '\n')) while (fgetc(stdin) != '\n');

		if (atoi(src) <= 0) {//determining if the value is an integer
			printf("Value Must be a Positive Integer\n");
			getchar();
			out = -1;
		}
	} while (out != -1);

	for (int i = 0; out != -2; i++) {
		if (atoi(src) == atoi(record[i].ISBN)) {
			found = i;
			out = -2;
		}
		else if (i == bookCount) {
			out = -2;
			printf("The record requested was not found");
		}
	}
	if (found != -1) {
		printf("%-15s: %s\n", "ISBN#", record[found].ISBN);
		printf("%-15s: %s\n", "Condition", conditionOut(record[found].condition));
		printf("%-15s: $%.2lf\n", "Purchase Amount", (double)record[found].purchaseAmt / 100);

		totalMinRent -= rentAmount(record[found]);//subtracting total min rent to add back if changed
		printf("Change Purchase Amount? (Y/N)");
		do {
			YN = getchar();
			if (strchr("YyNn", YN) == NULL) {
				printf("Invalid");
			}
		} while (strchr("YyNn", YN) == NULL); //value must be y or n to proceed
		if (strchr("Yy", YN) != NULL) {
			printf("Enter the new value\n");
			double temp;

			do {
				if (scanf("%lf", &temp) != 1) {
					/*record[found].purchaseAmt = -1;

					record[found].purchaseAmt = temp * 100;*/
					printf("Invalid value\n");
				}
				else if (temp > 3000 || temp <= 0) printf("Input out of range\n");
				else {
					record[found].purchaseAmt = -1;
					record[found].purchaseAmt = temp * 100;
				}
			} while (temp > 3000 || temp <= 0);
			//while (getchar() != '\n');
		}
		printf("Do you want to change the condition of the book (Y/N)");
		do {
			while (getchar() != '\n');
			YN = getchar();
			if (strchr("YyNn", YN) == NULL) {//value must be y or n to proceed
				printf("Invalid");
			}
		} while (strchr("YyNn", YN) == NULL);

		if (strchr("Yy", YN) != NULL) {
			printf("Enter the new value\n");
			printf("What is the new condition of the book\n");
			printf("A - Excellent\n");
			printf("B - Fair\n");
			printf("C - Good\n");
			while (getchar() != '\n');
			do {
				switch (record[found].condition) {//subtracting from the tally in case the values are changed
				case 'a': {
					AConCount--;
					break; }
				case 'b': {
					BConCount--;
					break; }
				case 'c': {
					CConCount--;
					break; }
				}
				record[found].condition = getchar();
				switch (record[found].condition) {
				case 'a': {
					AConCount++;
					break; }
				case 'b': {
					BConCount++;
					break; }
				case 'c': {
					CConCount++;
					break; }
				}
				if (record[found].condition != '\n') while (getchar() != '\n');

				record[found].condition = tolower(record[found].condition);
				if (strchr("abc", record[found].condition) == NULL) {
					if (record[found].condition == '\n') {
						printf("No Input Entered\n");
					}
					else {
						printf("Invalid Selection\n");
					}
					//clearing lines
					system("pause");
					printf("\33[2K");
					printf("\033[A");
					printf("\33[2K");
					printf("\033[A");
					printf("\33[2K");
					printf("\033[A");
					printf("\33[2K");
				}

			} while (strchr("abc", record[found].condition) == NULL);
		}
		totalMinRent += rentAmount(record[found]);
		
	}
}
void displayLogs() {
	system("color f0");
	char reportHeader[HEADERSIZE] =
		"UTECH Book Inventory Tracker\n";
	char headings[500];//holds the string for the headings
	int lines = snprintf(headings, sizeof(headings), "%-8s|%-13s|%-15s|%-15s|\n", "ISBN", "Condition", "Purchase Price", "Rental Fee");//creates a formated heading string and stores its size to use for table borders
	for (int i = 0; i < lines - 1; i++) {
		strcat(reportHeader, "-");
	}

	strcat(reportHeader, "\n");//add new line to report header
	strcat(reportHeader, headings);
	for (int i = 0; i < lines - 1; i++) {
		strcat(reportHeader, "-");//making border
	}
	strcat(reportHeader, "\n");
	system("cls");//clearscreen
	printf("%s", reportHeader);
	char tempRecord[200];
	
	for (int i = 0; i<bookCount; i++) {//print formated records
		record[i];
		snprintf(tempRecord, sizeof(tempRecord), "%-8s|%-13s|$%14.2lf|$%14.2lf|\n", record[i].ISBN, conditionOut(record[i].condition), (double)record[i].purchaseAmt / 100, (double)rentAmount(record[i])/100);
		printf("%s", tempRecord);
		if (bookCount == (i + 1)) {
			for (int i = 0; i < lines - 1; i++) {
				printf("-");
			}
			printf("\n");
		}
	}
	//printing tallies
	snprintf(tempRecord, sizeof(tempRecord), "The total of Number of Books Supplied is:         %d\n", bookCount);
	printf("%s", tempRecord);
	printf("%-35s:$%14.2lf\n"," Total Potential Rent" , (double)totalMinRent / 100);
	printf("%-35s:%15d\n", "\"Excellent\" Condition Books", AConCount);
	printf("%-35s:%15d\n", "\"Fair\" Condition Books", BConCount);
	printf("%-35s:%15d\n", "\"Good\" Condition Books CConCount)", CConCount);
	system("pause");
}

char *conditionOut(char key) {//returns a string when given a key
	static char Out[10];
	switch (key) {
	case 'a': {
		strcpy(Out, "Excellent");
		break; }
	case 'b': {
		strcpy(Out, "Fair");
		break; }
	case 'c': {
		strcpy(Out, "Good");
		break; }
	}
	return Out;
}
int password(char *somthing) {//takes a password as an argument
	printf("Enter the pasword to enter the access the system");
	int attempts = 0;//track the number of attempts made
	char passWordEntered[20];// what the user can enter
	passWordEntered[0] = '\0';//sets the value of the entered container to a string terminator
	
	do{
	char temp = 'i';
	for (int i = 0; temp != '\r'; i++) {
		temp = getch();
		if (temp == '\r')break;//stops the loop if the user presses enter
		if (temp != '\0') {
			if (temp == '\b' && i != 0 ) {
				printf("\b");
				printf(" ");
				printf("\b");
				passWordEntered[i - 1] = '\0';
				i -= 2;
			}
			else {
				if (i < 19 && temp != '\b') {//removes visable characters from the screen and replaces them with asterisks
					passWordEntered[i] = temp;
					passWordEntered[i + 1] = '\0';
					printf("*");
				}
				else {
					i--;
				}

			}
		}
		else {
			i--;
		}

	}
	if (strcmp(passWordEntered, somthing) != 0) {
		attempts++;
		printf("\nIncorrect Password\n");

	}
	} while (strcmp(passWordEntered, somthing)!=0 && attempts != 3);//loops while attempts isn't 3 and the password entered is incorrect
	if (attempts == 3) {
		printf("Too many attempts, Programming Exiting");
		getch();
		getch();
		return -1;//returns with too many incorrenct attempts 
	}
	else {
		printf("Password Verified");
		getch();
		return 0;//returns with a correct attempt
	}
}