from machine import Pin, I2C
from classes import Button, Time, WaterPump, Buzzer


ALARM_SET_BUTTON_PIN = 2
CURRENT_TIME_SET_BUTTON_PIN = 7
ALARM_OFF_BUTTON_PIN = 4      
INCREMENT_TIME_BUTTON_PIN = 5   
DECREMENT_TIME_BUTTON_PIN = 6   
WATER_PUMP_PIN = 3          
BUZZER_PIN = 1              

INITIAL_HOURS_VAL = 23
INITIAL_MINS_VAL = 59

alarm_off_button = Button(ALARM_OFF_BUTTON_PIN)
alarm_set_button = Button(ALARM_SET_BUTTON_PIN)
current_time_set_button = Button(CURRENT_TIME_SET_BUTTON_PIN)
increment_time_button = Button(INCREMENT_TIME_BUTTON_PIN)
decrement_time_button = Button(DECREMENT_TIME_BUTTON_PIN)
current_time = Time(INITIAL_HOURS_VAL, INITIAL_MINS_VAL)

if INITIAL_MINS_VAL == 59:
    alarm_time = Time(INITIAL_HOURS_VAL, INITIAL_MINS_VAL - 1)
else:
    alarm_time = Time(INITIAL_HOURS_VAL, INITIAL_MINS_VAL + 1)

temp_time = Time(INITIAL_HOURS_VAL, INITIAL_MINS_VAL)
water_pump = WaterPump(WATER_PUMP_PIN)
buzzer = Buzzer(BUZZER_PIN)



def setup():
        
    alarm_off_button.init()
    alarm_set_button.init()
    current_time_set_button.init()
    increment_time_button.init()
    decrement_time_button.init()
    water_pump.init()
    buzzer.init()
    
    print("All components initialized successfully")



def main():
    
    
    if current_time.equals(alarm_time):
        print("Turning on buzzer and water pump")
        buzzer.turn_on()
        water_pump.turn_on()
    else:
        buzzer.turn_off()
        water_pump.turn_off()
    
    if alarm_off_button.is_pressed():
        buzzer.turn_off()
        water_pump.turn_off()
    
    if current_time_set_button.is_pressed():
        current_time.set_time(temp_time, alarm_set_button, increment_time_button, decrement_time_button)
        
    if alarm_set_button.is_pressed():
        alarm_time.set_time(temp_time, alarm_set_button, increment_time_button, decrement_time_button)
        
    
    current_time.update()
    
    


try:
    setup()
    while True:
        main()
except KeyboardInterrupt:
    print("\nProgram stopped by user")
    buzzer.turn_off()
    water_pump.turn_off()
  
if __name__ == "__main__":
    main()