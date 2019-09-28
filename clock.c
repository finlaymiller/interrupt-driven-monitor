/*
 * clock.c
 *
 *  Created on: Sep 27, 2019
 *      Author: finlay
 */

int main_clock;			// timing for main TIME command-related clock
int alrm_clock;			// timing for ALARM command-related clock
int alrm_clock_state;	// state of ALARM clock.
						// TRUE = running, FALSE = not running

/*
 * Initialize all clock settings. All times are set to 0
 * and alarm clock is stopped
 *
 * @param: None
 * @return: None
 */
void initClocks(void)
{
	main_clock 			= 0;
	alrm_clock 			= 0;
	alrm_clock_state 	= FALSE;
}
