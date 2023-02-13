/* Class Name: COP 4338
 * Author: Tao Lin
 * Version: 09/14/2021 
 * This file contains count function and some relevant functions
 */
#include "calendar.h"
//This method gets the two date and returns the number of days between them
int count(int fromMonth, int fromDay, int fromYear, int toMonth, int toDay, int toYear) 
{    
    int totalDays;//total amount of day difference
	int daysInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};//daysInMonth array shows the total days for each month, the index refers to the month 
    
    int Date1 = (fromYear * 10000) + (fromMonth * 1000) + (fromDay);
    int Date2 = (toYear * 10000) + (toMonth * 1000) + (toDay);

    if (Date1 > Date2)//swap dates when the begin date is larger than the end date
    {
       
       int tmp1 = fromMonth, tmp2 = fromDay , tmp3 = fromYear;
	   //Swapping
       fromMonth = toMonth;
	   fromDay = toDay;
       fromYear = toYear;

       toMonth = tmp1;
	   toDay = tmp2;
       toYear = tmp3;
    }

    //If the difference between the fromYear and toYear is larger than a 1 year or more
    if(toYear > (fromYear + 1))
    {   
	int yeardiff = 0;
	yeardiff = toYear - (fromYear + 1);
        totalDays += yeardiff * 365;
        //Check if the year after fromYear is leap year
        for (int i = (fromYear + 1); i < toYear; i++) 
        {
            if (isLeapYear(i))
                totalDays++;//Leap year is 366, so totalDay should plus 1
        }
    }

    //If the difference between fromYear and toYear year is less than 1 year
    if((toYear > fromYear))
    {   
        //Calculate the left days from the next month to the end of the year
        for (int i = fromMonth + 1; i <= 12; i++)//Begins with the fromMonth+1 to December
        {
            totalDays += daysInMonth[i];
            //Check if fromYear is leap year
            if (i == 2 && isLeapYear(fromYear)) 
                totalDays++;
        }
        totalDays += daysInMonth[fromMonth] - fromDay;//The days remaining in the fromMonth

        //Calculate the total number of days from the beginning of the year to the end of the previous month
        for (int j = 1; j < toMonth; j++)//Begin with the January
        {
            totalDays += daysInMonth[j];
            if (j == 2 && isLeapYear(toYear))//Check if the month is Feb and toYear is a leap year
                totalDays++;
        }
        totalDays += toDay;//Add the days in toMonth;
    }
    else//toYear == fromYear
    {   
		//Calculate the total number of days after the fromMonth to the previous month of the toMonth
        for (int i = (fromMonth + 1); i < toMonth; i++)//Begins with the fromMonth+1 to the previous month of toMonth
        {
            totalDays += daysInMonth[i];
            //Check if the month is Feb and the current is a leap year. Note that fromYear == toYear
            if (i == 2 && isLeapYear(fromYear)) 
                totalDays++;
        }
        if (fromDay > toDay)//if the fromDay larger than toDay
        {
            //Check if the month is current is a leap year
            totalDays += (daysInMonth[fromMonth] + isLeapYear(fromYear)) - fromDay;
            totalDays += toDay;
        }
        else
        {
            if (toMonth > fromMonth)
            {
                totalDays += daysInMonth[fromMonth];
                //Check if the month is Feb and the current is a leap year
                if (fromMonth == 2 && isLeapYear(fromYear)) 
                    totalDays++;
            }
            totalDays += (toDay - fromDay);
        }
    }
    //Set the resulting amount of days to a negative number.
    if (Date1 > Date2)
	{ 
        totalDays = -1 * totalDays;
	}
    printf("The difference in days is: %d\n", totalDays);
    return 0;
}

//This method returns the month if the given month larger than 0 and less or equal than 12
int getMonth(char token[]) 
{
	int n;
	//Check if the first and the second char are both less than '0' or large than '9'
	if (token[0] < '0' || token[0] > '9' || token[1] < '0' || token[1]> '9')
		return 0;//error in retrieving the month
	n = 10 * (token[0] - '0') + token[1] - '0';
	if (n > 12)
		return 0;//error, month should be from 1 and 12...
	return n;
}

//This method returns the days in a month 
int getDay(char token[]) {
	int n;
	//Check if the first and the second char are both less than '0' or large than '9'
	if (token[0] < '0' || token[0]> '9' || token[1] < '0' || token[1]> '9')
		return 0;//error in retrieving the day
	n = 10 * (token[0] - '0') + token[1] - '0';
	if (n > 31)
		return 0;//error, the days in a month should be less or equal to 31
	return n;
}

//This method returns the year
int getYear(char token[]) 
{
	int n;
	/* Check if the first to the last char are both less than '0' 
	 * or large than '9', the year should be consist of 4 digits.
	 */
	if (token[0] < '0' || token[0]> '9' ||
		token[1] < '0' || token[1]> '9' ||
		token[2] < '0' || token[2]> '9' ||
		token[3] < '0' || token[3]> '9')
		return 0;//error in retrieving the year
	n = 1000 * (token[0] - '0') + 100 * (token[1] - '0') + 10 * 
	(token[2] - '0') + token[3] - '0';
	return n;
}

void handleCount(void) 
{
	/* Your code comes here */
	char token1[MAX_COMMAND_TOKEN_LENGTH], token2[MAX_COMMAND_TOKEN_LENGTH];
	//If the user only type the not enough command
	if (getCommandWord(token1, MAX_COMMAND_TOKEN_LENGTH) == '\n') 
	{
		printf("Too few arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n");
		return;
	} 
	//If the user input the characters larger than MAX_COMMAND_TOKEN_LENGTH = 15 print error information
	if (getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n') 
	{
		printf("Too many arguments for count command! It must be in the form of count MM/DD/YYYY mm/dd/yyyy.\n");
		while (getCommandWord(token2, MAX_COMMAND_TOKEN_LENGTH) != '\n');//infinite while loop
		return;
	}
	//If token[2] != '/' or token[5] != '/' then print then print error; The format should be MM/DD/YYYY mm/dd/yyyy
    if (!(token1[2] == '/') || !(token1[5] == '/') && !(token2[2] == '/') || !(token2[5] == '/'))
	{
        printf("Invalid format! It must be in the form of count MM/DD/YYYY mm/dd/yyyy. Please try again!\n");
	}
	else
	{   
		char fromMonth[2], fromDay[2], fromYear[4], toMonth[2], toDay[2], toYear[4];
		int MM, DD, YY, mm, dd, yy;
		for (int i = 0; i < 2; i++)
		{
			fromMonth[i] = token1[i];
			toMonth[i] = token2[i];
		}
		MM = getMonth(fromMonth);//convert char fromMonth to integer
		mm = getMonth(toMonth);//convert char toMonth to integer

		int indexOfDay = 3;//The date format is MM/DD/YYYY or mm/dd/yyyy, get day's char from token[3] to token[4]
		for (int j = 0; j < 2; j++)
		{
			fromDay[j] = token1[indexOfDay];
			toDay[j] = token2[indexOfDay];
			indexOfDay++;
		}
		DD = getDay(fromDay);//convert char fromDay to integer
		dd = getDay(toDay);//convert char toDay to integer

		int indexOfYear = 6;//The date format is MM/DD/YYYY or mm/dd/yyyy, put year's char from token[6] to token[9]
		for (int k = 0; k < 4; k++)
		{
			fromYear[k] = token1[indexOfYear];
			toYear[k] = token2[indexOfYear];
			indexOfYear++;
		}
		YY = getYear(fromYear);//convert char fromYear to integer
		yy = getYear(toYear);//convert char toYear to integer
        
		//Check if the given dates are valid
		if (isValidDate(MM, DD, YY) == 0 || isValidDate(mm, dd, yy) == 0)
		{
			printf("Invalid date! Please try again!\n");
		}
        else
		{
			printf("counting days from %s to %s\n", token1, token2);
			count(MM, DD, YY, mm, dd, yy);//Correct format count the number of days betweem two dates
		}
	}
}

//This method returns the number of days in the given month of the given year
int monthDays(int month, int year) 
{
	switch (month) {
	//If the month is Jan, Mar, May, July, Aug, Oct, Dec return 31 days
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	//If the month is Apr, June, Sep, Nov return 30 days
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	//If month is February 
	case 2:
	    //Check if the given year is leap year
		if (isLeapYear(year))
			return 29;
		else
			return 28;
	}
	return -1;//invalid month 
}

//This method checks whether the given date is valid or not
int isValidDate(int month, int day, int year) 
{
	return year >= 1 && month >= 1 && month <=12 && day >= 1 && day <= monthDays(month, year);
}

//This method checks whether the given year is leap year or not
int isLeapYear(int year) //97 leap years in every 400 years... 365 days + 97/400
{   
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);//2000, 2020, 1600, 2024, 2016,... are leap years...
	//1900, 1800, 1700, 2100, 2002, 2019,... are not leap years...
}