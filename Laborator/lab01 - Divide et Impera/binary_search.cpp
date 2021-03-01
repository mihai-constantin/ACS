#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

vector <int> v;
int n;

int elem;
int contor;

void read(){
    
    int x;
    printf("n = ");
    scanf("%d", &n);
    printf("Introduceti elementele vectorului: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &x);
        v.push_back(x);
    }
    
    scanf("%d", &elem);
}

int binary_search(){
    int left, right, mid;
    
    left = 0;
    right = v.size() - 1;
    
    while(left <= right){
        mid = (left + right) / 2;
        
        contor++;
        if(v[mid] == elem){
            printf("count = %d\n", contor);
            return mid;
        }
        
        if(elem > v[mid]){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    
    return -1;
}

int main(void){
    
    read();
    printf("pos = %d\n", binary_search());
    
    
    return 0;
}
