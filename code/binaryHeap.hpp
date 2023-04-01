template<typename T>
class Heap {
public:
  Heap(size_t _cap) : sz(0), cap(_cap) {
    arr = new T[cap];
  }
  ~Heap() {
    delete [] arr;
  }
  void insert(T val) {
    sz++;
    arr[sz] = val;
    up(sz);
  }
  T getMin() {
    return arr[1];
  }
  void deleteMin() {
    arr[1] = arr[sz];
    sz--;
    down(1); 
  }
  bool isEmpty() {
    return sz == 0;
  }

private:
  void up(size_t x) {
    while(x > 1 && arr[x] < arr[x / 2]) {
      T tmp = arr[x];
      arr[x] = arr[x / 2];
      arr[x / 2] = tmp;
      x /= 2;
    }
  }
  void down(size_t x) {
    size_t t;
    while(x * 2 <= sz) {
      t = x * 2;
      if(t + 1 <= sz && arr[t + 1] < arr[t]) t++;
      if(arr[t] >= arr[x]) break;
      T tmp = arr[x];
      arr[x] = arr[t];
      arr[t] = tmp;
      x = t;
    }
  }
  T* arr;
  size_t sz, cap;
};