#include "4b.h"
#include <stdio.h>

void ff_free(void *addr)
{
	// Diese Funktion sollt ihr implementieren


	if(addr == NULL){
        return;
	}

	if(addr < &heap[0] || addr > &heap[CHUNK_SIZE * NUM_CHUNKS - 1]){
        exit(255);
	}
	
	
	/*
	 * chunk_index ist der Index des Chunks, in dem addr liegt.
	 */
	size_t chunk_index = ((char*)addr - heap) / CHUNK_SIZE;

	if(allocation_list[chunk_index].length == 0){
        exit(255);
	}

	int lower_chunk_index = chunk_index - 1;
	int upper_chunk_index = chunk_index + 1;

    while (upper_chunk_index < NUM_CHUNKS && allocation_list[upper_chunk_index].length == 0){
        ++upper_chunk_index;
    }

    while (lower_chunk_index >= 0 && allocation_list[lower_chunk_index].length == 0){
        --lower_chunk_index;
    }

    if(upper_chunk_index < NUM_CHUNKS && allocation_list[upper_chunk_index].status == CHUNK_FREE){
        allocation_list[chunk_index].length = allocation_list[chunk_index].length + allocation_list[upper_chunk_index].length;
        allocation_list[upper_chunk_index].length = 0;
    }

    allocation_list[chunk_index].status = CHUNK_FREE;

    if(lower_chunk_index >= 0 && allocation_list[lower_chunk_index].status == CHUNK_FREE){
        allocation_list[lower_chunk_index].length = allocation_list[lower_chunk_index].length + allocation_list[chunk_index].length;
        allocation_list[chunk_index].length = 0;
    }

}
