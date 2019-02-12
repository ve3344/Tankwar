class DataSet {
   public:
     std::vector<Point> tankTemplate[4]= {
        {{0,1},{0,2},{1,0},{1,1},{2,1},{2,2}},//up
        {{0,0},{0,1},{1,1},{1,2},{2,0},{2,1}},//down
        {{0,1},{1,0},{1,1},{1,2},{2,0},{2,2}},//left
        {{0,0},{0,2},{1,0},{1,1},{1,2},{2,1}}//right
    };
    DrawTemplate tankDrawTemplate[4];

    DataSet(){
        for (int i=0; i<4 ; i++ ) {
            tankDrawTemplate[i]=DrawTemplate(3,3);
            tankDrawTemplate[i].clear();
            tankDrawTemplate[i].draw(tankTemplate[i]);
        }


    }
};
