#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *p;
	int cpuCount = get_nprocs();
	int a, i, processCount;
	int *processes;
	errno = 0;

	if (argc == 2)
	{
		processCount = strtol(argv[1], &p, 10);
		if (*p != '\0' || errno != 0 || processCount <= 0 || processCount > 128)
		{
			printf("Fehler: Nicht erlaubte Prozessanzahl!\n");
			return 1;
		}
	} else {
		processCount = cpuCount;
	}

	printf("Anzahl der Prozessoren: %d\n", cpuCount);
	printf("Anzahl der Prozesse: %d\n", processCount);
	processes = malloc(processCount * sizeof *processes);

	for (i = 0; i < processCount; i++)
	{
		processes[i] = fork();

		if (processes[i] == -1)
		{
			printf("Fehler: Neuer Prozess konnte nicht erzeugt werden!\n");
			processCount = i;
			break;
		}

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

	if (errno == 0)
	{
		printf("Prozesse wurden gestartet. Beenden mit Tastendruck\n");
		getchar();
	}

	for (i = 0; i < processCount; i++)
	{
		kill(processes[i], SIGKILL);
	}

	free(processes);

	if (errno != 0)
	{
		return 1;
	}

	printf("Fertig\n");
	return 0;
}

