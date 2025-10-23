#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void drawLine(){
  display.clearDisplay();
  for (int i = 0x0; i < SCREEN_WIDTH; i += 2){
    display.drawPixel(i, SCREEN_HEIGHT/2, WHITE);
    display.display();
  }
}

void setup(){
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("SSD1306 allocation failed");
  }

  display.clearDisplay();
  display.drawPixel(127, 63, WHITE);
  display.display();

  drawLine();

}



void loop(){
  
}