from machine import Pin, I2C
import utime
import ssd1306
import random
import RTC_DS3231

class Button:
    def __init__(self, pin):
        self.pin = Pin(pin, Pin.IN, Pin.PULL_DOWN)
        self.consecutive_highs = 0
        self.consecutive_lows = 0
        self.last_stable_state = 0
        self.is_button_pressed = False 
        
    def init(self):
        self.pin.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=self._on_pin_change)
    
    def is_pressed(self):
        return self.is_button_pressed
    
    def _on_pin_change(self, pin):  
        current_state = self.pin.value()
        
        if current_state == 0:
            self.consecutive_highs = 0
            self.consecutive_lows += 1
        else:
            self.consecutive_highs += 1
            self.consecutive_lows = 0
            
        if self.consecutive_highs >= 6 and self.last_stable_state == 0:
            self.last_stable_state = 1
            self.is_button_pressed = True
            print("button pressed")
            
        if self.consecutive_lows >= 6 and self.last_stable_state == 1:
            self.last_stable_state = 0
            self.is_button_pressed = False
            print("button let go")        
        
        
    
    


class Time:
    def __init__(self, hours_val, minutes_val):
        self.hours_val = hours_val
        self.minutes_val = minutes_val
        self.seconds_val = 0
        self.str_hours_val = ""
        self.str_minutes_val = ""
        self.str_seconds_val = ""
        
    
    def equals(self, time_obj):
        return (self.hours_val == time_obj.hours_val and 
                self.minutes_val == time_obj.minutes_val)
    
    def update(self):
        
        if not hasattr(self, '_last_timer_val'):
            self._last_timer_val = 0
        
        current_timer_val = utime.ticks_ms()
        
        if utime.ticks_diff(current_timer_val, self._last_timer_val) >= 1000:
            self._last_timer_val = current_timer_val
            
            if self.seconds_val == 59:
                self.seconds_val = 0
                if self.minutes_val == 59:
                    self.minutes_val = 0
                    if self.hours_val == 23:
                        self.hours_val = 0
                    else:
                        self.hours_val += 1
                else:
                    self.minutes_val += 1
            else:
                self.seconds_val += 1
                
            print(self.get_formatted_time())
    

    def update_hours(self, direction):
        if direction == 1:
            if self.hours_val == 23:
                self.hours_val = 0
            else:
                self.hours_val += 1
        elif direction == -1:
            if self.hours_val == 0:
                self.hours_val = 23
            else:
                self.hours_val -= 1
    
    def update_minutes(self, direction):
        if direction == 1:
            if self.minutes_val == 59:
                self.minutes_val = 0
            else:
                self.minutes_val += 1
        elif direction == -1:
            if self.minutes_val == 0:
                self.minutes_val = 59
            else:
                self.minutes_val -= 1
    
    def set_time(self, temp_time, alarm_set_button, increment_time_button, decrement_time_button):
        
        print("Setting time now")
        
        while not alarm_set_button.is_pressed():
            
            print("Set hours val")
            
            if increment_time_button.is_pressed():
                temp_time.update_hours(1)
                utime.sleep_ms(200)  
            
            if decrement_time_button.is_pressed():
                temp_time.update_hours(-1)
                utime.sleep_ms(200)  
            
            utime.sleep_ms(50)  
        
        self.hours_val = temp_time.hours_val
        print(f"Set hours to {temp_time.hours_val}")
        
     
        while not alarm_set_button.is_pressed():
            
            print("Set mins val")

            
            if increment_time_button.is_pressed():
                temp_time.update_minutes(1)
                utime.sleep_ms(200)  
            
            if decrement_time_button.is_pressed():
                temp_time.update_minutes(-1)
                utime.sleep_ms(200)  
            
            utime.sleep_ms(50)  
        
        self.minutes_val = temp_time.minutes_val
        print(f"Set minutes to {temp_time.minutes_val}")
    
    def get_formatted_time(self):
        if self.hours_val < 10:
            self.str_hours_val = "0" + str(self.hours_val)
        else:
            self.str_hours_val = str(self.hours_val)
        
        if self.minutes_val < 10:
            self.str_minutes_val = "0" + str(self.minutes_val)
        else:
            self.str_minutes_val = str(self.minutes_val)
        
        if self.seconds_val < 10:
            self.str_seconds_val = "0" + str(self.seconds_val)
        else:
            self.str_seconds_val = str(self.seconds_val)
        
        return self.str_hours_val + ":" + self.str_minutes_val + ":" + self.str_seconds_val


class WaterPump:
    def __init__(self, pin):
        self.pin = pin
        self._gpio_pin = None
    
    def init(self):
        self._gpio_pin = Pin(self.pin, Pin.OUT)
    
    def turn_on(self):
        self._gpio_pin.on()  
    
    def turn_off(self):
        self._gpio_pin.off() 


class Buzzer:
    def __init__(self, pin):
        self.pin = pin
        self._gpio_pin = None
    
    def init(self):
        self._gpio_pin = Pin(self.pin, Pin.OUT)
    
    def turn_on(self):
        self._gpio_pin.on()
    
    def turn_off(self):
        self._gpio_pin.off()

