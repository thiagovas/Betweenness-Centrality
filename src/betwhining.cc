// Don't mind this code.
// I understood the school work wrong.
// Betwhining is the wrong version of betweenness.

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

int n;
vector<ii> graph[MAXN];
vector<int> gtmp[MAXN];
ll father[MAXN];
ll dist[MAXN];
bool informed[MAXN];
ll vcnt[MAXN], vtmp[MAXN];
ll inDegree[MAXN];
bool visited[MAXN];
stack<int> topo;


void dfs(int u)
{
  if(visited[u]) return;
  visited[u] = true;

  for(int v : gtmp[u])
    if(!visited[v]) dfs(v);
  topo.push(u);
}


void backcnt()
{
  // TopoSort
  memset(visited, false, sizeof(visited));
  memset(vtmp, 0, sizeof(vtmp));
  while(!topo.empty()) topo.pop();
  for(int i = 0; i < n; i++)
    if(!visited[i]) dfs(i);
  
  for(int i = 0; i < n; i++)
  {
    cout << i << ":";
    for(int v : gtmp[i])
      cout << " " << v;
    cout << endl;
  }

  // Updating vtmp...
  while(!topo.empty())
  {
    int cur = topo.top();
    topo.pop();
    
    if(inDegree[cur] == 0) vtmp[cur] = 1;
    for(int v : gtmp[cur])
      vtmp[v] += vtmp[cur];
  }
  
  for(int i = 0; i < n; i++)
    if(inDegree[i] == 0 || gtmp[i].size() == 0)
      vtmp[i] = 0;
  
  for(int i = 0; i < n; i++)
  {
    cout << i << ":" << vtmp[i] << " ";
    vcnt[i] += vtmp[i];
  }
  cout << endl << endl;
}

void dijkstra(ll begone)
{
  set<ii> pq;
  
  pq.insert(mp(0, begone));
  memset(dist, INF, sizeof(dist));
  memset(father, -1, sizeof(father));
  memset(inDegree, 0, sizeof(inDegree));
  dist[begone] = 0;
  for(int i = 0; i < MAXN; i++) gtmp[i].clear();
  
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
        gtmp[v].clear();
        gtmp[v].pb(u);
        pq.insert(mp(dist[v], v));
      }
      else if(dist[u]+we == dist[v])
        gtmp[v].pb(u);
    }
  }
  
  for(int i = 0; i < n; i++)
    for(int v : gtmp[i])
      inDegree[v]++;
  backcnt();
}

int main()
{
  ios::sync_with_stdio(false);
  
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
    if(informed[i])
      dijkstra(i);

  vector<pair<int, int> > vresp;
  for(int i = 0; i < MAXN; i++)
    if(informed[i]) vresp.pb(mp(-vcnt[i], i));
  sort(vresp.begin(), vresp.end());
  for(unsigned i = 0; i < vresp.size(); i++)
    cout << vresp[i].second << " " << -vresp[i].first << endl;
  
  return 0;
}
