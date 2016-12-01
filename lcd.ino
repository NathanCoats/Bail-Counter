// include the library code:
#include <LiquidCrystal.h>
#include <Keypad.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte row_pins[ROWS] = {9, 10, 11, 12};
byte col_pins[COLS] = {A0, A1, A2, A3};

int input_pin = 2;

Keypad keypad = Keypad( makeKeymap(keys), row_pins, col_pins, ROWS, COLS );

bool has_changed;
bool logged_in;

int stat;
int in_process;
int bail_count;

String input = "";
String password = "1234";

void setup() {
    pinMode(input_pin, INPUT);
    logged_in = false;
    has_changed = false;
    stat = 0;
    in_process = 0;
    bail_count = 0;
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Pin:"); 
    lcd.setCursor(0,1);
     
    input = "";
}

void loop() {

  if(logged_in) {
    char key = keypad.getKey();

    if (key != NO_KEY) {
        input += key;
        if(input == password) {
         setup();
        }
    }

    stat = digitalRead(input_pin);
    
    if(stat == in_process) {
        has_changed = false;
    }
    else {
        has_changed = true;
        in_process  = stat;
    }

    if(has_changed && stat > 0) {
    bail_count++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bail Count:");
    lcd.setCursor(0,1);
    lcd.print(bail_count);
    }
    
  }
  else {

    char key = keypad.getKey();

    if (key != NO_KEY) {
      if( key != '#' ) {
        input += key;
        lcd.setCursor(0,1);
        lcd.print(input);
      }
      else {
        if( input == password ) {
          logged_in = true;
          bail_count = 0;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Bail Count:");
          lcd.setCursor(0,1);
          lcd.print(bail_count);
          input = "";
        }
        else {
          input = "";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter Pin:"); 
        
        }
      }
      
    }
      
  }
}

//void updateBails(int amount) {
//    bail_count += amount;
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("Bail Count:");
//    lcd.setCursor(0,1);
//    lcd.print(bail_count);
//}


