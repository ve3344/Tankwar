#pragma once
#include<memory>
#include<stdlib.h>
#include"vstring.hpp"
inline int random(int min, int max) {
    static int a = 999;
    a +=  rand()%a-1000;
    return abs(a) % (max - min + 1) + min;
}
class Time {
public:
    int year, month, day, hour, minute, second;
    static  void init() {
        srand(time(NULL));
    }
    static Time now() {
        Time time ;
        time_t t= ::time(NULL);
        struct tm *ct = localtime(&t);
        time.initByTm(*ct);
        return time;
    }
    Time() {
    }
    Time(time_t t) {
        struct tm *ct = localtime(&t);
        initByTm(*ct);
    }
    void initByTm(const struct tm &t) {
        year = t.tm_year + 1900;
        month = t.tm_mon + 1;
        day = t.tm_mday;
        hour = t.tm_hour;
        minute = t.tm_min;
        second = t.tm_sec;

    }
    struct tm toTm() {
        struct tm t;
        t.tm_year = year - 1900;
        t.tm_mon = month - 1;
        t.tm_mday = day;
        t.tm_hour = hour;
        t.tm_min = minute;
        t.tm_sec = second;
        return t;
    }
    time_t makeTime() {
        struct tm t = toTm();
        return mktime(&t);
    }
    String format(const char *format) {
        char t[3 + strlen(format)];
        sprintf(t, format, year, month, day, hour, minute, second);
        return String(t);
    }
    String formatCn() {
        return format("%d年%d月%d日%d时%d分%d秒");
    }
    String formatChar() {
        return format("%d-%d-%d %d:%d:%d:");
    }
};

class Timer {
protected:
    float startTime;
public:
    Timer() {
        start();
    }

    inline void start() {
        startTime =now();
    }

    inline bool operator >(float ut) {
        if (pass() > ut) {
            start();
            return true;
        } else {
            return false;
        }
    }
    inline bool operator <(float ut) {
        if (pass() < ut) {
            start();
            return true;
        } else {
            return false;
        }
    }
    inline float pass() {
        return now()-startTime;
    }
    inline bool passOver(float ut) {
        if (pass() > ut) {
            start();
            return true;
        } else {
            return false;
        }
    }
    inline static  float now() {
        return  ((float )clock())/ CLOCKS_PER_SEC;
    }

};







