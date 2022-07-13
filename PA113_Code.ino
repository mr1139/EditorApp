#include<Servo.h>
Servo myservo;

int R = A2;
int F = A3;
int L = A4;
int  a, b, c, d;
int m11 = 7;
int m12 = 6;
int m21 = 5;
int m22 = 4;
char z;
int relay = 2;
int mq = A5;
int Buzzer = 11;

void setup() {
  pinMode(Buzzer, OUTPUT);
  pinMode(mq, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(L, INPUT);
  pinMode(R, INPUT);
  pinMode(F, INPUT);
  Serial.begin(9600);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  myservo.attach(9);
}

void loop() {
  if (Serial.available() > 0) {
    z = Serial.read();
    Serial.println(z);
  }

  if (z == 'A') {
    Serial.println("forward");
    digitalWrite (m11, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m22, HIGH);
    fire();
  }
  else if (z == 'C') {
    Serial.println("left");
    digitalWrite (m11, LOW);
    digitalWrite(m12, HIGH);
    digitalWrite(m21, LOW);
    digitalWrite(m22, HIGH);
    fire();
  }
  else if (z == 'B') {
    Serial.println("BAck");
    digitalWrite (m11, LOW);
    digitalWrite(m12, HIGH);
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
    fire();
  }
  else if (z == 'D') {
    Serial.println("right");
    digitalWrite (m11, HIGH);
    digitalWrite(m12, LOW);
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
    fire();
  }
  else if (z == 'E') {
    Serial.println("stop");
    digitalWrite (m11, LOW);
    digitalWrite(m12, LOW);
    digitalWrite(m21, LOW);
    digitalWrite(m22, LOW);
    fire();
  }
}
void fire() {
  a = analogRead(R);
  b = analogRead(F);
  c = analogRead(L);
  d = analogRead(mq);
  Serial.print("MQsensor:");
  Serial.print(d);
  Serial.print("  L:");
  Serial.print(c);
  Serial.print("  R:");
  Serial.print(a);
  Serial.print("  F :");
  Serial.println(b  );
  delay(1000);
  if (d > 170) {
    if (((c < 500) && (a < 500) && (b < 500))) {

      Serial.println("No fire detected");
      digitalWrite(relay, HIGH);
      myservo.write(0);
      digitalWrite(Buzzer, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      delay(100);

    }
    if ((c > 500) && (a < 500) && (b < 500)) {
      Serial.println("fire detected on left");
      digitalWrite(relay, LOW);
      myservo.write(0);
      digitalWrite(Buzzer, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      delay(100);
    }
    if ((c < 500) && (a < 500) && (b > 400)) {
      myservo.write(90);
      Serial.println("Fire on front");
      digitalWrite(relay, LOW);
      digitalWrite(Buzzer, HIGH);
      delay(100);
      digitalWrite(Buzzer, LOW);
      delay(100);
    }
    else if ((c < 500) && (a > 400) && (b < 500)) {
      myservo.write(180);
      Serial.println("Fire on right");
      digitalWrite(Buzzer, HIGH);
      digitalWrite(relay, LOW);
      delay(100);
      digitalWrite(Buzzer, LOW);
      delay(100);
    }
    else if ((c < 500) && (a > 400) && (b > 400)) {
      for (int i = 90; i <  180; i++) {
        myservo.write(i);
        Serial.println("Fire on right");
        digitalWrite(relay, LOW);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        a = analogRead(R);
        b = analogRead(F);
        c = analogRead(L);
        d = analogRead(mq);
      }
    }
    else if ((c > 400) && (a < 500) && (b > 400)) {
      for (int i = 0; i < 90; i++) {
        myservo.write(i);
        Serial.println("Fire on left and front");
        digitalWrite(relay, LOW);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        a = analogRead(R);
        b = analogRead(F);
        c = analogRead(L);
        d = analogRead(mq);
      }
    }
    else if (((c > 400) && (a > 400) && (b > 500)) || ((c > 500) && (a > 500) && (b < 500))) {
      for (int i = 0; i < 180; i++) {
        myservo.write(i);
        Serial.println("Fire on all side");
        digitalWrite(relay, LOW);
        digitalWrite(Buzzer, HIGH);
        delay(100);
        digitalWrite(Buzzer, LOW);
        delay(100);
        a = analogRead(R);
        b = analogRead(F);
        c = analogRead(L);
        d = analogRead(mq);
      }
    }
  } else if (d < 170) {
    Serial.print("No smoke detected");
    digitalWrite(relay, HIGH);
  }
}
