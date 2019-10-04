/*
 *
 * todo: factorize integer->string for month and vice-versa
 */

#include "date.h"

static date_struct date;

const char *month_list[NUM_MONTHS + 1] =
{
 	 "ERR", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
	 "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
};

const char day_list[2][NUM_MONTHS] =
{
	{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},	// non-leap-year
	{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}	// leap-year days
};

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
	int leap_index = IS_LEAP_YEAR(year);

	// year check
	if((0 < year) && (year < 10000))
		valid_date++;

	for(i = 0; i <= NUM_MONTHS; i++)
	{
		if(!(strncmp(month, month_list[i], MONTH_LEN)))
		{
			// valid month found
			valid_date++;

			// day check
			// second day_list index is i + 1 to account for month 0 = ERR
			if((day > 0) && (day <= day_list[leap_index][i + 1]))
				valid_date++;

			break;
		}
	}

	return valid_date;
}

void dateInit(void)
{
	date_struct *dptr = &date;

	dptr->day 	= 1;
	dptr->month	= 1;
	dptr->year 	= 1;
}

void dateSet(char **date_str)
{
	// TODO: 	catch wrong array length
	date_struct *dptr = &date;
	int date_d, date_m, date_y;
	int i = 0;

	int day 	= atoi(date_str[0]);
	char month[MONTH_LEN + 1];	// to account for '\0'
	int year	= atoi(date_str[2]);

	// convert month to upper case
	while(date_str[1][i] != '\0')
	{
		month[i] = toupper((unsigned char) date_str[1][i]);
		i++;
	}


	// check validity of input date
	// ideally I'd check for cases where dateCheck returns > 3...
	if(dateCheck(day, month, year) < NUM_DATE_ELEMS)
	{
		UART0_TXChar('?');
		return;
	}

	// dates are valid! Now we can send them to the structure
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
	
	dptr->day 	= date_d;
	dptr->month	= date_m;
	dptr->year 	= date_y;
}

void dateIncrement(void)
{
	date_struct *dptr = &date;
	int leap_year = (dptr->year % 4) ? 1 : 0;

	dptr->day++;

	if(dptr->day > day_list[leap_year][dptr->month])
	{
		dptr->day = 1;
		dptr->month++;
	}
	if(dptr->month >= 12)
	{
		dptr->month = 0;
		dptr->year++;
	}

}

void datePrint(void)
{
	date_struct *dptr = &date;
	char date_string[32] = {0};
	int year = dptr->year;
	int div = 1000;
	int i = 0;

	date_string[i++] = (dptr->day / 10) + '0';
	date_string[i++] = (dptr->day % 10) + '0';
	date_string[i++] = '-';
	date_string[i++] = month_list[dptr->month][0];
	date_string[i++] = month_list[dptr->month][1];
	date_string[i++] = month_list[dptr->month][2];
	date_string[i++] = '-';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = getNumDigit(&year, &div) + '0';
	date_string[i++] = '\0';

	UART0_TXStr("Date is ");
	UART0_TXStr(date_string);
}

int getNumDigit(int *year, int *pos)
{
	int digit = *year / *pos;

	*year %= *pos;
	*pos /= 10;

	return digit;
}

/*
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 *
 */
char* itoa(int value, char* result) {

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= 10;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * 10)];
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

