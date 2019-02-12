#pragma once
#include"varray.hpp"
#include<stdio.h>
#include<string.h>
#include<memory>
#include<stdarg.h>
#include"vplatform.hpp"

#if defined(_ANDROID_)
#define isChinese(x) x>128
#else
#define isChinese(x) x<0
#endif
static char String_buff[32];
class String {

  std::shared_ptr < char >data;
  int len = 0;

  static void deleter(char *mdata) {
    delete[]mdata;
  }
  String(int size, bool b) {
    len = size;
    data.reset(new char[len + 1], &deleter);
  }
public:

  String() {
  }
  String(bool b) {
    reset(b ? "true" : "false");
  }
  String(int number) {
    sprintf(String_buff, "%d", number);
    reset(String_buff);
  }
  String(long number) {
    sprintf(String_buff, "%ld", number);
    reset(String_buff);
  }

  String(char c) {
    sprintf(String_buff, "%c", c);
    reset(String_buff);
  }
  String(float number) {
    sprintf(String_buff, "%f", number);
    reset(String_buff);
  }
  String(const char *str) {
    reset(str);
  }
  String(char chars[], int l) {
    len = l;
    data.reset(new char[len + 1], &deleter);
    memcpy(data.get(), chars, l);
  }
  String(const String & o) {
    len = o.len;
    data = o.data;

  }
  void reset(const char *str) {
    len = strlen(str);
    data.reset(new char[len + 1], &deleter);
    strcpy(data.get(), str);
  }
  char *get() {
    return data.get();
  }

  int compare(String o) {
    return strcmp(data.get(), o.get());
  }
  void print() {
    printf(data.get());
  }
  void println() {
    puts(data.get());
  }
  int length() {
    return len;
  }
  char &operator [] (int index) {
    return data.get()[index];
  }
  String operator +(String o) {
    String s(o.len + len, true);
    strcpy(s.get(), data.get());
    strcat(s.get(), o.get());
    return s;
  }

  String operator +=(String o) {
    std::shared_ptr < char >s = data;
    len += o.len;
    data.reset(new char[len + 1], &deleter);
    strcpy(data.get(), s.get());
    strcat(data.get(), o.get());
    return *this;
  }
  bool operator ==(String o) {
    return o.get() == data.get();
  }
  bool equals(String o) {
    if (data.get() == NULL) {
      return o.get() == NULL ? true : false;
    }
    return strcmp(data.get(), o.get()) == 0;
  }
  String sub(int start, int count) {
    String s(count, false);
    strncpy(s.get(), data.get() + start, count);
    return s;
  }
  bool startWith(char c) {
    return data.get()[0] == c;
  }
  bool endWith(char c) {
    return data.get()[len - 1] == c;
  }
  int indexOf(char c) {
    char *str = data.get();
    for (int i = 0; i < len; i++) {
      if (str[i] == c) {
        return i;
      }
    }
    return -1;
  }

  int lastIndexOf(char c) {
    char *str = data.get();
    for (int i = len - 1; i >= 0; i--) {
      if (str[i] == c) {
        return i;
      }
    }
    return -1;
  }
  void scanf(char *format, ...) {
    va_list strList;
    va_start(strList, format);
    vsscanf(data.get(), format, strList);
    va_end(strList);
  }
  Array < String > subBy(char c) {
    Array < String > s;
    char *str = data.get();
    int count = 0;
    for (int i = 0; i < len; i++) {
      if (str[i] == c) {
        count++;
      }
    }
    s.resize(count);
  }

  ~String() {
  }

};