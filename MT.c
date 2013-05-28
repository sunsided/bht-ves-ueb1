/*****************************************************************************
*                                                                            *
*      Beispiel f�r einen minimalen Multithreading-Betrieb (MT-Betrieb)      *
*                      auf einem Prozessor der 8051-Familie                  *
*                                                                            *
*  to do: siehe Aufgabenblatt zur 1. Aufgabe                                 *
*                                                                            *
*****************************************************************************/
 
/*****************************************************************************
*                                                                            *
*                              A C H T U N G                                 *
*                                                                            *
*    - Unbedingt in �Vision unter "Options > BL51 > Size/Location"           *
*      RamSize auf 256 setzen!                                               *
*                                                                            *
*    - "Lokale" Variablen in einem Thread oder einer von ihm aufgerufenen    *
*      Funktion als static definieren!                                       *
*                                                                            *
*    - Verwenden Sie f�r Funktionen, die aus der Int-Funktion, bzw. einer    *
*      Thread-Funktion aufgerufen werden, mit "using n" immer die richtige   *
*      Registerbank                                                          *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include <assert.h>
#include "rtos/rtos.h"

// Alle Threads laufen in Registerbank 0
void thread0(void)
{
	static int i = 0;

	while(1) {			// PROBLEM: nullter Thread wird nie betreten.
		i++;    
	}
}


void thread1(void)
{
	static int i = 0;

	while(1) {
		i++;
		printf("T1 i = %d\n", i);
	}
}


void thread2(void)
{
	static int i = 0;
	
	while(1) {
		i++;
	}
}


void thread3(void)
{
	static int i = 0;
	
	while(1) {
		i++;
	}
}


void thread4(void)
{
	int i = 0;
	
	while(1) {
		i++;
	}
}

/**
* Sichert �ber eine Assertion, dass der Thread registriert wurde.
*/
#define ASSERT_THREAD_REGISTERED(threadno) \
	assert(THREAD_REGISTER_ERROR != (threadno))

/**
* Registriert die user threads.
*/
void register_threads() {
	threadno_t thread;
		
	thread = register_thread(thread0, PRIO_NORMAL, "Erster Thread");
	ASSERT_THREAD_REGISTERED(thread);
	printf("thread0 registriert als ID %u.\r\n", (uint16_t)thread); // NOTE: Cast ist ein Fix f�r endianness
	
	thread = register_thread(thread1, PRIO_NORMAL, "Zweiter Thread");
	ASSERT_THREAD_REGISTERED(thread);
	printf("thread1 registriert als ID %u.\r\n", (uint16_t)thread);
	
	thread = register_thread(thread2, PRIO_NORMAL, "Dritter Thread");
	ASSERT_THREAD_REGISTERED(thread);
	printf("thread2 registriert als ID %u.\r\n", (uint16_t)thread);
	
	thread = register_thread(thread3, PRIO_NORMAL, "Vierter Thread");
	ASSERT_THREAD_REGISTERED(thread);
	printf("thread3 registriert als ID %u.\r\n", (uint16_t)thread);
}

void main(void) {
	init_os();
	register_threads();
	
	// Starten des Multithreading
	// Diese Funktion terminiert nie!
	start_os();							
}
