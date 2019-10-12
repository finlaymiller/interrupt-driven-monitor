/*
 * 	date.c
 *
 *  Created on: Sep 20, 2019
 * Modified on:	Oct 05, 2019
 *      Author: Finlay Miller
 *
 *	Contains date command-related functions including set, clear, print, and
 *	others. More detail on the alarm function can be found in the design docs
 *	and in the program description at the beginning of main.c. Note that alarm
 *	data is stored in the global SysTick struct described in systick.c
 *
 */

#include "date.h"

/* globals */
extern Monitor monitor;
const char *month_list[NUM_MONTHS] =	// list of supported months
{
 	 "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
	 "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};
const char day_list[2][NUM_MONTHS] =	// list of number of days in each month
{
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},	// non-leap-years
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}	// leap-years
};


/*
 * This function is called when a date command is entered. If a date is
 * provided following the format described in main.c the date is set to that
 * date. If no argument is provided the date is printed.
 *
 * @param arg:	Argument provided by user, NULL if none is provided.
 * @returns:	TRUE if command execution was a success, FALSE otherwise
 *
 */
int dateHandler(char *arg)
{
	char *date_to_set[NUM_DATE_ELEMS];
	unsigned int i = 0;

    if(arg)
    {
        // isolate date components
		date_to_set[i] = strtok(arg, "-");
		while(date_to_set[i] != NULL)
				date_to_set[++i] = strtok(NULL, "-");

        // setup date structure
        if(!dateSet(date_to_set))
        	return FALSE;
    }

    datePrint();

    return TRUE;
}

/*
 * This function checks the validity of the entered date.
 * Day must be between 1 and the corresponding value in the global day list
 * table.
 * Month must correspond to a month from the global month list table.
 * Year must be between 0 and
 *
 * @param day, month, year:	Tokenized and converted arguments
 * @returns:	1 if all dates are valid, 0 if any date is invalid
 */
int dateCheck(int day, char *month, int year)
{
	unsigned int i, valid_day = FALSE, valid_month = FALSE, valid_year = FALSE;
	// row of day_list to use. 0 if not a leap year, 1 if a leap year.
	unsigned int leap_index = IS_LEAP_YEAR(year);

	valid_year = (0 <= year) && (year < 10000);		// year check

	for(i = 0; i <= NUM_MONTHS; i++)
	{
		if(!(strncmp(month, month_list[i], MONTH_LEN)))
		{
			valid_month = TRUE;		// if we get here month is valid
			// day check
			valid_day = (day > 0) && (day <= day_list[leap_index][i]);

			break;
		}
	}

	return (valid_day && valid_month && valid_year);
}

/*
 * Initialize date structure to October 1st, 2019
 *
 * @param:		None
 * @returns:	None
 */
void dateInit(void)
{
	monitor.date.day 	= 1;
	monitor.date.month	= 9;
	monitor.date.year 	= 2019;
}

/*
 * Set system date struct to the user-provided date
 *
 * @param date_str:	tokenized argument string
 * @returns:		TRUE on success, FALSE on failure
 */
static int dateSet(char **date_str)
{
	//sys_date *dptr = &date;
	char month[MONTH_LEN + 1];	// +1 to account for '\0'
	unsigned int date_d, date_m, date_y, day, year;
	unsigned int i = 0;

	/* extract day, month, and year portions of argument */
	if(!(my_atoi(date_str[0], (int *)&day)
			&& my_atoi(date_str[2], (int *)&year)))
		return FALSE;

	while(date_str[1][i] != '\0')
	{	// convert month to upper case
		month[i] = toupper((unsigned char) date_str[1][i]);
		i++;
	}

	// check validity of date elements now that they're isolated and converted
	if(!dateCheck(day, month, year))
		return FALSE;

	/* date is valid! Now we can send them to the structure */
	date_d = day;
	date_y = year;

	for(i = 0; i <= NUM_MONTHS; i++)
	{
		if(!strcmp(month, month_list[i]))
		{
			date_m = i;
			break;
		}
	}

	monitor.date.day 	= date_d;
	monitor.date.month	= date_m;
	monitor.date.year 	= date_y;

	return TRUE;
}

/*
 * Handle date incrementing and rollover
 *
 * @param: 		None
 * @returns:	None
 */
void dateIncrement(void)
{
	//sys_date *dptr = &date;
	unsigned int leap_year = IS_LEAP_YEAR(monitor.date.year);

	monitor.date.day++;

	if(monitor.date.day > day_list[leap_year][monitor.date.month])
	{
		monitor.date.day = 1;
		monitor.date.month++;
	}
	if(monitor.date.month >= 12)
	{
		monitor.date.month = 0;
		monitor.date.year++;
	}
	if(monitor.date.year >= 10000)
	{
		monitor.date.year = 0;
	}
}

/*
 * This function prints the current date.
 * If you know a more efficient/practical/pretty way of doing the actual
 * date-to-string conversion for printing I would love to know how! I tried
 * many things and this was the best I could come up with.
 *
 * @param	None
 * @returns	None
 */
static void datePrint(void)
{
	//sys_date *dptr = &date;
	char date_string[32] = {0};
	int year = monitor.date.year;
	int div = 1000;
	unsigned int i = 0;

	date_string[i++] = (monitor.date.day / 10) + '0';
	date_string[i++] = (monitor.date.day % 10) + '0';
	date_string[i++] = '-';
	date_string[i++] = month_list[monitor.date.month][0];
	date_string[i++] = month_list[monitor.date.month][1];
	date_string[i++] = month_list[monitor.date.month][2];
	date_string[i++] = '-';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = '\0';

	UART0_TXStr("Date is ");
	UART0_TXStr(date_string);
}

/*
 * This is a simple function to help the datePrint function correctly print the
 * year.
 *
 * @param:	year:	The year to be printed
 * @param:	pos:	The position of the digit to print
 * @returns:		The digit at that position
 */
int getNumDigit(int *year, int *pos)
{
	int digit = *year / *pos;

	*year %= *pos;
	*pos /= 10;

	return digit;
}
