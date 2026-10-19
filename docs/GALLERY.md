# 智能风扇图片与结构图集

以下 30 张图片提取自用户提供的智能风扇 Word 报告，按实物、硬件、选型和历史开发截图分类。备选模块不代表实际装配；图片中的控制值不代表实测 RPM。原报告的部分性能表述不作为本次新增测试结论。

[返回项目首页](../README.md) · [查看图片来源记录](images/sources.json)

## 系统总结构

![系统总结构](images/diagrams/architecture.svg)

## 实物与操作照片

![对应结构与流程](images/diagrams/control-flow.svg)

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-23.jpeg"><img src="images/gallery/fan-23.jpeg" width="350" alt="定时参数设置实拍"></a><br><strong>定时参数设置实拍</strong><br>原报告标注为设置 30 秒的操作照片；不据此推出计时精度。<br><sub>Word 原报告 · image23.jpeg</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-24.jpeg"><img src="images/gallery/fan-24.jpeg" width="350" alt="定时运行状态实拍"></a><br><strong>定时运行状态实拍</strong><br>面包板、OLED 与风扇运行状态的历史照片。<br><sub>Word 原报告 · image24.jpeg</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-25.jpeg"><img src="images/gallery/fan-25.jpeg" width="350" alt="定时结束状态实拍"></a><br><strong>定时结束状态实拍</strong><br>原报告标注的倒计时结束照片，保留为历史展示。<br><sub>Word 原报告 · image25.jpeg</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-26.jpeg"><img src="images/gallery/fan-26.jpeg" width="350" alt="手动控制值为零的实拍"></a><br><strong>手动控制值为零的实拍</strong><br>控制值用于 PWM 调节；不是通过转速传感器测得的 RPM。<br><sub>Word 原报告 · image26.jpeg</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-27.jpeg"><img src="images/gallery/fan-27.jpeg" width="350" alt="手动调速面包板实拍"></a><br><strong>手动调速面包板实拍</strong><br>展示电机、主控、编码器和 OLED；界面中的数值为控制值。<br><sub>Word 原报告 · image27.jpeg</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-28.jpeg"><img src="images/gallery/fan-28.jpeg" width="350" alt="检测操作照片一"></a><br><strong>检测操作照片一</strong><br>原报告标注 30mm 的操作场景；距离与触发效果未在本次独立测量。<br><sub>Word 原报告 · image28.jpeg</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-29.jpeg"><img src="images/gallery/fan-29.jpeg" width="350" alt="检测操作照片二"></a><br><strong>检测操作照片二</strong><br>原报告标注 15mm 的操作场景，展示传感器门控操作。<br><sub>Word 原报告 · image29.jpeg</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-30.jpeg"><img src="images/gallery/fan-30.jpeg" width="350" alt="检测操作照片三"></a><br><strong>检测操作照片三</strong><br>原报告标注 5mm 的操作场景，保留原始照片，不新增距离测试结论。<br><sub>Word 原报告 · image30.jpeg</sub></td>
</tr>
</table>

## 主控与外围电路

![对应结构与流程](images/diagrams/signal-map.svg)

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-09.png"><img src="images/gallery/fan-09.png" width="350" alt="系统硬件模块电路总览"></a><br><strong>系统硬件模块电路总览</strong><br>原报告电路图片，展示主控、接口和外围模块；保留原图内容，不作为本次电气验收。<br><sub>Word 原报告 · image9.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-10.png"><img src="images/gallery/fan-10.png" width="350" alt="STM32 主控引脚连接"></a><br><strong>STM32 主控引脚连接</strong><br>原报告的 MCU 连接图，使用前与源码引脚及实际板卡逐项核对。<br><sub>Word 原报告 · image10.png</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-11.png"><img src="images/gallery/fan-11.png" width="350" alt="低速晶振原图"></a><br><strong>低速晶振原图</strong><br>保留原报告截图中的元件值；晶振与负载电容需要结合实际芯片和电路复核。<br><sub>Word 原报告 · image11.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-12.png"><img src="images/gallery/fan-12.png" width="350" alt="高速晶振原图"></a><br><strong>高速晶振原图</strong><br>原资料的外部高速时钟电路截图。<br><sub>Word 原报告 · image12.png</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-13.png"><img src="images/gallery/fan-13.png" width="350" alt="复位电路原图"></a><br><strong>复位电路原图</strong><br>NRST 按键与外围电路截图。<br><sub>Word 原报告 · image13.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-14.png"><img src="images/gallery/fan-14.png" width="350" alt="SWD 下载接口原图"></a><br><strong>SWD 下载接口原图</strong><br>SWCLK、SWDIO、电源和地的接口示意。<br><sub>Word 原报告 · image14.png</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-15.png"><img src="images/gallery/fan-15.png" width="350" alt="DHT11 接口原图"></a><br><strong>DHT11 接口原图</strong><br>原图标注 5V 供电；与 3.3V 主控连接前应核对模块输出和上拉电压。<br><sub>Word 原报告 · image15.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-16.png"><img src="images/gallery/fan-16.png" width="350" alt="红外检测电路原图"></a><br><strong>红外检测电路原图</strong><br>原图的器件名称与正文、代码符号有差异，保留待核对说明。<br><sub>Word 原报告 · image16.png</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-17.png"><img src="images/gallery/fan-17.png" width="350" alt="独立按键电路"></a><br><strong>独立按键电路</strong><br>PB0 为菜单移动键，PB10 为确认键；原图按下接地。<br><sub>Word 原报告 · image17.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-18.png"><img src="images/gallery/fan-18.png" width="350" alt="旋转编码器接口"></a><br><strong>旋转编码器接口</strong><br>S1 / S2 / KEY 对应 PB15 / PB14 / PB1，用于调节与锁定。<br><sub>Word 原报告 · image18.png</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-19.png"><img src="images/gallery/fan-19.png" width="350" alt="OLED 接口"></a><br><strong>OLED 接口</strong><br>PB8 / PB9 对应软件 I²C 时钟与数据线。<br><sub>Word 原报告 · image19.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-20.png"><img src="images/gallery/fan-20.png" width="350" alt="电机驱动连接原图"></a><br><strong>电机驱动连接原图</strong><br>展示 TB6612FNG A 通道及电机端子，须结合硬件文档核对供电和 STBY。<br><sub>Word 原报告 · image20.png</sub></td>
</tr>
</table>

## 器件选型与备选方案

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-01.png"><img src="images/gallery/fan-01.png" width="350" alt="DS18B20 备选温度传感器"></a><br><strong>DS18B20 备选温度传感器</strong><br>原报告的器件选型对比图；风扇公开源码采用 DHT11，不将此图当作已用器件。<br><sub>Word 原报告 · image1.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-02.png"><img src="images/gallery/fan-02.png" width="350" alt="DHT11 温湿度模块"></a><br><strong>DHT11 温湿度模块</strong><br>原报告所用温湿度采集模块示意，DATA 信号对应 PA0。<br><sub>Word 原报告 · image2.png</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-03.jpeg"><img src="images/gallery/fan-03.jpeg" width="350" alt="L9110S 备选驱动模块"></a><br><strong>L9110S 备选驱动模块</strong><br>器件选型对比图；本项目公开接线采用 TB6612FNG。<br><sub>Word 原报告 · image3.jpeg</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-04.png"><img src="images/gallery/fan-04.png" width="350" alt="TB6612FNG 驱动模块"></a><br><strong>TB6612FNG 驱动模块</strong><br>直流电机驱动模块图片，实际模块引脚定义仍需核对。<br><sub>Word 原报告 · image4.png</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-05.png"><img src="images/gallery/fan-05.png" width="350" alt="HC-SR501 备选红外模块"></a><br><strong>HC-SR501 备选红外模块</strong><br>原报告的方案比较图；不是本仓库确认的实际装配模块。<br><sub>Word 原报告 · image5.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-06.jpeg"><img src="images/gallery/fan-06.jpeg" width="350" alt="反射式红外模块图片"></a><br><strong>反射式红外模块图片</strong><br>报告标注 TCRT5000，其他资料出现 TCRT1000 / HCSR505 名称，型号和有效电平待核对。<br><sub>Word 原报告 · image6.jpeg</sub></td>
</tr>
</table>

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-07.png"><img src="images/gallery/fan-07.png" width="350" alt="LCD1602 备选显示模块"></a><br><strong>LCD1602 备选显示模块</strong><br>选型比较图；本项目采用 OLED 显示。<br><sub>Word 原报告 · image7.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-08.png"><img src="images/gallery/fan-08.png" width="350" alt="OLED 显示模块"></a><br><strong>OLED 显示模块</strong><br>0.96 寸四线接口模块图片，具体电平和驱动以硬件说明为准。<br><sub>Word 原报告 · image8.png</sub></td>
</tr>
</table>

## 开发与仿真历史截图

<table>
<tr>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-21.png"><img src="images/gallery/fan-21.png" width="350" alt="Proteus 电路历史截图"></a><br><strong>Proteus 电路历史截图</strong><br>仅为原报告的仿真界面图片；当前仓库未提供可编辑仿真工程，也未在本次重新运行。<br><sub>Word 原报告 · image21.png</sub></td>
<td width="50%" align="center" valign="top"><a href="images/gallery/fan-22.png"><img src="images/gallery/fan-22.png" width="350" alt="Keil 主函数与历史构建输出"></a><br><strong>Keil 主函数与历史构建输出</strong><br>原截图显示 0 errors、14 warnings；它不是本次图片更新重新构建得到的结果。<br><sub>Word 原报告 · image22.png</sub></td>
</tr>
</table>

## 阅读与验证边界

点击图片可查看完整大小。原文档未整体上传，标题页、姓名、学号、指导教师信息与文档元数据未纳入图集。结构图依据公开源码和现有资料绘制，表示功能关系，不能替代电气设计与实物验收。
