#include <iostream>
#include <vector>
#include <unordered_map>

/* deoarece numerele sunt sterse din domeniu odata ce sunt folosite, solutia
generata este garantata sa nu contina duplicate. Astfel, atunci cand domeniul
ajunge vid, solutia este intotdeauna corecta */
bool check(std::vector<int> solution) {
    for (unsigned i = 0; i < solution.size(); ++i) {
        for (unsigned j = i + 1; j < solution.size(); ++j) {
            if (solution[i] == solution[j]) {
                return false;
            }
        }
    }

    return true;
}

bool printSolution(std::vector<int> solution) {
    for (int s : solution) {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

void back(std::vector<int> domain, std::vector<int> solution) {
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
        /* cream o solutie noua si un domeniu nou care sunt identice cu cele
        de la pasul curent */
        std::vector<int> newSolution(solution), newDomain(domain);

         /* adaugam in noua solutie elementul ales din domeniu */
        newSolution.push_back(domain[i]);
         /* stergem elementul ales din noul domeniu */
        newDomain.erase(newDomain.begin() + i);

        /* apelam recursiv backtracking pe noul domeniu si noua solutie */
        back(newDomain, newSolution);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./perms_general n\n";
        exit(1);
    }

    int n = atoi(argv[1]);
    /* dupa ce am citit n initializam domeniul cu n elemente, numerele de la 1
    la n, iar solutia este vida initial */
    std::vector<int> domain(n), solution;
    for (int i = 0; i < n; ++i) {
        domain[i] = i + 1;
    }

    /* apelam backtracking pe domeniul nostru, cautand solutia in vectorul
    solution */
    back(domain, solution);
}