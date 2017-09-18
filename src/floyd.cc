#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

#define MAXN 200

int graph[MAXN][MAXN];
int father[MAXN][MAXN];
bool informed[MAXN];
int vcnt[MAXN];

void clean()
{
  for(int i = 0; i < MAXN; i++)
    for(int j = 0; j < MAXN; j++)
      father[i][j] = -1;

  memset(vcnt, 0, sizeof(vcnt));
  memset(graph, INF, sizeof(graph));
}

void floyd(int n)
{
  for(int i = 0; i < MAXN; i++) graph[i][i] = 0;
  
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(graph[i][j] != INF)
        father[i][j] = i;
  
  for(int k = 0; k < n; k++)
  {
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
      {
        if(graph[i][j] > graph[i][k] + graph[k][j])
        {
          father[i][j] = father[k][j];
          graph[i][j] = graph[i][k] + graph[k][j];
        }
      }
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  
  clean();
  int n = 0;
  while(true)
  {
    int u, v, c;
    cin >> u;
    cin.get();
    cin >> v;
    cin.get();
    cin >> c;
    if(not cin) break;
    if(u == 0 && v == 0 && c == 0) break;

    n = max(n, u);
    n = max(n, v);
    graph[u][v] = graph[v][u] = 100-c;
    informed[u] = informed[v] = true;
  }
  n += 1;
  
  floyd(n);
  
  for(int i = 0; i < n; i++)
  {
    if(!informed[i]) continue;
    for(int j = 0; j < n; j++)
    {
      if(!informed[j]) continue;
      
      int p = father[i][j];
      while(p != i)
      {
        if(p == -1) return 0;
        vcnt[p]++;
        p = father[i][p];
      }
    }
  }

  vector<pair<int, int> > vresp;
  for(int i = 0; i < MAXN; i++)
    if(informed[i]) vresp.pb(mp(-vcnt[i], i));
  sort(vresp.begin(), vresp.end());
  for(unsigned i = 0; i < vresp.size(); i++)
    cout << vresp[i].second << " " << -vresp[i].first << endl;
  
  return 0;
}
