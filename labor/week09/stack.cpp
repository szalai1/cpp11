#include <iostream>
#include <cstdlib>
#include <new>
#include <stdexcept>

struct X {
  X(int x) {
    //throw std::bad_alloc();
  }
  X(X const &x) {
    throw std::bad_alloc();
  }
};

template <typename T>
class Stack {
public:
  Stack(size_t max_size);
  Stack(Stack const &orig);
  Stack & operator=(Stack const &orig) = delete;
  ~Stack();
  void push(T const &what);
  bool empty() const;
  void pop();
  T last();
private:
    size_t size_;
    size_t max_size_;
    T *pData_;
};


template <typename T>
Stack<T>::Stack(size_t max_size) {
    size_ = 0;
    pData_ = (T*) malloc(sizeof(T) * max_size_);
    if (pData_ == nullptr) {
      throw std::bad_alloc();
    }
    max_size_ = max_size;
}


template <typename T>
Stack<T>::Stack(Stack<T> const &orig) {
    pData_ = (T*) malloc(sizeof(T) * orig.max_size_);
    for (size_t i = 0; i != orig.size_; ++i)
        new (&pData_[i]) T{orig.pData_[i]};
    size_ = orig.size_;
    max_size_ = orig.max_size_;
}


template <typename T>
Stack<T>::~Stack() {
  for (size_t i = 0; i != size_; ++i)
    pData_[i].~T();
  free(pData_);
}


/* Push element onto stack. */
template <typename T>
void Stack<T>::push(T const &what) {
  new (&pData_[size_]) T{what};
  size_++;
}


/* Pop element from top of the stack. */
template <typename T>
T Stack<T>::last() {
  return pData_[size_-1];
}

template <typename T>
void Stack<T>::pop() {
  pData_[size_-1].~T();
  size_--;
}

template <typename T>
bool Stack<T>::empty() const {
    return size_ == 0;
}


int main() {
    Stack<X> s{100};
    try {
      s.push(X{3});
    } catch(...) {
      std::cout << s.empty() << std::endl;
    }
    Stack<char> ss{10};
    ss.push('a');
    ss.push('y');
    std::cout << ss.last() << ss.last() << std::endl;
}
