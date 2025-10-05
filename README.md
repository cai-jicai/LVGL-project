#LVGL8.2实战项目

学习资料
https://www.freecodecamp.org/chinese/news/5-ways-to-use-linux-on-a-windows-machine/
https://no-chicken.com/content/FryPi/5.LVGL%E5%9F%BA%E7%A1%80%E7%9F%A5%E8%AF%86/3.LVGL%E4%BB%BF%E7%9C%9F.html
https://blog.csdn.net/weixin_49337111/article/details/136536375
https://lvgl.100ask.net/master/details/integration/ide/pc-simulator.html


####Project Introduction：
本项目有一个基于VS Code的LVGL仿真，以及实际应用在嵌入式项目上的成品

####Languages and Tools：
C语言、仿真平台VS Code、keil

####software：
Windows、

####hardware（文件夹中硬件资料支持嘉立创与AD，内容一样）：
主控板：STM32F103ZET6核心板
触摸屏：ILI9806G（LCD）、GT911（电容触摸芯片）
接口：触摸屏（IIC：SCL-GPIOB1、SDA-GPIOF9）、LCD（Intel8080-16——FSMC）

#### VSCode仿真
PC模拟LVGL8.3-VSCode
	1.环境搭建
		VSCode插件：C/C++工具、CMake、CMake Tools
		CMAke 官网下载
		MinGW-64
		SDL2——SDL2-devel-2.30.1-mingw.zip
		LVGL8.3版本
			lvgl-release-v8.3
			lv_port_pc_eclipse-release-v8.3
			lv_drivers-release-v8.3
		lvgl_template_v8.3
				lvgl
					lvgl-release-v8.3
				lv_drivers
					lv_drivers-release-v8.3
				根目录
					lv_port_pc_eclipse-release-v8.3
				bin
					把sdl2.dll放在这里
	2.移植BMS的触摸屏代码到搭建的工程文件lv_mainstart.h
		在lvgl/pe_examples中放置代码.c.h
		写入main.c函数里，改变长宽lv_drv_conf.h
		在 CMakeLists.txt 中，将 lv_mainstart.c 所在的源文件明确添加到可执行文件的构建列表中，确保编译器编译该文件并参与链接。
			file(GLOB_RECURSE INCLUDES "lv_drivers/*.h" "lvgl/demos/*.h"  "lvgl/*.h"  "./*.h" "lvgl/pe_examples/*.h" )
			file(GLOB_RECURSE SOURCES  "lv_drivers/*.c" "lvgl/demos/*.c"  "lvgl/src/*.c" "lvgl/pe_examples/*.c")
			add_executable(main main.c mouse_cursor_icon.c ${SOURCES} ${INCLUDES})

####Code Optimization Module Introduction：

	（1）静态动态界面分割：将界面拆分为 静态右边区域 和 动态左边区域，通过复用对象和减少渲染范围优化性能。在回调中限制刷新区域仅为左边动态区域，通过刷新数据坐标判断左右边

	（2）预创建动态界面对象池：
		A.预创建多个列表对象并复用，避免频繁创建/销毁，对新旧列表进行显示与隐藏
		B.数据懒加载，仅在列表可见时更新内容

####Introduction to the Next Version Plan：
	（1）数据脏标记：仅刷新数据区域，进一步减少面积