#include <stdio.h>
#include <stdbool.h>

bool running = true;
int ip = 0;				//instruction pointer
int sp = -1;			//stack pointer

int stack[256];

typedef enum
{
	PSH,
	ADD,
	POP,
	HLT
}InstructionSet;

const int program[] =
{
	PSH, 5,
	PSH, 6,
	ADD,
	POP,
	HLT
};

int fetch()
{
	return program[ip];
}

void eval(int instr)
{
	switch (instr)
	{
		case HLT:
		{
			running = false;
			printf("done");
			break;
		}
		case PSH:
		{
			sp++;
			stack[sp] = program[++ip];
			break;
		}
		case ADD:
		{
			int a = stack[sp--];
			int b = stack[sp--];

			int res;
			res = a + b;
			sp++;
			stack[sp] = res;

			break;
		}
		case POP:
		{
			int val_popped = stack[sp--];
			printf("res = %d\n", val_popped);
			break;
		}
	}
}

int main()
{
	while (running)
	{
		eval(fetch());
		ip++;		
	}
}