#include<stdio.h>
int n,m,sol[20];
 
void scrie()
{
	for(int i=1;i<=m;++i)
		printf("%d ",sol[i]);
	printf("\n");
}
 
void back(int k)//completeaza elem de pe poz k din sol
{
	if(k==m+1)
	{
		scrie();
		return;
	}
	for(int i=1+sol[k-1] ; i<=n-m+k ; ++i)//aleg o valoare pt sol[k]
	{
		sol[k]=i;
		back(k+1);
	}
}
 
int main()
{
	freopen("submultimi.in","r",stdin);
	freopen("submultimi.out","w",stdout);
	scanf("%d",&n);
	for(m=1;m<=n;m++)
		back(1);
	return 0;
}
