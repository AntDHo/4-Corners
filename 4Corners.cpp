// Name:						Anthony Ho
// Class:						CSC 413
// Teacher:						Dr. Byrant Walley
// Project:						Project 2 Binary Matrix, Square and Rectangle coordinates locate
// Date:						4/19/2017
// Resubmit:					4/28/2017
// Purpose:						Purpose of the project is to learn to traverse a multi dimensional array
//								and locating 4 coordinates that form a square or rectangle and outputting
//								the data onto a text file.
//								Purpose of this program is to take the user's entered values for the rows "n"
//								and columns "m" so it would be  "N x M". After you get the values, you create
//								matrixes of those width and height and then fill the matrix with 1s and 0s
//								using rand function. After filling the matrix you will out put it to a text file
//								called "matrix.txt" and close it. Then you will open it and process the data
//								into a new matrix in which you will do calculations and traversing to find
//								0 coordinates that form squares and rectangles then output the coordinate 
//								location onto a text file called "corners.txt". 
// User Logic/ Algorithm:		4 loops, first 2 loops will find p1 and p2 which are the upper 2 points 
//								then if both are found, a variable valid1 and valid2 will be equaled to 1
//								so that it allows the program to move on to the next 2 points, p3 and p4,	
//								which are the bottom points. So basically once p3 and p4 are found
//								the points will be tested to see if a square or rectangle. p3 and p4 will
//								constantly change and get tested with the original p1 and 2 points until
//								you hit the limits of both rows and columns, then p1 and p2 will increment
//								to the next set of 0s found and the process repeats again for p3 and p4


#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <sstream>

using namespace std;

struct point // holds the x and y cordinates per points
{
	int x, y; 
} p1, p2, p3, p4;

void display();
void create(int n, int m);
void option(int n, int m); 

int aOrthogonal(point a, point b, point c)// calculate 
{
	return (b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0;
}

int aRec(point a, point b, point c, point d)// testing to see if a rectangle
{
	return
		aOrthogonal(a, b, c) &&
		aOrthogonal(b, c, d) &&
		aOrthogonal(c, d, a);
}

int randRectangle(point a, point b, point c, point d)// if random order of points
{
	return aRec(a, b, c, d) ||
		   aRec(b, c, a, d) ||
		   aRec(c, a, b, d);
}



int dSQR(point a, point b) // distance square, calculate distance between points
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

bool aSQR(point p1, point p2, point p3, point p4) // is it a square
{
	int d2 = dSQR(p1, p2);  // p1 to p2, calling in function to check distance between points
	int d3 = dSQR(p1, p3);  // p1 to p3
	int d4 = dSQR(p1, p4);  // p1 to p4

	if (d2 == d3 && 2 * d2 == d4)// if d2 and d3 are the same, d4 is twice the value of d2
	{
		int d = dSQR(p2, p4);
		return (d == dSQR(p3, p4) && d == d2);
	}

	// The below two cases are similar to above case
	if (d3 == d4 && 2 * d3 == d2)
	{
		int d = dSQR(p2, p3);
		return (d == dSQR(p2, p4) && d == d3);
	}
	if (d2 == d4 && 2 * d2 == d3)
	{
		int d = dSQR(p2, p3);
		return (d == dSQR(p3, p4) && d == d2);
	}

	return false;
}


int main()
{

	display();

	int ans = 0;// variable to choose options
	int row = 0;// my row value
	int col = 0; // my column value
	int bop1 = 0; // i use this to make sure user has entered required data before proceeding
	int bop2 = 0; // same for bop1
	int boop = 0; // i use this to keep while loops going, value will be changed once data is satisfied to leave the loop
	int boop2 = 0; // same for boop
	while (1)
	{
		cout << "Which option will you choose: ";
		cin >> ans;

		while (cin.fail()) // My error checking, makes sure user inputs an integer
		{
			cout << "Error not a number, enter a number: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> ans;
		}

		if (ans == 1) // option 1
		{
			
				while (boop == 0)// keep loop going until data is satisfied
				{
					cout << "Enter row size that is between 10 and 50. "; // obtain row value
					cin >> row;

					while (cin.fail()) // My error checking, makes sure user inputs an integer
					{
						cout << "Error not a number, enter a number: ";
						cin.clear();
						cin.ignore(256, '\n');
						cin >> row;
					}

					if (row < 10 || row > 50)// error is incoorec value
						cout << "Wrong value, try again. " << endl;

					if (row >= 10 && row <= 50)// if user enters correct info, boop increments to leave while loop
					{
						boop++;
						cout << "Row size has been recorded. " << endl;
					}
				}
			
				while (boop2 == 0) // keep loop going until data is satisfied
				{
					cout << "Enter column size that is between 10 and 80. "; // obtain column value
					cin >> col;

					while (cin.fail()) // My error checking, makes sure user inputs an integer
					{
						cout << "Error not a number, enter a number: ";
						cin.clear();
						cin.ignore(256, '\n');
						cin >> col;
					}

					if (col < 10 || col > 80)// error if incorrect value
						cout << "Wrong value, try again. " << endl;

					if (col >= 10 && col <= 80) // increment boop2 if value is satisfied
					{
						boop2++;
						cout << "Column size has been recorded. " << endl;
					}
				}
				bop1 = 1;// use this to make sure user has entered correct row and column values before proceeding to next option
		}

		if (ans == 2) //option 2
		{
			if (bop1 == 1)// checks to see if option 1 has been satisified
			{
				create(row, col);// create/write to file function call
				bop2 = 1;//used to check if option 2 is satisified to proceed to option 3
			}

			else// if option 1 is not satisfied, option 2 will not work.
				cout << "You have to enter a column and row size to create matrix and write it to a file. " << endl;
		}


		if (ans == 3)// option 3
		{
			if (bop1 == 1 && bop2 == 1)// makes sure option 1 and 2 have been satisified
			{
				option(row, col);// process the file function call

			}

			else// will not work if option 1 and 2 is not satisified
				cout << "You must have done option 1, 2 and 3 in that order to process the file. ";

		}

		if (ans < 0 || ans >= 4)// make sure user stays in range of available options
			cout << "Option choice is invalid, try again: " << endl;

	}

	//delete[] matrix;
	//delete[] matrix2;
	system("PAUSE");
	return 0; 

}

void display()// display screen/ menu 
{
	cout << "Hello this is a program that will take in a values to create a matrix and process it." << endl;
	cout << "After creating the matrix, you have the a couple other options to choose from." << endl;
	cout << "Option 1: Obtain row and column sizes. " << endl;
	cout << "Option 2: Create a matrix with provided values which will be made up of binary numbers(1, 0), and output to a text file" << endl;
	cout << "Option 3: You will process the created text file (matrix.txt) in which it will be opened and ";
	cout << "it's contents will be outputted into a new matrix then processed for squares and rectangles.";
	cout << "After the matrix has been processed, all coordinate corners of squares and rectangles will be";
	cout << "outputted to a text file called (corners.txt). " << endl;
}

void create(int n, int m)
{
	//create matrix multi array
	int **matrix = new int*[n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[m];
	}

	ofstream outFile; // open/create file
	outFile.open("matrix.txt");

	//fill matrix with 1s and 0s and write to file
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matrix[i][j] = rand() % 2;
			outFile << matrix[i][j] << " ";
		}
		outFile << endl;
	}
	outFile.close(); // close the file
	
	cout << '\n' << "Random binary matrix has been created and outputted to text file (matrix.txt). " << endl;

	delete[] matrix; // delete for safety

}

void option(int n, int m)
{
	int **matrix2 = new int*[n];// created second array, so data can be read into it
	for (int i = 0; i < n; i++)
	{
		matrix2[i] = new int[m];
	}

	int **matrix3 = new int*[n];// created third array, so data can be read into it
	for (int i = 0; i < n; i++)
	{
		matrix3[i] = new int[m];
	}

	ifstream inFile; // needed to open a text file

	inFile.open("matrix.txt"); // open created file

	for (int i = 0; i < n; i++) // reading from file into different array
	{
		for (int j = 0; j < m; j++)
		{
			inFile >> matrix2[i][j]; // reading into the matrix from file

			cout << matrix2[i][j] << " ";// for me to see, visual aspect
		}
		cout << endl; // for me to see
	}

	inFile.close();

	ofstream outFile;
	outFile.open("corners.txt");	

	int valid1 = 0;
	int valid2 = 0;
	int valid3 = 0;
	int valid4 = 0;
	

	for (int i = 0; i < n; i++) // out loop 1 rows
	{
		for (int j = 0; j < m; j++) // out loop 2 columns
		{
			if (matrix2[i][j] == 0 && valid1 == 0)// find p1 and if 0, store it, make valid1 = 1 to move onto next point
			{
				p1 = { i, j };
				valid1 = 1;		
				j++;// increment j so that same value won't move onto p2
			}
			if (matrix2[i][j] == 0 && valid1 == 1)// find p2 and if 0, store it, make valid2 = 1 to move onto bottom points
			{
				p2 = { i , j };
				valid2 = 1;
				
			}
			if (valid1 == 1 && valid2 == 1)// check to see if p1 and p2 were found
			{
				for (int ii = i + 1; ii < n; ii++) //loop 3, rows, the subrow
				{
					for (int jj = 0; jj < m; jj++) // loop 4, columns
					{
						if (matrix2[ii][jj] == 0 && valid3 == 0)// find p3, if 0, store it, increment jj++ so value won't move into p4, valid3 gets = 1
						{
							p3 = { ii, jj };
							valid3 = 1;
							jj++;
						}
						if (matrix2[ii][jj] == 0 && valid3 == 1)// find p4, if 0, store it, valid4 = 1
						{
							p4 = { ii, jj};
							valid4 = 1;
						}

						if (valid3 == 1 && valid4 == 1)// check if p3 and p4 were found, then test the points
						{
							if (aSQR(p1, p2, p3, p4) == true)// if a square, output coordinates corners.txt
							{
								outFile << "(" << p1.x << "," << p1.y << "), "
									<< " (" << p2.x << "," << p2.y << "), "
									<< " (" << p3.x << "," << p3.y << "), "
									<< " (" << p4.x << "," << p4.y << ")" << endl;
							}
							if(randRectangle(p1, p2, p3, p4) == true)// if is a rectangle, output to corners
							{
								outFile << "(" << p1.x << "," << p1.y << "), "
									<< " (" << p2.x << "," << p2.y << "), "
									<< " (" << p3.x << "," << p3.y << "), "
									<< " (" << p4.x << "," << p4.y << ")" << endl;
							}

							valid3 = 0;//both valid 3 and 4 get put back to 0 for retesting other points
							valid4 = 0;
						}
					}// loop 4 end
						
				}// loop 3   end

				valid1 = 0;// valid 1 and 2 get set to 0 for retesting of other points
				valid2 = 0;
			}
		}// out loop 2 end


	}// out loop 1 end
	
         
	delete[] matrix2; // delete for safety
	outFile.close(); // close the file
} // end of function