#include <stdio.h>
#include <stdlib.h>
 
const int mod = 9917;
const int dmax = 100000;
 
int v[dmax+1], aux[dmax+1];
int N;
 
int interclasare(int st, int dr)
{
    int i,j,k,m;
    int inv_count = 0;
 
    i = k = st; m = (st+dr)/2; j = m+1;
 
    while(i <= m && j <= dr)
        if(v[i] <= v[j]) aux[k++] = v[i++];
            else
            {
                aux[k++] = v[j++];
                inv_count += m - i + 1;
            }
 
    while(i <= m)
        aux[k++] = v[i++];
 
    while(j <= dr)
        aux[k++] = v[j++];
 
    for(int i = st; i <= dr; i++)
        v[i] = aux[i];
 
    return inv_count;
}
 
int divide(int st, int dr)
{
    int inv_count = 0;
 
    if(st == dr) return 0;
 
    int m = (st+dr)/2;
 
    inv_count += divide(st,m);
    inv_count += divide(m+1,dr);
 
    inv_count += interclasare(st,dr);
 
    return inv_count % mod;
}
 
int main()
{
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
        scanf("%d", &v[i]);
 
    printf("%d\n", divide(1, N));
 
    return 0;
}
