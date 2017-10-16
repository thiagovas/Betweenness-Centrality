#include <algorithm>
#include <queue>
#include <set>
#include <stack>

#include "graph.h"

Graph::Graph(int nVertices)
{
  this->nVertices_ = nVertices;
  this->graph.resize(nVertices);
  this->vsigma.resize(nVertices, 0);
  this->vbetweenness.resize(nVertices, 0);
}

void Graph::addEdge(int u, int v, int c)
{
  this->graph[u].push_back(std::make_pair(v, c));
  this->graph[v].push_back(std::make_pair(u, c));
}

std::vector<long double> Graph::betweenness()
{
  // On this function I run a Dijkstra from every vertex.
  // Then, I compute the dependency values
  // Sum them all and return the betweennesses.
  
  
  // Running all Dijkstras, after this step,
  // vsigma and the dependency matrices will be computed.
  // As well as the vbetweenness vector.
  for(int i = 0; i < this->nVertices_; i++)
    dijkstra(i);
  
  return vbetweenness;
}

void Graph::dijkstra(int s)
{
  // Dijkstra's Priority Queue
  std::set<std::pair<long long int, std::pair<int, int> > > pq;
  
  std::vector<long long int> vDist(this->nVertices_, 0x3f3f3f3f3f3f3f3fll);
  std::stack<int> S;
  std::vector<std::vector<int> > vChildren(this->nVertices_);
  std::vector<bool> visited(this->nVertices_, false);
  
  this->vsigma.assign(this->nVertices_, 0);
  pq.insert(std::make_pair(0, std::make_pair(s, s)));
  vDist[s] = 0;
  vsigma[s] = 1;
  
  while(!pq.empty())
  {
    std::pair<int, std::pair<int, int> > cur = *pq.begin();
    pq.erase(pq.begin());
    int u = cur.second.first;
    long long int w = cur.first;
    int father = cur.second.second;
    if(vDist[u] < w) continue;
    
    
    vsigma[u] += vsigma[father];
    vChildren[u].push_back(father);
    
    if(visited[u]) continue;
    S.push(u);
    visited[u] = true;
    
    for(std::pair<int, int> pe : this->graph[u])
    {
      int v = pe.first;
      long long int we = pe.second;
      if(vDist[u]+we <= vDist[v])
      {
        vDist[v] = vDist[u]+we;
        pq.insert(std::make_pair(vDist[v], std::make_pair(v, u)));
      }
    }
  }
  
  std::vector<long double> vDependency(this->nVertices_, 0);
  
  while(!S.empty())
  {
    int cur = S.top();
    S.pop();
    long double factor = ((long double)1.0 + vDependency[cur])/((long double)vsigma[cur]);
    for(int v : vChildren[cur])
      vDependency[v] += ((long double) vsigma[v])*factor;
    if(cur != s) this->vbetweenness[cur] += vDependency[cur]/2.0;
  }
}
