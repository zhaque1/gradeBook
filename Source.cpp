// Zayd Haque
// project #3 
// date: 11/3/2016

#include <iostream>
#include <fstream>
#include <string>																		
#include <iomanip>																				
#include <cctype>											
using namespace std;																			
																						
//  structure 

struct Student{
	
	string lName;
	string fName;
	string studId;
	string userName;
	int test1;
	int test2;
	int test3;
	int test4;
	int test5;
	float avg;
	char grade;
};

const int SIZE = 100;

// ------------- function prototypes --------------------------------
// sorting
void sortScore(Student[], int, char);
// search
int searchScore(Student[], int, string); // checked
// find avg for each student
void findAvg(Student[], int); // checked
// find grade
void findGrade(Student[], int); // checked
// find count of each letter grade
int countLetter(Student[], int, char); // checked
// calc class avg
float calcClassAvg(Student[], int); // checked 
// creating userName for each student
void findUserName(Student[], int); // checked
// check user input for search
bool validateInput(string); // checked
//-------------------------------------------------------------------


int main(){
	
	Student stud[SIZE]; // array of student struct for each student
	
	int count = 0; // counter variable to keep track of how many students so far
	int totalA, totalB, totalC, totalD, totalF; // holds the count of each letter grade
	float classAvg;

	ifstream inFile;
	inFile.open("grade.dat"); // opens grade.dat file for reading info into the program

	while (!inFile.eof()){ // keep reading till there is nothing unread in the file

		inFile >> stud[count].lName >> stud[count].fName >> stud[count].studId >> stud[count].test1 >> stud[count].test2 >> stud[count].test3 >> stud[count].test4 >> stud[count].test5;
			

		++count; // keep track of how many stdudents
	}
	
	
	cout << fixed << setprecision(2) << showpoint;
	
	findAvg(stud, count); // call to find the average test score for each students
	findGrade(stud, count); // will find the letter grade for each student
	classAvg = calcClassAvg(stud, count); // calculates the average of the class
	

	// find the total of each grade
	totalA = countLetter(stud, count, 'A');
	totalB = countLetter(stud, count, 'B');
	totalC = countLetter(stud, count, 'C');
	totalD = countLetter(stud, count, 'D');
	totalF = countLetter(stud, count, 'F');

	// creating usernames
	findUserName(stud, count);

	// --------------------outputting data below ------------------------
	cout << setw(12) << endl;
	// table goes here 
	cout << "LastName   " << "FirstName   " << "studID   " << "UserName   " << "Test1 " << "Test2 " << "Test3 " << "Test4 " << "Test5 " << "AVG " << "GRADE " << endl;
	cout << endl;
	// edit the output to be cleaner

	for (int i = 0; i < (count - 1); i++){

		cout <<stud[i].lName << "   " << stud[i].fName << "   " << stud[i].studId << "   " << stud[i].userName << "   " << stud[i].test1 << " " << stud[i].test2 << " "
			<< stud[i].test3 << " " << stud[i].test4 << " " << stud[i].test5 << " " << stud[i].avg << " " << stud[i].grade << "\n";

	}

	cout << endl;

	// the class average here

	cout << "The class average for CS 5 tests is " << classAvg << endl;

	cout << endl << endl;

	// count of each letter grade in the class

	cout << "The total number of students with an A: " << totalA << endl;
	cout << "The total number of students with an B: " << totalB << endl;
	cout << "The total number of students with an C: " << totalC << endl;
	cout << "The total number of students with an D: " << totalD << endl;
	cout << "The total number of students with an E: " << totalF << endl;

	

	cout << endl << endl;

	// sorting prompt and call here
	
	char choice;

	cout << "Please input sorting choice: A = Ascending & D = Descending: " << endl;
	cin >> choice;

	toupper(choice);

	if (choice != 'A' && choice != 'D')
		cout << "Invalid Input......." << endl;

	else
		sortScore(stud, count, choice);
	
	// searching  prompt call here
	
	cout << endl << endl;

	string user;
	int result; // what is return from the function
	do{

		cout << "Please enter the username to search For: ( enter -1 to exit) " << endl;
		cin >> user;

		// do input checking here
		if (user != "-1" && !validateInput(user)){
			
			cout << "INVALID INPUT PLEASE TRY AGAIN....." << endl;
			cout << "Please enter the username to search For: ( enter -1 to exit) " << endl;
			cin >> user;
			validateInput(user);
		}

	

		result = searchScore(stud, count, user);

		if (result == -1)
			cout << "Student NOT FOUND" << endl;

		else
			cout << "Student wiith UserName, " << stud[result].userName << " is " << stud[result].fName << " " << stud[result].lName << " who as a grade of " << stud[result].grade << endl;
		


	} while (user != "-1");
	
	cout << endl << endl;

	cout << "BYE !" << endl;
	
	inFile.close(); // closing the file
	return 0;

}

// ----------- FUNCTIONS BELOW------------------------

void findAvg(Student stud[], int count){
	
	for (int i = 0; i < count - 1; i++){
		float  total = 0;
		total = stud[i].test1 + stud[i].test2 + stud[i].test3 + stud[i].test4 + stud[i].test5;
		stud[i].avg = total / 5;


	}


}


void findGrade(Student stud[], int count){


	for (int i = 0; i < (count - 1); i++){

		if (stud[i].avg >= 90.0)
			stud[i].grade = 'A';

		else if (stud[i].avg >= 80.0 && stud[i].avg <= 89.9)
			stud[i].grade = 'B';

		else if (stud[i].avg >= 70.0 && stud[i].avg <= 79.9)
			stud[i].grade = 'C';

		else if (stud[i].avg >= 60.0 && stud[i].avg <= 69.9)
			stud[i].grade = 'D';

		else
			stud[i].grade = 'F';

	}

		

}


int countLetter(Student stu[], int count, char grade){

	int tracker = 0;

	for (int i = 0; i < (count - 1); i++){

		if (stu[i].grade == grade)
			
			
			++tracker;


	}


	return tracker;

}

float calcClassAvg(Student stu[], int count){

	float avg;
	float total = 0;
	
	for (int i = 0; i < (count - 1); i++){

		total += stu[i].avg;

	}

	avg = total / (count - 1);


	return avg;
}


void findUserName(Student stu[], int size){

	string temp1, temp2;

	for (int i = 0; i < (size - 1); i++){

	
		
		temp1 = tolower(stu[i].lName.at(0)); // gets first letter of Last Name 
		
		
		temp2 = tolower(stu[i].fName.at(0)); // gets first letter of 1st Name
		
		
		temp1.append(temp2); // places them together in temp1
		
		temp1 = temp1 + stu[i].studId; // add the id to the temp string 
		
		stu[i].userName = temp1; // places the temp string into the username

		
	}

	

}

void sortScore(Student list[], int size, char option){


	bool swap;
	Student temp;
	int count = 0;

	if (option == 'D'){ // for descending order
		do{
			swap = false;
			while (count < (size - 1)){

				if (list[count].avg < list[count + 1].avg){


					temp = list[count];
					list[count] = list[count + 1];
					list[count + 1] = temp;



					swap = true;
				}

				++count;
			}
		} while (swap);

	}
	// -----------------------------------------------------------BELOW IS ASCENDING ORDER -----------------------------------
	else if (option == 'A'){ // for Ascending order
		do{
			swap = false;
			while (count < (size - 1)){

				if (list[count].avg > list[count + 1].avg){
					// sorts grades																
					temp = list[count];													
					list[count] = list[count + 1];										
					list[count + 1] = temp;

	
					swap = true;
				}

				++count;
			}
		} while (swap);

		



	} // end of if


} // end of function


int searchScore(Student list[], int size, string user){

	int i = 0;
	int pos = -1;

	while (i < (size - 1)){

		if (user == list[i].userName){

			pos = i;
			
		}

		++i;
	}

	return pos;
}


bool validateInput(string word){ // checks if user input has 2 LOWERCASE letters and 4 digits
	
	
	
	if (isalpha(word[0]) && isalpha(word[1])){

		if (islower(word[0]) && islower(word[1])){

			if (isdigit(word[2]) && isdigit(word[3]) && isdigit(word[4]) && isdigit(word[5]))

				return true;
		}

	}


	return false ;

}