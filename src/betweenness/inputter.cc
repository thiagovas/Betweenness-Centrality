#include <iostream>
#include <vector>
#include <utility>

#include "inputter.h"

// Inputter Constructor
Inputter::Inputter() {
  // Turning off the synchronization between stdio and iostream...
  std::ios::sync_with_stdio(false);

  this->nVertices = 0;
}

Graph Inputter::readInput()
{
  std::vector<std::pair<int, std::pair<int, int> > > vedges;
  while(true)
  {
    int u, v, c;
    std::cin >> u;
    std::cin.get();
    std::cin >> v;
    std::cin.get();
    std::cin >> c;
    if(not std::cin) break;
    if(u == 0 && v == 0 && c == 0) break;
    
    vedges.push_back(std::make_pair(100-c, std::make_pair(u, v)));
    this->mapvertex(u);
    this->mapvertex(v);
  }
  
  Graph g(this->nVertices);
  for(std::pair<int, std::pair<int, int> > p : vedges)
  {
    int c = p.first;
    int u = p.second.first;
    int v = p.second.second;

    u = this->inputtoperm[u];
    v = this->inputtoperm[v];
    g.addEdge(u, v, c);
  }
  
  return g;
}

void Inputter::mapvertex(int u)
{
  if(this->inputtoperm.find(u) == this->inputtoperm.end())
  {
    this->inputtoperm[u] = this->nVertices;
    this->permtoinput[this->nVertices] = u;
    this->nVertices++;
  }
}
