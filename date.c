#include "date.h"

static date_struct date;

void dateHandler(char *arg)
{
	// three parts to date: day, month, year
	char *date_to_set[3];
	int i = 0;

    if(arg)
    {
        // isolate date components
		date_to_set[i] = strtok(arg, "-");
		while(date_to_set[i] != NULL)
				date_to_set[++i] = strtok(NULL, "-");

        // setup date structure
        dateSet(date_to_set);
    }

    datePrint();
}

int dateCheck(int day, char *month, int year)
{
	int i;
	// incremented each time a section of the date is confirmed to be correct
	// date is only written to global struct if this function returns a 3
	int valid_date = 0;
	// row of day_list to use. 0 if not a leap year, 1 if a leap year.
	int leap_index = 0;
	char *month_list[NUM_MONTHS] =
	{
		"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
		"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
	};

	char day_list[2][NUM_MONTHS] =
	{
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},	// non-leap-year
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}	// leap-year days
	};

	// year check
	if(0 < year < 10000)
		valid_date++;

	for (i = 0; i < NUM_MONTHS; i++)
	{
		// month check
		if(!strncmp(month, month_list[i], MONTH_LEN))
		{
			valid_date++;

			// leap year check
			if(!(year % 4))
				leap_index = 1;

			// day check
			if(day <= day_list[leap_index][i])
				valid_date++;

			break;
		}
	}

	return valid_date;
}

void dateInit(void)
{
	date_struct *dptr = &date;

	dptr->day = 1;
	strcpy(dptr->month, "Jan");
	dptr->year = 1970;
}

void dateSet(char **date_str)
{
	// TODO: 	catch wrong array length
	date_struct *dptr = &date;
	int date_d 	 = atoi(date_str[0]);
	char date_m[MONTH_LEN + 1];			// +1 to account for \0
	int date_y   = atoi(date_str[2]);
	int i;

	// convert month to lower case
	 for(i = 0; date_str[1][i]; i++)
	   date_m[i] = toupper(date_str[1][i]);
	// check validity of input date
	// ideally I'd check for cases where dateCheck returns > 3...
	if(dateCheck(date_d, date_m, date_y) < NUM_DATE_ELEMS)
	{
		enQ(UART_TX, '?');
		return;
	}
	
	dptr->day 	= date_d;
	strcpy(dptr->month, date_m);
	dptr->year 	= date_y;
}

void datePrint(void)
{
	date_struct *dptr = &date;
	char year[4];

	itoa(dptr->year, year, 10);

	enQ(UART_TX, KEY_ENTER);
	enQ(UART_TX, (dptr->day / 10) + '0');
	enQ(UART_TX, (dptr->day % 10) + '0');
	enQ(UART_TX, '-');
	enQ(UART_TX, dptr->month[0]);
	enQ(UART_TX, dptr->month[1]);
	enQ(UART_TX, dptr->month[2]);
	enQ(UART_TX, '-');
	enQ(UART_TX, year[0]);
	enQ(UART_TX, year[1]);
	enQ(UART_TX, year[2]);
	enQ(UART_TX, year[3]);
}


/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

