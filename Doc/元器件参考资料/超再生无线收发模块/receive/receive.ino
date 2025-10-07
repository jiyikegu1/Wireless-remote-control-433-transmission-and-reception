#include <RCSwitch.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RCSwitch mySwitch = RCSwitch();

// 接收统计变量
unsigned long lastReceiveTime = 0;
int receiveCount = 0;
bool isFirstReceive = true;

void setup() {
  Serial.begin(9600);
  
  // 初始化OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED初始化失败"));
    while(1);
  }
  
  // 显示初始界面
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("无线接收器启动中");
  display.println("wait message 666");
  display.display();
  
  // 设置接收引脚
  mySwitch.enableReceive(11);
}

void loop() {
  if (mySwitch.available()) {
    unsigned long value = mySwitch.getReceivedValue();
    
    // 只处理值为666的信号
    if(value == 666) {
      // 更新接收信息
      receiveCount++;
      lastReceiveTime = millis();
      
      // 串口输出
      Serial.print("收到666信号！接收次数：");
      Serial.println(receiveCount);
      
      // OLED显示更新
      display.clearDisplay();
      
      // 显示大号"666"
      display.setTextSize(3);
      display.setCursor(30, 10);
      display.print("666");
      
      // 显示接收信息
      display.setTextSize(1);
      display.setCursor(0, 40);
      display.print("接收次数: ");
      display.println(receiveCount);
      
      // 显示最后接收时间
      display.setCursor(0, 50);
      display.print("最后接收: ");
      display.print(millis()/1000);
      display.print("s");
      
      display.display();
      
      isFirstReceive = false;
    }
    
    mySwitch.resetAvailable();
  }
  
  // 首次启动或无接收时的显示
  if(isFirstReceive || (millis() - lastReceiveTime > 5000)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("waitting message 666");
    
    if(!isFirstReceive) {
      display.setCursor(0, 20);
      display.print("receivecount: ");
      display.print((millis()-lastReceiveTime)/1000);
      display.println("prosec");
      
      display.setCursor(0, 30);
      display.print("sum: ");
      display.print(receiveCount);
      display.println("n");
    }
    
    // 添加信号强度指示动画
    int animPos = (millis()/200)%8;
    for(int i=0; i<animPos; i++) {
      display.fillRect(50+i*10, 50, 5, 10-i, WHITE);
    }
    
    display.display();
  }
}