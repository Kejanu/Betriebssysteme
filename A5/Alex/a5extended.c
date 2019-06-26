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

    clock_t t_start, t_end;

    if((t_start = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

    char buffer[bufferSize];
    int fd_from, fd_to;
    ssize_t read_count = 1;
    ssize_t write_count = 1;


    //Öffnen

    if((fd_from = open(from, O_RDONLY)) == -1){
        perror("Fehler beim Öffnen von from");
        exit(EXIT_FAILURE);
    }

    if((fd_to = open(to, O_WRONLY)) == -1){
        perror("Fehler beim Öffnen von to");
        exit(EXIT_FAILURE);
    }

    /*

    int stat_from, stat_to;
    struct stat fileinfo_from, fileinfo_to;




    //Falls Ziel kleiner als Ursprung - > Fehler (Notwendig??)


    if((stat_from = fstat(fd_from, &fileinfo_from)) == -1 || (stat_to = fstat(fd_to, &fileinfo_to)) == -1){
        perror("Fehler bei Größenbestimmung");
        exit(EXIT_FAILURE);
    }

    if(S_ISREG(fileinfo_from.st_mode) && S_ISREG(fileinfo_to.st_mode)){
        if(fileinfo_from.st_size > fileinfo_to.st_size){
            printf("Datei könnte nicht komplett kopiert werden.");
            exit(EXIT_FAILURE);
        }
    }

     */


    //Kopieren

    while (read_count != 0 && write_count != 0){



        if((read_count = read(fd_from, buffer, bufferSize)) == -1){
            perror("Fehler beim Einlesen");
            exit(EXIT_FAILURE);
        }

        if(read_count != 0){
            //Es befindet sich etwas im Puffer zum Kopieren


            if((write_count = write(fd_to, buffer, read_count)) == -1){
                perror("Fehler beim Schreiben");
                exit(EXIT_FAILURE);
            }
        }

    }

    //Schließen

    if(close(fd_from) == -1){
        perror("Fehler beim Schließen von from");
        exit(EXIT_FAILURE);
    }

    if(close(fd_to) == -1){
        perror("Fehler beim Schließen von to");
        exit(EXIT_FAILURE);
    }

    if((t_end = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

    printf("Zeit benötigt: %ld ms\n", (t_end - t_start));

}

void copyUsingFullRead(char from[], char to[]) {

    clock_t t_start, t_end;

    if((t_start = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

    int fd_from, fd_to;


    //Öffnen

    if((fd_from = open(from, O_RDONLY)) == -1){
        perror("Fehler beim Öffnen von from");
        exit(EXIT_FAILURE);
    }

    if((fd_to = open(to, O_WRONLY)) == -1){
        perror("Fehler beim Öffnen von to");
        exit(EXIT_FAILURE);
    }


    //Größenbestimmung

    int stat_from;
    struct stat fileinfo_from;


    if((stat_from = fstat(fd_from, &fileinfo_from)) == -1){
        perror("Fehler bei Größenbestimmung");
        exit(EXIT_FAILURE);
    }

    if(!S_ISREG(fileinfo_from.st_mode)) {
        printf("Größe konnte nicht bestimmt werden");
        exit(EXIT_FAILURE);
    }

    //Kopieren

    char data[fileinfo_from.st_size];

    if(read(fd_from, data, fileinfo_from.st_size) == -1){
        perror("Fehler beim Einlesen");
        exit(EXIT_FAILURE);
    }

    if(write(fd_to, data, fileinfo_from.st_size) == -1){
        perror("Fehler beim Schreiben");
        exit(EXIT_FAILURE);
    }

    //Schließen

    if(close(fd_from) == -1){
        perror("Fehler beim Schließen von from");
        exit(EXIT_FAILURE);
    }

    if(close(fd_to) == -1){
        perror("Fehler beim Schließen von to");
        exit(EXIT_FAILURE);
    }

    if((t_end = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

    printf("Zeit benötigt: %ld ms\n", (t_end - t_start));

}

void copyUsingMap(char from[], char to[]) {

    clock_t t_start, t_end;

    if((t_start = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

    int fd_from, fd_to;


    //Öffnen

    if((fd_from = open(from, O_RDONLY)) == -1){
        perror("Fehler beim Öffnen von from");
        exit(EXIT_FAILURE);
    }

    if((fd_to = open(to, O_WRONLY)) == -1){
        perror("Fehler beim Öffnen von to");
        exit(EXIT_FAILURE);
    }

    //Größenbestimmung

    int stat_from;
    struct stat fileinfo_from;


    if((stat_from = fstat(fd_from, &fileinfo_from)) == -1){
        perror("Fehler bei Größenbestimmung");
        exit(EXIT_FAILURE);
    }

    if(!S_ISREG(fileinfo_from.st_mode)) {
        printf("Größe konnte nicht bestimmt werden");
        exit(EXIT_FAILURE);
    }

    //Kopieren

    void *addr;


    if((addr = mmap(NULL, fileinfo_from.st_size, PROT_READ,MAP_PRIVATE, fd_from, 0)) == MAP_FAILED){
        perror("Fehler bei Speicherabbild");
        exit(EXIT_FAILURE);
    }

    if(write(fd_to, addr, fileinfo_from.st_size) == -1){
        perror("Fehler beim Schreiben");
        exit(EXIT_FAILURE);
    }

    //Schließen

    if(close(fd_from) == -1){
        perror("Fehler beim Schließen von from");
        exit(EXIT_FAILURE);
    }

    if(close(fd_to) == -1){
        perror("Fehler beim Schließen von to");
        exit(EXIT_FAILURE);
    }

    if((t_end = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

    printf("Zeit benötigt: %ld ms\n", (t_end - t_start));

}

void copyUsingSystemCall(char from[], char to[]) {

    clock_t t_start, t_end;

    if((t_start = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

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

    if((t_end = clock()) == -1){
        perror("Fehler bei Zeitmessung");
        exit(EXIT_FAILURE);
    }

    printf("Zeit benötigt: %ld ms\n", (t_end - t_start));
}
