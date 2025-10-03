# 开发日志

## 2022.6.13 Mon - 赵

-  MPPT控制器：参照嘉立创元器件库，修改完成LT8491原理图对应电阻和电容封装。

## 2022.2.22 Tue - 赵

-  MPPT控制器：1、在ADI官网上下载LT8491封装文件（文件类型bxl），参照[bxl类型封装怎么转换为AD库封装](https://jingyan.baidu.com/article/48b558e326e1b17f39c09a57.html),转化为AD软件可以使用文件；2、由于LT8491原理图封装是按照顺序排列引脚的，根据需要改为引脚间功能相近的在一起；3、参照原理图中引脚1、FBIR（输入电压检测），理解RFBIN1、RFBIN2、RDACI1、RDACI2、CDAC1数值的计算方法。
- ![LT8491原理部分1.png](imgs/LT8491原理部分1.png)
