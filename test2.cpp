#include <iostream>
using namespace std;

int m,n;
char mp[50][50];
//int p[8] = {0,0,1,-1,-1,1,0,0};
int p[2][4] = {(0,1,0,-1),(1,0,-1,0)};
void dfs(int x, int y)
{
	if(x < 0 || x >= m || y < 0 || y >= n || mp[x][y] == '*') 
	{
		return;
	}
	mp[x][y] = '*';
	for(int i = 0 ; i < 4; i++)
	{
		//dfs( x + p[i], y + p[i+4]);
		dfs( x + p[0][i], y + p[1][i]);
	}
}
int main()
{   
	int sum = 0;
	cin>>m>>n;
	for(int i = 0 ; i < m ; i++)
	{
		cin>>mp[i];
	}
	for(int i = 0 ; i < m; i++)
		for(int j = 0 ; j < n; j++)
		{
			if( (i == 0 || i == m - 1 || j == 0 || j == n - 1) && mp[i][j] == '0')
			{
				dfs(i,j);
			}
		}
	for(int i = 0 ; i < m; i++)
		for(int j = 0 ; j < n; j++)
		{
			if(mp[i][j] == '0') sum++;
		}
	cout<<sum;
	return 0;
}
