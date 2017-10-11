#include "graph.h"

Graph::Graph(int nVertices)
{
  this->nVertices_ = nVertices;
  this->graph.resize(nVertices);
}

void Graph::addEdge(int u, int v, int c)
{
  this->graph[u].push_back(make_pair(v, c));
  this->graph[v].push_back(make_pair(u, c));
}

void computeSigma()
{
  // On this function I'll have to run a Dijkstra from every vertex.
  // Then, 
}
