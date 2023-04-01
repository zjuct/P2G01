#include<fstream>
#include<vector>
#include<string.h>
#include<assert.h>

#ifdef FIBO
#include"fiboHeap.hpp"
#endif

#ifdef PAIR
#include "pairHeap.hpp"
#endif

#ifdef BINARY
#include "binaryHeap.hpp"
#endif

using namespace std;

class Dijkstra {
public:
  using P = pair<size_t, size_t>;
  Dijkstra(istream& is) {
    char magic;
    size_t from, to, dist;
    is >> magic;
    assert(magic == 'p');
    is >> g.n_num >> g.a_num;
    g.adjList = new struct Edge*[g.n_num + 1];
    // 由于顶点数量太多，因此不包含dummy head
    for(size_t i = 0; i < g.n_num + 1; i++) {
      g.adjList[i] = nullptr;
    }
    while(is >> magic >> from >> to >> dist) {
      assert(magic == 'a');
      struct Edge* p = new Edge(to, dist, g.adjList[from]);
      g.adjList[from] = p;
      p = new Edge(from, dist, g.adjList[to]);
      g.adjList[to] = p;
    }

    this->dist = new size_t[g.n_num + 1];
  }
  // s到其它所有点的最短路径
  size_t dijkstra(size_t s, size_t t) {
#ifndef BINARY
    Heap<P> pq;
#else
    Heap<P> pq(g.a_num);
#endif
    memset(dist, 0x3f, sizeof(size_t) * (g.n_num + 1));
    dist[s] = 0;
    pq.insert(P(0, s));
    while(!pq.isEmpty()) {
      P cur = pq.getMin(); pq.deleteMin();
      size_t v = cur.second;
      if(dist[v] < cur.first) continue;
      Edge* arc = g.adjList[v];
      while(arc) {
        if(dist[arc->to] > dist[v] + arc->dist) {
          dist[arc->to] = dist[v] + arc->dist;
          pq.insert(P(dist[arc->to], arc->to));
        }
        arc = arc->next;
      }
    }
    return dist[t];
  } 
  
  struct Edge {
    size_t to, dist;
    struct Edge* next;
    Edge(size_t _to, size_t _dist, struct Edge* _next) : to(_to), dist(_dist), next(_next) {}
  };
  struct Graph {
    size_t a_num, n_num;    // sizeof arc node
    struct Edge** adjList;  // 邻接表
  };

  Graph g;
  size_t* dist;
};