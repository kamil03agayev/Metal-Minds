#include <Servo.h>

#define motor1 11
#define motor2 3
#define mode_switch 2
#define redpin 10
 #define greenpin 9
#define start_button 4
int last_value = 0;
const int lefts = 6;
const int midles = 5;
const int rights = 7;
Servo servo;


#define rpi 12

int speed = 150;

int zero_point = 97;
int right_angle = 10;
int left_angle = 170;

int right_angleob = 30;
int left_angleob = 150;

void setup() {
  

  Serial.begin(9600);

  pinMode(13, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(mode_switch, INPUT_PULLUP);
  pinMode(rpi, INPUT);
  pinMode(redpin, INPUT);
  pinMode(greenpin, INPUT);
  pinMode(lefts, INPUT_PULLUP);
  pinMode(midles, INPUT_PULLUP);
  pinMode(rights, INPUT_PULLUP);
  pinMode(start_button, INPUT_PULLUP);


  servo.attach(A1);

  servo_test();
  servo.write(zero_point);
  delay(100);
}
void freestyle() {
  while (1) {
    motor(speed);
    if (digitalRead(mode_switch)) last_value = 1;
    else last_value = 2;


    if (!digitalRead(midles)) {
      servo.write(zero_point);
      motor(0);
      delay(50);

      if (last_value > 0) {
        if (last_value == 1) {
          servo.write(left_angle);
        } else if (last_value == 2) {
          servo.write(right_angle);
        }
        motor(-speed);

        delay(1000);
        if (last_value == 2) {
          servo.write(left_angle);
        } else if (last_value == 1) {
          servo.write(right_angle);
        }
        motor(speed);
        delay(700);
      }
    } else if (!digitalRead(rights) && !digitalRead(midles)) {
      servo.write(left_angle);

      motor(speed);

      delay(1000);
      if (last_value == 0) {
        last_value = -1;
      }
    } else if (!digitalRead(lefts) && !digitalRead(midles)) {
      servo.write(right_angle);

      motor(speed);

      delay(1000);
      if (last_value == 0) {
        last_value = -2;
      }
    } else if (!digitalRead(lefts)) {
      servo.write(right_angle);
      motor(speed);
      delay(500);

    } else if (!digitalRead(rights)) {
      servo.write(left_angle);
      motor(speed);

      delay(500);
      if (last_value == 0) {
        last_value = 2;
      }
    } else {
      servo.write(zero_point);
      delay(50);
    }
  }
}
void obstacle_mode() {
  while (1) {
    motor(speed);
    Serial.print(digitalRead(redpin));
    Serial.println(digitalRead(greenpin));
    if (digitalRead(mode_switch)) last_value = 1;
    else last_value = 2;

    if (digitalRead(redpin)) {
      servo.write(right_angleob);
      delay(400);
      servo.write(zero_point);
      delay(200);
    } else if (digitalRead(greenpin)) {
      servo.write(left_angleob);
      delay(400);
      servo.write(zero_point);
      delay(200);

    } else if (!digitalRead(midles)) {
      servo.write(zero_point);
      motor(0);
      delay(50);

      if (last_value > 0) {
        if (last_value == 1) {
          servo.write(left_angle);
        } else if (last_value == 2) {
          servo.write(right_angle);
        }
        motor(-speed);

        delay(1000);
        if (last_value == 2) {
          servo.write(left_angle);
        } else if (last_value == 1) {
          servo.write(right_angle);
        }
        motor(speed);
        delay(700);
      }
    } else if (!digitalRead(rights) && !digitalRead(midles)) {
      servo.write(left_angle);

      motor(speed);

      delay(1000);
      if (last_value == 0) {
        last_value = -1;
      }
    } else if (!digitalRead(lefts) && !digitalRead(midles)) {
      servo.write(right_angle);

      motor(speed);

      delay(1000);
      if (last_value == 0) {
        last_value = -2;
      }
    } else if (!digitalRead(lefts)) {
      servo.write(right_angle);
      motor(speed);
      delay(500);

    } else if (!digitalRead(rights)) {
      servo.write(left_angle);
      motor(speed);

      delay(500);
      if (last_value == 0) {
        last_value = 2;
      }
    } else {
      servo.write(zero_point);
      delay(50);
    }
  }
}
void loop() {
  if (!digitalRead(start_button)) {
    if (!digitalRead(rpi)) {
      freestyle();
    } else if (digitalRead(rpi)) {
      obstacle_mode();
    }
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
  for (int i = 90; i < 180; i++) {
    servo.write(i);
    delay(5);
  }
  for (int i = 180; i > 0; i--) {
    servo.write(i);
    delay(5);
  }
  for (int i = 0; i < 90; i++) {
    servo.write(i);

    delay(5);
  }
  servo.write(zero_point);
}

