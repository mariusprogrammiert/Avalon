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
	int processCreatedCount = 0;
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

	printf("Anzahl der logischen Prozessoren: %d\n", cpuCount);
	printf("Anzahl der zu startenden Prozesse: %d\n", processCount);

	processes = malloc(processCount * sizeof *processes);
	if (processes == NULL)
	{
		printf("Fehler: Arbeitsspeicher konnte nicht angefordert werden!\n");
		return 1;
	}

	for (i = 0; i < processCount; i++)
	{
		processes[i] = fork();

		if (processes[i] == -1)
		{
			printf("Fehler: Neuer Prozess konnte nicht erzeugt werden!\n");
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
		processCreatedCount++;
	}

	if (errno == 0)
	{
		if (processCreatedCount == 1)
		{
			printf("Der Prozess wurde gestartet.");
		} else {
			printf("Die Prozesse wurden gestartet.");
		}
		printf(" Beenden mit Tastendruck\n");
		getchar();
	} else {
		errno = 0;
	}

	for (i = 0; i < processCreatedCount; i++)
	{
		kill(processes[i], SIGKILL);
	}

	free(processes);

	if (errno != 0)
	{
		printf("Fehler: Das Beenden von mindestens einem Prozess hat nicht funktioniert!\n");
		return 1;
	}

	printf("Fertig\n");
	return 0;
}
