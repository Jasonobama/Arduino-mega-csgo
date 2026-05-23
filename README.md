# Arduino-Mega-CSGOC4

#### 介绍
基于 Arduino Mega 的 CS:GO C4 炸弹拆弹模拟器道具项目。通过 4x4 矩阵键盘输入密码（默认为 CS:GO 经典拆弹码 `7355608`），I2C LCD 屏幕显示交互提示，继电器提供按键反馈与拆弹成功触发信号。支持在设备上直接修改密码。

B站账号：DixieBoy

#### 功能特性
- 4x4 矩阵键盘输入，每次按键触发继电器1发出咔嗒反馈
- I2C LCD 1602 屏幕显示交互信息（输入提示、成功/失败、密码修改）
- 密码正确时触发继电器2（可外接电磁锁、LED、蜂鸣器等）并自动复位
- 按下 `D` 键进入密码修改模式，可设置 5 位新密码
- 按下 `*` 键验证密码，按下 `#` 键清空当前输入
- 串口（9600 波特率）同步输出调试信息

#### 硬件清单

| 元件 | 规格 | 说明 |
|---|---|---|
| Arduino Mega 2560 | ATmega2560 | 主控板 |
| 4x4 矩阵键盘 | 16键薄膜/机械键盘 | 自定义键位布局 |
| I2C LCD 1602 | 16列x2行，带I2C转接板 | I2C 地址 `0x27` |
| 2路继电器模块 | 5V 继电器 | 继电器1=按键反馈, 继电器2=拆弹触发 |
| 杜邦线 | 公母/母母若干 | 连接各模块 |

#### 引脚接线

| 外设 | 引脚 |
|---|---|
| 键盘行引脚 R1-R4 | 9, 8, 7, 6 |
| 键盘列引脚 C1-C4 | 5, 4, 3, 2 |
| I2C LCD SDA | 20 (Mega SDA) |
| I2C LCD SCL | 21 (Mega SCL) |
| 继电器1（按键反馈） | 11 |
| 继电器2（拆弹触发） | 13 |

#### 键盘布局

```
D   #   0   *
C   9   8   7
B   6   5   4
A   3   2   1
```

#### 软件架构
- **平台**: Arduino Mega AVR
- **依赖库**:
  - `Password.h` (已包含在项目中) — 密码管理
  - `Keypad.h` — 矩阵键盘驱动（需在 Arduino IDE 库管理器中安装）
  - `LiquidCrystal_I2C.h` — I2C LCD 驱动（需在 Arduino IDE 库管理器中安装）
  - `Wire.h` — I2C 通信（Arduino 内置）
- **主程序**: `C¥.ino`

#### 安装教程

1. 在 Arduino IDE 库管理器中安装 `Keypad` 和 `LiquidCrystal_I2C` 库
2. 将整个项目文件夹放入 Arduino  sketches 目录
3. 用 Arduino IDE 打开 `C¥.ino`
4. 选择开发板为 `Arduino Mega or Mega 2560`
5. 选择正确端口，点击上传
6. 上传完成后 LCD 显示 `Enter Password:`，即可使用

#### 使用说明

| 操作 | 按键 | 说明 |
|---|---|---|
| 输入密码 | `0-9`, `A-C` | 逐位输入密码字符 |
| 验证密码 | `*` | 密码正确→继电器2触发→系统复位；错误→显示提示后复位 |
| 清空输入 | `#` | 清空当前输入的密码，重新开始 |
| 修改密码 | `D` | 进入修改模式，输入5位新密码后自动保存并显示 |

#### 项目结构

```
arduino-mega-csgo/
├── C¥.ino                  # 主程序
├── README.md               # 项目说明
└── Password/               # Password 密码管理库
    ├── Password.h
    ├── Password.cpp
    ├── keywords.txt
    └── Examples/
        ├── PasswordKeypad/     # 键盘密码示例
        ├── SerialMonitor/      # 串口密码示例
        └── HelloPassword/      # Password 库基础用法
```
