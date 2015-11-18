/**
 * Koszonom a segitseget (meg a hatarido hosszabitast is)!
 * udv,
 * peti
 */


#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>
#include <cstring>

struct VariableBase;

struct VariableBase {
  virtual ~VariableBase(){}
  virtual void set_begin() = 0;
  virtual void step() = 0;
  virtual bool has_next() = 0;
};

template<typename T>
struct Variable: public VariableBase  {
  Variable(std::vector<T> t, typename std::vector<T>::iterator i)
    :values_{t}, current_(i){}
  std::vector<T> values_;
  typename std::vector<T>::iterator current_;
  void set_begin() { current_ = values_.begin();  }
  void step() { ++current_;  }
  bool has_next() { return current_ == values_.end(); }
};

class NewTester {
public:
  using Constraint = std::function<bool()>;
  using Activity = std::function<void()>;
  
private:
  using Iterator = typename std::vector<VariableBase*>::const_iterator;
  std::vector<VariableBase*> variables_;
  std::vector<Constraint> constraints_;
  
public:
  template<typename T>
  std::function<T()> add_variable(std::initializer_list<T> values_) {
    return this->add_variable(std::vector<T>{values_});
  }
  
  template<typename T>
  std::function<T()> add_variable(std::vector<T> values_) {
    variables_.push_back(new Variable<T>{values_,
          typename std::vector<T>::iterator()});
    size_t pos = variables_.size()-1;
    return [this, pos] () -> T {
      return *(dynamic_cast<Variable<T>*>((
                             (this->variables_)[pos]
                                         ))->current_);
          };
  }
  
  void add_constraint(Constraint values_) {
    constraints_.push_back(values_);
  }

  void solve(Activity do_what) {
    for (auto & v : variables_)
      v->set_begin();

    bool end = false;
    while (!end) {
      auto satisfied = std::all_of(
                                   constraints_.begin(), constraints_.end(),
                                   [] (Constraint cons) { return cons(); });
      if (satisfied)
        do_what();

      bool carry = true;
      size_t i = 0;
      while (carry && i != variables_.size()) {
        variables_[i]->step();
        carry = variables_[i]->has_next();
        if (carry)
          variables_[i]->set_begin();
        ++i;
      }
      end = carry;
    }
  }
};

int main() {
    NewTester t;
 
    /* Bugyuta példa: kilistázza azokat a (szám;szó) párokat,
     * amelyeknél hossz(szó) = szám */
    auto size = t.add_variable({1,2,3,4,5});
    auto word = t.add_variable({"alma", "korte", "barack"});
    t.add_constraint([=] {
        return size() == (int) strlen(word());
    });
    t.solve([=] {
        std::cout << "strlen(" << word() << ") = " << size() << std::endl;
    });
}
