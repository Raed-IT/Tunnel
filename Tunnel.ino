#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display


#define senor_infrarade 2
#define sensor_manual_door 8
#define manual_lock_door_control  6
#define auto_door_control  7
#define pump 3
int timeSterilization = 20000;
void setup() {
  Serial.begin (9600);
  pinMode (senor_infrarade , INPUT);
  pinMode (auto_door_control , OUTPUT);
  pinMode (manual_lock_door_control , OUTPUT);
  pinMode (pump , OUTPUT);
  pinOn(auto_door_control);
  pinOff(manual_lock_door_control);
  pinOff(pump);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print ("Wating ...");
  delay(2000);
  lcd.clear ();
  lcd.setCursor(3, 0);
  lcd.print ("Redy ...");
  delay(2000);
  pinOn(auto_door_control);
  delay(500);
  lcd.clear ();
  lcd.clear ();
  lcd.setCursor(2, 0);
  lcd.print ("redy for new");
  lcd.setCursor(1, 1);
  lcd.print ("sterilization");

}

void loop() {

  if (readSensor()) {
    if (digitalRead(sensor_manual_door)) {
      //      close namual dore
      pinOn(manual_lock_door_control);
      pinOn(pump);
      lcd.clear ();
      lcd.setCursor(0, 0);
      lcd.print ("sterilization ...");
      for (int i = 1000; i <= timeSterilization ; i = i + 1000) {
        delay(1000);
        lcd.setCursor(6, 1);
        lcd.print (String((timeSterilization - i)/1000));
        lcd.print ("  ");
      }
      lcd.clear ();
      lcd.setCursor(3, 0);
      lcd.print ("DONE ...");
      pinOff(pump);
      pinOff(manual_lock_door_control);
      pinOff(auto_door_control);
      delay (5000);
      pinOn(auto_door_control);
      lcd.clear ();
      lcd.setCursor(2, 0);
      lcd.print ("redy for new");
      lcd.setCursor(1, 1);
      lcd.print ("sterilization");
    } else {
      sound ();
    }
  }
}
void sound () {
}

//the function below  return value for read sensor
bool  readSensor () {
  return !digitalRead (senor_infrarade);
}
bool  readPin (int pinNimber) {
  return digitalRead (pinNimber);
}

void pinOn (int pinNumber ) {
  digitalWrite(pinNumber, LOW);
}
void pinOff (int pinNumber ) {
  digitalWrite(pinNumber, HIGH);
}
