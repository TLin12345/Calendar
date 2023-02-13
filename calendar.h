/* Class Name: COP 4338
 * Author: Tao Lin
 * Version: 09/09/2021 
 * The calendar.h file contains function declarations and 
 * macro definitions to be shared between several source files.
 */
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_TOKEN_LENGTH 15
char getCommandWord(char command[], int maxLength);
int getMonth(char token[]);
int getDay(char token[]);
int getYear(char token[]);
int monthDays(int month, int year);
int isValidDate(int month, int day, int year);
void handleCount(void);
int count(int fromMonth, int fromDay, int fromYear, int toMonth, int toDay, int toYear);
void handlePrint(void);
int isLeapYear(int year);
int get_1st_WeekDay(int month, int day, int year);