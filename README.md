# lazyExcel
a simply software like MS-Excel.it can be running muiti-platform...

1、2005年写的Excel，可跨平台（Grid部分跨平台，需要实现OSFace\xxplatform\GDI\CLDrawer类），现在放出来

2、可以替代微软的excel大部分功能，同时加入了一些新特性，可以非常方便的实现各种需要复杂报表

3、脚本语言（ScriptEngine）:

	a、采用类c语法，不支持指针操作，不支持?:操作
	
	b、只支持3种变量类型 number-->数值型   string-->字符串型 list
	
	c、支持自定义函数以及其他特征；
	
	d、支持动态回调接口，可以调用c/c++编写的函数，可以支持外部变量动态求值
	
	e、本引擎为跨平台嵌入式引擎，可以嵌入到任何应用中
	
