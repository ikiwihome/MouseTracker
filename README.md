# MouseTracker

实时显示鼠标XY坐标的极简Win32窗体应用，基于C++实现，适用于Windows 10以上系统，生成的exe最小只有17KB。

---


坐标为鼠标所在位置相对于显示屏分辨率的坐标值，坐标每50ms更新，窗体显示在最上方，显示效果如下：

![](MouseTracker.png)


GCC编译命令(GCC需自行安装)：

```powershell
x86_64-w64-mingw32-g++.exe -Os -s -mwindows -lgdi32 -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffunction-sections -fdata-sections -Wl,--gc-sections -flto MouseTracker.cpp -o MouseTracker.exe
```

或者

```powershell
g++.exe -Os -s -mwindows -lgdi32 -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffunction-sections -fdata-sections -Wl,--gc-sections -flto MouseTracker.cpp -o MouseTracker.exe
```
