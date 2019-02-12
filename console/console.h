#pragma once
#include<vector>
#include<memory>
#include<functional>
#include<termios.h>
#include <sys/ioctl.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <signal.h>"

using std::vector;
using std::shared_ptr;
using std::function;
#define freep(x) freePtr(&x)
template < typename T > void freePtr(T ** p) {
    if (*p != NULL) {
        delete *p;
        *p = NULL;
    }
}
class Timer;
class Time;
class String;

class File;
#include"vstring.hpp"
#include"vfile.hpp"
#include"vtime.hpp"
#include"vplatform.hpp"

class Console {
public:
    class Color;
    class Activity;
    class View;
    class Piexl;
    class Drawable;

private:
    static vector < Activity * >activities;
    static int consoleRow,consoleColum,consoleSizeSign;
public:

#include"shape.hpp"
#include"drawable.h"
#include"color.h"
#include"view.h"
#include"activity.h"

    Console() {
    }
    static void startActivity(Activity & a) {
        if (!activities.empty()) {
            activities.back()->pause();
        }
        activities.push_back(&a);
        a.run();
    }

    static void init() {
        showCursor(false);
        showConsoleInput(false);
        Color::init();
#if defined(_ANDROID_)
        consoleSizeSign=0;
        while(consoleSizeSign<2) {
            signal(SIGWINCH, sigWinsize);
        }
#else
        struct winsize wsize;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize) >= 0) {
            consoleColum=wsize.ws_col;
            consoleRow=wsize.ws_row;
        }
#endif
    }

    static void sigWinsize(int signo) {
        struct winsize wsize;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize) >= 0) {
            consoleSizeSign++;
            consoleColum=wsize.ws_col;
            consoleRow=wsize.ws_row;
        }
    }
    static void showConsoleInput(bool show) {
        struct termios buff, option;
        tcgetattr(0, &buff);
        option = buff;
        if (show) {
            option.c_lflag |= ECHO;
            option.c_lflag |= ICANON;
        } else {
            option.c_lflag &= ~ECHO;
            option.c_lflag &= ~ICANON;
        }
        tcsetattr(0, TCSANOW, &option);
    }

    static bool kbhit() {
        bool ret;
        fd_set fds;
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        select(1, &fds, 0, 0, &tv);
        ret = FD_ISSET(0, &fds);
        return ret;
    }
    static void gotoxy(int x, int y) {
        printf("\e[%d; %df", y + 1, x + 1);
    }
    static void clear() {
        printf("\e[2J\e[0; 0f");
    }
    static void restart() {
        printf("\e[0; 0f");
    }
    static void clearColor() {
        printf("\e[0m");
    }
    static void showCursor(bool s) {
        printf(s ? "\e[?25h" : "\e[?25l");
    }

};



short Console::Color::system[16];
short Console::Color::gray[25];
short Console::Color::transparent=-1;

vector < Console::Activity * >Console::activities;
int Console::consoleRow=0,Console::consoleColum=0,Console::consoleSizeSign=0;



int main(int argc, char *s[]) {
    Time::init();
    Console::init();
    int cmain(Array < String > args);
    Array < String > args(argc);
    for (int i = 0; i < argc; i++) {
        args[i] = s[i];
    }
    return cmain(args);
}