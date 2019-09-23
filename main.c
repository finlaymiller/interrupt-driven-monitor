#include "main.h"

int parseCommand(char **command)
{
	int x;
	int i;

	for(i = 0; i < NUM_ARGS; i++)
	{
		if(strcasecmp(command[0], arg_table[i].name) == 0)
		{
			x = timeHandler(command[1]);
			break;
		}
	}

	return x;
}

int main(void)
{
    char ts1[] = "Time 24:66:90.11";

	char **cmd = strToArray(ts1, " ", 2);
	int y = parseCommand(cmd);

    return 0;
}
