const int buzzer = 9;
const int led = 10;
const int ldr = A0;
int buzzed = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
}

void loop() {
  int ldr_status = analogRead(ldr);
  int brightness = 255 - ldr_status;
  
  if (brightness > 0) {
    analogWrite(led, brightness);
    buzzed = 0;
  }
  else if (brightness <= 0 && buzzed == 0){
    analogWrite(led, 0);
    tone(buzzer, 500);
    delay(1000);    
    noTone(buzzer);
    delay(2000);
    buzzed = 1;
  }
}
