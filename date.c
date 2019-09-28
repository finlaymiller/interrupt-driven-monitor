#include "date.h"

void dateHandler(char *arg)
{
    if(arg == NULL)
    {
        // TODO: print current date
    }
    else
    {
        //TODO: update SysTick
        // isolate date components
        char **date_to_set = strToArray(arg, "-", NUM_DATE_ELEMS);

        // setup date structure
        date_ptr d_ptr = dateInit();
        dateSet(d_ptr, date_to_set);
        datePrint(d_ptr);
    }
}

int monthCheck(char *month)
{
	int i;
	int month_found = FALSE;
	char *month_list[NUM_MONTHS] =
	{
		"Jan", "Feb", "Mar", "Apr",
		"May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec"
	};

	for (i = 0; i < NUM_MONTHS; i++)
	{
		if(!strcmp(month, month_list[i]))
			month_found = TRUE;
	}

	return month_found;
}

date_ptr dateInit(void)
{
	date_ptr date = (date_ptr)malloc(sizeof(date_struct));
	date->day = 1;
	strcpy(date->month, "Jan");
	date->year = 1970;

	return date;
}

void dateSet(date_ptr date, char **date_str)
{
	// TODO: 	catch wrong array length
	//			account for months with different # of days
	int date_d 	 = atoi(date_str[0]);
	char *date_m = date_str[1];
	int date_y   = atoi(date_str[2]);

	date->day 	= date_d;
	strcpy(date->month, date_m);
	date->year 	= date_y;

	if ((date_d < 1) || (date_d > 31))
	{
		printf("Invalid number of days in month entered");
		datePrint(date);
	}
	else if (!monthCheck(date->month))
	{
		printf("Invalid month string entered");
	}
	else if (date_y < 1)
	{
		printf("Invalid year entered");
	}
	
	datePrint(date);

	return;
}

void datePrint(date_ptr date)
{
	printf("\nPrinting date:\t\t");
	printf("DD-MM-YYYY ---> %02d:%s:%d", date->day, date->month, date->year);
}
