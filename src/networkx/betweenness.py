import math
import sys
import networkx as nx

G = nx.Graph();

while True:
    u, v, c = map(int, raw_input().split(','))
    if (u == 0 and v == 0 and c == 0):
        break
    c = 100-c
    G.add_edge(u, v, weight=c)

ans = nx.betweenness_centrality(G, k=None, normalized=False, weight="weight", endpoints=False);

#vetor = []
#
#for x in ans:
#    vetor.append( (ans[x],-x) )
#    #print x, ans[x]
#
#vetor.sort()
#vetor.reverse()
#
#tam = 0
#solucao = ''
#for x in vetor:
#	if tam != 0:
#		solucao += ","
#	solucao += str(-x[1])
#	tam+=1
#
#print solucao

ue = []

for key, value in ans.iteritems():
  ue.append((-value, key))

ue.sort()

jafoi = False
for (value, key) in ue:
  if jafoi:
    sys.stdout.write(','+str(key))
  else:
    jafoi = True
    sys.stdout.write(str(key))
sys.stdout.write("\n")
