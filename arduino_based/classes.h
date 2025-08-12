

class Button {


  private:

  uint8_t pin;

  public:

  Button(uint8_t pin){
    
    this->pin = pin;
  
  }

  void init(){

    pinMode(pin, INPUT_PULLUP);

  }

  bool is_pressed(){

    return !digitalRead(this->pin);

  }


};


class Time {

  private:

  uint8_t hours_val;
  uint8_t minutes_val;
  uint8_t seconds_val = 0;
  String str_hours_val;
  String str_minutes_val;
  String str_seconds_val;
  Adafruit_SSD1306 *oled;

  public:

  Time(uint8_t hours_val, uint8_t minutes_val, Adafruit_SSD1306 *oled){

    this->hours_val = hours_val;
    this->minutes_val = minutes_val;
    this->*oled = oled;

  }

  void init(){

    if(!this->oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }

    delay(2000);

    this->oled.setTextSize(1);
    this->oled.setTextColor(WHITE);

  }

  bool equals(Time time_obj){

    return this->hours_val == time_obj.hours_val && this->minutes_val == time_obj.minutes_val;

  }

  void update(){

    static unsigned long last_timer_val = 0;

    unsigned long current_timer_val = millis();

    if(current_timer_val - last_timer_val >= 1000){

      last_timer_val = current_timer_val;



      if(this->seconds_val == 59){

      this->seconds_val = 0;

      if(this->minutes_val == 59){

        this->minutes_val = 0;

        if(this->hours_val == 23){

          this->hours_val = 0;

        } else {

          this->hours_val = this->hours_val + 1;

        }

      } else {

        this->minutes_val = this->minutes_val + 1;

      }

      } else {

          this->seconds_val = this->seconds_val + 1;

      }


    }

  }

  void show(String text, uint8_t row, uint8_t col){

    this->oled.setCursor(row, col);
    this->oled.println(text);
    this->oled.display(); 

  }

  void update_hours(uint8_t direction){


    switch(direction){

      case 1:

        if(this->hours_val == 23){

        this->hours_val = 0;

        } else {

          this->hours_val = this->hours_val + 1;

        }

        break;


      case -1:

        if(this->hours_val == 0){

        this->hours_val = 23;

        } else {

          this->hours_val = this->hours_val - 1;

        }

        break;


    }

  }

  void update_minutes(uint8_t direction){

    switch(direction){

      case 1:

        if(this->minutes_val == 59){

        this->minutes_val = 0;

        } else {

          this->minutes_val = this->minutes_val + 1;

        }

        break;


      case -1:

        if(this->minutes_val == 0){

        this->minutes_val = 59;

        } else {

          this->minutes_val = this->minutes_val - 1;

        }

        break;


    } 

  }



  void set_time(Time temp_time, Button alarm_set_button, Button increment_time_button, Button decrement_time_button){


    while(!alarm_set_button.is_pressed()){

      this->show("Setting time: hours", 0, 10);
      this->show(temp_time.str_hours_val, 5, 10);
      this->oled.clearDisplay();

      if(increment_time_button.is_pressed()){

        temp_time.update_hours(1);

      }

      if(decrement_time_button.is_pressed()){

        temp_time.update_hours(-1);

      }


    }


    this->hours_val = temp_time.hours_val;


    while(!alarm_set_button.is_pressed()){

      this->show("Setting time: mins", 0, 10);
      this->show(temp_time.str_minutes_val, 5, 10);
      this->oled.clearDisplay();

      if(increment_time_button.is_pressed()){

        temp_time.update_minutes(1);

      }

      if(decrement_time_button.is_pressed()){

        temp_time.update_minutes(-1);

      }


    }


    

  }


  String get_formatted_time(){

    if(this->hours_val < 10){

      this->str_hours_val = "0" + String(this->hours_val);

    } else {

      this->str_hours_val = String(this->hours_val);

    }

    if(this->minutes_val < 10){

      this->str_minutes_val = "0" + String(this->minutes_val);

    } else {

      this->str_minutes_val = String(this->minutes_val);

    }

    if(this->seconds_val < 10){

      this->str_seconds_val = "0" + String(this->seconds_val);

    } else {

      this->str_seconds_val = String(this->seconds_val);

    }

    return this->str_hours_val + ":" + this->str_minutes_val + ":" + this->str_seconds_val;

  }

};


class WaterPump {

  private:

  uint8_t pin;


  public:

  WaterPump(uint8_t pin){

    this->pin = pin;

  }

  void init(){

    pinMode(pin, OUTPUT);

  }

  void turn_on(){

    digitalWrite(pin, HIGH);

  }

  void turn_off(){

    digitalWrite(pin, LOW);

  }

};



class Buzzer {

  private:

  uint8_t pin;


  public:

  Buzzer(uint8_t pin){

    this->pin = pin;

  }

  void init(){

    pinMode(pin, OUTPUT);

  }

  void turn_on(){

    digitalWrite(pin, HIGH);

  }

  void turn_off(){

    digitalWrite(pin, LOW);

  }

};