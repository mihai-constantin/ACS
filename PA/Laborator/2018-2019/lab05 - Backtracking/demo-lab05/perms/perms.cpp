#include <iostream>
#include <vector>
#include <unordered_set>

bool check(std::vector<int> &solution) {
    return true;
}

bool printSolution(std::vector<int> &solution) {
    for (auto s : solution) {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

void back(int step, int stop, std::vector<int> &domain,
        std::vector<int> &solution, std::unordered_set<int> &visited) {
    /* vom verifica o solutie atunci cand am adaugat deja N elemente in solutie,
    adica step == stop */
    if (step == stop) {
        /* deoarece am avut grija sa nu se adauge duplicate, "check()" va returna
        intotdeauna "true" */
        if(check(solution)) {
            printSolution(solution);
        }
        return;
    }

    /* Adaugam in solutie fiecare element din domeniu care *NU* a fost vizitat
    deja renuntand astfel la nevoia de a verifica duplicatele la final prin
    functia "check()" */
    for (unsigned int i = 0; i < domain.size(); ++i) {
        /* folosim elementul doar daca nu e vizitat inca */
        if (visited.find(domain[i]) == visited.end()) {
            /* il marcam ca vizitat si taiem eventuale expansiuni nefolositoare
            viitoare (ex: daca il adaug in solutie pe 3 nu voi mai avea
            niciodata nevoie sa il mai adaug pe 3 in continuare) */
            visited.insert(domain[i]);

            /* adaugam elementul curent in solutie pe pozitia pasului curent
            (step) */
            solution[step] = domain[i];

            /* apelam recursiv backtracking pentru pasul urmator */
            back(step + 1, stop, domain, solution, visited);

            /* stergem vizitarea elementului curent (ex: pentru N = 3, dupa ce
            la pasul "step = 0" l-am pus pe 1 pe prima pozitie in solutie si
            am continuat recursiv pana am ajuns la solutiile {1, 2, 3} si
            {1, 3, 2}, ne dorim sa il punem pe 2 pe prima pozitie in solutie si
            sa continuam recursiv pentru a ajunge la solutiile {2, 1, 3} etc.) */
            visited.erase(domain[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./perms n\n";
        exit(1);
    }

    int n = atoi(argv[1]);
    /* dupa ce am citit n initializam domeniul cu n elemente, numerele de la 1 la n,
    iar solutia este initializata cu un vector de n elemente (deoarece o permutare
    contine n elemente) */
    std::vector<int> domain(n), solution(n);
    std::unordered_set<int> visited;
    for (int i = 0; i < n; ++i) {
        domain[i] = i + 1;
    }

    /* apelam back cu step = 0 (atatea elemente avem adaugate in solutie),
    stop = n (stim ca vrem sa adaugam n elemente in solutie pentru ca o
    permutare e alcatuita din n elemente), domain este vectorul de valori
    posibile, solution este vectorul care simuleaza stiva pe care o vom
    umple, visited este un unordered_set (initial gol) in care retinem daca
    un element din domeniu se afla deja in solutia curenta la un anumit pas */
    back(0, n, domain, solution, visited);
}