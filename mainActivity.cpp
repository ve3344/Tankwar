


class MainActivity:public Activity {
   public:
class Thing;
class Bullet;
class Wall;
class Motion;
class Tank;
class Role;
class Enemy;
class Manager;
static Manager *manager;
#include"manager.cpp"
#include"thing.cpp"
public:
     Role role;
    MainActivity(){

        manager=new Manager();
        manager->setSize(width(),height());
        manager->setRole(&role);

        manager->addWall(new Wall(12,12));



    }

    void onDraw(Drawable & screen) override {
        screen.fill(Piexl(' ',60, 113));
        manager->show(screen);

        role.show(screen);

    }
    ~MainActivity(){
        freep(manager);
    }

    void onKeyDown(char key) override {
        if (key=='q'){
            manager->randAddEnemy();
        }
        role.onKeyDown(key);
       // finish();
    }
};
