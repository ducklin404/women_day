#include <Arduino.h>

int randRangeInt(int a, int b) { return a + (rand() % (b - a + 1)); }
float randRangeF(float a, float b) { return a + (float(rand()) / RAND_MAX) * (b - a); }