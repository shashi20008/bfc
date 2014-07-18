#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_LENGTH 500
#define STACK_MAX 100
#define STACK_UNDERFLOW -1
#define STACK_OVERFLOW -2

char* BASE = NULL;
char* CUR = NULL;
size_t len = DEF_LENGTH;
int inputLength = 0;
fpos_t stack[STACK_MAX];
int stackTop = 0;

void push(fpos_t location)
{
	stack[stackTop++] = location;
}

fpos_t pop()
{
	stackTop--;
	if(stackTop == -1)
	{
		return STACK_UNDERFLOW;
	}
	return stack[stackTop];
}

fpos_t peep()
{
	return stack[stackTop - 1];
}

char readChar()
{
	return 'a';
}

void fillArr(char val, char* arr, int length)
{
	int i;
	for(i = 0; i < length; i++)
	{
		arr[i] = val;
	}
}

int main(int argc, char* argv[])
{
	fpos_t location = 0;
	if(argc < 2)
	{
		printf("No Input file specified!\r\n");
		printf("Syntax: bfc <filename.bf> \"<inputString>\"\r\n");
		printf("Anymore extra arguments and runtime inputs are gracefully ignored.");
	}
	
	FILE* file = fopen(argv[1], "r");
	
	if(file == NULL)
	{
		printf("The specified File couldn't be found. Check for typos");
	}
	
	BASE = (char*) malloc(len);
	CUR = BASE;
	char ch = getc(file);
	
	fillArr(0, BASE, len);
	
	while(ch != EOF)
	{
		switch(ch)
		{
			case '>':
				CUR++;
				break;
			case '<':
				CUR--;
				break;
			case '+':
				(*CUR)++;
				break;
			case '-':
				(*CUR)--;
				break;
			case ',':
				(*CUR) = readChar();
				break;
			case '.':
				printf("%c", *CUR);
				break;
			case '[':
				fgetpos(file, &location);
				push(location);
				break;
			case ']':
				if(*CUR)
				{
					location = peep();
					fsetpos(file, &location);
				}
				else
				{
					pop();
				}
				break;
				
			default:
				break;
				
		}
		ch = getc(file);
		//printf("%c", ch);
	}
	
	return 0;
}
