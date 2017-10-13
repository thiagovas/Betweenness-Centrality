import sys
import networkx as nx

g = nx.MultiGraph();

while True:
    u, v, c = map(int, raw_input().split(','))
    if (u == 0 and v == 0 and c == 0):
        break
    g.add_edge(u, v, weight=100-c)
    
ans = nx.betweenness_centrality (g, normalized=False, weight='weight');

ue = []

for key, value in ans.iteritems():
  ue.append((-value, key))

ue.sort()
for (value, key) in ue:
  print str(key), ":", str(-value)

sys.stdout.write("\n")
for (value, key) in ue:
  sys.stdout.write(str(key)+",")
sys.stdout.write("\n")
