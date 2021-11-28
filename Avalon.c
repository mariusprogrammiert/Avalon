#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/sysinfo.h>

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

int main(int argc, char *argv[])
{
	int cpuCount = get_nprocs();
	int a, i, processCount;
	int *processes;

	if (argc == 2)
	{
		processCount = atoi(argv[1]);
		if (processCount <= 0 || processCount > 128)
		{
			printf("Fehler: Nicht erlaubte Prozessanzahl!\n");
			return 1;
		}
	} else
	{
		processCount = cpuCount;
	}

	printf("Anzahl der Prozessoren: %d\n", cpuCount);
	printf("Anzahl der Prozesse: %d\n", processCount);
	processes = malloc(processCount * sizeof *processes);

	for (i = 0; i < processCount; i++)
	{
		processes[i] = fork();
		if (processes[i] == 0)
		{
			a = 0;
			while (1)
			{
				if (a > 1000)
				{
					a = 0;
				}
				a++;
			}
			exit(0);
		}
	}

	printf("Prozesse wurden gestartet. Beenden mit Tastendruck\n");
	getchar();

	for (i = 0; i < processCount; i++)
	{
		kill(processes[i], SIGKILL);
	}

	free(processes);	
	printf("Fertig\n");

	return 0;
}

