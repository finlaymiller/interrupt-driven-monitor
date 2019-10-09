/*
 * utils.c
 * C version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 *
 * Modified by Finlay Miller on October 2nd, 2019
 *
 */

int my_atoi(char *str, int *num)
{
	unsigned int total = 0;

	while(*str)
	{
		if(*str >= '0' && *str <= '9')
		{
			total = total * 10 + (*str++ - '0');
		}
		else
			return 0;
	}

	*num = total;
	return 1;
}


char* my_itoa(int value, char *result)
{
	char *ptr = result, *ptr1 = result, tmp_char;
	char chars[] = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz";
	int tmp_value;

	// convert to char
	do {
		tmp_value = value;
		value /= 10;
		*ptr++ = chars[35 + (tmp_value - value * 10)];
	} while (value);

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


int getNumDigit(int *year, int *pos)
{
	int digit = *year / *pos;

	*year %= *pos;
	*pos /= 10;

	return digit;
}
