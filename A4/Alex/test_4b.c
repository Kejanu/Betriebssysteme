#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "4b.h"

#define soft_assert(expr) \
	if (!(expr)) { \
		printf("%s:%d: Assertion %s failed\n", __FILE__, __LINE__, #expr); \
	}

int main(void)
{
	char *addr[16];
	int i = 0;

	printf("Aktuelles (leeres) Speicherlayout:\n");
	dump_memory();
	
	printf("Alloziere  10 kiB -> %p\n", addr[i++] = ff_alloc( 10 * 1024));
	dump_memory();
	
	printf("Gebe %p (10 kiB) frei\n", addr[0]);
	ff_free(addr[0]);
	*addr[0] = 'F';
	dump_memory();
	
	printf("Alloziere  10 kiB -> %p\n", addr[i++] = ff_alloc( 10 * 1024));
	dump_memory();
	
	printf("Alloziere  10 kiB -> %p\n", addr[i++] = ff_alloc( 10 * 1024));
	dump_memory();
	
	printf("Gebe %p (10 kiB) frei\n", addr[1]);
	ff_free(addr[1]);
	*addr[1] = 'F';
	dump_memory();
	
	printf("Alloziere  14 kiB -> %p\n", addr[i++] = ff_alloc( 14 * 1024));
	dump_memory();
	
	printf("Gebe %p (10 kiB) frei\n", addr[2]);
	ff_free(addr[2]);
	*addr[2] = 'F';
	dump_memory();
	
	printf("Gebe %p (14 kiB) frei\n", addr[3]);
	ff_free(addr[3]);
	*addr[3] = 'F';
	dump_memory();
	
	printf("Alloziere  10 kiB -> %p\n", addr[i++] = ff_alloc( 10 * 1024));
	dump_memory();
	
	printf("Alloziere 500 kiB -> %p\n", addr[i++] = ff_alloc(944 * 1024));
	dump_memory();
	
	printf("Alloziere   1   B -> %p\n", addr[i++] = ff_alloc(1));
	dump_memory();
	
	printf("Alloziere 200 kiB -> %p\n", addr[i++] = ff_alloc(200 * 1024));
	dump_memory();
	
	printf("Alloziere  40 kiB -> %p\n", addr[i++] = ff_alloc( 40 * 1024));
	dump_memory();
	
	printf("Alloziere   1   B -> %p\n", addr[i++] = ff_alloc(1));
	dump_memory();
	
	/* original Test falsche Ausgabe: printf("Gebe %p (200 kiB) frei\n", addr[3]); */
    printf("Gebe %p (200 kiB) frei\n", addr[7]);
    ff_free(addr[7]);
	*addr[7] = 'F';
	dump_memory();
	
	printf("Gebe NULL frei\n");
	ff_free(NULL);
	dump_memory();
	
	printf("Alloziere  20 kiB -> %p\n", addr[i++] = ff_alloc( 20 * 1024));
	dump_memory();

	return 0;
}
