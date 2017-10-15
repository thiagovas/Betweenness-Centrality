#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

#include "graph.h"
#include "inputter.h"
using namespace std;


// Comparison function
bool comp(const pair<long double, int>& pa, const pair<long double, int>& pb)
{
  // This function was implemented only because comparisons between
  // two floating points must be done with an EPSILON...
  if(fabsl(pa.first-pb.first) < 1e-8) return pa.second < pb.second;
  return pa.first > pb.first;
}

int main()
{
  Inputter inp;

  Graph g = inp.readInput();
  vector<long double> vbet = g.betweenness();

  // Just a temporary vector I use to sort the output.
  vector<std::pair<long double, int> > vtmp;

  for(int i = 0; i < g.nVertices(); i++)
    vtmp.push_back(std::make_pair(vbet[i], inp.getVertexId(i)));
  
  // Sorting it, so I can print everything beautifully :)
  std::sort(vtmp.begin(), vtmp.end(), comp);
  
  for(int i = 0; i < g.nVertices(); i++)
  {
    if(i == 0) cout << vtmp[i].second;
    else cout << "," << vtmp[i].second;
  }
  cout << endl;
  
  return 0;
}
