# kiran-log-qt5

基于zlog在Qt5上使用的封装

## 编译

1. 安装运行依赖

   ```bash
   yum install zlog-devel qt5-qtbase-devel
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

安装了之后可使用pkgcofnig加入编译依赖

```bash
pkg-config --libs --cflags kiran-log-qt5
```

使用Log::instance()->init(...)进行日志库初始化并加入Qt日志输出回调中

需要输出日志输出，根据自身需要选择相关宏 LOG_DEBUG，LOG_DEBUG_S... 