#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
typedef long long int ll;
typedef long double ld;
typedef pair<ll, ll> ii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

#define MAXN 200

vector<ii> graph[MAXN];
ll father[MAXN];
ll dist[MAXN];
bool informed[MAXN];
ll vcnt[MAXN];

void dijkstra(ll begone)
{
  set<ii> pq;
  
  pq.insert(mp(0, begone));
  memset(dist, INF, sizeof(dist));
  memset(father, -1, sizeof(father));
  dist[begone] = 0;
  father[begone] = begone;

  while(!pq.empty())
  {
    ii cur = *pq.begin();
    pq.erase(pq.begin());
    ll u = cur.second;
    ll w = cur.first;
    if(dist[u] < w) continue;
    
    for(ii p : graph[u])
    {
      ll v = p.first;
      ll we = p.second;
      if(dist[u]+we < dist[v])
      {
        dist[v] = dist[u]+we;
        father[v] = u;
        pq.insert(mp(dist[v], v));
      }
    }
  }
}

int main()
{
  ios::sync_with_stdio(false);
  
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
    
    graph[u].pb(mp(v, 100-c));
    graph[v].pb(mp(u, 100-c));
    informed[u] = informed[v] = true;
  }
  n += 1;
  
  for(int i = 0; i < n; i++)
  {
    if(informed[i])
    {
      dijkstra(i);
      for(int j = 0; j < n; j++)
      {
        if(informed[j])
        {
          int p = father[j];
          while(p != i)
          {
            vcnt[p]++;
            p = father[p];
          }
        }
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
