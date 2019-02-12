const static int UP = 0;
const static int DOWN = 1;
const static int LEFT = 2;
const static int RIGHT = 3;
const static int BACK = 4;

class Thing;
class Wall;
class Bullet;
class Tank;
class Role;

class Thing {
  public: protected: bool exist = true;
  int x = 0, y = 0;
    Thing(int nx, int ny):x(nx), y(ny) {
  } public:void set(int nx, int ny) {
    x = nx;
    y = ny;
  }
  void setExist(bool e) {
    exist = e;
  }
  bool isExist() {
    return exist;
  }
  virtual void show(Drawable & d) {
  }
  virtual void run() {
  }
  virtual bool collide(const Thing & t) {
    return x == x && y == y;
  }
  int getX() {
    return x;
  }
  int getY() {
    return y;
  }
};
class Motion:public Thing {
protected:
  int aspect = UP;
    public: Motion():Thing(0, 0) {
  } Motion(int nx, int ny):Thing(nx, ny) {
  }

  int getAspect() {
    return aspect;
  }
  virtual bool cantmove() = 0;

  void move(int nAspect) {

    int oldAspect = aspect, oldX = x, oldY = y;
    if (nAspect == BACK) {
      switch (aspect) {
      case UP:
        y++;
        break;
      case DOWN:
        y--;
        break;
      case LEFT:
        x++;
        break;
      case RIGHT:
        x--;
        break;
      }
    } else {
      if (aspect != nAspect) {
        aspect = nAspect;
      } else {
        switch (aspect) {
        case UP:
          y--;
          break;
        case DOWN:
          y++;
          break;
        case LEFT:
          x--;
          break;
        case RIGHT:
          x++;
          break;
        }
      }
    }
    if (cantmove()) {

      aspect = oldAspect;
      x = oldX;
      y = oldY;
    }
  }
};

class Bullet:public Motion {
  protected:Timer moveTimer;
  Tank *owner;
    public:Bullet(Tank * from):owner(from) {
    aspect = from->getAspect();
    x = from->getX();
    y = from->getY();
  } bool collide(Tank & t) {
    return t.collide(*this);
  }
  bool collide(Bullet & t) {
    return Thing::collide(t);
  }
  bool cantmove() override {
    return manager->collideEnemies(*this) || manager->collideWalls(*this);
  }
  void run() {
    if (moveTimer > 0.004) {
      int oldX = x, oldY = y;
      switch (aspect) {
      case UP:
        y--;
        break;
      case DOWN:
        y++;
        break;
      case LEFT:
        x--;
        break;
      case RIGHT:
        x++;
        break;
      }
      if (manager->outOfMap(this)) {
        x = oldX;
        y = oldY;
        exist = false;
      }
      Enemy *enemy = manager->getCollideEnemy(*this);
      if (manager->isRole(owner) && enemy != NULL) {
        exist = false;
        enemy->setExist(false);
      }
      Bullet *bullet = manager->getCollideBullet(*this);
      if (bullet != NULL) {
        exist = false;
        bullet->setExist(false);
      }
    }
  }
  void show(Drawable & d) {
    d.draw(x, y, Piexl(" ", 99, 89));
  }
};
class Wall:public Thing {
  protected: public: Wall(int x, int y):Thing(x, y) {
  } bool collide(Tank & t) {
    return t.collide(*this);
  }
  bool collide(Bullet & t) {
    return Thing::collide(*this);
  }
  void show(Drawable & d) {
    d.draw(x, y, Piexl(' ', 107, 126));
  }
};




class Tank:public Motion {
protected:
  int hp = 0;
    std::list < Bullet * >bullets;
  Timer attackTimer;

    public: Tank():Motion(1, 1) {
  } Tank(int nx, int ny, int a):Motion(nx, ny) {
    aspect = a;
  }
   bool cantmove()override {
    return x <= 0 || y <= 0 || x >= manager->width() - 1
      || y >= manager->height() - 1 || manager->collideWalls(*this);;
  }

  bool collide(Wall & w) {
    return at(w.getX() - x + 1, w.getY() - y + 1);
  }
  bool collide(Bullet & w) {
    return at(w.getX() - x + 1, w.getY() - y + 1);
  }
  bool collide(Tank & t) {
    if (abs(x - t.x) >= 3 || abs(y - t.y) >= 3) {
      return false;
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (at(i, j) && t.at(i + x - t.getX(), j + y - t.getY())) {
          return true;
        }
      }
    }
    return false;
  }
  bool at(int nx, int ny) {
    return (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
      && datas.tankDrawTemplate[aspect].at(nx, ny);
  }

  DrawTemplate dt() {
    return datas.tankDrawTemplate[aspect];
  }
  virtual void attack() {
    if (attackTimer > 0.1) {
      manager->addBullet(this);
    }
  }
  void show(Drawable & d) override {
    d.draw(x - 1, y - 1, dt(), Piexl(' ', 133, 144));
  }
};
class Enemy:public Tank {
  Timer autoReactTimer;
public:
    Enemy(int x, int y, int a):Tank(x, y, a) {
  } 
  bool cantmove() override {
    return Tank::cantmove() || manager->collideTanks(*this);
  }

  void autoReact() {
    if (autoReactTimer > 0.5) {
      int action = random(0, 6);
      if (action<=4){
      Motion::move(action);
      }
      if (random(0, 2) == 0) {
        attack();
      }
    }
  }
  void run() override {
    autoReact();
  }
  void show(Drawable & d) override {
    d.draw(x - 1, y - 1, dt(), Piexl(' ', 123, 111));
  }
};

class Role:public Tank {
public:
  Role() {

  } bool cantmove() override {
    return Tank::cantmove() || manager->collideEnemies(*this);
  }
  void onKeyDown(int key) {
    switch (key) {
    case 'w':
      move(UP);
      break;
    case 's':
      move(DOWN);
      break;
    case 'a':
      move(LEFT);
      break;
    case 'd':
      move(RIGHT);
      break;
    case 'e':
      move(BACK);
      break;

    case ' ':
      attack();
      break;

    }

  }
  void show(Drawable & d) override {
    d.draw(x - 1, y - 1, dt(), Piexl("  ", 173, 174));
  }


};