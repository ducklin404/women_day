#include <Adafruit_GFX.h>


struct Particle {
  float x, y;
  float vx, vy;
  uint8_t life;  
  uint8_t size;   
  uint8_t shape; 
  bool active;
};