# 坦克大战的CPP实现

使用方法：
Linux下编译运行：
```
git clone https://github.com/ve3344/Tankwar.git
cd Tankwar
g++ main.cpp -std=c++11 -w
```

绘制部分使用了Linux控制台的api，所以 目前只能在linux下运行

![运行效果图](https://upload-images.jianshu.io/upload_images/12618874-1d744f306aa5b0a9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

console文件夹里是封装的控制台绘图接口

绘制使用多重缓冲，不会导致刷新闪烁。
