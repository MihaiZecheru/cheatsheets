#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void enable_colors()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

bool startswith(const char* pre, const char* str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

/* my personal implementation of strlen before i realized strlen was a function included in string.h :(
int length(const char* str) 
{
	for (int len = 0; ; len++)
	{
		if (!str[len]) return len;
	}
}
*/

bool ishelp(const char* str)
{
	return !strcmp(str, "help")   ||
		   !strcmp(str, "-help")  ||
		   !strcmp(str, "--help") ||
		   !strcmp(str, "h")      ||
		   !strcmp(str, "-h")     ||
		   !strcmp(str, "--h");

}

int main(const int argc, const char** argv)
{
	enable_colors();
	if (argc == 1 || (argc == 2 && ishelp(argv[1])))
	{
		printf(ANSI_COLOR_CYAN "\tThis program was made with the intent of providing quick answers to common programming problems in order to save you time that would have instead been spent on tedious googling. "
			   					 "This cheatsheet CLI will return \"cheatsheets\" "
			    				 "as the results to its queries, which are created through the given command-line arguments. This program's main usage is a \"--lang\" flag and a query, "
			    				 "for example \"how to append to list --javascript\"\n\n"
			    				 "\tIf you're in the mood to learn something new, you can use the \":random\" tag to view a random cheatsheet, or you can start learning another language entirely in "
			    				 "the command line by passing a \"--lang\" flag and the \":learn\" tag to the CLI. If you don't care for this, there are two \"search operators\" you can use "
			    				 "to refine your results. To exclude certain words from the results, prefix those words with a minus sign (-). To retrieve multiple different cheatsheets, "
			    				 "all containing specific keyword(s), prefix those keyword(s) with a tilda (~).\n\n%s%s%s%s%s%s\n" ANSI_COLOR_RESET,
			   ANSI_COLOR_YELLOW "Usages:\n\tc <command> [--lang]\n\tc <--lang> :learn\n\tc :random\n\n",
			   ANSI_COLOR_CYAN   "Examples:\n\tc sum of list --python\n\tc add to end of list --javascript\n\tc use curl --shell\n\tc ls --cmd\n\n",
			   ANSI_COLOR_YELLOW "To exclude certain words from results, prefix the word with a minus sign (-)\n\n",
			   ANSI_COLOR_CYAN   "Examples:\n\tc --python multiply matrices -numpy\n\tc hello world --cpp -printf\n\n",
			   ANSI_COLOR_YELLOW "Note: to find results containing certain keywords, prefix the keywords with a tilda (~)\n\n",
			   ANSI_COLOR_CYAN   "Examples:\n\tc --js ~array\n\tc ~inheritance ~classes --python\n\t"
		);

		return 1;
	}

	bool language_flag = false;
	int flag_position = 0;

	for (int i = 1; i < argc; i++)
	{
		if (startswith("--", argv[i]))
		{
			if (!language_flag)
			{
				language_flag = true;
				flag_position = i;
			}
			else
			{
				printf(ANSI_COLOR_RED "Only one \"--lang\" flag can be provided. You've given at least the following two (but you should only have one):\n\t%s\n\t%s\n" ANSI_COLOR_RESET, argv[flag_position], argv[i]);
				return 1;
			}
		}
	}

	// get the language without the -- prefix
	char lang[1000];
	strcpy(lang, argv[flag_position]);
	memmove(lang, lang + 2, strlen(lang));
	
	bool add_lang = true;
	// convert language
	if (!strcmp(lang, "c++"))
	{
		strcpy(lang, "cpp");
	}
	else if (!strcmp(lang, "shell") || !strcmp(lang, "cmd") || !strcmp(lang, "command"))
	{
		add_lang = false;
	}

	// create command following this template: curl https://cheat.sh/lang/
	char cmd[5000];
	strcpy(cmd, "curl https://cheat.sh/");
	if (language_flag && add_lang)
	{
		strcat(cmd, lang);
		strcat(cmd, "/");
	}

	// add query to command
	if (argc > (2 - !language_flag))
	{
		for (int i = (1 - !language_flag); i < argc; i++)
		{
			if (i == flag_position) continue;

			// prevent "/+" from occurring in the url
			if (cmd[strlen(cmd) - 1] != '/')
			{
				strcat(cmd, "+");
			}

			strcat(cmd, argv[i]);
		}
	}

	printf(ANSI_COLOR_YELLOW "Sending request to ");
	printf(ANSI_COLOR_CYAN "%s\n\n" ANSI_COLOR_RESET, cmd + 5);

	// execute command
	system(cmd);
}
