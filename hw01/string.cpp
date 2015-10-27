#include "string.h"

std::map<std::string, StringValue*> MyString::catalog_;

StringValue::StringValue(char* str) {
  string = str;
}

void StringValue::deref() {
  --ref;
}

void StringValue::refer() {
  ++ref;
}

StringValue::~StringValue() {
  delete[] string;
}

MyString::MyString(char const *str) {
  std::cout << "construktor "  << str << std::endl;
  auto it = catalog_.find(str);
  if ( it == catalog_.end()) {
    std::cout << "nincs benne\n";
    char *s = new char[strlen(str) +1];
    strcpy(s, str);
    string_ = new StringValue{s};
    catalog_[str] = string_;
  }
  else {
    std::cout << "van benne\n";
    string_ = it->second;
  }
  string_->refer();
  
}

MyString::MyString( MyString const &rvl) {
  string_ = rvl.string_;
  string_->refer();
}

MyString::MyString( MyString&& rvl) {
  string_=rvl.string_;
  rvl.string_ = nullptr;
}

char const *MyString::get_str() const {
  if (string_ == nullptr) {
    return nullptr;
  }
  return string_->get_str();
}

void MyString::deref() {
  if ( string_ != nullptr ) {
    std::cout << "DEREF " << *this << " " << string_->get_ref()<<  std::endl;
    string_->deref();
    if ( string_->get_ref() == 0 ) {
      std::cout << "DELET: " << string_->get_str() << std::endl;
      catalog_.erase(string_->get_str());
      delete string_;
    }
    string_=nullptr;
  }
}

void MyString::ref(StringValue* str) {
  string_=str;
  if ( string_ !=  nullptr) {
    string_->refer();
  }
}

MyString& MyString::operator=(MyString  const &rvl) {
  if ( string_ != rvl.string_) {
    deref();
    ref(rvl.string_);
  }
  return *this;
}

MyString&  MyString::operator=(char const *str) {
  auto it = catalog_.find(str);
  if ( it == catalog_.end()) {
    deref();
    char *s = new char[strlen(str)+1];
    strcpy(s, str);  
    string_ = new StringValue{s};
    catalog_[str] = string_;
  }
  else {
    string_ = it->second;
    string_->refer();
  }
  return *this;
}

MyString& MyString::operator=(MyString &&rvl) {
  deref();
  string_= rvl.string_;
  rvl.string_ = nullptr;
  return *this;
}

void MyString::change_letter(size_t s, char c) {
  std::cout << "change\n";
  if ( string_->get_str()[s] == c) {
    return;
  }
  StringValue* tmp = string_;
  char *str_tmp = new char[size()+1];
  strcpy(str_tmp, tmp->get_str());
  str_tmp[s] = c;
  if (catalog_.find(str_tmp) == catalog_.end()) {
    string_ = new StringValue{str_tmp};
  }
  else {
    deref();
    string_ = catalog_.find(str_tmp)->second;
    string_->refer();
    delete str_tmp;
  }
}

CharRep MyString::operator[](size_t s) {
  std::cout << "op[] " << s <<  " "<< string_->get_str() << std::endl;
  if (s > size() ) {
    throw "change_letter";
  }
  std::cout << "op[]2 " << s << std::endl;
  return CharRep{string_->get_str()+s,s, this};
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
  return MyString{s} ;
}

MyString& MyString::operator+=(MyString const &rvl) {
  std::cout << *this << " += " << rvl << std::endl;
  MyString b = *this + rvl;
  std::cout << "#: " << string_->get_str() << string_->get_ref() << std::endl;
  deref();
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
  return MyString{s};
}

MyString& MyString::operator+=(const char c) {
  MyString b = *this + c;
  std::cout << "#: " << string_->get_str() << string_->get_ref() << std::endl;
  deref();
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
