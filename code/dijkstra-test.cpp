#ifndef MODIFY
#include "ordinary-dijkstra.hpp"
#else
#include "modified-dijkstra.hpp"
#endif

#include<iostream>
#include<random>
#include<ctime>
#include<unistd.h>

#define SEED 12345678

// usage: ./dijkstra-test file size
int main(int argc, char** argv) {
  assert(argc == 3);
  ifstream ifs(argv[1], ios::in);
  Dijkstra d(ifs);
  ifs.close();
  size_t sz = atoi(argv[2]);

  uniform_int_distribution<unsigned> u(1, d.g.n_num);
  // 使用固定的种子，保证公平性
  default_random_engine e(SEED);
  size_t from, to;
  time_t t_start, t_end;
  t_start = time(0);
  for(size_t i = 0; i < sz; i++) {
    from = u(e);
    do {
      to = u(e);
    }while(to == from);
    cout << from << " " << to << " " << d.dijkstra(from, to) << endl;
  }
  t_end = time(0);

  cout << "----------------------------------" << endl;
#ifdef FIBO
  cout << "FIBO: ";
#endif
#ifdef PAIR
  cout << "PAIR: ";
#endif
#ifdef LEFT
  cout << "LEFT: ";
#endif
#ifdef BINARY
  cout << "BINARY: ";
#endif
  cout << "#vertices: " << d.g.n_num << "  #arcs: " << d.g.a_num << endl;
  cout << "#queries: " << sz << endl;
  cout << "total time: " << t_end - t_start << "sec" << endl;
  cout << "average time: " << (t_end - t_start) / (double)sz << "sec" << endl;  
}
