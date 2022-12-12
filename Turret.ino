#include<Servo.h>

Servo serX;
Servo serY;
int trigger = 6;

int minY = 55;
int maxY = 117;

String data;

void setup() {
  serX.attach(8);
  serY.attach(10);
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, HIGH);
  Serial.begin(9600);
  Serial.setTimeout(5);
  serX.write(90);
  serY.write(90);
}

void loop() {
  data=Serial.readString();
  if(data!=NULL){
    int X=parseX(data);
    int Y= 180 - parseY(data);
    int shoot = parseShoot(data);
    
    if(X!=serX.read())
      serX.write(X);

    if(Y!=serY.read())
      serY.write(Y);

    if(shoot)
      digitalWrite(trigger, LOW);
    else
      digitalWrite(trigger, HIGH);
  }
}

int parseX(String Data){
  Data.remove(Data.indexOf("-"));
  return Data.toInt();
}

int parseY(String Data){
  Data.remove(0, Data.indexOf("-") + 1);
  Data.remove(Data.indexOf(","));
  int val = Data.toInt();
  val = min(maxY, val);
  val = max(minY, val);
  return val;
}

int parseShoot(String Data){
  Data.remove(0, Data.indexOf(",") + 1);
  Data.remove(Data.indexOf("\n"));
  return Data.toInt();
}
