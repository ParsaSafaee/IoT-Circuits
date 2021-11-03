#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
const byte row = 4;
const byte col = 3;
char KeyMap[row][col] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rows[row] = {29, 30, 31, 32};
byte cols[col] = {24, 23, 22};
Keypad customKeypad = Keypad( makeKeymap(KeyMap), rows, cols, row, col); 
const int buzzer = 7;
int num = 0;
int password = 1234;
int correct = 0;
int change_password = 0;
int len = 0;
const int led_red = 20;
const int led_green = 21;
Servo myservo; 
LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

void setup() {
  myservo.attach(0);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
}
void loop() {
  char key = customKeypad.getKey();
  if (correct == 0 && change_password == 0 && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')){
     num = num * 10 + (key - 48);  
     lcd.setCursor(len, 0);
     lcd.print(key);
     len++;
     if(num == password && len == 4){
         correct = 1;
         myservo.write(180);
         digitalWrite(led_green, HIGH);
         len = 0;
         num = 0;
     }
     if(num != password && len == 4){
         digitalWrite(led_red, HIGH);
         tone(buzzer, 500);
         delay(1000);
         digitalWrite(led_red, LOW);
         noTone(buzzer);
         lcd.clear();
         len = 0;
         num = 0;
     }
  }
  if (correct == 1 && change_password == 1 && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')){
     num = num * 10 + (key - 48);  
     lcd.setCursor(len, 1);
     lcd.print(key);
     len++;
     lcd.setCursor(0, 1);
     lcd.print(num);
     if(len == 4){
        password = num;
        myservo.write(180);
        digitalWrite(led_green, HIGH);
        len = 0;
        num = 0;
        change_password = 0;
     }
  }
  if (key == '*' && correct == 1){
    change_password = 1;
  }
  if (key == '#') {
    digitalWrite(led_green, LOW);
    myservo.write(90);
    lcd.clear();
    num = 0;
    correct = 0;
    change_password = 0;
    len = 0;
  }
}
