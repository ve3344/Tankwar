
#pragma once
#include<memory>


template <typename T>
class Array {
protected:
    int len=0;
    std::shared_ptr<T> data;
    static void deleter(T* mdata) {
        delete []mdata;
    }
public:
    Array() {

    }
     Array(int l) {
        len=l;
        data.reset(new T[l],&deleter);
    }
    Array(T* mdata,int l) {
        len=l;
        data.reset(mdata,&deleter);
    }
    Array(const Array &o) {
        len=o.len;
        data=o.data;
    }
    void resize(int l) {
        len=l;
        data.reset(new T[l],&deleter);
    }
    int length(){
    return len;
    }
T &operator [](int index) {
        return data.get()[index];
    }

};