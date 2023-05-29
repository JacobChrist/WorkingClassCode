/*
  Working Class Chess Timer with LiquidCrystal Library

  Uses a 16x2 LCD display based on example code at:
  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

  The circuit:
   LCD VSS pin to ground
   LCD VCC pin to 5V
   LCD V0 pin to 3.3K Ohm R to ground (use 10K Ohm pot for more control)
   LCD RS pin to digital pin 12
   LCD R/W pin to ground
   LCD Enable pin to digital pin 11
   LCD D0-D3 pin No Connect
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD A pin to 5V
   LCD K pin to 390 Ohm R to ground

  Pico Pi W Inputs:
   GPIO 6 10k Ohm pull-up to Working Button
   GPIO 7 10k Ohm pull-up to Worker 1 Button
   GPIO 8 10k Ohm pull-up to Worker 2 Button
   GPIO 9 10k Ohm pull-up to Worker 3 Button

  Pico Pi W Outputs:
   GPIO 16 Get to work LED A
   GPIO 17 Okay to talk LED A

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const uint8_t BIN_MAX = 4;
uint8_t bin = -1;
uint8_t bin_last = -1;

uint32_t timer[BIN_MAX];

char bin_name[BIN_MAX][10] = {
  "Working",
  "Jacob",
  "Patrick",
  "Guest"
};

float percent_talking = 0.10;

void setup() {
  // Button Inputs
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  // LED Outputs
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" Working  Class");
  lcd.setCursor(0, 1);
  lcd.print("  Chess  Timer");
  delay(5000);
}

void loop() {
  static uint32_t seconds_last = 0;
  uint32_t seconds = millis() / 1000;
  char line0[100];
  char line1[100];
  static uint8_t line0_position = 0;
  static uint8_t line1_position = 0;
  static uint32_t time_last_bin_changed = 0;
  uint32_t time_delta_since_last_bin_changed = millis() - time_last_bin_changed;
  uint32_t time_s[BIN_MAX];
  uint32_t talking = 0;

  // Detect if the worker bin has changed
  if (digitalRead(6) == LOW) bin = 0;
  if (digitalRead(7) == LOW) bin = 1;
  if (digitalRead(8) == LOW) bin = 2;
  if (digitalRead(9) == LOW) bin = 3;

  // if our bin has changed then reset time_last_bin_changed
  if (bin != bin_last) 
  {
    if(bin_last >= 0)
      timer[bin_last] += time_delta_since_last_bin_changed;
    time_last_bin_changed = millis();
    time_delta_since_last_bin_changed = millis() - time_last_bin_changed;
  }

  // Convert current worker time to seconds
  for (int bin_index = 0; bin_index < BIN_MAX; bin_index++)
  {
    time_s[bin_index] = (timer[bin_index] + (bin == bin_index ? time_delta_since_last_bin_changed : 0)) / 1000;
    if(bin_index > 0)
      talking += time_s[bin_index];
  }
  
  // Calculate if we are spending too much time talking and light the corasponding LED
  if( talking > (percent_talking * time_s[0]) ) {
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
  }
  else
  {
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
  }

  // Display Status on LCD
  sprintf(line0, "Worker#=%d Talking Time=%d Wokring Time=%d ", bin, talking, time_s[0]);
  lcd_scroll(line0, 0, line0_position);
  
  sprintf(line1, "%s:%d %s:%d %s:%d %s:%d ", bin_name[0], time_s[0], 
                                             bin_name[1], time_s[1], 
                                             bin_name[2], time_s[2], 
                                             bin_name[3], time_s[3]);
  lcd_scroll(line1, 1, line1_position);
  delay(500);


  bin_last = bin;
}
