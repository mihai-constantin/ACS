#include <iostream>
#include <vector>
#include <unordered_map>

/* deoarece numerele sunt sterse din domeniu odata ce sunt folosite, solutia generata este garantata sa nu contina duplicate. Astfel, atunci cand domeniul ajunge vid, solutia este intotdeauna corecta */
bool check(std::vector<int> solution) {
    return true;
}

bool printSolution(std::vector<int> &solution) {
    for (int s : solution) {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

void back(std::vector<int> &domain, std::vector<int> &solution) {
    /* dupa ce am folosit toate elementele din domeniu putem verifica daca
    am gasit o solutie */
    if (domain.size() == 0) {
        if(check(solution)) {
            printSolution(solution);
        }
        return;
    }

    /* incercam sa adaugam in solutie toate valorile din domeniu, pe rand */
    for (unsigned int i = 0; i < domain.size(); ++i) {
        /* retinem valoarea pe care o scoatem din domeniu ca sa o readaugam dupa
        apelarea recursiva a backtracking-ului */
        int tmp = domain[i];

        /* adaug elementul curent la potentiala solutie */
        solution.push_back(domain[i]);
        /* sterg elementul curent din domeniu ca sa il pot pasa prin referinta
        si sa nu fie nevoie sa creez alt domeniu */
        domain.erase(domain.begin() + i);

        /* apelez recursiv backtracking pe domeniul si solutia modificate */
        back(domain, solution);

        /* refac domeniul si solutia la modul in care aratau inainte de apelarea
        recursiva a backtracking-ului, adica readaug elementul eliminat in
        domeniu si il sterg din solutie */
        domain.insert(domain.begin() + i, tmp);
        solution.pop_back();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./perms_ref n\n";
        exit(1);
    }

    int n = atoi(argv[1]);
    /* dupa ce am citit n initializam domeniul cu n elemente, numerele de la 1 la n,
    iar solutia este vida initial */
    std::vector<int> domain(n), solution;
    for (int i = 0; i < n; ++i) {
        domain[i] = i + 1;
    }

    /* apelam backtracking pe domeniul nostru, cautand solutia in vectorul solution */
    back(domain, solution);
}
