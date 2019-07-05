# MyCPP_Practical-Training
## 一些介绍
1. 这是我的首个C++实训项目   
2. 本游戏基于easyX图形库,需要安装文件包内的EasyX_2018春分版才可运行
3. 特别鸣谢以下师兄对我的技术支持帮助
   1. [sola](https://github.com/unlimitedsola)
   2. [Clovin](https://github.com/Clovin)
   3. [hangxingliu](https://github.com/hangxingliu)
---
一些运行要求:  
VC6 默认使用的 MBCS 编码，而 VC2008 及高版本 VC 默认使用的 Unicode 编码。以下详细解释这个问题：  
用 char 表示字符时，英文占用一个字节，中文占用两个字节。  
这样有一个严重的问题：两个连续字节，究竟是两个英文字符，还是一个中文字符？  
为了解决这个问题，Unicode 编码诞生了。Unicode 编码不管中文英文都用两个字节表示。  
 对于 **MBCS** 编码，字符变量用 **char** 定义。  
 对于 **Unicode** 编码中，字符变量用 **wchar_t** 定义。  
 **故在Visual Sstudio 高版本中可使用  _T("abc")  或  项目 —> 属性  —> 更改字符集  —> Unicode —> 多字符集 即可**  
 因为编译本程源码所用编译器的版本是 **Visual Studio 2017** 采用了 **V141** 版本的工具集  
 若要在**VS12**中运行，修改**工具集版本**即可
