#!/usr/bin/env python
# coding: utf-8
# By Thiago Silva
#
# This piece of code just generates random weighted graphs.
# The number of vertices varies from 10 to 100.
# The number of edges varies from 2n to n^2.
# The weights of the edges varies from 1 to 100.


from sys import argv
from random import randint
from random import shuffle

def initUnionFind():
  return [x for x in range(200)]

def Find(uf, a):
  if uf[a] == a:
    return a
  else:
    uf[a] = Find(uf, uf[a])
    return uf[a]

def Union(uf, a, b):
  uf[Find(uf, a)] = Find(uf, b)

def gen(filename):

  n = randint(10, 100)
  m = randint(2*n, (n*(n-1))//2)
  edges = []
  resp_edges = []
  
  uf = initUnionFind()
  
  for i in range(n):
    for j in range(i+1, n):
      edges.append((i, j))
  shuffle(edges)
  
  for i in range(m):
    resp_edges.append(edges[i])
    Union(uf, edges[i][0], edges[i][1])
  
  for i in range(n):
    if(Find(uf, i) != Find(uf, 0)):
      Union(i, 0)
      resp_edges.append((i, 0))
  
  fout = open(filename, 'w')
  for (a, b) in resp_edges:
    fout.write(str(a) + "," + str(b) + "," + str(randint(1, 100)) + "\n")
  fout.write("0,0,0\n")
  fout.close()
  
  

def main():
  if len(argv) != 2:
    print "Expected just one argument."
    print "Usage: ", argv[0], "[The number of test cases]"
    return
  
  for i in range(int(argv[1])):
    filename = 't' + str(i)
    gen(filename)
  

if __name__ == '__main__':
  main()
