CONSTANTIN MIHAI - 321CD
Tema 3 - ER Simulator

In cadrul acestei teme am simulat intr-un design orientat pe obiecte un sistem
simplificat de Emergency Room.
In implimentarea acesteia, am folosit un behavioural pattern (Observer) si
doua creational patterns(Singleton si Factory).

Structura temei este organizata sub forma unor pachete si clase, dupa cum
urmeaza:

-> pachetul entities contine urmatoarele clase
- Doctor:	structura de baza a unui doctor. Pe langa informatia citita din
		fisierul de intrare, am adaugat factorii de ameliorare C1, C2,
		o lista a afectiunilor tratate, cat si o lista a pacientilor
		internati. 
		Clasa este extinsa de urmatoarele clase (tipurile de doctori):
		-> Cardiologist
		-> ER_Physician
		-> Gastroenterologist
		-> GeneralSurgeon
		-> Internist
		-> Neurologist

		Fiecare subclasa a lui Doctor este folosita in clasa DoctorFactory
		din pachetul factories pentru a crea obiectul specializat.
		Se seteaza factorii C1 si C2 specifici pentru fiecare tip de doctor
		si se formeaza lista de afectiuni pe care le poate trata doctorul
		in cauza.

- Patient:	structura de baza a unui pacient. Pe langa informatia citita din
		fisierul de intrare, am adaugat status-ul, rezultatul investigatiei
		(initial NOT_DIAGNOSED) pacientului de catre ERTechnician, tipul
		urgentei (initial NOT_DETERMINED) si numarul de zile(runde) pe care 
		pacientul trebuie sa le petreaca in spital in caz de internare.

- ERTechnician:	decide daca un pacient trebuie operat, internat sau trimis 
		acasa cu tratament. Deoarece nu avem nevoie de mai multe
		instante ale clasei, am folosit pattern-ul Singleton.

- Nurses:	trateaza fiecare pacient spitalizat. In urma ingrijirilor primite,
		severitatea pacientului scade cu valoarea T si numarul de runde 
		cat timp va fi aplicat tratamentul scade cu 1

-> pachetul input contine clasa InputFile ce reprezinta structura de baza a
   fisierului de intrare. Contine campul simulationLength, nurses, 
   investigators si listele cu doctorii si pacientii ce vor fi tratati

-> pachetul stages contine 3 clase ce folosesc pattern-ul Singleton

- TriageQueue:	adauga intr-o coada pacientii ce trebuie sa intre in runda
		respectiva (campul time), iar primii numberOfNurses pacienti
		vor fi scosi din coada si adaugati in ExaminationQueue. Restul
		raman in triageQueue si vor fi examinati turele viitoare.

- ExaminationQueue:	pacientii din examinationQueue vor fi sortati dupa urgenta
			si vor fi consultati de catre doctori specializati. Daca
			nu exista niciun doctor care trateaza afectiunea
			pacientului, acesta va fi transferat la un alt spital.
			Daca am gasit un medic pentru pacient, avem doua situatii:
			- acesta a fost deja vizitat de catre un ERTechnician,
			caz in care pacientul este operat, internat, sau trimis
			acasa cu tratament in functie de rezultatul investigatiei
			- pacientul nu a fost trimis inca la investigatii, caz in
			care doctorul poate trimite pacientul acasa(daca nu este
			nimic grav) sau il poate trimite la un ERTechnician pentru
			investigatii

- InvestigationsQueue:	pacientii din investigationsQueue sunt sortati dupa
			urgenta afectiunii si primii numberOfInvestigators
			pacienti vor fi diagnosticati si trimisi inapoi in
			examinationQueue, restul ramanand in coada pentru
			turele viitoare

-> pachetul simulation contine urmatoarele clase
- Hospital:	instanta clasei este unica (Singleton) si reprezinta elementul 
		observabil pentru design pattern-ul Observer. Contine listele de 
		doctori si de pacienti.
- Simulation:	instanta clasei este unica (Singleton) si simuleaza fiecare
		runda. La finalul fiecarei runde, apelam metoda update() din 
		clasa Hospital

-> pachetul observers contine cele doua clase care implementeaza Observer
Elementul observabil este hospital (instanta unica a clasei Hospital).

- NextRound:		incrementeaza numarul rundei (campul numberOfRound din clasa
			Hospital)
- SituationPrinter:	afiseaza situatia fiecarei runde pentru pacienti, asistente
			si doctori

-> pachetul skel care contine clasele din scheletul temei

- enum-urile IllnessType (tipurile de afectiuni de care poate suferi un pacient),
InvestigationResult (rezultatele posibile oferite de un ERTechnician in urma
investigatiilor), State (starea actuala a pacientului) si Urgency (tipurile de
urgenta pentru un pacient - cat de grava este afectiunea suferita)

- clasa UrgencyEstimator:	clasa cu instantiere unica (Singleton) care 
				determina prin metoda estimateUrgency(), cat de
				grava este afectiunea suferita de un pacient

-> pachetul utils contine  clase folosite de-a lungul implementarii temei

- PatientComparator:	comparator folosit pentru sortarea unui array de pacienti
			in functie de urgency (crescator), severity (descrescator) 
			si name (descrescator)
- SeverityComparator:	comparator folosit pentru sortarea unui array de 
			pacienti in functie de severity (descrescator)
- Severity:	enum pentru valorile ce exprima cat de grava este afectiunea 
		unui pacient
- PatientState:	starea unui pacient (illnessName + severity)		

-> clasa Main:	entry-point-ul aplicatiei care nu se afla in niciun pachet
		In aceasta clasa se realizeaza efectiv maparea din fisierul de intrare, 
		cu ajutorul API-ului pus la dispozitie de catre biblioteca Jackson 
		pentru fisierele in format JSON. Se adauga observatorii pentru hospital 
		si se realizeaza simularea efectiva.


