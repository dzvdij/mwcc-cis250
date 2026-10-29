#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
	FILE *file;
	pid_t pid;
	char text_command[BUFFER_SIZE];
	char *args[10];
	char *p;
	int arg_count;
	int status;
	int total = 0;
	int pass = 0;
	int fail = 0;
	int k;
	
	// Open tests.txt for reading.
	file = fopen("tests.txt", "r");

	// If the file cannot be opened, report the error and terminate.
	if (file == NULL)
	{
		perror("tests.txt");
		return 1;
	}

	// Read the file one line at a time.
	while (fgets(text_command, BUFFER_SIZE, file) != NULL)
	{
		// Remove newline char.
		for (k = 0; text_command[k] != '\0'; k++)
		{
			if (text_command[k] == '\n')
			{
				text_command[k] = '\0';
				break;
			}
		}

		// Skip space characters at beginning of line.
		k = 0;
		while (text_command[k] == ' ' || text_command[k] == '\t')
		{
			k++;
		}

		// Skip blank lines and comments.
		if (text_command[k] == '\0' || text_command[k] == '#')
		{
			continue;
		}

		// Parse each test command.
		arg_count = 0;
		p = text_command;

		while (*p != '\0' && arg_count < 9)
		{
			// Skip spaces.
			while (*p == ' ' || *p == '\t')
			{
				p++;
			}

			if (*p == '\0')
			{
				break;
			}

			args[arg_count] = p;
			arg_count++;

			// Finding end of argument.
			while (*p != '\0' && *p != ' ' && *p != '\t')
			{
				p++;
			}

			if (*p != '\0')
			{
				*p = '\0';
				p++;
			}
		}

		// Ends arg_array with null.
		args[arg_count] = NULL;
		if (arg_count == 0)
		{
			continue;
		}

		// Count amount of tests.
		total++;

		// Prints test command.
		printf("Starting test: ");
		for (k = 0; args[k] != NULL; k++)
		{
			printf("%s ", args[k]);
		}

		printf("\n");
		fflush(stdout);

		// Child process created.
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			fail++;
			continue;
		}

		// Child process cont.
		if (pid == 0)
		{
			execvp(args[0], args);
			perror("execvp");
			exit(1);
		}

		// Parent waits for child to terminate.
		if (wait(&status) == -1)
		{
			perror("wait");
			fail++;
			continue;
		}

		// Checks child's exit status.
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		{
			printf("Result: PASS\n");
			pass++;
		}
		
		else
		{
			printf("Result: FAIL\n");
			fail++;
		}
	}

	// Close input file after processing all tests.
	fclose(file);

	printf("\n================================\n");
	printf("          TEST SUMMARY\n");
	printf("================================\n");
	printf("Tests executed: %d\n", total);
	printf("Tests passed:   %d\n", pass);
	printf("Tests failed:   %d\n", fail);
	printf("================================\n");

	return 0;
}

