#include "4a.h"
#include <stdio.h>
// Hier ggf. weitere Includes

/*
 * Hier könnt ihr ggf. benötigte globale Varibalen und/oder Hilfsfunktionen ablegen
 */

void *ff_alloc(size_t size)
{
	/*
	 * Diese Funktion sollt ihr implementieren.
	 */

	if(size <= 0){
        return NULL;
	}

	size_t chunks_needed = size_to_chunks(size);
	
	
	/*
	 * Der Laufindex
	 */
	 size_t chunk_index;
	 int allocation_possible = 0;


     for (chunk_index = 0; chunk_index < NUM_CHUNKS ; ++chunk_index) {

        if(allocation_list[chunk_index].length != 0 && allocation_list[chunk_index].status == CHUNK_FREE){
            if(allocation_list[chunk_index].length >= chunks_needed) {

                allocation_possible = 1;
                break;
            }
        }

        /*
        if(allocation_list[chunk_index].status == CHUNK_ALLOCATED){
            chunk_index = chunk_index + allocation_list[chunk_index].length;
        }
         */

    }

    if(!allocation_possible){
        return NULL;
    } else {

        int upper_chunk_index = chunk_index + 1;

        while (upper_chunk_index < NUM_CHUNKS && allocation_list[upper_chunk_index].length == 0){
            ++upper_chunk_index;
        }

        allocation_list[chunk_index].status = CHUNK_ALLOCATED;
        allocation_list[chunk_index].length = chunks_needed;

        if(allocation_list[chunk_index + chunks_needed].length == 0){
            allocation_list[chunk_index + chunks_needed].status = CHUNK_FREE;
            allocation_list[chunk_index + chunks_needed].length = upper_chunk_index - (chunk_index + chunks_needed);
        }

    }

	/*
	 * Gibt die Startadresse des belegten Speicher zurück. 
	 */
	return heap + chunk_index * CHUNK_SIZE;
}
