/*
	Multilingual Compiler
	Detects language and calls necessary compiler.
	@oishikm | 03-30-2019
	V 1.0
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef enum lang_t
{
	help =		0x0,	// Not a language, but to address --help option
	c =			0x1,	// .c
	cpp =		0x2,	// .cpp
	java =		0x3,	// .java
	python =	0x4,	// .py or .py3
	shell =		0x5		// .sh
} lang_t;

char* extcopy(char dest[10], char src[20], int start, int end)
{
	int i, j;
	for(i=0, j=start; i<9, j<=end; i++, j++)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';
	dest[9] = '\0';	// Fail-proofing
	return dest;
}

lang_t detect_language(char f[20])
{
	// Returns language detected, or finds if help was requested
	char ext[10];
	int i, n;
	if(strcmp(f, "--help") == 0)
	{
		return help;
	}
	else
	{
		n = strlen(f);
		for(i=n ;i>=0; i--)
		{
			if(f[i] == '.')
			{
				break;	
			}
		}
		
		extcopy(ext, f, i+1, n);	// Copies file extension into ext
		
		if(strcmp(ext, "c") == 0)
		{
			return c;
		}
		else if(strcmp(ext, "cpp") == 0)
		{
			return cpp;
		} 
		else if(strcmp(ext, "java") == 0)
		{
			return java;
		}
		else if(strcmp(ext, "py") == 0 || strcmp(ext, "py3") == 0)
		{
			return python;
		}
		else if(strcmp(ext, "sh") == 0)
		{
			return shell;
		}
	}
}

void choose_compiler(char f[20], char com[10])
{
	lang_t lang = detect_language(f);
	
	if(lang == help)
	{
		// Prints help and exits
		printf("HELP: runp: multilingual compiler. \ndetects language and calls necessary compiler.\n");
		printf("Usage: runp file [compiler] \n");
		exit(0);
	}
	else if(lang == c)
	{
		strcpy(com, "gcc");
	}
	else if(lang == cpp)
	{
		strcpy(com, "g++");
	} 
	else if(lang == java)
	{
		strcpy(com, "javac");
	}
	else if(lang == python)
	{
		strcpy(com, "python3");
	}
	else if(lang == shell)
	{
		strcpy(com, "bash");
	}
}

void prepare_command(char cmd[50], char f[20], char c[10])
{
	strcpy(cmd, c);
	strcat(cmd, " ");
	strcat(cmd, f);
}

int main(int argc, char* argv[])
{
	char filename[20], compiler[10], command[50];
		
	if(argc == 1)
	{
		printf("runp: error: no input file. \ncompilation terminated.");
	}
	else if(argc == 2)
	{
		strcpy(filename, argv[1]);
		choose_compiler(filename, compiler);
		prepare_command(command, filename, compiler);
		system(command);
	}
	else if(argc==3)
	{
		strcpy(filename, argv[1]);
		strcpy(compiler, argv[2]);
		prepare_command(command, filename, compiler);
		system(command);
	}
	else
	{
		printf("runp: error: too many input files. \ncompilation terminated.");
	}
	printf("\n");	// newline to next CL
	return 0;
}
