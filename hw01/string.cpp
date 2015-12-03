#include "string.h"

std::map<std::string, StringValue*> MyString::catalog_;

StringValue::StringValue(char* str) :string{str}, ref{0} {
}

StringValue::~StringValue() {
  delete[] string;
}

MyString::MyString(char const *str) {
  auto it = catalog_.find(str);
  if ( it == catalog_.end()) {
    char *s = new char[strlen(str) +1];
    strcpy(s, str);
    attach( new StringValue{s});
    catalog_[str] = string_;
  }
  else {
    attach(it->second);
  }
}

MyString::MyString( MyString const &rvl) {
  attach(rvl.string_);
}

MyString::MyString( MyString&& rvl) {
  string_=rvl.string_;
  rvl.string_ = nullptr;
}

char const *MyString::get_str() const {
  if (string_ == nullptr) {
    return nullptr;
  }
  return string_->string;
}

void MyString::detach() {
  if ( string_ != nullptr ) {
    string_->ref--;
    if ( string_->ref == 0 ) {
      catalog_.erase(string_->string);
      delete string_;
    }
    string_=nullptr;
  }
}

void MyString::attach(StringValue* str) {
  string_ = str;
  if ( string_ !=  nullptr) {
    string_->ref++;
  }
}

MyString& MyString::operator=(MyString  const &rvl) {
  if ( string_ != rvl.string_) {
    detach();
    attach(rvl.string_);
  }
  return *this;
}

MyString&  MyString::operator=(char const *str) {
  auto it = catalog_.find(str);
  if ( it == catalog_.end()) {
    detach();
    char *s = new char[strlen(str)+1];
    strcpy(s, str);  
    attach(new StringValue{s});
    catalog_[str] = string_;
  }
  else {
    attach(it->second);
  }
  return *this;
}

MyString& MyString::operator=(MyString &&rvl) {
  detach();
  string_= rvl.string_;
  rvl.string_ = nullptr;
  return *this;
}

void MyString::change_letter(size_t s, char c) {
  if ( string_->string[s] == c) {
    return;
  }
  StringValue* tmp = string_;
  char *str_tmp = new char[size()+1];
  strcpy(str_tmp, tmp->string);
  str_tmp[s] = c;
  detach();
  if (catalog_.find(str_tmp) == catalog_.end()) {
    attach(new StringValue{str_tmp});
    catalog_[str_tmp] = string_;
  }
  else {
    attach(catalog_.find(str_tmp)->second);
    delete[] str_tmp;
  }
}

CharRep MyString::operator[](size_t s) {
  if (s > size() ) {
    throw "change_letter";
  }
  return CharRep{string_->string+s,s, this};
}

MyString operator+(MyString const &lvl, MyString const &rvl) {
  size_t len  = lvl.size() + rvl.size();
  char *s = new char[len+1];
  if ( lvl.size() != 0 ) {
    strcpy(s, lvl.get_str());
  }
  if ( rvl.size() != 0 ) {
    strcpy(s+lvl.size(), rvl.get_str());
  }
  MyString sum{s};
  delete[] s;
  return sum;
}

MyString& MyString::operator+=(MyString const &rvl) {
  MyString b = *this + rvl;
  detach();
  string_ = b.string_;
  b.string_ = nullptr;
  return *this;
}

MyString operator+(MyString const &str, const char c) {
  int len  = str.size() + 1;
  char *s = new char[len+1];
  if ( str.size() != 0 ) {
    strcpy(s, str.get_str());
  }
  s[str.size()] = c;
  s[len]='\0';
  MyString sum{s};
  delete[] s;
  return sum;
}

MyString& MyString::operator+=(const char c) {
  MyString b = *this + c;
  detach();
  string_ = b.string_;
  b.string_=nullptr;
  return *this;
}

std::ostream& operator<<(std::ostream& os, MyString const &s) {
  if (s.get_str() == nullptr) {
    return os;
  }
  return os <<  s.get_str();
}
