#include<fstream>
#include<assert.h>
#include<string.h>
#include<queue>
#include<iostream>
#ifdef FIBO
#include"fiboHeap.hpp"
#endif

#ifdef LEFT
#include"leftHeap.hpp"
#endif

#ifdef PAIR
#include "pairHeap.hpp"
#endif

using namespace std;

#define INF 0x7f7f7f7f

struct pqNode {
  pqNode() : node(0), dist(INF) {};
  pqNode(size_t n, size_t d) : node(n), dist(d) {};
  size_t node, dist;
  bool operator< (const pqNode& other) const {
    return this->dist < other.dist;
  } 
  bool operator> (const pqNode& other) const {
    return !this->operator<(other);
  }
  pqNode operator-(const pqNode& other) const {
    return pqNode(node, this->dist - other.dist);
  }
  void operator-=(const pqNode& other) {
    this->dist -= other.dist;
  }
  bool operator==(const pqNode& other) const {
    return this->node == other.node && this->dist == other.dist;
  }
};

class Dijkstra {
public:
  // get input from is
  Dijkstra(istream& is) {
    /*
      input format
      p n_num a_num
      a from to dist
      a from to dist
      ...
    */
    char magic;
    size_t from, to, dist;
    is >> magic;
    assert(magic == 'p');
    is >> g.n_num >> g.a_num;
    g.adjList = new struct Node*[g.n_num + 1];
    // adjList包含dummy head
    for(size_t i = 0; i < g.n_num + 1; i++) {
      g.adjList[i] = new struct Node(0, 0, NULL);
    }
    while(is >> magic >> from >> to >> dist) {
      assert(magic == 'a');
      struct Node* p = new Node(to, dist, g.adjList[from]->next);
      g.adjList[from]->next = p;
      p = new Node(from, dist, g.adjList[to]->next);
      g.adjList[to]->next = p;
    }

    this->visited = new bool[g.n_num + 1];
    this->dist = new size_t[g.n_num + 1];
    this->heap_arr = new heap_node<pqNode>*[g.n_num + 1];
  }

  ~Dijkstra() {
    for(size_t i = 0; i < g.n_num + 1; i++) {
      Node* p = g.adjList[i];
      Node* np = NULL;
      while(p) {
        np = p->next;
        delete p;
        p = np;
      }
    }
    delete [] g.adjList;
    delete [] visited;
    delete [] dist;
    delete [] heap_arr;
  }

  // 返回从from到to的最短路长度
  size_t dijkstra(size_t from, size_t to) {
    memset(dist, 0x7f, sizeof(size_t) * (g.n_num + 1));
    dist[from] = 0;
    for(size_t i = 0; i < g.n_num + 1; i++) {
      visited[i] = false;
    }
    Heap<pqNode> h;
    for(size_t i = 1; i <= g.n_num; i++) {
      pqNode n(i, dist[i]);
      heap_arr[i] = h.insert(n);    // 保存所有Heap结点，供decreaseKey使用
    }
    while(!h.isEmpty()) {
      //dbg_print();
      pqNode cur = h.getMin();
      h.deleteMin();
      if(cur.node == to) 
        return dist[to];
      if(visited[cur.node]) 
        break;
      Node* arc = g.adjList[cur.node]->next;
      visited[cur.node] = 1;
      while(arc) {
        if(!visited[arc->to] && dist[arc->to] > dist[cur.node] + arc->dist) {
          pqNode dec(arc->to, dist[arc->to] - (dist[cur.node] + arc->dist));
          h.decreaseKey(heap_arr[arc->to], dec);
          dist[arc->to] = dist[cur.node] + arc->dist;
        }
        arc = arc->next;
      }
    }
    size_t ret = dist[to];
    return ret;
  }
public:
  // 邻接表结点
  struct Node {
    size_t to, dist;
    struct Node* next;
    Node(size_t _to, size_t _dist, struct Node* _next): to(_to), dist(_dist), next(_next) {}
  };

  struct Graph {
    size_t a_num, n_num;    // sizeof arc node
    struct Node** adjList;  // 邻接表
  };

  Graph g;
  bool* visited;
  size_t* dist;     // 每个结点当前的最短路径长度
  heap_node<pqNode>** heap_arr;
};