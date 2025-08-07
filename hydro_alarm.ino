#define LIGHT_PIN PB0  // Define the pin number for the LED
#define BUTTON_PIN PB4 

// Define states as simple integer constants
#define OFF 0
#define BLINKING 1
#define ON 2

class FSM {
  public:

  FSM(int initial_state, int button_pin) {

    this->state = initial_state;
    this->button_pin = button_pin;

  }
  
  int get_state() {
    return this->state;
  }
  
  void set_state(int new_state) {
    this->state = new_state;
  }

  void update(){

    this->button_val = digitalRead(this->button_pin);


    if(this->button_val){

      switch(this->state){

        case OFF:

          set_state(BLINKING);

        case BLINKING:

          set_state(ON);

        case ON:

          set_state(OFF);

      }

    }


    handle_outputs();


  }


  void handle_outputs(){

    switch(this->state) {

    case OFF:
      
      handle_off();

      break;
      
    case BLINKING:
      
      handle_blinking();

      break;
      
    case ON:
      
      handle_on();

      break;

    }

  }

  void handle_off(){

    digitalWrite(LIGHT_PIN, LOW);

  }

  void handle_blinking(){

    digitalWrite(LIGHT_PIN, HIGH);
    delay(1000);
    digitalWrite(LIGHT_PIN, LOW);
    delay(1000);

  }

  void handle_on(){

    digitalWrite(LIGHT_PIN, HIGH);

  }
  
  private:

  int state;
  int button_pin;
  int button_val;



};

FSM fsm(OFF, BUTTON_PIN);

void setup() {

  // put your setup code here, to run once:
  pinMode(LIGHT_PIN, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  fsm.update();
  
  delay(100);  // Small delay for stability

}