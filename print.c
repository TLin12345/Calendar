/* Class Name: COP 4338
 * Author: Tao Lin
 * Version: 09/14/2021 
 * This file contains a print function that prints a table showing the days of agiven month in a given year
 */
#include "calendar.h"

//This method is used to print the calendar for the given month and year
void print(int month, int year) 
{
	/* Your code comes here */
	int firstDay = get_1st_WeekDay(month, 1, year);//The first day of the week in the current month
	int day;//The day present in a month
	int dayInMonth;//The total days in a monthd
	dayInMonth = monthDays(month, year);//The amount of days in the chosen month and year
	int weekday;//Current weekday
    
	printf("\n------------%d/%d-----------\n", month, year);
	printf("\n  Su  Mo  Tu  We  Th  Fr  Sa\n");
        //The first few days of the first week of each month are represented by spaces
	for (weekday = 0; weekday < firstDay; weekday++)
	{
	    printf("    ");
	}
        //From the first to the end of each month
	for (day = 1; day <= dayInMonth; day++)
	{   
		//If the chosen year is leap year
		if (isLeapYear(year) && month == 2)
			dayInMonth = 29;
		printf("%4d", day);
		//Turn to the next line after reach each Saturday of the month
		if(++weekday > 6)
		{   
			printf("\n");
			weekday = 0;
		}	
	}	
	printf("\n-----------------------------\n");
}

void handlePrint(void) 
{
	/* Your code comes here */
	char token[MAX_COMMAND_TOKEN_LENGTH];
	//If the user input the characters larger than MAX_COMMAND_TOKEN_LENGTH = 15 print error information
	if (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n')//new input getCommand until the space
	{   
		printf("Too many arguments for print command! It must be in the form of print MM/YYYY.\n");
		while (getCommandWord(token, MAX_COMMAND_TOKEN_LENGTH) != '\n');//infinite while loop
		return;
	}
	if (!(token[2] == '/'))//The token[2] != '/' that is different with the format of MM/YYYY, then print error
	{
		printf("Invalid format! It must be in the form of print MM/YYYY. Please try again! \n");
	}
	else
	{
        char month[2], year[4];
		int m, y;
		for (int i = 0; i < 2; i++)
		{
			month[i] = token[i];
		}
		m = getMonth(month);//convert char month to integer month, call funtion getMonth()
		int index = 3;//The format is MM/YYYY, get year's char from token[3] to token[6]
		for (int j = 0; j < 4; j++)
		{
			year[j] = token[index];
			index++;
		}
        y = getYear(year);//convert char year to integer year, call function getYear()

        //Checking if the input date is valid
	    if ((m < 1) || (m > 12) || (y < 1))
	    {
		    printf("Invalid Date! Please try again!\n");
	    }
	    else
	    {
		    printf("Printing the weeks of month %s\n", token);
		    print(m, y);//Correct format then print the given month and year calendar
	    }
	}
}

//This method calculates the day of the week on the first day of the month
int get_1st_WeekDay(int month, int day, int year)
{
	for (int i = 1; i < month; i++)
	{   
		//If month is 1, 3, 5, 7, 8, 10, 12
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
		    day += 31;
		else if (i == 2)//If month is 2
		{
			if(isLeapYear(year))
			   day += 29;
			else
			   day += 28;
		}
		else//The rest of months
		    day += 30;
	}
	int temp = ((year - 1) + ((year - 1) / 4) - ((year - 1) / 100) + ((year - 1) / 400) + day) % 7;
	return temp;
}
