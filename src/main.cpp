#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define LOADING_WIDTH 58
#define LOADING_HEIGHT 16
#define INNER_LOADING_OFFSET 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void tearEverythingDown(int text_x, int text_y, String text){
  for (int y = 0; y< SCREEN_HEIGHT; ++y){
    for (int x = 0; x< SCREEN_WIDTH; ++x){
      display.drawPixel(x, y, BLACK);
    }
    display.setCursor(text_x, text_y);
    display.print(text);
    display.display();
  }
}

void drawLoading(float percentage, int* x, int*y, String* final_text){
  display.clearDisplay();
  int start_x = SCREEN_WIDTH/2 - LOADING_WIDTH/2;
  int start_y = SCREEN_HEIGHT/2 - LOADING_HEIGHT/2;

  int inner_x = start_x + INNER_LOADING_OFFSET;
  int inner_y = start_y + INNER_LOADING_OFFSET;
  int INNER_WIDTH = LOADING_WIDTH - INNER_LOADING_OFFSET*2;
  int INNER_HEIGHT = LOADING_HEIGHT - INNER_LOADING_OFFSET*2;

  int16_t x1, y1;
  uint16_t w, h;
  uint16_t loading_w, loading_h;
  uint16_t single_w, single_h;

  

  display.getTextBounds("Loading...", 0, 0, &x1, &y1, &loading_w, &loading_h);
  display.getTextBounds("000.00", 0, 0, &x1, &y1, &w, &h);
  display.getTextBounds("0", 0, 0, &x1, &y1, &single_w, &single_h);


  int default_text_x = start_x + LOADING_WIDTH/2 - int(w/2);
  *y = start_y + LOADING_HEIGHT/2 - int(h/2);
  int loading_x = start_x;
  int loading_y = start_y - loading_h - 2;

  int target = int(round(percentage * 100.0));

  for (int i = 0; i <= target; i+= 2) {
    float progress = i / 100.0;              
    display.clearDisplay();
    display.drawRect(start_x, start_y, LOADING_WIDTH, LOADING_HEIGHT, WHITE);
    display.fillRect(inner_x, inner_y, int((progress/100.0) * INNER_WIDTH), INNER_HEIGHT, WHITE);

    
    *final_text = String(progress, 2);
    *x = default_text_x + (6 - (*final_text).length()) * (single_w/2); 
    display.setCursor(loading_x, loading_y);
    display.drawPixel(0,0, WHITE);
    display.print("Loading...");
    display.setCursor(*x, *y);
    display.print(*final_text);
    display.display();
  }

  

}


void setup(){
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("SSD1306 allocation failed");
  }

  //set up for text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setFont();

  display.clearDisplay();

  int x, y;
  String last_text;
  drawLoading(20.10, &x, &y, &last_text);
  delay(2000);
  tearEverythingDown(x, y, last_text);


}



void loop(){
  
}