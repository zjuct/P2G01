#ifndef MODIFY
#include "ordinary-dijkstra.hpp"
#else
#include "modified-dijkstra.hpp"
#endif

#include<iostream>
#include<random>
#include<ctime>
#include<sys/time.h>
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
  struct timeval t_start, t_end;
  gettimeofday(&t_start, NULL);
  for(size_t i = 0; i < sz; i++) {
    from = u(e);
    do {
      to = u(e);
    }while(to == from);
    cout << from << " " << to << " " << d.dijkstra(from, to) << endl;
  }
  gettimeofday(&t_end, NULL);
  cerr << "----------------------------------" << endl;
#ifdef FIBO
  cerr << "FIBO: ";
#endif
#ifdef PAIR
  cerr << "PAIR: ";
#endif
#ifdef LEFT
  cerr << "LEFT: ";
#endif
#ifdef BINARY
  cerr << "BINARY: ";
#endif
  cerr << "#vertices: " << d.g.n_num << "  #arcs: " << d.g.a_num << endl;
  cerr << "#queries: " << sz << endl;
  cerr << "total time: " << (t_end.tv_sec * 1000 + t_end.tv_usec / 1000) - (t_start.tv_sec * 1000 + t_start.tv_usec / 1000)  << "msec" << endl;
  cerr << "average time: " << ((t_end.tv_sec * 1000 + t_end.tv_usec / 1000) - (t_start.tv_sec * 1000 + t_start.tv_usec / 1000)) / (double)sz << "msec" << endl;  
}
