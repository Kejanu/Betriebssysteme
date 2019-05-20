#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>







/* Geteilter Speicher zum Ablegen der Primzahl */

#ifdef RINGBUFFER


/* Buffer der Groeße 10 (mehrere Elemente)*/

int buffer[10];
int indexEingabe = 0;
int indexAusgabe = 0;
int size=0;

int isEmpty(){
    if( buffer[indexAusgabe] == 0){
        return 1;
    } else {
        return 0;
    }
}

void bufferAdd(int x){
    if(size < 10){
        buffer[indexEingabe] = x;
        ++size;
        indexEingabe = (indexEingabe + 1) % 10;
    }
}

int bufferRemove(){
    if(!isEmpty()){
        int toReturn = buffer[indexAusgabe];
        buffer[indexAusgabe] = 0;
        --size;
        indexAusgabe = (indexAusgabe + 1) % 10;
        return toReturn;
    } else {
        return 0;
    }
}


#define ADD(x) bufferAdd(x);
#define REMOVE bufferRemove()
#define CAP 10


#else

unsigned int primzahl;

#define ADD(x) primzahl = x;
#define REMOVE primzahl
#define CAP 1

#endif




/* Hier müsst Ihr ggf. Euren Code einfügen. */
sem_t frei;
sem_t belegt;

pthread_t pthreadPrimserv;
pthread_t pthreadPrimeat;


/* naive Implementierung eines Primzahltests */
static int ist_primzahl(unsigned x) {
	int i;
	if (x < 2) return 0;
	for (i = 2; i * i <= x; ++i) {
		if ((x % i) == 0) {
			return 0;
		}
	}
	return 1;
}

/* Primzahl-Fabrik */
static void* primserv(void *arg) {
	unsigned int i;
	struct timespec sleepTime;

	sleepTime.tv_sec = 0;
	sleepTime.tv_nsec = 500000000;

	/* endlos Primzahlen produzieren ... */
	for (i = 1; ; ++i) {
		if (!ist_primzahl(i))
			continue;

		/* Hier müsst Ihr ggf. Euren Code einfügen. */
		if( sem_wait(&frei) != 0){
		    perror("Wait");
            exit(EXIT_FAILURE);
		}



		/*
		 * Die Zeichenfolge "\033" dient zur Steuerung der Ausgabe auf der Konsole.
		 * Über "\033[01;31;40m" wird z.B. die Hintergrundfarbe ("40") auf Schwarz
		 * und die Vordergrundfarbe auf ein helles Rot gesetzt.
		 * Durch "\033[0m" werden alle Einstellungen wieder zurückgesetzt.
		 * Weitere Infos finden sich in der man-Page console_codes(4)
		 * oder z.B. hier: https://misc.flogisoft.com/bash/tip_colors_and_formatting
		 */


		printf("\033[01;31;40mprimserv(%ld): Primzahl %u produziert!\033[0m\n", syscall(SYS_gettid), i );


		/*primzahl = i;*/
		ADD(i)



		/* Hier müsst Ihr ggf. Euren Code einfügen. */
		if( sem_post(&belegt) != 0){
		    perror( "Post");
		    exit(EXIT_FAILURE);

		}



		/* ein bisschen schlafenlegen ... Primzahlen Erzeugen macht muede! */
		nanosleep(&sleepTime, NULL);
	}

	return NULL;
}

static void* primeat(void *arg) {
	struct timespec sleepTime;

	sleepTime.tv_sec = 1;
	sleepTime.tv_nsec = 500000000;

	/* endlos Primzahlen konsumieren ... */
	while (1) {

		/* Hier müsst Ihr ggf. Euren Code einfügen. */
		if( sem_wait(&belegt) != 0){
		    perror("Wait");
            exit(EXIT_FAILURE);
		}

		/*
		 * Hier werden ebenfalls Steuercodes verwendet, Erklärung siehe
		 * primeserv().
		 */

		/*printf("\033[01;33;40mprimeat (%ld): Primzahl %u konsumiert!\033[0m\n", syscall(SYS_gettid), primzahl);*/

        printf("\033[01;33;40mprimeat (%ld): Primzahl %u konsumiert!\033[0m\n", syscall(SYS_gettid), REMOVE);


        /* Hier müsst Ihr ggf. Euren Code einfügen. */
		if( sem_post(&frei) != 0){
		    perror("Post");
            exit(EXIT_FAILURE);
		}

		/* ein bisschen schlafenlegen ... Primzahlen Konsumieren macht muede! */
		nanosleep(&sleepTime, NULL);
	}

	return NULL;
}

static void signalHandler(int signal) {
	if (signal == SIGINT) {
		pthread_cancel(pthreadPrimserv);
		printf("primeserv beendet\n");
		pthread_cancel(pthreadPrimeat);
		printf("primeat beendet\n");
	} else {
		fprintf(stderr, "Anderes Signal als SIGINT gefangen: %d\n", signal);
		exit(EXIT_FAILURE);
	}
}



int main(int argc, const char *argv[]) {
	int ret;
	struct sigaction sa;

	/*
	 * Registriere Signal-Handler für das Signal SIGINT.
	 * So kann alles sauber aufgeräumt werden,
	 * wenn das Programm mit Strg+C abgebrochen wird.
	 */
	sa.sa_handler = signalHandler;
	sigemptyset(&sa.sa_mask);

	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		perror("sigaction");
		return EXIT_FAILURE;
	}

	/* Hier müsst Ihr ggf. Euren Code einfügen. */
    if(sem_init(&frei, 0, CAP) != 0) {
        perror("Initialisierung der Semaphore");
        return EXIT_FAILURE;
    }

    if(sem_init(&belegt, 0, 0) != 0) {
        perror("Initialisierung der Semaphore");
        return EXIT_FAILURE;
    }




	/* Erzeuge primeserv-Thread */
	ret = pthread_create(&pthreadPrimserv, NULL, &primserv, NULL);
	if (ret) {
		fprintf(stderr, "Cannot create producer thread: %s\n", strerror(ret));
		return EXIT_FAILURE;
	}
	/* Erzeuge primeat-Thread */
	ret = pthread_create(&pthreadPrimeat, NULL, &primeat, NULL);
	if (ret) {
		fprintf(stderr, "Cannot create eater thread: %s\n", strerror(ret));
		return EXIT_FAILURE;
	}
	/* Warte auf Terminierung des primserv-Threads */
	ret = pthread_join(pthreadPrimserv, NULL);
	if (ret) {
		fprintf(stderr, "Cannot wait for producer thread: %s\n", strerror(ret));
		return EXIT_FAILURE;
	}
	/* Warte auf Terminierung des primeat-Threads */
	ret = pthread_join(pthreadPrimeat, NULL);
	if (ret) {
		fprintf(stderr, "Cannot wait for eater thread: %s\n", strerror(ret));
		return EXIT_FAILURE;
	}

	/* Hier müsst Ihr ggf. Euren Code einfügen. */
    if(sem_destroy(&frei) != 0) {
        perror("Beseitigung der Semaphore");
        return EXIT_FAILURE;
    }

    if(sem_destroy(&belegt) != 0) {
        perror("Beeitigung der Semaphore");
        return EXIT_FAILURE;
    }



	printf("Alles ist aufgeräumt. Ende!\n");

	return EXIT_SUCCESS;
}
