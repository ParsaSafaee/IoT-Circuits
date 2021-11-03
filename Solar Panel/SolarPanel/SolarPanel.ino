#include <Servo.h>
#include <LiquidCrystal.h>

const int led = 13;
const int morning = A0;
const int afternoon = A1;
const int night = A2;
Servo myservo;
LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

void setup() {
  myservo.attach(0);
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);
  pinMode(morning, INPUT);
  pinMode(afternoon, INPUT);
  pinMode(night, INPUT);
}

void loop() {
  int morning_status = analogRead(morning);
  int afternoon_status = analogRead(afternoon);
  int night_status = analogRead(night);

  if (morning_status >= afternoon_status && morning_status >= night_status) {
    myservo.write(0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Morning");
    
  }
  else if (afternoon_status >= morning_status && afternoon_status >= night_status){
    myservo.write(90);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Afternoon");
    
  }
  else if (night_status >= afternoon_status && night_status >= morning_status){
    myservo.write(180);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Night");
  }
  delay(500);
}
