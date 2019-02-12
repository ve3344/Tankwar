class View {
protected:
  Activity * activity;
  int x=0,y=0,w=0, h=0;
public:
  Drawable canvas;
    public:View(Activity * a):activity(a), canvas() {
    	w=a->width();
    	h=a->height();
  }

  void invalidate() {
    onDraw(canvas);
  }
  void invalidate(function<void(Drawable&) > draw) {
    draw(canvas);
  }
  Activity *getActivity() {
    return activity;
  }
  void draw() {

  }


  virtual void onKeyDown(char c) {
  }
  virtual void onDraw(Drawable & canvas) {
  }
  virtual void onResize(int w, int h) {
  }
};
