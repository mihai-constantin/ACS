#include <iostream>
#include <vector>
#include <fstream>

int binary_search(const std::vector <int> &v, int i, int j, const int x){
    
    int left = i;
    int right = j;
    
    while(left <= right){
        int mid = (left + right) / 2;
        
        if(v[mid] == x){
            return mid;
        }
        
        if(x > v[mid]){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    
    return -1;
}

int main(void){
    
    int n, x, k;
    
    std::ifstream f("data.in");
    
    std::vector<int> v;

    f >> n;
    for(int i = 0; i < n; i++){
        f >> x;
        v.push_back(x);
    }
    f >> k;
    
    for(int i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << '\n';
    
    std::cout << "Element de cautat: ";
    std::cin >> x;
    if(x >= v[0]){
        std::cout << binary_search(v, 0, n - k - 1, x) << '\n';
    }
    else{
        std::cout << binary_search(v, n - k, v.size() - 1, x) << '\n';
    }
    
    return 0;
}
