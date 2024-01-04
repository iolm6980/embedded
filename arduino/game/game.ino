#include<Wire.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);
const int ledA =10;
const int ledB =11;
const int ledC =12;
const int xAxisPin = 0;
const int yAxisPin = 1;
const int zAxisPin = 7;
int a=15; //a~d까지 시작할 노드 위치 설정
int b=18;
int c=20;
int d=23;
int life=3;
int score=0;
void setup() {

  Serial.begin(9600);
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,1);
  lcd.print("GAME START");
  delay(300);
  lcd.clear();
}

void loop() {

  int xValue = analogRead(xAxisPin);
  int xDisplay = map(xValue, 0, 1023, 0, 1);

 if(life != 0){
  lcd.setCursor(0,0);
  lcd.print("                              ");
  lcd.setCursor(0,1);
  lcd.print("                              ");
  lcd.setCursor(0, xDisplay);
  lcd.print("|");


  lcd.setCursor(a,0);
  lcd.print("o");
  a--;

  lcd.setCursor(b,1);
  lcd.print("o");
  b--;

  lcd.setCursor(c,0);
  lcd.print("o");
  c--;

  lcd.setCursor(d,1);
  lcd.print("o");
  d--;

  if(a == 0){
    a = left(xDisplay);
    lcd.setCursor(a,0);
  }
  if(b == 0){
    b = right(xDisplay);
    lcd.setCursor(b,1);
  }
   if(c == 0){
    c = left(xDisplay);
    lcd.setCursor(c,0);
  }
  if(d == 0){
    d = right(xDisplay);
    lcd.setCursor(d,1);
  }
  //delay(300);
}
  
  if(life == 3){
    digitalWrite(ledA,HIGH);
    digitalWrite(ledB,HIGH);
    digitalWrite(ledC,HIGH);
  }
    if(life == 2){
    digitalWrite(ledA,HIGH);
    digitalWrite(ledB,HIGH);
    digitalWrite(ledC,LOW);
  }
    if(life == 1){
    digitalWrite(ledA,HIGH);
    digitalWrite(ledB,LOW);
    digitalWrite(ledC,LOW);
  }
    if(life==0){
      digitalWrite(ledA,LOW);
      digitalWrite(ledB,LOW);
      digitalWrite(ledC,LOW);
      delay(300);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GAME OVER");
      Serial.println("GAME OVER");
      lcd.setCursor(0,1);
      lcd.print("Your score: ");
      lcd.print(score);
      Serial.print("Your score: ");
      Serial.println(score);
      
      digitalWrite(ledA,HIGH);
      digitalWrite(ledB,HIGH);
      digitalWrite(ledC,HIGH);
      delay(300);
    }
}


int left(int xDisplay){
  if(xDisplay == 0){
      score++;
      Serial.print("score: ");
      Serial.println(score);
    }
    else{
      life--;
      Serial.println("lost life");
      Serial.print("life is ");
      Serial.println(life);
    }
     return 15+random(0,5);  
}


int right(int xDisplay){
  if(xDisplay == 1){
      score++;
      Serial.print("score: ");
      Serial.println(score);
    }
    else{
      life--;
      Serial.println("lost life");
      Serial.print("life is ");
      Serial.println(life);
    }
     return 15+random(0,5);  
}
