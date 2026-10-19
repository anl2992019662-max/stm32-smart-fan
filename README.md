# 基于 STM32 的智能风扇系统

基于 STM32F103C8T6 的嵌入式课程项目，通过 DHT11、旋转编码器、独立按键、OLED 和 TB6612FNG 驱动直流风扇，实现定时、手动和自动调速。保留 Keil MDK 与 STM32CubeIDE 两套原始工程。

## 功能

| 模式 | 代码实现的行为 |
| --- | --- |
| 定时模式 | 设置时、分、秒及速度控制值，倒计时结束后停止电机 |
| 手动模式 | 通过旋转编码器调节 0～100 的速度控制值；按编码器按钮切换调节锁定状态 |
| 自动模式 | 选择温度或湿度控制，按 DHT11 读数计算速度控制值，并可启用 PA8 检测信号门控 |
| 显示与操作 | OLED 中文菜单、两个独立按键和旋转编码器 |

界面中的“转速”和变量 `Speed` 表示 PWM 控制值。工程没有提供实际 RPM 测量或闭环转速反馈。

## 目录

```text
.
├── README.md
├── .gitignore
├── THIRD_PARTY_NOTICES.md
├── docs/
│   ├── HARDWARE.md
│   └── VERSION_NOTES.md
└── 代码/
    ├── Smart_Fan v2.3.hex
    └── Code/
        ├── Keil5 MDK/Smart_Fan v2.3/
        │   ├── Core/
        │   ├── Drivers/
        │   ├── MDK-ARM/
        │   └── Smart_Fan v2.3.ioc
        └── STM32CubeIDE/Smart_Fan v2.3/
            ├── Core/
            ├── Drivers/
            └── Smart_Fan v2.3.ioc
```

接线和器件说明见 [硬件说明](docs/HARDWARE.md)，工程差异和验证状态见 [版本说明](docs/VERSION_NOTES.md)。

## 打开与编译

### Keil MDK

1. 在 Keil 中打开 `代码/Code/Keil5 MDK/Smart_Fan v2.3/MDK-ARM/Smart_Fan v2.3.uvprojx`。
2. 工程记录的编译器为 **Arm Compiler 5.06 update 7 build 960**，器件包为 **Keil.STM32F1xx_DFP 2.2.0**。准备相应工具；使用其他版本时需自行验证兼容性。
3. 选择工程目标并执行 Build。HAL 和 CMSIS 文件已随工程保留。
4. 根据所用下载器重新设置本机调试参数，检查硬件连线后再下载。

### STM32CubeIDE

1. 通过 `File > Import > General > Existing Projects into Workspace` 选择 `代码/Code/STM32CubeIDE/Smart_Fan v2.3`。
2. 执行 Build Project，按实际开发板和下载器重新设置 Debug 配置。
3. Keil 工程的 `.ioc` 记录 STM32CubeMX **6.13.0**，CubeIDE 工程记录 **6.12.0**；两者的 STM32Cube F1 均为 **V1.8.6**。这些记录不代表所有 IDE 版本均已测试。

导入已有工程即可开始检查源码。重新生成 CubeMX 代码前应另存副本，避免覆盖已有修改。

## 操作

1. 使用 PB0 按键移动菜单指针，PB10 按键确认或返回。
2. 定时模式下，旋转编码器修改当前选中的时间或速度值，选择“确定”启动倒计时。
3. 手动模式初始控制值为 50；按编码器按钮解锁后转动旋钮调速。
4. 自动模式选择温度或湿度控制；原菜单中的“人体感应”开关实际控制 PA8 输入门控。模块型号和信号极性需按 [版本说明](docs/VERSION_NOTES.md) 核对。

## 固件与验证状态

`代码/Smart_Fan v2.3.hex` 是随原始目录提供的预编译固件。本次未重新编译，无法确认它对应哪套源码，也未进行烧录、实物或仿真运行验证。

该固件的 SHA-256：

```text
fc0ad6e0e14c9a9db5056a2a660f02f320f09fffddc0437b392764ac0a9c8a15
```

原始目录中的图纸为 PDF 导出件，没有提供可编辑的仿真工程。含个人信息的课程文档、图纸原件、原始表格和第三方论文全文未收入本仓库，器件及接线内容已整理为文字说明。

## 版权与许可

STMicroelectronics、ARM CMSIS 及江协科技等第三方代码保留原始署名和随附许可说明，详见 [第三方声明](THIRD_PARTY_NOTICES.md)。本仓库尚未为应用代码指定统一开源许可证。
