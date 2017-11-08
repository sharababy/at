#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define RED     "\033[31m" 
#define RESET   "\033[0m"


/*	
	
	initial state : 0
			
	DFA 1: 

	0  -{-> 1 -char-> 2 -operator-> 3 -int-> 0 -}-> 0
			    _________________	|--operator--> 4 -> 3
	operators:	|= + - * / % > <|
				`````````````````

	DFA 2:

	0 -char-> 4 -operator-> 5 -operator-> -2 -int-> 200
	
	= =
	! =
	> =
	+ =
	- =
	* =
	/ =

	Supported operators in c

	a = b
	a + b
	a - b
	a * b
	a / b
	a % b
	a > b
	a < b
	
	a == b
	a != b
	a >= b
	a <= b
	a += b
	a -= b
	a *= b
	a /= b

	a[b]
	a(a1, a2)

	all ops are only allowed inside functions {}

*/

int state,semi,semi1;

int main(int argc, char const *argv[])
{
	FILE* in;
	char e;

	state = 0;
	semi = 0;
	semi1 = 0;

	printf("\n==== Legal Integer Identifiers ==== \n\n");



	in = fopen(argv[1] , "r+");

	while( fread(&e , 1 , 1 , in) == 1){

		if (state >= 0 && state < 200)
		{
			
			if (isalpha(e) > 0)
			{
				if (state == 1)
				{
					state = 2;
				}
				
			}
			else if (e == '{')
			{
				if (state == 0)
				{
					state = 1;
					
				}
				semi++;
			}
			else if (e == '}')
			{
				if (semi > 0 )
				{
					
					semi--;
				}

				if (semi == 0)
				{
					state = 0;
				}
			}
			else if (e == '=' || e == '+' || e == '-' || e == '*' || e == '/' || e == '%' || e == '>' || e == '<')
			{
				if (state == 2)
				{
					state = -1;

				}

				if (state != 2 && e == '/')
				{
					state = 199;
				}
				else if (state == 199 && e == '/')
				{
					state = 300;
				}
			}
			else if (e == '\"')
			{
				state = 200;
			}

		}
		else if(state == 200){

			if (e == '\"')
			{
				state = 1;
			}
		}
		else if(state == 300){

			if (e == '\n')
			{
				state = 1;
			}
		}
		else if ( state < 0 )
		{
			
			if (state == -1)
			{
				if (e == ' ' && semi1 == 1){
					printf(RED"Invalid Syntax !");
					printf(RESET"\n");
				}
				else if (e == ' ' && semi1 == 0)
				{

				}
				else if (e == '=')
				{
					state = -1;
				}
				else if (e == ';')
				{
					state = 1;
					semi1 = 0;
					printf("\n");
				}
				else if (isalpha(e) > 0  && semi1 == 0)
				{
					state = 2;
					semi1 = 0;
				}
				else if (isalpha(e) > 0  && semi1 == 1)
				{
					printf(RED"Invalid Syntax !");
					printf(RESET"\n");
				}
				else if (e =='.'  && semi1 == 1)
				{
					printf("->Float\n");
				}
				else if( e >= 48 && e <= 57)
				{
					printf("%c", e);
					semi1 = 1;	
				}
				else if(e == ')' && semi1 == 1){

					state = 1;
					semi1 = 0;

					printf("\n");
				}
				
				
			}

		}

		//printf("%d -> %c  |  semi = %d\n",state , e , semi);
	}

	fclose(in);

	return 0;
}