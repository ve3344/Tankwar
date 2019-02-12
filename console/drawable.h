template < typename T > class BaseDrawable {
protected:
    int w = 0, h = 0;
    std::shared_ptr < T > data;


    static void deleter(T * mdata) {
        delete mdata;
    }
    static void arrayDeleter(T * mdata) {
        delete[]mdata;
    }
    static int min(int a, int b) {
        return a > b ? b : a;
    }
    virtual void malloc(int size) =0;
public:
    void resize(int wid, int hei) {
        w = wid;
        h = hei;
        malloc(w * h);

    }
    void fill(T p) {
        int count = w * h;
        T *piexls = data.get();

        for (int i = 0; i < count; i++) {
            piexls[i] = p;
        }
    }
    void draw(int x, int y, int wid, int hei, T p) {
        int W = min(wid, w- x);
        int H = min(hei, h - y);
        for (int cx = 0; cx < W; cx++) {
            for (int cy = 0; cy < H; cy++) {
                at(cx + x, cy + y) = p;
            }
        }
    }

    T & at(int x, int y) {
        return data.get()[y * w + x];
    }
    T *get(int x, int y) {
        return &data.get()[y * w + x];
    }
    int width() {
        return w;
    }
    int height() {
        return h;
    }

};
class DrawTemplate:public BaseDrawable < bool > {

    void malloc(int size) override {
        data.reset(new bool[size], &arrayDeleter);
    }
public:
    DrawTemplate() {
    }

    DrawTemplate(int wid, int hei) {
        resize(wid,hei);
    }

    DrawTemplate draw(int x,int y) {
        at(x,y)=true;
        return *this;
    }
    void clear(){
        fill(false);
    }
    void draw(std::vector<Point> ps) {
        for (Point p:ps) {
            at(p.x,p.y)=true;
        }
    }
};










class Piexl {
public:
    short bg = 0, fg = 0;
    char word[3] = { 0, 0, 0};
    Piexl() {
        set(' ',Color::transparent,Color::transparent);
    }
    Piexl(char mc, short bg, short fg) {
        set(mc,bg,fg);
    }

    Piexl(const Piexl & o) {
        if (bg > 0 && fg > 0) {
            set(o);
        }
    }
    Piexl(char *mword, short bg, short fg) {
        set(mword,bg,fg);
    }
    void set(char mc, short mbg, short mfg) {
        word[0] = mc;
        bg = mbg;
        fg = mfg;
    }
    void set(const Piexl & o) {
        word[0] = o.word[0];
        word[1] = o.word[1];
        word[2] = o.word[2];
        bg=o.bg;
        fg = o.fg;

    }

    void set(const char *mword, short mbg, short mfg) {
        word[0] = mword[0];
        if (isChinese(word[0])) {
            word[1] = mword[1];
            word[2] = mword[2];
        }
        bg = mbg;
        fg = mfg;
    }

    void print() {
        if (bg < 0 || fg < 0) {
            printf("\e[0;m  ");
        } else {
            printf("\e[38;5;%dm\e[48;5;%dm", fg, bg);
            if (isChinese(word[0])) {
                putchar(word[0]);
                putchar(word[1]);
                putchar(word[2]);
            } else {
                putchar(' ');
                putchar(word[0]);


            }
        }

    }

};
class Drawable :public BaseDrawable<Piexl> {
protected :
    void malloc(int size) override {
        data.reset(new Piexl[size], &arrayDeleter);
    }

public:
    Drawable() {

    }
    Drawable(int wid, int hei) {
        resize(wid,hei);
    }
    void save(File f) {
        FileStream fs(f);

        fs.open("w+");
        fs.printf("width=%d\n",w);
        fs.printf("height=%d\n",h);
        int count=w*h;
        Piexl p;
        for (int i = 0; i < count; i++) {
            p.set(data.get()[i]);
            fs.printf("%d,%d,%s\n",p.bg,p.fg,p.word);
        }
        fs.close();
    }
    static Drawable load(File f) {
        Drawable d;
        int w=0,h=0;
        FileStream fs(f);
        fs.open("r+");
        fs.scanf("width=%d\n",&w);
        fs.scanf("height=%d\n",&h);
        d.resize(w,h);
        int count=w*h;

        int bg,fg;
        char word[4];
        for (int i = 0; i < count&&!fs.end(); i++) {
            fs.scanf("%d,%d,%s\n",&bg,&fg,word);
            d.data.get()[i].set(word,bg,fg);
        }
        fs.close();
        return d;
    }
    void clear(short color) {
        Piexl p(' ', color, 0);
        fill(p);
    }
    void draw(std::vector<Point> points,const Piexl & piexl) {
        for (Point p:points) {
            at(p.x,p.y)=piexl;
        }
    }
    void draw(int x, int y, short bg, short fg, String s) {
        int cx = x, cy = y;
        Piexl p;
        char *str = s.get();
        for (int i = 0; i < s.length();) {
            p.bg = bg;
            p.fg = fg;

            if (isChinese(str[i])) {
                p.word[0] = str[i];
                i++;
                p.word[1] = str[i];
                i++;
                p.word[2] = str[i];
                i++;

            } else {
                p.word[0] = str[i];
                i++;
            }

            at(cx, cy) = p;
            cx++;
            if (cx >= w) {
                cx = x;
                cy++;
                if (cy >= h) {
                    break;
                }
            }

        }
    }
    void draw(int x, int y, DrawTemplate d,const Piexl& p) {
        int W = min(d.width(), w - x);
        int H = min(d.height(), h - y);
        for (int cx = 0; cx < W; cx++) {
            for (int cy = 0; cy < H; cy++) {
                if (d.at(cx, cy)) {
                    at(cx + x, cy + y) =p;
                }
            }
        }
    }    void draw(int x, int y,const Piexl& p) {
            at(x,y) =p;
    }

    void show(int x0, int y0) {
        for (int y = 0; y < h; y++) {
            printf("\e[%d;%df", y + y0 + 1, (x0 << 1) + 1);
            for (int x = 0; x < w; x++) {

                at(x, y).print();
            }
        }
    }
    void draw(int x, int y,  Drawable d) {
        int W = min(d.w, w - x);
        int H = min(d.h, h - y);


        for (int cx = 0; cx < W; cx++) {
            for (int cy = 0; cy < H; cy++) {
                at(cx + x, cy + y) = d.at(cx, cy);
            }
        }
    }

    #define DrawBy(ca,op) case ca:for (int cx = 0; cx < W; cx++) {for (int cy = 0; cy < H; cy++) {op;}}break;
    void draw(int x, int y,  Drawable  d,int a) {
        int W = min(d.w, w - x);
        int H = min(d.h, h - y);

        switch (a) {
        	DrawBy(0,at(cx + x, cy + y) = d.at(cx, cy));
        	DrawBy(1,at(cx + x, cy + y) = d.at(W-1-cx, cy));
        	DrawBy(2,at(cx + x, cy + y) = d.at(cx, H-1-cy));
        	DrawBy(3,at(cx + x, cy + y) = d.at(cy, cx));
        	DrawBy(4,at(cx + x, cy + y) = d.at(cy,W-1-cx));
        	DrawBy(5,at(cx + x, cy + y) = d.at(H-1-cy, cx));

        	/*
        case 0:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(cx, cy);
                }
            }
            break;

        case 1:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(W-1-cx, cy);
                }
            }
            break;
        case 2:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(cx,H-1-cy);
                }
            }
            break;
        case 3:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(W-1-cx,H-1-cy);
                }
            }
            break;



        case 4:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(cy,cx);
                }
            }
            break;
        case 5:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(H-1-cy,cx);
                }
            }
            break;

        case 6:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(cy,W-1-cx);
                }
            }
            break;
        case 7:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(H-1-cy,W-1-cx);
                }
            }
            break;
        default:
            for (int cx = 0; cx < W; cx++) {
                for (int cy = 0; cy < H; cy++) {
                    at(cx + x, cy + y) = d.at(cx, cy);
                }
            }
            break;
            */
        }
    }
void draw(int x, int y, DrawTemplate  d,Piexl p,int a) {
        int W = min(d.width(), w - x);
        int H = min(d.height(), h - y);

        switch (a) {
        	DrawBy(0,if (d.at(cx, cy))at(cx + x, cy + y) =p);
        	DrawBy(1,if (d.at(W-1-cx, cy))at(cx + x, cy + y) =p);
        	DrawBy(2,if (d.at(cx, H-1-cy))at(cx + x, cy + y) =p );
        	DrawBy(3,if (d.at(cy, cx))at(cx + x, cy + y) =p );
        	DrawBy(4,if (d.at(cy, W-1-cx))at(cx + x, cy + y) =p );
        	DrawBy(5,if (d.at(H-1-cy, cx))at(cx + x, cy + y) =p );
        }


    }

};
