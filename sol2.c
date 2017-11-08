#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*	

	initial state : 0  
	0 -> i -> 1 -> n -> 2 -> t -> 101 - -> -1
	
	0 -f-> 3 -l-> 4 -o-> 5 -a-> 6 -t-> 102 - -> -2

	0 -d-> 7 -o-> 8 -u-> 9 -b-> 10 -l-> 11 -e-> 103 - -> -3

	0 -c-> 12 -h-> 13 -a-> 14 -r-> 104 - -> -4

	state for " => 200
	state for ' => 201

	state for / => 300

	Legal Types: 
	int float double char 
	-1   -2     -3    -4
	if data type found , state = -1
*/

int state,semi;

int main(int argc, char const *argv[])
{
	FILE* in;
	char e;

	int variables[] = {0,0,0,0,0};

	state = 0;
	semi  = 0;

	printf("\n==== Legal Identifiers ==== \n\n");



	in = fopen(argv[1] , "r+");

	while( fread(&e , 1 , 1 , in) == 1){

		if (state >= 0 && state <  200)
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
					state = 101;
				}
				else if (state == 6)
				{
					state = 102;
				}
			}

			else if (e == 'f')
			{
				if (state == 0)
				{
					state = 3;
				}
			}

			else if (e == 'l')
			{
				if (state == 3)
				{
					state = 4;
				}
				else if (state == 10)
				{
					state = 11;
				}
			}

			else if (e == 'o')
			{
				if (state == 4)
				{
					state = 5;
				}
				else if (state == 7)
				{
					state = 8;
				}
			}
			else if (e == 'a')
			{
				if (state == 5)
				{
					state = 6;
				}
				else if (state == 13)
				{
					state = 14;
				}
			}

			else if (e == 'd')
			{
				if (state == 0)
				{
					state = 7;
				}
			}
			
			//0 -d-> 7 -o-> 8 -u-> 9 -b-> 10 -l-> 11 -e-> -3

			else if (e == 'u')
			{
				if (state == 8)
				{
					state = 9;
				}
			}
			else if (e == 'b')
			{
				if (state == 9)
				{
					state = 10;
				}
			}
			else if (e == 'e')
			{
				if (state == 11)
				{
					state = 103;
				}
			}

			//0 -c-> 12 -h-> 13 -a-> 14 -r-> -4

			else if (e == 'c')
			{
				if (state == 0)
				{
					state = 12;
				}
			}

			else if (e == 'h')
			{
				if (state == 12)
				{
					state = 13;
				}
			}

			else if (e == 'r')
			{
				if (state == 14)
				{
					state = 104;
				}
			}

			else if (e == ' ')
			{
				if (state == 101)
				{
					state = -1;
				}
				else if (state == 102)
				{
					state = -2;
				}
				else if (state == 103)
				{
					state = -3;
				}
				else if (state == 104)
				{
					state = -4;
				}
			}
			else if (e == '\"')
			{
				state = 200;
			}
			else if (e == '/')
			{
				if (state != 299)
				{
					state = 299;
				}
				else if (state == 299)
				{
					state = 300;
				}
				
			}
			else{
				state = 0;
			}

		}
		else if(state == 200){

			if (e == '\"')
			{
				state = 0;
			}
		}
		else if(state == 300){

			if (e == '\n')
			{
				state = 0;
			}
		}
		else if (state < 0)
		{
			if (e == ' ' && semi == 0)
			{
				continue;	
			}
			else if (e == ' ' && ( semi == 1 || semi == 3))
			{
				semi = 3;
			}
			else if (e == '(')
			{
				variables[4]++;
				state = 0;
				printf("\tfunction");
				printf("\n");
			}
			else if ( (e == ',' || e == ';') && ( semi == 1 || semi == 3))
			{	
				if (state == -1)
				{
					variables[0]++;	
					printf("\tint");
				}
				else if (state == -2)
				{
					variables[1]++;	
					printf("\tfloat");
				}
				else if (state == -3)
				{
					variables[2]++;	
					printf("\tdouble");
				}
				else if (state == -4)
				{
					variables[3]++;	
					printf("\tchar");
				}
				
				if ( e == ';' )
				{
					state = 0;
					
				}
				if ( e == ',' )
				{
					semi = 0;
				}

				printf("\n");
				
			}
			else if( ( ( e >= 65 && e <= 90 ) || ( e >= 97 && e <= 122 ) || e == '_') && semi == 0 ){

				semi = 1;
			}
			// else if( ( ( e >= 48 && e <= 57 ) || ( e >= 65 && e <= 90 ) || ( e >= 97 && e <= 122 ) || e == '_') && semi == 1 ){

			// 	semi = 1;
			// }
			else if( ( ( e >= 48 && e <= 57 ) || ( e >= 65 && e <= 90 ) || ( e >= 97 && e <= 122 ) || e == '_') && semi == 3 ){

				printf("Invalid Syntax ! \n\n");
				
			}

			
			if (isalnum(e) > 0)
			{
				printf("%c",e);
			}
			
			//printf("%d -> %c  |  semi = %d\n",state , e , semi);

		}



	}


	printf("\n\n==== Report ====\n\n");
	printf("Number of Ints: %d\n", variables[0]);
	printf("Number of Floats: %d\n", variables[1]);
	printf("Number of Double: %d\n", variables[2]);
	printf("Number of Chars: %d\n", variables[3]);
	printf("Number of Functions : %d\n", variables[4]);

	fclose(in);

	return 0;
}