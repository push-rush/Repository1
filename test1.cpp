#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    int N,m;
    int p[m],v[m];
    int dp[m];
    int f[25][30000];
    cin>>N>>m;
    for(int i = 0; i < m; i++)
    {
        cin>>p[i]>>v[i];
        dp[i] = p[i] * v[i];
    }
    for(int i = 0; i < m; i++)
        for(int j = 0; j < N; j++)
        {
            if(p[i] <= j)
            {
                f[i][j] = max(f[i - 1][j],dp[i] + f[i - 1][j - p[i]]);
            }
            else
            {
                f[i][j] = f[i - 1][j];
            }
        }
    cout<<f[m - 1][N - 1];
    return 0;
}