#kiran-log
基于zlog在Qt5和GTK3上的封装
## 编译
1. 安装运行依赖
   ```bash
   yum install zlog-devel qt5-qtbase-devel glibmm24-devel
   ```
2. 在源码根目录下创建**build**目录并进入
   ```bash
   mkdir build && cd build
   ```
3. 通过cmake生成Makefile
   ```bash
   cmake -DCMAKE_INSTALL_PREFIX=/usr ..
   ```
4. 通过生成的Makefile进行构建
   ```bash
   make -j`cat /proc/cpuinfo|grep processor|wc -l`
   ```
## 安装
1. 编译完成之后执行
   ```bash
   sudo make install
   ```
## 使用
   具体使用可见源码根目录下**test**目录