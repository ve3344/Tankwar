#include"console/console.h"
#include<list>

class App:public Console {
public:


#include"dataSet.cpp"
static DataSet datas;
#include"mainActivity.cpp"


};
App::MainActivity::Manager* App::MainActivity::manager=NULL;
App::DataSet App::datas;

int cmain(Array < String > args) {
    App::MainActivity a ;
   App::startActivity(a);

    return 0;
}





























