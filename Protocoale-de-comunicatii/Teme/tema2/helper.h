// Protocoale de comunicatii
// Tema 2
// Constantin Mihai - 321CD

#ifndef _HELPERS_H
#define _HELPERS_H 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIE(assertion, call_description)	\
	do {									\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",	\
					__FILE__, __LINE__);	\
			perror(call_description);		\
			exit(EXIT_FAILURE);				\
		}									\
	} while(0)

#define BUFLEN		1600	// dimensiunea maxima a calupului de date
#define MAX_CLIENTS	10	// numarul maxim de clienti in asteptare

// formatul mesajelor pentru clientii UDP
// folosim pragma pack(1) pentru a evita crearea padding-ului
#pragma pack(push, 1)
typedef struct Message_UDP {

	char topic[50];
	uint8_t tip_date;

	union continut {

		struct MyInteger {
			uint8_t sign;
			uint32_t networkByteOrder;
		} MyInteger;

		struct MyShortReal {
			uint16_t nb;
		} MyShortReal;

		struct MyFloat {
			uint8_t sign;
			uint32_t networkByteOrder;
			uint8_t power;
		} MyFloat;

		struct MyString {
			char messsage[1500];
		} MyString;

	} continut;

} Message_UDP;
#pragma pack(pop)

/*
 * Functie auxiliara folosita pentru a verifica corectitudinea mesajelor
 * primite. Tratam cele 4 cazuri, in functie de valoarea tipului de data: INT, 
 * SHORT_REAL, FLOAT, STRING
*/

void writeToConsole(Message_UDP message_UDP, struct sockaddr_in from_station) {
	uint8_t tipdate = message_UDP.tip_date;

	switch(tipdate) {
		// INT
		case 0:
		{	
			uint32_t number;
			number = ntohl(message_UDP.continut.MyInteger.networkByteOrder);
			if(message_UDP.continut.MyInteger.sign == 1) {
				number = -number;
			}
			// IP:PORT client_UDP - topic - tip_date - valoare mesaj
			printf("%s:%d - %s - INT - %d\n", inet_ntoa(from_station.sin_addr), 
					ntohs(from_station.sin_port), message_UDP.topic, number);

		}
			break;

		// SHORT_REAL
		case 1:
		{	
			float number;
			number = (float)(ntohs(message_UDP.continut.MyShortReal.nb)) / 100;
			// IP:PORT client_UDP - topic - tip_date - valoare mesaj
			printf("%s:%d - %s - SHORT_REAL - %.2f\n", 
					inet_ntoa(from_station.sin_addr), 
					ntohs(from_station.sin_port), message_UDP.topic, number);

		}
			break;

		// FLOAT
		case 2:
		{
			uint32_t number;
			number = ntohl(message_UDP.continut.MyFloat.networkByteOrder);
			int power = message_UDP.continut.MyFloat.power;
			float number1 = (float)(number) / pow(10, power);

			if(message_UDP.continut.MyFloat.sign == 1) {
				number1 = -number1;
			}

			printf("%s:%d - %s - FLOAT - %.*f\n", 
					inet_ntoa(from_station.sin_addr), 
					ntohs(from_station.sin_port), message_UDP.topic, 
					power, number1);
		}
			break;

		// STRING
		default:
			printf("%s:%d - %s - STRING - %s\n", 
				inet_ntoa(from_station.sin_addr),
				ntohs(from_station.sin_port), message_UDP.topic, 
				message_UDP.continut.MyString.messsage);

			break;
	}
}

#endif
