// Protocoale de comunicatii
// Tema 2
// Constantin Mihai - 321CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <netinet/tcp.h>
#include "helper.h"

#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <unordered_map>

#define dmax 25

using namespace std;

/*
 * Utilizare: ./server server_port
 */

char buffer[BUFLEN];
char topic[BUFLEN];
char short_real_buf[dmax];
char short_float_buf[dmax];


// sursa de inspiratie
// https://thispointer.com/how-to-search-by-value-in-a-map-c/
int findByValue(unordered_map <int, string> mapOfElements, string value) {

	auto it = mapOfElements.begin();
	while(it != mapOfElements.end()) {
		if(it -> second == value) {
			return it -> first;
		}
		it++;
	}

	// nu am gasit cheia cautata
	return -1;
}

void usage(char *file)
{
	fprintf(stderr, "Usage: %s <server_port>\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc != 2){
		usage(argv[0]);
	}

	int ret, portno, i, sockfd, newsockfd, n, pos_elem;
	unsigned int j, k, space_pos;
	struct sockaddr_in subs_addr;
	socklen_t subs_len;
	socklen_t socklen = sizeof(struct sockaddr);

	// creare socket TCP
	int domain = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;

	sockfd = socket(domain, type, protocol);
	DIE(sockfd < 0, "socket TCP");

	fd_set read_fds; // multimea de citire folosita in select()
	fd_set tmp_fds; // multimea folosita temporar
	int fdmax; // valoare maxima fd din multimea read_fds

	// se goleste multimea de descriptori de citire (read_fds)
	// si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	// server_port
	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	struct sockaddr_in serv_addr;

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = domain;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// legare proprietati de socket
	ret = bind(sockfd, (struct sockaddr*) &serv_addr, socklen);
	DIE(ret < 0, "bind");

	// ascultare de conexiuni
	ret = listen(sockfd, MAX_CLIENTS);	
	DIE(ret < 0, "listen");

	// se adauga noul file descriptor (socket-ul pe care se asculta conexiuni) 
	// in multimea read_fds
	FD_SET(sockfd, &read_fds);
	FD_SET(0, &read_fds); 		// stdin

	/*
	 * Map care face asocieri intre socket-ul fiecarul client si id-ul sau.
	*/
	unordered_map<int, string> umap1; // socket_client -> id_client

	/*
	 * Map care face asocieri intre topic-ul la care un client s-a abonat sau 
	 * dezabonat si lista de id_clienti abonati la topicul respectiv la un 
	 * moment dat.
	*/
	unordered_map<string, vector<string> > subscriptions;
	// vector folosit pentru stocarea temporara a id_clients la un topic
	vector<string> myVect;
	vector<string> myVect2;


	// dezactivarea algoritmului Neagle
	// toate comenzile si mesajele trimise in platforma isi vor produce
	// efectul imediat
	int flag = 1;
	setsockopt(sockfd,            /* socket affected */
                IPPROTO_TCP,     /* set option at TCP level */
                TCP_NODELAY,     /* name of option */
                (char *) &flag,  /* the cast is historical cruft */
                sizeof(int));    /* length of option value */

	/*
	 * SOCKET UDP
	*/

	int socketUDP;
	socketUDP = socket(PF_INET, SOCK_DGRAM, 0); // deschidere socket UDP

	// se adauga file descriptor-ul socket-ului UDP in multimea read_fds
	FD_SET(socketUDP, &read_fds);

	struct sockaddr_in from_station;
	// setare struct sockaddr_in pentru a specifica unde trimit datele
	from_station.sin_family = AF_INET;
	from_station.sin_port = htons(atoi(argv[1]));

	// legare de proprietati de socket
	bind(socketUDP, (struct sockaddr*) &from_station, socklen);

 	// maximul dintre socketii TCP si UDP
	fdmax = max(socketUDP, sockfd);

	Message_UDP message_UDP;

	/*
	 * Map-uri care trateaza cazurile cu SF = 1
	*/

	// id_client -> 1, daca clientul cu id_client e conectat
	// id_client -> 0, daca clientul cu id_client e deconectat
	unordered_map<string, bool> isConnected;

	// id_client -> lista de (topic, SF)
	unordered_map<string, vector<pair<string, int> > > storeAndForward;
	vector<pair<string, int> > myVectPair;

	unordered_map <string, vector<string> > myStorage;
	string forwardString;

	unordered_map <string, int> sfClient;

	while(1) {
		tmp_fds = read_fds;

		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		// citire de la tastatura
		if(FD_ISSET(0, &tmp_fds)) {
			memset(buffer, 0, BUFLEN);
			fgets(buffer, BUFLEN, stdin);
			if(strncmp(buffer, "exit\n", 5) == 0) {
				// inchidere server + inchidere clienti
				for(i = 0; i <= fdmax; i++) {
					close(i);
				}
			}
			close(sockfd);
			return 0;
		}

		for(i = 0; i <= fdmax; i++) {
			// i se afla in multimea temporara a descriptorilor
			if(FD_ISSET(i, &tmp_fds)) {

				// socket TCP
				if(i == sockfd) {
					// a venit o cerere de conexiune pe socketul inactiv 
					// (cel cu listen), pe care serverul o accepta
					subs_len = sizeof(subs_addr);
					newsockfd = accept(sockfd, (struct sockaddr *) &subs_addr, 
										&subs_len);
					DIE(newsockfd < 0, "accept");

					// se adauga noul socket intors de accept() la 
					// multimea descriptorilor de citire
					FD_SET(newsockfd, &read_fds);
					// update fdmax
					if(newsockfd > fdmax) {
						fdmax = newsockfd;
					}
				}
				else {
					// socket UDP
					if(i == socketUDP) {	

						memset(&message_UDP, 0, sizeof(Message_UDP));
						// primesc mesajul direct in structura de tip 
						// Message_UDP
						recvfrom(socketUDP, &message_UDP, sizeof(Message_UDP), 
							0, (struct sockaddr*) &from_station, &socklen);
						
						// prelucrare buffer pe care il trimit catre 
						// clientii TCP
						memset(buffer, 0, BUFLEN);

						// IP
						strcpy(buffer, inet_ntoa(from_station.sin_addr));
						strcat(buffer, ":");
						// PORT
						unsigned short int sinPort =  from_station.sin_port;
						string portUDP = to_string(ntohs(sinPort));
						strcat(buffer, portUDP.c_str());
						strcat(buffer, " - ");
						// TOPIC
						strcat(buffer, message_UDP.topic);
						strcat(buffer, " - ");

						uint8_t tipdate = message_UDP.tip_date;
						uint32_t netByteOrderInt = 
							message_UDP.continut.MyInteger.networkByteOrder;

						uint16_t nbReal = message_UDP.continut.MyShortReal.nb;

						uint32_t netByteOrderFloat = 
							message_UDP.continut.MyFloat.networkByteOrder;

						switch(tipdate) {
							// INT
							case 0:
							{
								int number = ntohl(netByteOrderInt);
								if(message_UDP.continut.MyInteger.sign == 1) {
									number = -number;
								}

								strcat(buffer, "INT");
								strcat(buffer, " - ");
								strcat(buffer, (to_string(number)).c_str());
							}
								break;

							// SHORT_REAL
							case 1:
							{
								float number;
								number = (float)(ntohs(nbReal)) / 100;

								strcat(buffer, "SHORT_REAL");
								strcat(buffer, " - ");
								sprintf(short_real_buf, "%.2f", number);
								strcat(buffer, short_real_buf);
							}
								break;
							// FLOAT
							case 2:
							{
								uint32_t number = ntohl(netByteOrderFloat);
								int power = message_UDP.continut.MyFloat.power;
								float nb1 = (float)(number) / pow(10, power);

								if(message_UDP.continut.MyFloat.sign == 1) {
									nb1 = -nb1;
								}

								strcat(buffer, "FLOAT");
								strcat(buffer, " - ");
								sprintf(short_float_buf, "%.*f", power, nb1);
								strcat(buffer, short_float_buf);
							}
								break;

							// STRING
							default:
							{
								strcat(buffer, "STRING");
								strcat(buffer, " - ");
								strcat(buffer, 
									message_UDP.continut.MyString.messsage);
							}
								break;
						}
						
						/*
						 * Pentru fiecare abonat la un topic, trimitem pe 
						 * socket-ului TCP mesaj-ul codificat in buffer.
						 */
						myVect2.clear();
						myVect2 = subscriptions[message_UDP.topic];
						for(j = 0; j < myVect2.size(); j++) {
							string x = myVect2[j];
							int sock_client = findByValue(umap1, x);

							// verific daca abonatul la care vreau sa trimit este deconectat
							if(isConnected[x] == true) {
								send(sock_client, buffer, BUFLEN, 0);
							}
							else {
								// vreau sa fac store la mesaje pentru a putea trimite 
								// dupa ce clientul se reconecteaza

								// daca SF = 0, nu fac store&forward la topicul respectiv
								myVectPair.clear();
								myVectPair = storeAndForward[x];
								for(auto& iter : myVectPair) {
									if(strcmp(iter.first.c_str(), message_UDP.topic) == 0) {
										if(iter.second == 1) {
											myVect.clear();
											myVect = myStorage[x];
											myVect.push_back(buffer);
											myStorage[x] = myVect;
											// break;
										}
									}
								}
							}
						}
					}
					else {
						// s-au primit date pe unul din socketii de client,
						// asa ca serverul trebuie sa le receptioneze
						memset(buffer, 0, BUFLEN);
						n = recv(i, buffer, sizeof(buffer), 0);
						DIE(n < 0, "recv");

						if(n == 0) {	
							// conexiunea s-a inchis
							printf("Client %s disconnected.\n", 
											umap1.at(i).c_str());

							// se scode din umap1 
							// (sock_client_deconectat, id_client)
							isConnected[umap1.at(i)] = false;

							umap1.erase(i);
							
							// se scote din multimea de citire socketul inchis
							FD_CLR(i, &read_fds);
							
							// inchidere socket client deconectat
							close(i);
						}
						else {
							// soket-ul clientului TCP nu exista
							// il adaugam in map-ul umap1
							if(umap1.find(i) == umap1.end()) {
								printf("New client %s connected from %s:%d.\n", 
									buffer, inet_ntoa(subs_addr.sin_addr), 
								ntohs(subs_addr.sin_port));

								umap1[i] = buffer;

								// iau cliend_id din socket-ul i
								isConnected[buffer] = true;

								myVect.clear();
								myVect = myStorage[buffer]; // myVector - vector<string>

								if(myStorage[buffer].empty() == false) {
									// afisare myStorage[buffer]

									forwardString.clear();
									for(j = 0; j < myVect.size() - 1; j++) {
										string x = myVect[j]; 
										forwardString = forwardString + x + '\n';
									}
									forwardString = forwardString + myVect[myVect.size() - 1];
									
									// trimit la clientul TCP
									send(i, forwardString.c_str(), BUFLEN, 0);

									myVect.clear();
									myStorage[buffer] = myVect;
								}
							}
							else {
								/* 
								 * Exista socket-ul in map-ul umap1.
								 * Trebuie sa tratam cazurile in care avem
								 * comanda subscribe sau unsubscribe.
								*/

								// subscribe
								if(strncmp(buffer, "subscribe", 9) == 0) {
									strcpy(topic, buffer + 10);
								}

								// unsubscribe
								if(strncmp(buffer, "unsubscribe", 11) == 0) {
									strcpy(topic, buffer + 12);
								}

								// space_pos -> unde se termina topic-ul
								for(j = 0; j < strlen(topic); j++) {
									if(topic[j] == ' ') {	
										space_pos = j;
										break;
									}
								}

								// subscribe - formare topic
								if(strncmp(buffer, "subscribe", 9) == 0) {
									memset(topic, 0, BUFLEN);
									for(j = 0; j < space_pos; j++) {
										topic[j] = buffer[j + 10];
									}

									int sf = buffer[strlen(buffer) - 2] - '0';
									pair<string, int> p(topic, sf);

									int pos_gasit = -1;
									myVectPair.clear();
									myVectPair = storeAndForward[umap1[i]];
									for(j = 0; j < myVectPair.size(); j++) {
										string t = myVectPair[j].first;
										if(t.compare(topic) == 0) {
											pos_gasit = j;
											break;
										}
									}

									if(pos_gasit != -1) {
										myVectPair[pos_gasit].second = sf;
									}
									else {
										// topicul nu este in vector -> trebuie adaugat
										myVectPair.clear();
										myVectPair = storeAndForward[umap1[i]];
										myVectPair.push_back(make_pair(topic, sf));
									}

									// update map
									storeAndForward[umap1[i]] = myVectPair;

									// update sfClient map
									sfClient[umap1[i]] = sf;

									// adaug topic in map, deoarece nu exista 
									if(subscriptions.find(topic) 
													== subscriptions.end()) {
										myVect.clear();
										
										/*
										 * Formare vector pentru a-l pune ca 
										 * valoare in map-ul subscriptions.
										 * In acest caz, vectorul contine un
										 * singur element, anume id_client-ul
										 * care s-a abonat la noul topic.
										*/
										myVect.push_back(umap1[i]);
										subscriptions[topic] = myVect;
									}
									else {
										/*
										 * Topicul exista deja. O sa adaugam
										 * id-ul noului client abonat la topic.
										*/
										myVect.clear();
										myVect = subscriptions[topic];
										myVect.push_back(umap1[i]);
										subscriptions[topic] = myVect;
									}
								}

								// unsubscribe - formare topic
								if(strncmp(buffer, "unsubscribe", 11) == 0) {
									memset(topic, 0, BUFLEN);
									for(j = 0; j < space_pos; j++) {
										topic[j] = buffer[j + 12];
									}

									myVect.clear();
									myVect = subscriptions[topic];
									
									/*
									 * Determinam pozitia id_client pe care il
									 * vom elimina de la topicul respectiv.
									*/
									
									for(k = 0; k < myVect.size(); k++) {
										string aux = myVect[k];
										string aux1 = umap1[i];
										if(!strcmp(aux.c_str(), aux1.c_str())) {
											pos_elem = k;
											break;
										}
									}

									// eliminare id_client de la topic
									myVect.erase(myVect.begin() + pos_elem);
									
									// actualizare vectorul id_clients pentru
									// topicul respectiv
									subscriptions[topic] = myVect;
								}

							}

						}
					}
				}
			}
		}
	}

	// inchidere socket
	close(sockfd);

	return 0;
}