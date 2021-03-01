CONSTANTIN MIHAI - 321CD

Tema implementeaza un sistem de versionare (Version Control System) ce permite
salvarea starii curente a unui sistem de fisiere, cat si revenirea la versiuni
anterioare ale acestuia.
Pentru implementarea comenzilor unix, am folosit scheletul de cod.

In pachetul vcs, am adaugat urmatoarele clase:

-> Branch 		
-	cuprinde ca atribute ale clasei numele branch-ului, cat si lista de 
	commit-uri ale acestuia
-	metode: setteri si getteri pentru campuri

-> Commit
-	cuprinde ca atribute ale clasei id-ul commit-ului, mesajul, cat si starea 
	sistemului de fisiere corespunzatoare		
-	metode: setteri si getteri pentru campuri

Urmatoarele clase definesc fiecare operatie pentru VCS, extinzand clasa 
abstracta VcsOperation, si facand override la metoda execute(Vcs vcs). 

-> StatusOperation
-	afiseaza branch-ul curent si ce schimbari s-au produs de la ultimul commit

-> BranchOperation 
-	creeaza un nou branch si un prim commit pentru acesta cu aceeasi stare 
	a sistemului de fisiere ca cel al commit-ului curent
- 	daca exista deja un branch cu acelasi nume ca cel pe care vrem sa-l cream, 
	returnam ErrorCodeManager.VCS_BAD_CMD_CODE(-1)

-> CommitOperation
-	creeaza un nou commit daca exista cel putin o operatie in staging
-	daca staging-ul este vid, returnam ErrorCodeManager.VCS_BAD_CMD_CODE(-1)

-> CheckOutOperation
-	muta pointerul HEAD pe un commit anterior al branch-ului curent sau 
	pe ultimul commit al unui alt branch, daca nu exista operatii in staging
- 	daca id-ul commitului sau branch-ul pe care dorim sa ne mutam nu exista,
	returnam eroare 

-> LogOperation
-	afiseaza id-ul si mesajul fiecarui commit din branch-ul curent

-> RollBackOperation
- 	goleste staging-ul si aduce snapshot-ul de filesystem la versiunea data 
	de ultimul commit

-> InvalidVcsOperation
-	returneaza ErrorCodeManager.VCS_BAD_CMD_CODE(-1)