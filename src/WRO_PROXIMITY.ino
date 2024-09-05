#include <HCSR04.h>
#include <Servo.h>

#define motor1 11
#define motor2 3

int last_value = 0;
const int lefts = 5;
const int midles = 7;
const int rights = 6;

Servo servo;


const int speed = 90;
// int Red = 0, Blue = 0, Green = 0;  //RGB values
int zero_point = 80;
int right_angle = 0;
int left_angle = 180;
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

int Ldist = 50;
int Mdist = 50;
int Rdist = 50;
int obstacledist = 10;
void setup() {
  pinMode(lefts, INPUT_PULLUP);
  pinMode(midles, INPUT_PULLUP);
  pinMode(rights, INPUT_PULLUP);

  Serial.begin(9600);  e
  servo.attach(A1);

  servo_test();
  servo.write(zero_point);
  delay(2000);
}

void loop() {
  long ct = millis();

  motor(speed);
  Serial.print(digitalRead(lefts));
  Serial.print(digitalRead(midles));
  Serial.println(digitalRead(rights));
  if (Serial.available()) {
    char data = Serial.read();
    if (data == "right") servo.write(right_angle);
    else if (data == "left") servo.write(left_angle);
  } else if (!digitalRead(lefts)) {
    servo.write(right_angle);
    motor(speed);
    delay(500);
    last_value = 1;
  } else if (!digitalRead(rights)) {
    servo.write(left_angle);
    motor(speed);

    delay(500);
    last_value = 2;
  } else if (!digitalRead(rights) && !digitalRead(midles)) {
    servo.write(left_angle);

    motor(speed);

    delay(2000);
    last_value = -1;
  }

  else if (!digitalRead(lefts) && !digitalRead(midles)) {
    servo.write(right_angle);

    motor(speed);

    delay(2000);
    last_value = -2;
  } else if (!digitalRead(midles)) {
    servo.write(zero_point);
    motor(0);
    delay(200);

    if (last_value > 0) {
      if (last_value == 1) {
        servo.write(left_angle);
      } else if (last_value == 2) {
        servo.write(right_angle);
      }
      motor(-speed);

      delay(1500);
      if (last_value == 2) {
        servo.write(left_angle);
      } else if (last_value == 1) {
        servo.write(right_angle);
      }
    } else if (last_value < 0) {
      if (last_value == -1) {
        servo.write(left_angle);
      } else if (last_value == -2) {
        servo.write(right_angle);
      }
      motor(-speed);

      delay(1500);
      if (last_value == -2) {
        servo.write(left_angle);
      } else if (last_value == -1) {
        servo.write(right_angle);
      }
      if (last_value == -1) {
        servo.write(left_angle);
      } else if (last_value == -2) {
        servo.write(right_angle);
      }
      motor(-speed);

      delay(1500);
      if (last_value == -2) {
        servo.write(left_angle);
      } else if (last_value == -1) {
        servo.write(right_angle);
      }
    }
    motor(speed);

    delay(1500);
  } else if (!digitalRead(lefts) && !digitalRead(midles) && !digitalRead(rights)) {
    servo.write(zero_point);
    motor(-speed);
    delay(1500);
  } else {
    servo.write(zero_point);
    delay(50);
  }

}

void motor(int value) {
  if (value > 0) {
    analogWrite(motor1, abs(value));
    digitalWrite(motor2, LOW);
  } else if (value < 0) {
    digitalWrite(motor1, LOW);
    analogWrite(motor2, abs(value));
  } else {
    digitalWrite(motor1, 0);
    digitalWrite(motor2, 0);
  }
}

void servo_test() {
  servo.write(zero_point);
  for (int i = 0; i < 180; i++) {
    servo.write(i);
    delay(5);
  }
  for (int i = 180; i > 0; i--) {
    servo.write(i);
    delay(5);
  }
}
