#include <vector>
#include <fstream>
#include <iostream>
#include <fstream>
#include <map>

struct Complex {
    // Partea reala
    float r;
    // Partea imaginara
    float i;
};

std::ostream& operator<<(std::ostream &stream, Complex c)
{
    stream << "(" << c.r << ", " << c.i << ")";
    return stream;
}

std::vector<Complex> get_sorted(const std::vector<Complex> &v);

std::map<Complex, int> get_mapping(const std::vector<Complex> &v);

bool operator<(const Complex &a, const Complex &b);

std::vector<Complex> read_data(const char* filename)
{
    std::ifstream f(filename);
    int n;
    std::vector<Complex> res;

    // Citeste numarul de elemente din vector
    f >> n;
    // Citeste elementele
    while (n--) {
        Complex current;
        f >> current.r;
        f >> current.i;
        res.push_back(current);
    }
    return res;
}

void write_vector(const std::vector<Complex> &v)
{
    for (unsigned int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}
