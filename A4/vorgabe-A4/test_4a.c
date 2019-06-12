#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <assert.h>

#include "4a.h"


int main(void)
{
	char *addr[16];
	int i = 0;

	printf("heap -> %p\n", (void*)heap);
	printf("Aktuelles (leeres) Speicherlayout:\n");
	dump_memory();
	printf("Alloziere  10 kiB -> %p\n", addr[i] = ff_alloc( 10 * 1024));
	*addr[i] = 'A';
	i++;
	dump_memory();
	
	printf("Alloziere 500 kiB -> %p\n", addr[i++] = ff_alloc(500 * 1024));
	dump_memory();
	
	printf("Alloziere   1   B -> %p\n", addr[i] = ff_alloc(1));
	*addr[i] = 'A';
	i++;
	dump_memory();
	
	printf("Alloziere 200 kiB -> %p\n", addr[i] = ff_alloc(200 * 1024));
	*addr[i] = 'A';
	i++;
	dump_memory();
	
	printf("Alloziere   0   B -> %p\n", addr[i++] = ff_alloc( 0 ));
	dump_memory();
	
	printf("Alloziere  40 kiB -> %p\n", addr[i] = ff_alloc( 40 * 1024));
	*addr[i] = 'A';
	i++;
	dump_memory();
	
	printf("Alloziere   1   B -> %p\n", addr[i++] = ff_alloc(1));
	dump_memory();

	return 0;
}
