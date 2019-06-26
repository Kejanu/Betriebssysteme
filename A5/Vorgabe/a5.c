#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "a5.h"

void copyUsingBuffer(char from[], char to[], long unsigned int bufferSize) {

}

void copyUsingFullRead(char from[], char to[]) {

}

void copyUsingMap(char from[], char to[]) {

}

void copyUsingSystemCall(char from[], char to[]) {

	struct stat statBuffer;
	int sourceFD, destFD;
	ssize_t fileSize;

	// Dateien pruefen
	if (stat(to, &statBuffer) == -1) {
		if (errno != ENOENT) {
			perror("Fehler beim Pruefen der Zieldatei");
			exit(EXIT_FAILURE);
		}
	} else {
		if (!(S_ISREG(statBuffer.st_mode))) {
			printf("Die Zieldatei ist keine regulaere Datei\n");
			exit(EXIT_FAILURE);
		}
	}

	// Dateien oeffnen
	sourceFD = open(from, O_RDONLY);
	if (sourceFD == -1) {
		perror("Fehler beim Oeffnen der Quelldatei");
		exit(EXIT_FAILURE);
	}
	if (fstat(sourceFD, &statBuffer) == -1) {
		perror("Fehler beim Pruefen der Quelldatei");
		exit(EXIT_FAILURE);
	}
	if (!(S_ISREG(statBuffer.st_mode))) {
		printf("Die Quelldatei ist keine regulaere Datei\n");
		exit(EXIT_FAILURE);
	}
	fileSize = (size_t) statBuffer.st_size;
	destFD = open(to, O_WRONLY | O_CREAT | O_TRUNC, statBuffer.st_mode);
	if (destFD == -1) {
		perror("Fehler beim Oeffnen der Zieldatei");
		exit(EXIT_FAILURE);
	}

	// Kopieren
	if (sendfile(destFD, sourceFD, NULL, fileSize) != fileSize) {
		perror("Fehler bei sendfile()");
		exit(EXIT_FAILURE);
	}

	// Dateien schliessen
	close(sourceFD);
	close(destFD);
}
