#include "4a.h"
// Hier ggf. weitere Includes

/*
 * Hier könnt ihr ggf. benötigte globale Varibalen und/oder Hilfsfunktionen ablegen
 */

void *ff_alloc(size_t size)
{
	/*
	 * Diese Funktion sollt ihr implementieren.
	 */
	
	
	/*
	 * Der Laufindex
	 */
	 size_t chunk_index;

	 
	 
	/*
	 * Gibt die Startadresse des belegten Speicher zurück. 
	 */
	return heap + chunk_index * CHUNK_SIZE;
}
