// 给定密度和顶点数，随机生成图
// 生成的图输出到stdout中，可以利用重定向保存到文件中
#include<iostream>
#include<cmath>
#include<set>
#include<random>
#include<cassert>
#include<cmath>
#include<set>
#include<ctime>

using namespace std;

#define MAX_DIST 100000
using P = pair<size_t, size_t>;

size_t v_num;
double density;
size_t e_num;
set<P> s;

// ./graph-gen v_num density
// density的取值为[1, 2]
int main(int argc, char** argv) {
  assert(argc == 3);
  v_num = atoi(argv[1]);
  density = atof(argv[2]);
  assert(density >= 1.0f && density <= 2.0f);
  uniform_int_distribution<unsigned> u(1, v_num);
  uniform_int_distribution<unsigned> udist(1, MAX_DIST);
  default_random_engine e(time(0));
  e_num = (size_t)(pow((double)v_num, density) / 2.0);
  e_num = max(v_num, e_num);
  e_num = min(e_num, (v_num) * (v_num - 1) / 2);
  cout << "p " << v_num << " " << e_num << endl;
  size_t from, to, dist;
  size_t i = 0;
  while(i < e_num) {
    from = u(e);
    to = u(e);
    if(s.find(P(from, to)) != s.end() || s.find(P(to, from)) != s.end()) {
      continue;
    }
    s.insert(P(from, to));
    i++;
    dist = udist(e);
    cout << "a " << from << " " << to << " " << dist << endl;
  }
}