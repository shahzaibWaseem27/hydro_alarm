

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



#include "classes.h"


#define ALARM_SET_BUTTON_PIN PB2
#define ALARM_OFF_BUTTON_PIN PB4
#define INCREMENT_TIME_BUTTON_PIN PB5
#define DECREMENT_TIME_BUTTON_PIN PB6
#define WATER_PUMP_PIN PB3
#define BUZZER_PIN PB1

#define INITIAL_HOURS_VAL 12
#define INITIAL_MINS_VAL 30

Button alarm_off_button(ALARM_SET_BUTTON_PIN);
Button alarm_set_button(ALARM_OFF_BUTTON_PIN);
Button increment_time_button(INCREMENT_TIME_BUTTON_PIN);
Button decrement_time_button(DECREMENT_TIME_BUTTON_PIN);
Time current_time(INITIAL_HOURS_VAL, INITIAL_MINS_VAL, &oled);
Time alarm_time(INITIAL_HOURS_VAL, INITIAL_MINS_VAL-1, &oled);
Time temp_time(INITIAL_HOURS_VAL, INITIAL_MINS_VAL, &oled);
WaterPump water_pump(WATER_PUMP_PIN);
Buzzer buzzer(BUZZER_PIN);



void setup(){

  Serial.begin(9600);  

  alarm_off_button.init();
  water_pump.init();
  buzzer.init();
  current_time.init();


}


void loop(){

  Serial.print(current_time.get_formatted_time());

  // current_time.show(current_time.get_formatted_time(), 0, 10);

  if(current_time.equals(alarm_time)){

    buzzer.turn_on();
    water_pump.turn_on();

  } else {

    buzzer.turn_off();
    water_pump.turn_off();

  }

  if(alarm_off_button.is_pressed()){

    buzzer.turn_off();
    water_pump.turn_off();

  }

  if(alarm_set_button.is_pressed()){

    alarm_time.set_time(temp_time, alarm_set_button, increment_time_button, decrement_time_button);

  }

  
  current_time.update();


}
