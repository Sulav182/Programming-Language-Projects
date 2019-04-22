/* Sulav Poudyal
 This program is written in C and is complied in cygwin
 This program also includes stack.c file and can be compiled using 'gcc -o interpreter interpret.c stack.c' instruction.
 */

#include"stack.h"


//declaring p as global variable
int p=0;
#define TRUE 1
#define FALSE 0
//functions used in the program.
int A(char* in);
int L(char* in);
int AT_Tail(char* in);
int AT(char* in);
int OT_Tail(char* in);
int OT(char* in);
int IT_Tail(char* in);
int IT(char* in);
int B(char* in);


//main function

int main(void)
{
	char in[100];
	int i=0;
	char ch;
	char a;
	int space=0;
	printf("Enter expression: \n");
	while ((ch=getchar())!='\n')
	{
		in[i++]=ch;
		if(ch==' ')
			space=1;
	}
	in[i]='\0';
	//printf("length of in %d and ch is %c%c%c%c ",strlen(in),in[0],in[1],in[2],in[3]);
	char val;
	val=B(in);
	a=pop();
	if (space)
		printf("Syntax should not include space");
	else if ((val==1 || val==0) && a!='\0')
	{
		printf("Value of Expression is %c",a);
	}

}


//boolean function A: Checks for 'T' and 'F' and then pushes the value in stack
int A(char* in)
{


	if (in[p]=='F')
	{

		push('F');
		++p;
		return TRUE;
	}
	else if(in[p]=='T')
	{
		push('T');
	//	printf("  Value of P before increment %d  ",p );
		++p;
	//	printf("Pushing Value T in A and next character is %c and p is %d ", in[p],p);
		return TRUE;
	}
	else if(in[p]=='(')
	{
		++p;
		IT(in);
		return TRUE;
	}
	else
	{

		if(in[p]!='~')
			printf("Invalid character %c", in[p]);
		return FALSE;
	}
}
//boolean function L: Checks for negation
int L(char* in)
{
	char temp;
	//lex=get(in);
	//printf("Inside L");
	if(A(in))
	{
	//	printf("1");
		return TRUE;
	}
	else if(in[p]=='~')
	{
		++p;
	//	printf(" Inside negation ");
		if(in[p]=='T')
			in[p]='F';
		else
			in[p]='T';
		L(in);
		return TRUE;

	}
	else
		return FALSE;

}
//checks for and symbol
int AT_Tail(char* in)
{
	char temp1,temp2;
	//printf("Inside AT Tail 1 %c",in[p]);
	if(in[p]=='^')
	{
		++p;
//		printf("Inside AT Tail");
		if(L(in))
		{
			//printf("2");
			temp1=pop();
			temp2=pop();
			if(temp1==temp2)
				push(temp1);
			else
				push('F');

			if(AT_Tail(in))
				return TRUE;
			else
				return FALSE;
			return TRUE;
		}
		else
			return FALSE;
	}
	else if((in[p]=='-' && in[p+1]=='>') || in[p]=='.' || in[p]=='v')
		return TRUE;
	else
		return FALSE;
}

int AT(char* in)
{
//	printf("3");
	if(L(in))
	{
//		printf("Inside AT and next char is %c ",in[p]);
		if(AT_Tail(in))
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

//checks for or symbol
int OT_Tail(char* in)
{
	char temp1,temp2;
	if(in[p]=='v')
	{
		++p;
		if(AT(in))
		{
			temp1=pop();
			temp2=pop();

			if(temp1=='T' || temp2=='T')
				push('T');
			else
				push('F');

			if(OT_Tail(in))
				return TRUE;
			else
				return FALSE;

			return TRUE;
		}
		else
			return FALSE;
	}
	else if((in[p]=='-' && in[p+1]=='>') || in[p]=='.' || in[p]=='v')
		return TRUE;
	else
		return FALSE;

}

int OT(char* in)
{
	if(AT(in))
	{
		if(OT_Tail(in))
		{
			return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}
//checks for implies symbol
int IT_Tail(char* in)
{
	char temp1,temp2;
	if(in[p]=='-' && in[p+1]=='>')
	{
		p=p+2;
		printf("Inside IT tail");
		if(OT(in))
		{
			temp1=pop();
			temp2=pop();
			if(temp1=='F' || (temp1=='T' && temp2=='T'))
				push('T');
			else
				push('F');

			if(IT_Tail(in))
				return TRUE;
			else
				return FALSE;

			return TRUE;
		}
		else
			return FALSE;
	}
	else if(in[p]=='-' && in[p+1]==' ')
	{
		printf("Syntax Error");
		return FALSE;
	}
	else if(in[p]=='.' || in[p]==')')
		return TRUE;
	else
		return FALSE;
}

int IT(char* in)
{
	if(OT(in))
	{
		if(IT_Tail(in))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
		return FALSE;
}

int B(char* in)
{
	int j=0;

//	printf(" |%d| ",strlen(in));


	if(in[(strlen(in))-1]!='.')
	{
		printf("Syntax should end with '.'\n");
		return FALSE;
	}
	else if(IT(in))
	{
		++p;
		return TRUE;
	}
	else
		return FALSE;
}




