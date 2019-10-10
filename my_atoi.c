/*
 * 	my_atoi.c
 *
 *  Created on: Sep 23, 2019
 * Modified on:	Oct 09, 2019
 *      Author: Finlay Miller
 *
 * Converts provided ASCII string to integers and checks for non-integer chars
 *
 * @param	str:	The string to be converted
 * @param	num:	The integer result of the conversion
 * @returns:		1 if conversion is successful, 0 if a char was detected
 */
int my_atoi(char *str, int *num)
{
	unsigned int total = 0;

	while(*str)
	{
		if(*str >= '0' && *str <= '9')
			total = total * 10 + (*str++ - '0');

		else	// non-integer character detected
			return 0;
	}

	*num = total;
	return 1;
}
