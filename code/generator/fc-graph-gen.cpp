// 给定顶点数，随机生成全连接图
#include <random>
#include <ctime>
#include <iostream>
#include <cassert>

using namespace std;

#define MAX_LEN 100000

// ./a.out v_num
int main(int argc, char** argv) {
  assert(argc == 2);
  size_t size = atoi(argv[1]);
  uniform_int_distribution<unsigned> u(1, MAX_LEN);
  default_random_engine e(time(0));
  size_t dist;
  cout << "p " << size << " " << size * (size - 1) / 2 << endl;
  for(size_t i = 1; i <= size; i++) {
    for(size_t j = i + 1; j <= size; j++) {
      dist = u(e);
      cout << "a " << i << " " << j << " " << dist << endl; 
    }
  }
}