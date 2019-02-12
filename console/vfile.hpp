#pragma once
#include <stdarg.h>
#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include"vplatform.hpp"
#include"vstring.hpp"

#if !defined(_LINUX_)
#error this file only be used on linux
#endif
// only linux
class File {
  String path, name;
  struct stat info;
public:
File(){
	path="";
	name="";
}
    File(String path) {
    setPath(path);
  }
  File(File father, String name) {
    this->name = name;
    String fpath = father.getPath();
    path = fpath.endWith('/') ? fpath + name : fpath + '/' + name;

    int end = path.lastIndexOf('/');
    if (end != -1) {
      name = path.sub(end + 1, path.length() - end);
    }
    stat(path.get(), &info);
  }
  ~File() {

  }
  void setPath(String path){
  	this->path = path;

    int end = path.lastIndexOf('/');
    if (end != -1) {
      name = path.sub(end + 1, path.length() - end);
    }
    stat(path.get(), &info);
  }

  void createFile() {
    FILE *f = fopen(path.get(), "w+");
    if (f!=NULL){
    	fclose(f);
    	f=NULL;
    }
  }
  bool exist() {
    return access(path.get(), 0) == 0;
  }
  String getName() {
    return name;
  }
  String getPath() {
    return path;
  }
  long getSize() {
    return info.st_size;
  }
  long getTime() {
    return info.st_atime;
  }
  bool isDir() {
    return info.st_mode & S_IFDIR;
  }
  void mkdir(mode_t m) {
    ::mkdir(path.get(), m);
  }


  bool remove() {
    return::remove(path.get()) == 0;
  }
  void rename(String n) {
    String npath = path.sub(0, path.length() - name.length() + 1) + n;
    ::rename(path.get(), npath.get());
    path = npath;
    name = n;

  }
  String getFatherPath() {
    return path.sub(0, path.length() - name.length() - 1);
  }
  void moveTo(File f) {
     String npath = f.getPath() + '/' + name;
    ::rename(path.get(), npath.get());
    path = npath;
  }


};

 static char FileStream_buff[1024];
class FileStream{
	FILE *f = NULL;
	String path;
	public:
	FileStream(){
	path="";
}
    FileStream(String path) {
    this->path=path;
  }
  FileStream(File file) {
    path=file.getPath();
  }

	  bool isOpen() {
    return f != NULL;
  }

 ~FileStream(){
  	  if (f != NULL) {
      fclose(f);
      f = NULL;
    }
  }
  void open(const char *mode) {
    this->~FileStream();
    f = fopen(path.get(), mode);

  }
  void reopen(const char *mode) {
    if (f != NULL) {
      f = freopen(path.get(), mode, f);
    } else {
      f = fopen(path.get(), mode);
  }
  }
  FileStream & put(int c) {
    fputc(c, f);
    return *this;
  }
  long getPosition() {
    return ftell(f);
  }
  void rewind() {
    ::rewind(f);
  }
  void seek(long offset, int where) {
    fseek(f, offset, where);
  }
  bool end() {
    return feof(f);
  }
  String getLine() {
    return fgets(FileStream_buff, 1024, f);
  }
  void scanf(const char *format, ...) {
    va_list strList;
    va_start(strList, format);
    vfscanf(f, format, strList);
    va_end(strList);
  }
void printf(const char *format, ...) {
    va_list strList;
    va_start(strList, format);
    vfprintf(f, format, strList);
    va_end(strList);
  }

  FileStream & put(char c) {
    fputc(c, f);
    return *this;
  }
  char getc() {
    fgetc(f);
  }
  FileStream & put(String s) {
    fputs(s.get(), f);
    return *this;
  }
  void close() {
    if (f != NULL) {
      fclose(f);
      f = NULL;
    }
  }
  int fd() {
    return fileno(f);
  }
};
