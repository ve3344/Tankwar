
class Activity {
protected:
    enum Status {
        PREPARED,
        RUNNING,
        PAUSE,
        FINISHED
    } status;

    int wid = 0, hei = 0;
    int frame = 0, fps = 0;
    Timer drawTimer, frameTimer;
    Drawable screen;
public:
    Activity() {
        wid=consoleColum/2;
        hei=consoleRow;
        status = PREPARED;
        screen.resize(wid,hei)
;    }
    ~Activity() {
    }
    int mesure(String t) {
        return t.length()<<1;
    }
    void pause() {
        status=PAUSE;
        onPause();
    }
    void resume() {
        status=RUNNING;
        onResume();
        run();
    }




    void resize(struct winsize &size) {
        hei = size.ws_row;
        wid = size.ws_col / 2;
        onActivityResize(wid, hei);
    }
    void keyDown(char k) {
        onKeyDown(k);

    }
    virtual void onPause() {
    }
    virtual void onResume() {
    }
    virtual void onCreate() {
    }
    virtual void onActivityResize(int w, int h) {
    }

    virtual void onKeyDown(char key) {

    }
    int width() {
        return wid;
    }
    int height() {
        return hei;
    }
    virtual void onDraw(Drawable & screen) {

    }
    void run() {

        if(status==PREPARED){
            onCreate();
            status=RUNNING;
        }
        while (status==RUNNING) {
            usleep(100);
            fflush(stdin);
            onDraw(screen);
            if (frameTimer > 1) {
                fps = frame;
                frame = 0;
            }
            if (drawTimer>0.01) {
                frame++;
                screen.show(0, 0);
                fflush(stdout);
            }
            act();
        }
    }


    void act() {
        signal(SIGWINCH, sigWinsize);
        if (kbhit()) {
            keyDown(getchar());
            fflush(stdin);
        }
    }
    void finish() {
        status=FINISHED;
        clear();
        activities.pop_back();
        if (!activities.empty()) {
            activities.back()->resume();
        }

    }


private:
    static void sigWinsize(int signo) {
        struct winsize size;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) >= 0) {
            if (!activities.empty()) {
                activities.back()->resize(size);
            }
        }
    }
};
