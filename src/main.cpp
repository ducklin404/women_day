#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "structs/particle.h"
#include "utils/random.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define LOADING_WIDTH 58
#define LOADING_HEIGHT 16
#define INNER_LOADING_OFFSET 3
#define MAX_PARTICLES 80

const int LEFT_CANNON_X  = 0;
const int RIGHT_CANNON_X = SCREEN_WIDTH - 1;
const int CANNON_Y   = SCREEN_HEIGHT;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Particle particles[MAX_PARTICLES];

void tearEverythingDown(int text_x, int text_y, String text){
  for (int y = 0; y< SCREEN_HEIGHT; ++y){
    display.fillRect(0, y, SCREEN_WIDTH, 1, BLACK);
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
    display.print("Loading...");
    display.setCursor(*x, *y);
    display.print(*final_text);
    display.display();
  }
}

void spawnParticleFromLeft() {
  for (int i = 0; i < MAX_PARTICLES; ++i) {
    if (!particles[i].active) {
      particles[i].active = true;
      particles[i].x = LEFT_CANNON_X + 2; 
      particles[i].y = CANNON_Y;
      particles[i].vx = randRangeF(0.7f, 2.4f);  
      particles[i].vy = randRangeF(-5.2f, -0.2f);  
      particles[i].life = randRangeInt(24, 60);
      particles[i].size = randRangeInt(1, 3);
      particles[i].shape = randRangeInt(0, 3);
      break;
    }
  }
}

void spawnParticleFromRight() {
  for (int i = 0; i < MAX_PARTICLES; ++i) {
    if (!particles[i].active) {
      particles[i].active = true;
      particles[i].x = RIGHT_CANNON_X - 2;
      particles[i].y = CANNON_Y;
      particles[i].vx = randRangeF(-2.4f, -0.7f);  
      particles[i].vy = randRangeF(-5.2f, -0.2f); 
      particles[i].life = randRangeInt(24, 60);
      particles[i].size = randRangeInt(1, 3);
      particles[i].shape = randRangeInt(0, 3);
      break;
    }
  }
}


void playConfetti(unsigned long duration_ms, int text_x, int text_y, String text) {
  unsigned long start = millis();
  unsigned long lastSpawn = 0;
  const unsigned long spawnInterval = 60; 
  const float gravity = 0.12f;            

  // ensure particle pool is clear
  for (int i = 0; i < MAX_PARTICLES; ++i) particles[i].active = false;

  while (millis() - start < duration_ms) {
    unsigned long now = millis();

    // spawn a small burst from both sides occasionally
    if (now - lastSpawn >= spawnInterval) {
      lastSpawn = now;
      // spawn each side
      int leftBurst = randRangeInt(2, 6);
      int rightBurst = randRangeInt(2, 6);
      for (int i = 0; i < leftBurst; ++i) spawnParticleFromLeft();
      for (int i = 0; i < rightBurst; ++i) spawnParticleFromRight();
    }

    // Update particles physics
    for (int i = 0; i < MAX_PARTICLES; ++i) {
      if (!particles[i].active) continue;
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      particles[i].vy += gravity; // gravity pulls down
      // slight air resistance to horizontal speed
      particles[i].vx *= 0.995f;

      // decrease life, and deactivate if out of screen or life finished
      if (particles[i].life > 0) particles[i].life--;
      if (particles[i].life == 0 ||
          particles[i].y > SCREEN_HEIGHT + 4 ||
          particles[i].x < -6 ||
          particles[i].x > SCREEN_WIDTH + 6) {
        particles[i].active = false;
      }
    }

    // Draw frame
    display.clearDisplay();
    display.setCursor(text_x, text_y);
    display.print(text);
    for (int i = 0; i < MAX_PARTICLES; ++i) {
      if (!particles[i].active) continue;
      int px = int(particles[i].x + 0.5f);
      int py = int(particles[i].y + 0.5f);

      // different tiny paper styles: pixel, tiny line, small rect, diagonal
      switch (particles[i].shape) {
        case 0:
          // single pixel / dot
          display.drawPixel(px, py, WHITE);
          break;
        case 1:
          // horizontal tiny dash
          display.drawFastHLine(px - 1, py, particles[i].size + 1, WHITE);
          break;
        case 2:
          // vertical tiny dash
          display.drawFastVLine(px, py - 1, particles[i].size + 1, WHITE);
          break;
        default:
          // small square
          display.fillRect(px - (particles[i].size / 2), py - (particles[i].size / 2),
                           particles[i].size, particles[i].size, WHITE);
          break;
      }
    }

    display.display();
    delay(16); 
  }

  delay(150);
  display.clearDisplay();
  
  display.display();
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
  playConfetti(5000UL, x, y, last_text);

}



void loop(){
  
}