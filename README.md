# Avalon

Avalon ist ein CPU-Lasttest für Linux.
Je nach Systemausstattung oder Parameter beim Aufruf, wird eine bestimmte Anzahl an Prozessen gestartet, welche einzelne CPU-Kerne auslasten.
Logische CPU-Kerne werden unterstützt.

## Technik

Die Anwendung ist eine Konsolenanwendung welche in C für Linux-Systeme entwickelt wurde.

## Installation und Benutzung

Das Programm kann mit  
    gcc -o Avalon Avalon.c  
kompiliert werden.  
Anschließend wird es mit  
    ./Avalon  
    ./Avalon 4  
aufgerufen.  
Wenn die Anwendung ohne Parameter aufgerufen wird, ist die Anzahl der erzeugten Last-Prozesse gleich der Anzahl der logischen CPU-Kerne im System. Auf Wunsch kann als Parameter die Anzahl Last-Prozesse übergeben werden.

