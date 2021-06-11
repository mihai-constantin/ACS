#include <iostream>
#include <vector>
#include <fstream>

int main(void){
    
//    std::ifstream f("data.in");
//    std::ofstream g("data.out");
    
    std::vector<int> v;
    int n, x;
    std::cin >> n;
    for(int i = 0; i < n; i++){
        std::cin >> x;
        v.push_back(x);
    }
    
    for(int i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    
    std::cout << '\n';
    
    return 0;
}
