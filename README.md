# Calendar
In this program, it contains two functionalities: First, it outputs the weeks of a 
Gregorian month given a year number and month name. Another functionality of this 
program is that it should be able to count the number of days between two dates; 
e.g. given the dates “01/06/2021 01/12/2021”, the program should prints 6 on the 
creen; while for input “01/12/2021 01/06/2021”, the program will print -6 on the screen.

Program Input Commands:
1. There are two valid commands in this program: “count MM/DD/YYYY mm/dd/yyyy”
and “print MM/YYYY” where mm and MM represent months, dd and DD represent days,
and yyyy and YYYY represent years. If an invalid command is entered, the program 
should print an error message.
2. This program have the following three functions in separate files:
a. int main(). The main function which must be stored in calendar.c file.
b. int count(int MM, int DD, int YYYY, int mm, int dd, int yyyy). The count function gets 
two dates and returns the number of days between them. This function will be stored in 
count.c file.
c. void print(int MM, int YYYY). The print function prints a table showing the days of a
given month in a given year. This function must be stored in print.c file.
