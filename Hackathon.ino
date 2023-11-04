//Buzzer
  #include "pitches.h"
  // notes in the melody:
  int melody[] = {
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_B0};
  int duration = 2500;  // 2500 miliseconds
//LCD
  #include <LiquidCrystal.h>
  const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Keypad
  #include <Keypad.h>

  const byte ROWS = 4; //four rows
  const byte COLS = 4; //four columns
  //define the cymbols on the buttons of the keypads
  char hexaKeys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  byte rowPins[ROWS] = {22, 24, 26, 28}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {30, 32, 34, 36}; //connect to the column pinouts of the keypad

  //initialize an instance of class NewKeypad
  Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char KeyPresses[16];
void setup() {
  // put your setup code here, to run once:
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("PSU Founded Year");

  Serial.begin(9600);

  for(int i=0;i<16;i++){
    KeyPresses[i]=NULL;
  }

}
void win() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(2, melody[thisNote], duration);
     
    // Output the voice after several minutes
    delay(2700);
  }
  while (true){
    const int ledPinBlue = 4;
    const int ledPinWhite = 5;
    int ledState = HIGH;
    int ledState2 = HIGH;
    unsigned long previousMillis = 0;
    const long interval = 1000;
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    /*if (ledState == LOW) {
      ledState = HIGH;
      ledState2 = LOW;
    } else {
      ledState = LOW;
      ledState2 = HIGH;
    }*/

    // set the LED with the ledState of the variable:
    digitalWrite(ledPinBlue, ledState);
    digitalWrite(ledPinWhite, ledState2);

  }
  }

   
}
int p=0;
void loop() {
  // put your main code here, to run repeatedly:
    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);

  char customKey = customKeypad.getKey();
  
  char Answer[4] = {'1','8','5','5'};
  if (customKey){
    Serial.println(customKey);
    if(customKey == '*'||p>=16){
      for(int i = 0; i<p; i++){
        lcd.setCursor(i, 1);
        lcd.print(' ');
        
      }
      lcd.setCursor(0, 1);
      p = 0;
      for(int i=0;i<16;i++){
        KeyPresses[i]=NULL;
      }
    }
    else if (customKey == '#'){
      Serial.print(KeyPresses[0]);
      Serial.print(Answer[0]);
        if((KeyPresses[0] == Answer[0]) && (KeyPresses[1] == Answer[1]) && (KeyPresses[2] == Answer[2]) && (KeyPresses[3] == Answer[3])&&(KeyPresses[4]==NULL)){
           for(int i = 0; i<16; i++){
            lcd.setCursor(i, 1);
            lcd.print(' ');
            lcd.setCursor(i, 0);
            lcd.print(' ');
          }
          lcd.setCursor(0, 0);
          lcd.print("You Win");
          win();
          
        }
        else {
          for(int i = 0; i<16; i++){
            lcd.setCursor(i, 1);
            lcd.print(' ');
            lcd.setCursor(i, 0);
            lcd.print(' ');
          }
          lcd.setCursor(0, 0);
          lcd.print("Wrong Answer");
          for(int i=0;i<16;i++){
            KeyPresses[i]=NULL;
            }
          delay(1500);
          for(int i = 0; i<16; i++){
            lcd.setCursor(i, 1);
            lcd.print(' ');
            lcd.setCursor(i, 0);
            lcd.print(' ');
          }
          lcd.setCursor(0, 0);
          lcd.print("PSU Founded Year");
          p=0;
        }

    }
    else{
      lcd.setCursor(p,1);
      KeyPresses[p]= customKey;
      lcd.print(KeyPresses[p]);
      
      Serial.println(KeyPresses);
      p+=1;
    }
  }
  
}
