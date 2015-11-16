#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

template <typename VALUETYPE>
class Tester {
  public:
    /* Ilyen tĂĄrolĂł tĂĄrolja az egyes vĂĄltozĂłk lehetsĂŠges ĂŠrtĂŠkeit. */
    using Container = std::vector<VALUETYPE>;
    /* VariableValue: ez azt a vĂĄltozĂłt reprezentĂĄlja, amely tesztelĂŠs
     * kĂśzben kĂźlĂśnfĂŠle ĂŠrtĂŠkeket vesz fel. Ha meghĂ­vjuk a fĂźggvĂŠnyt,
     * megkapjuk az ĂŠrtĂŠket. */
    using VariableValue = std::function<VALUETYPE()>;
    /* Constraint: egy olyan paramĂŠter nĂŠlkĂźli fĂźggvĂŠny, amely megmondja,
     * hogy az elvĂĄrt ĂśsszefĂźggĂŠsek ĂŠpp teljesĂźlnek-e. */
    using Constraint = std::function<bool()>;
    /* Activity: ilyen fĂźggvĂŠnyt fog meghĂ­vni a Tester, amikor tesztelĂŠs
     * kĂśzben talĂĄl egy megoldĂĄst. */
    using Activity = std::function<void()>;


  private:
    using Iterator = typename Container::const_iterator;
    /* LehetsĂŠges ĂŠrtĂŠkek: egy tartomĂĄny iterĂĄtorai, ĂŠs az aktuĂĄlis
     * ĂŠrtĂŠket mutatĂł iterĂĄtor. */
    struct Variable {
        Container values_;
        Iterator current_;
    };
    /* Ezeket a vĂĄltozĂłkat kell vizsgĂĄlni */
    std::vector<Variable> variables_;
    /* Ezen feltĂŠtelek szerint */
    std::vector<Constraint> constraints_;
  
  public:
    /* Egy vĂĄltozĂł lehetsĂŠges ĂŠrtĂŠkeit tartalmazĂł tĂĄrolĂłt vĂĄrja.
     * Ad egy olyan fĂźggvĂŠnyt vissza, amelyet meghĂ­vva
     * lekĂŠrdezhetĹ, hogy a tesztelĂŠs kĂśzben az adott vĂĄltozĂłnak ĂŠppen
     * mi az ĂŠrtĂŠke. A hasznĂĄlĂł ezekre a fĂźggvĂŠnyekre tud majd ĂŠpĂ­teni.
     * Az std::vector push_back()-nĂŠl ĂĄthelyezheti a memĂłriĂĄban az
     * elemeket, Ă­gy a vektorba tett current iterĂĄtor referenciĂĄjĂĄt
     * nem adhatjuk vissza. Helyette megjegyezzĂźk, hogy a beszĂşrt
     * struktĂşra hĂĄnyadik indexre kerĂźlt, ĂŠs az kerĂźl a lambdĂĄba. */
    VariableValue add_variable(Container values_) {
        variables_.push_back(Variable{values_, Iterator{}});
        size_t pos = variables_.size()-1;
        return [this, pos] () -> VALUETYPE {
            return *variables_[pos].current_;
        };
    }

    /* FeltĂŠtel hozzĂĄadĂĄsa. A feltĂŠtel egy fĂźggvĂŠny, amely igaz ĂŠrtĂŠke
     * esetĂŠn az aktuĂĄlis ĂĄllapot elfogadhatĂł. */
    void add_constraint(Constraint values_) {
        constraints_.push_back(values_);
    }

    /* Teszteli az Ăśsszes lehetsĂŠges ĂŠrtĂŠket, ĂŠs amikor olyan
     * ĂĄllapotban vannak az iterĂĄtorok, amik ĂŠpp egy elfogadhatĂł
     * kombinĂĄciĂłra mutatnak, akkor meghĂ­vja a fĂźggvĂŠnyt. */
    void solve(Activity do_what) {
        /* iterĂĄtorok inicializĂĄlĂĄsa */
        for (auto & v : variables_)
            v.current_ = v.values_.begin();
        /* A Variable-k current iterĂĄtorait mĂĄr mind begin-re
         * ĂĄllĂ­tottuk, szĂłval most az elejĂŠn ĂĄll az Ăśsszes. */
        bool end = false;
        while (!end) {
            /* JĂł az aktuĂĄlis ĂĄllapot? Ha mindegyik jĂł. */
            auto satisfied = std::all_of(
                constraints_.begin(), constraints_.end(),
                [] (Constraint cons) { return cons(); });
            /* Megfelel ez az ĂĄllapot, ha mindegyik Constraint igazat vĂĄlaszolt. */
            if (satisfied)
                do_what();

            /* KĂśvetkezĹre ugrĂĄs: a digit "teljes ĂśsszeadĂł"ja kĂłdban. */
            bool carry = true;
            size_t i = 0;
            while (carry && i != variables_.size()) {
                /* ugrik az iterĂĄtor */
                ++variables_[i].current_;
                /* ĂŠs ha vĂŠgĂŠre ĂŠrt, akkor ugorjon a kĂśvetkezĹ
                 * is, ez meg vissza az elejĂŠre. */
                carry = variables_[i].current_ == variables_[i].values_.end();
                if (carry)
                    variables_[i].current_ = variables_[i].values_.begin();
                ++i;
            }
            /* Ha amiatt jĂśttĂźnk ki, mert i=values.size(), ĂŠs
             * mĂŠg mindig kĂŠne lĂŠptetni a kĂśvetkezĹt, akkor ĂŠrtĂźnk
             * kĂśrbe, ĂŠs megĂĄllhat a ciklus. */
            end = carry;
        }
    }
};


void task2_1() {
  Tester<int> t;
  std::vector<int> numbers;
  for (int i = 1; i < 100; ++i) {
    numbers.push_back(i);
  }
  auto a = t.add_variable(numbers);
  auto b = t.add_variable(numbers);
  auto c = t.add_variable(numbers);
  
  t.add_constraint([=](){ return a()*a() + b()*b() == c()*c() ; });
  t.add_constraint([=](){return a() < b() && b() < c() ;});
  auto print = [=]() {
    std::cout << a() << " " << b() << " " << c() << std::endl;
  };
  t.solve(print);
}

void task2_2() {
  Tester<int> t;
  std::vector<int> numbers;
  for (int i = 1; i < 100; ++i) {
    numbers.push_back(i);
  }
  auto goat = t.add_variable(numbers);
  auto juh = t.add_variable(numbers);
  auto pig = t.add_variable(numbers);

  t.add_constraint([=]() {return 600 == 21*pig() + 8*goat() + 3*juh();});
  auto print = [=]() {
    std::cout << juh() << " " << goat() << " " << pig() << std::endl;
  };
  t.solve(print);
}


void task2_3() {
  Tester<int> t;
  auto a = t.add_variable({0,1,2});
  auto b = t.add_variable({0,1,2});
  auto c = t.add_variable({0,1,2});
  auto d = t.add_variable({0,1,2});
  auto e = t.add_variable({0,1,2});

  t.add_constraint([=](){
      return b() != c() &&
        b() != a() &&
        b() != d() &&
        c() != a() &&
        c() != e() &&
        a() != e() &&
        a() != d();});

  t.add_constraint([=]() {return a() > b() && e() > d(); });
  auto print = [=]() {
    std::cout << a() << " " << b() << " " << c() <<" " << d() <<" "<< e() << std::endl;
  };
  t.solve(print);
}

void task2_4(int n) {
  Tester<int> t;
  std::vector<std::function<int()>> queens;
  std::vector<int> nums;
  for (int ii = 0; ii < n; ++ii) {
    nums.push_back(ii);
  }
  for (int ii = 0; ii < n; ++ii) {
      queens.push_back(t.add_variable(nums));
  }
  for (int ii = 0; ii < n; ++ii) {
    for (int jj = ii+1; jj < n; ++jj) {
      t.add_constraint([=]() { return queens[ii]() != queens[jj]();});
      t.add_constraint([=]() { return abs(queens[ii]()-queens[jj]()) != jj - ii ;});
    }
  }
  auto print = [=]() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        std::cout << (queens[i]() ==j ? 'x':'.');
    std::cout << std::endl;
  }
  };
  t.solve(print);
}


int main() {
  //  task2_1();
  //  task2_3();
  task2_4(8);
}
