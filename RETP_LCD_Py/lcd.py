#-*- coding: utf-8 -*-
import RPi.GPIO as GPIO
import time

# 接线，各行的注释表示LCD上对应的PIN脚编号
# 注意树莓派的PIN脚编号是BCM模式的，例如17，即为GPIO17，对应树莓派3B+的11号PIN（可在树莓派上输入pinout命令查看PIN位置）
LCD_RS = 17   # -> 4 LCD  H: data L: cmd
LCD_RST = 27  # -> 17 LCD L->H 重置
LCD_PSB = 22   # -> 15 LCD H：并行 L: 串行
LCD_E = 18  # -> 6 LCD H：使能 
LCD_RW = 23   # -> 5 LCD 并行读写信号 / 串行数据
DATA_PINS = [26, 19, 13, 6, 5, 25, 21, 20] # D0-D7
DATA_PINS.reverse() # 反向，便于后面传数据

# 如果你不需要LCD背光，可不连接
POWER_PWM_PIN = 12 # 背光控制 
PWM_DC = 10 # default PWM duty cycle. 调整此数值可更改背光强度
PWM_FREQ = 100 # default PWM frequency

class HomeScreen(object):
    def __init__(self):
        # 初始化IO
        self.io_init()

        # 初始化PWM背光控制
        p = GPIO.PWM(POWER_PWM_PIN, PWM_FREQ)
        self.backlight_pwm = p
        p.start(0) # 默认关闭背光

    def reset(self):
        GPIO.output(LCD_PSB, True)
        GPIO.output(LCD_RST, False)
        self.delay()
        GPIO.output(LCD_RST, True)
        self.delay()
        
    def backlight_toggle(self, dc):
        self.backlight_pwm.ChangeDutyCycle(dc)
                
    def io_init(self):
        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)
        GPIO.setup(LCD_RS, GPIO.OUT)
        GPIO.setup(LCD_RST, GPIO.OUT)
        GPIO.setup(LCD_PSB, GPIO.OUT)
        GPIO.setup(LCD_E, GPIO.OUT)
        GPIO.setup(LCD_RW, GPIO.OUT)
        GPIO.setup(POWER_PWM_PIN, GPIO.OUT, initial=GPIO.LOW)
        for pin in DATA_PINS:
            GPIO.setup(pin, GPIO.OUT, initial=GPIO.LOW)


    def delay(self):
        time.sleep(0.0002)

    # 写入一个指令或显示数据字节，从高到低位写至D7-D0
    def set_data(self, byt):
        tmp = byt;
        for i in range(0, 8):
            pin = DATA_PINS[i]
            out = tmp & 0x80
            GPIO.output(pin, out)
            tmp = (tmp << 1)

    # 发送指令至LCD
    def write_cmd(self, byt):
        GPIO.output(LCD_E, False)
        self.delay()
        GPIO.output(LCD_RS, False)
        self.delay()
        GPIO.output(LCD_RW, False)
        self.delay()
        GPIO.output(LCD_E, True)
        self.delay()
        self.set_data(byt)
        GPIO.output(LCD_E, False)
        self.delay()

    # 清屏
    def clear_screen(self):
        self.write_cmd(0x01)

    # 写入显示字节
    def write_display(self, byt):
        # 各GPIO的开关顺序须参考技术文档第4页的并口写数据时序图
        GPIO.output(LCD_E, False)
        self.delay()
        GPIO.output(LCD_RS, True)
        self.delay()
        GPIO.output(LCD_RW, False)
        self.delay()
        GPIO.output(LCD_E, True)
        self.delay()
        self.set_data(byt)
        self.delay()
        GPIO.output(LCD_E, False)
        self.delay()

    # 写入一行ASCII字符，传入`pos`位置时，会忽略行号
    def write_line(self, line_number, txt, pos=None):
        x_pos = [0x80, 0x90, 0x88, 0x98] # 1-4行的起始位置，参考技术文档第11页的表格
        pos = x_pos[line_number-1] if pos is None else pos
        # 下面写入指令，可参考技术文档第6页的《用户指令集》
        self.write_cmd(0x30) # 设置DL=1 
        self.write_cmd(0x30) # 使用RE=0，即基本指令集
        self.write_cmd(0x0c) # 显示开，游标关，游标位置关
        self.write_cmd(pos) # 指定显示起始坐标
        if isinstance(txt, int):
            self.write_display(txt)
            return
        for c in (txt):
            self.write_display(ord(c))

screen = HomeScreen()
# 重置显示屏
time.sleep(5)
screen.reset()
# 打开LCD显示
screen.write_line(1, 'Hurray now')
screen.write_line(3, 'the Tomorrow is here')
time.sleep(5)
screen.clear_screen()
screen.write_line(1, 'Children are')
screen.write_line(3, 'the leaders of tomorrow')
time.sleep(5)
# 打开背光
screen.backlight_toggle(PWM_DC)
time.sleep(5)
# 关闭背光
screen.backlight_toggle(0)
screen.reset()
