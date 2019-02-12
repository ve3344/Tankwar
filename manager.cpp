class Manager {
    std::list<Enemy*> enemies;
    std::list<Wall*> walls;
    std::list<Bullet*> bullets;
    Role* role;
    int w=0,h=0;
public:
    Manager() {}
    ~Manager() {
        clear();
    }
    void setRole(Role* r) {
        role=r;
    }
    bool isRole(Thing *t) {
        return t==role;
    }
    void setSize(int nw,int nh) {
        w=nw;
        h=nh;
    }
    bool outOfMap(Thing *t) {
        return t->getX()<0||t->getY()<0||t->getX()>=w||t->getY()>=h;
    }
    int width() {
        return w;
    }
    int height() {
        return h;
    }
    void clear() {
        for(Enemy *e:enemies) {
            delete e;
            e=NULL;
        }
        enemies.clear();
        for(Wall *w:walls) {
            delete w;
            w=NULL;
        }
        walls.clear();
        for(Bullet *b:bullets) {
            delete b;
            b=NULL;
        }
        bullets.clear();

    }
    void addEnemy(int x,int y,int a) {
        enemies.insert(enemies.end(),new Enemy(x,y,a));
    }
    void addEnemy(Enemy*e) {
        enemies.insert(enemies.end(),e);
    }
    void addBullet(Tank *t) {
        bullets.insert(bullets.end(),new Bullet(t));
    }
    void addWall(Wall *w) {
        walls.insert(walls.end(),w);
    }
    Enemy* getCollideEnemy(Bullet& t) {
        for(Enemy *e:enemies) {
            if (e->collide(t)) {
                return e;
            }
        }
        return NULL;
    }
    Enemy* getCollideEnemy(Tank& t) {
        for(Enemy *e:enemies) {
            if (e->collide(t)) {
                return e;
            }
        }
        return NULL;
    }
    Enemy* randAddEnemy() {
        Enemy *e;
        while(true) {
            int x=random(1,w-1);
            int y=random(1,h-1);
            int aspect=random(0,3);
            e=new Enemy(x,y,aspect);
            if (e->cantmove()) {
                delete e;

            } else {
                break;
            }
        }

        enemies.insert(enemies.end(),e);
        return e;
    }
    Bullet* getCollideBullet(Bullet& t) {
        for(Bullet *e:bullets) {
            if (e!=&t&&e->collide(t)) {
                return NULL;
            }
        }
        return NULL;
    }

    bool collideEnemies(Tank& t) {
        for(Enemy *e:enemies) {
            if (e->collide(t)) {
                return true;
            }
        }
        return false;
    }
    bool collideTanks(Tank& t) {
        if (&t!=role&&role->collide(t)) {
            return true;
        }
        for(Enemy *e:enemies) {
            if (&t!=e&&e->collide(t)) {
                return true;
            }
        }
        return false;
    }

    bool collideWalls(Tank t) {
        for(Wall *w:walls) {
            if (w->collide(t)) {
                return true;
            }
        }
        return false;
    }
    bool collideEnemies(Bullet t) {
        for(Enemy *e:enemies) {
            if (e->collide(t)) {
                return true;
            }
        }
        return false;
    }
    bool collideWalls(Bullet t) {
        for(Wall *w:walls) {
            if (w->collide(t)) {
                return true;
            }
        }
        return false;
    }

    void show(Drawable &a) {
        for (auto it =bullets.begin(); it!=bullets.end(); ) {
            Bullet *e=*it;
            if (e->isExist()) {
                e->run();
                e->show(a);
                it++;

            } else {
                it=bullets.erase(it);
                freep(e);
            }

        }


        for (auto it =walls.begin(); it!=walls.end(); ) {
            Wall *e=*it;
            if (e->isExist()) {
                e->run();
                e->show(a);
                it++;

            } else {
                it=walls.erase(it);
                freep(e);
            }

        }
        for (auto it =enemies.begin(); it!=enemies.end(); ) {
            Enemy *e=*it;
            if (e->isExist()) {
                e->run();
                e->show(a);
                it++;
            } else {
                it=enemies.erase(it);
                freep(e);
            }

        }

    }



protected:
private:
};
