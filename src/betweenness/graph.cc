#include <set>

#include "graph.h"

Graph::Graph(int nVertices)
{
  this->nVertices_ = nVertices;
  this->graph.resize(nVertices);
  this->vsigma.resize(nVertices, std::vector<long long int>(nVertices, 0));
  this->vdependency.resize(nVertices, std::vector<long double>(nVertices, -1));
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
  
  // Just cleaning the table before anything.
  for(unsigned i = 0; i < this->vsigma.size(); i++)
    for(unsigned j = 0; j < this->vsigma[i].size(); j++)
     this->vsigma[i][j] = 0;
  
  
  // Running all Dijkstras, after this step,
  // vsigma and the dependency matrices will be computed.  
  for(int i = 0; i < this->nVertices_; i++)
  {
    std::vector<std::vector<int> > dag = dijkstra(i);

    for(int j = 0; j < this->nVertices_; j++)
      this->computeDependency(dag, i, j);
  }
  
  std::vector<long double> vbetweenness(this->nVertices_, 0);
  
  for(int i = 0; i < this->nVertices_; i++)
  {
    for(int j = 0; j < this->nVertices_; j++)
    {
      if(i == j) continue;
      vbetweenness[j] += this->vdependency[i][j];
    }
  }
  
  return vbetweenness;
}

long double Graph::computeDependency(const std::vector<std::vector<int> > &dag,
                                     int s, int u)
{
  if(this->vdependency[s][u] < EPS)
  {
    this->vdependency[s][u] = 0;
    for(int v : dag[u])
    {
      long double factor = ((long double)this->vsigma[s][u]) / 
                                         this->vsigma[s][v];
      factor *= 1 + computeDependency(dag, s, v);
      this->vdependency[s][u] += factor;
    }
  }
  
  return this->vdependency[s][u];
}

std::vector<std::vector<int> > Graph::dijkstra(int s)
{
  std::set<std::pair<int, std::pair<int, int> > > pq;
  std::vector<int> vdist(this->nVertices_, 0x3f3f3f3f);
  std::vector<bool> visited(this->nVertices_, false);
  std::vector<std::vector<int> > dag(this->nVertices_);
  
  pq.insert(std::make_pair(0, std::make_pair(s, s)));
  vdist[s] = 0;
  vsigma[s][s] = 1;
  
  while(!pq.empty())
  {
    std::pair<int, std::pair<int, int> > cur = *pq.begin();
    pq.erase(pq.begin());
    int u = cur.second.first;
    int w = cur.first;
    int father = cur.second.second;
    if(vdist[u] < w) continue;
    if(u != father)
    {
      vsigma[s][u] += vsigma[s][father];
      dag[father].push_back(u);
    }
    if(visited[u]) continue;
    visited[u] = true;
    
    for(std::pair<int, int> pe : this->graph[u])
    {
      int v = pe.first;
      int we = pe.second;
      if(vdist[u]+we <= vdist[v])
      {
        vdist[v] = vdist[u]+we;
        pq.insert(std::make_pair(vdist[v], std::make_pair(v, u)));
      }
    }
  }
  return dag;
}
