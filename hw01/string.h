#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include <map>
#include <string>

class CharRep;

struct StringValue {
  char* string;
  int ref;
  ~StringValue();
  /**
   * Konstruktor
   * Eltarolja a kapott char*-ot, memoria foglalassal es masolassal
   * nem foglalkozik. Ellenben destruktorban felszabaditja azt.
   * @param char* a tarolando pointer.
   */
  explicit StringValue( char *str);
  StringValue() = delete;
};

class MyString {
 private:
  StringValue *string_;
  void detach();
  void attach(StringValue*);
 public:
  static std::map<std::string, StringValue*> catalog_;
  /**
   * MyString konstruktor. Nem tarol stringet.
   */
  explicit MyString():string_(nullptr){}
  /**
   * C stringgel inicializalva, az adott strinet tarolja el magaban.
   * @param az adott c string mutatoja.
   */
  explicit MyString( char const *);
  /**
   * Copy construktor 
   * @param ennek a MyStringnek az erteket veszi fel.
   */
  MyString(MyString const &);
  /**
   * Mozgato konstruktor.
   * @param a rvalue MyString
   */
  MyString(MyString &&);
  /**
   * Egyenloseg operator
   * @param az ertekul adando MyString
   * @return az ertekadas utan kapott MyString-ra egy referencia
   */
  MyString& operator=( MyString const &rvl);
  /**
   * Operator= jobb ertek eseten.
   * @param Egy MyString jobb ertek.
   * @return Az uj MyStringre referencia.
   */
  MyString& operator=( MyString &&rvl);
  /**
   * Egyenloseg operator c stringgel
   * @param c string 
   * @return MyString az ertek adas utan.
   */
  MyString& operator=(char const *str);
  /**
   * Megadja a string hosszat.
   * @return a tarolt string hossza.
   */
  size_t size() const {
    return string_ == nullptr? 0 : strlen(string_->string);
  }
  /**
   * operator+= a sima operator+-t hasznalja
   * @param a hozza adando MyString
   * @return az uj MyString ertek.
   */
  MyString& operator+=( MyString const &str);
  /**
   * operator+= a sima operator+-t hasznalja
   * @param  a hozza adando char
   * @return az uj MyString ertek.
   */
  MyString& operator+=(const char);
  /**
   * Visszater a tarolt stringgel, de nem lehet modositani.
   * @return Tarolt stringre constans pointer
   */
  char const  *get_str() const ;
  /**
   * indexelo operator
   * @param hanyadik karakter
   * @return referncia az adott karakterre
   */
  CharRep operator[](size_t);
  /**
   * Megvaltoztat egy karakter az s-helyen.
   * Arra van hogy a CharRep hivja, ha valtoztatni akar
   * @param hanyadik karakter
   * @param mire valtoztassa
   * @return void
   */
  void change_letter(size_t, char);
  /**
   * Destruktor: szol a tarolt StringValuenak, hogy neki mar
   * nincs ra szuksege.
   */
  ~MyString(){ detach(); };
};
/**
 * Hozzafuz egy karter egy MyStrinhez
 * @param MyString amihez hozza kell fuzni a karektert
 * @param a charakter
 * @return MyString ami az osszefuzott stringet tartalmazza
 */
MyString operator+( MyString const &, const char);
/**
 * Ket MyStringet fuz ossze
 * @param A bal oldali MyString
 * @param A jobb oldali MyString
 * @return az osszefuzott stringet tartalmazo MyString 
 */
MyString operator+(MyString const &, MyString const &);
/**
 *Kiiro operator a MyString osztalynak
 * @param std::ostream& egy tetszoleges outputstreamre kiir
 * @param MyString& a kiirando string
 * @return a stream kiiratas utan
 */
std::ostream& operator<<(std::ostream& os, MyString const &s);

class CharRep {
 private:
  MyString *mystr_;
  char *what_;
  size_t pos_;
 public:
  /**
   * Default construktor letiltva
   */
  CharRep() = delete;
  /**
   * Konstruktor csak a char reprezentalasra  
   * @param w a reprezentalt karakterre pointer
   * @param pos az adott StringValue-ben levo helye
   * @param mystr szetvalasztas eseten melyik stringet kell
   */
  explicit CharRep(char *w, size_t pos, MyString *mystr):
  mystr_{mystr},what_{w}, pos_{pos} {}
  /**
   * Ertekadas, innen tudom, hogy szet kell valasztani az eredeti stringet
   * @param c mi legyen az erteke
   * @return c
   */
  char operator=(char c) {
    mystr_->change_letter(pos_, c);
    return c; 
  }
  /**
   * char cast, hogy lehessen karakterkent hasznalni
   */
  operator char() const {
    return *what_;
  }
  char operator=(CharRep const &r) {
    operator=(*r.what_);
    return *r.what_;
  }
};

#endif
