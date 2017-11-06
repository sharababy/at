#include <stdio.h>
#include <stdlib.h>

/*	

	initial state : 0  
	0 -> i -> 1 -> n -> 2 -> t -> -1
	
	0 -f-> 3 -l-> 4 -o-> 5 -a-> 6 -t-> -2

	Legal Types: 
	int float double char 
	-1   -2     -3    -4
	if data type found , state = -1
*/

int state;

int main(int argc, char const *argv[])
{
	FILE* in;
	char e;

	char vInt[] = "int";

	int variables[] = {0,0,0,0};

	state = 0;

	in = fopen(argv[1] , "r+");

	while( fread(&e , 1 , 1 , in) == 1){

		if (state >= 0)
		{
			
			if (e == 'i')
			{
				if (state == 0)
				{
					state = 1;
				}
			}

			else if (e == 'n')
			{
				if (state == 1)
				{
					state = 2;
				}
			}

			else if (e == 't')
			{
				if (state == 2)
				{
					state = -1;
				}
			}

		}
		else if (state == -1)
		{
			if (e == ' ')
			{
				continue;	
			}
			else if (e == ',')
			{
				variables[0]++;
			}
			else if (e == ';')
			{
				variables[0]++;
				state = 0;
			}

		}

	}

	printf("Number of Ints: %d\n", variables[0]);

	fclose(in);

	return 0;
}