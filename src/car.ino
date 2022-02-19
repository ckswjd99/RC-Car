#define MOTOR_RIGHT_FRONT 2
#define MOTOR_RIGHT_REVERSE 3
#define MOTOR_LEFT_FRONT 4
#define MOTOR_LEFT_REVERSE 5
#define BT_TX 8
#define BT_RX 9

#define HALF_HIGH 128

#include <stdio.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(BT_RX, BT_TX);

char buf[10];
int top, right, bottom, left, button;

void setup()
{
  pinMode(MOTOR_RIGHT_FRONT, OUTPUT);
  pinMode(MOTOR_RIGHT_REVERSE, OUTPUT);
  pinMode(MOTOR_LEFT_FRONT, OUTPUT);
  pinMode(MOTOR_LEFT_REVERSE, OUTPUT);
  Serial.begin(38400);
  BTSerial.begin(38400);
}

void loop()
{
  top = 0;
  bottom = 0;
  right = 0;
  left = 0;
  button = 0;

  if (BTSerial.available())
  {
    int commandBuffer = BTSerial.read();
    // sprintf(buf, "%d", commandBuffer);
    // Serial.write(buf);

    if (commandBuffer & (1 << 0))
      top = 1;
    if (commandBuffer & (1 << 1))
      right = 1;
    if (commandBuffer & (1 << 2))
      bottom = 1;
    if (commandBuffer & (1 << 3))
      left = 1;
    if (commandBuffer & (1 << 4))
      button = 1;
  }

  if (right)
  {
    digitalWrite(MOTOR_RIGHT_FRONT, HIGH);
    digitalWrite(MOTOR_RIGHT_REVERSE, LOW);
    digitalWrite(MOTOR_LEFT_FRONT, LOW);
    digitalWrite(MOTOR_LEFT_REVERSE, HIGH);
  }
  else if (left)
  {
    digitalWrite(MOTOR_RIGHT_FRONT, LOW);
    digitalWrite(MOTOR_RIGHT_REVERSE, HIGH);
    digitalWrite(MOTOR_LEFT_FRONT, HIGH);
    digitalWrite(MOTOR_LEFT_REVERSE, LOW);
  }
  else if (top)
  {
    digitalWrite(MOTOR_RIGHT_FRONT, HIGH);
    digitalWrite(MOTOR_RIGHT_REVERSE, LOW);
    digitalWrite(MOTOR_LEFT_FRONT, HIGH);
    digitalWrite(MOTOR_LEFT_REVERSE, LOW);
  }
  else if (bottom)
  {
    digitalWrite(MOTOR_RIGHT_FRONT, LOW);
    digitalWrite(MOTOR_RIGHT_REVERSE, HIGH);
    digitalWrite(MOTOR_LEFT_FRONT, LOW);
    digitalWrite(MOTOR_LEFT_REVERSE, HIGH);
  }
  else
  {
    digitalWrite(MOTOR_RIGHT_FRONT, LOW);
    digitalWrite(MOTOR_RIGHT_REVERSE, LOW);
    digitalWrite(MOTOR_LEFT_FRONT, LOW);
    digitalWrite(MOTOR_LEFT_REVERSE, LOW);
  }

  Serial.print("joystick: ");
  Serial.print(top);
  Serial.print(", ");
  Serial.print(right);
  Serial.print(", ");
  Serial.print(bottom);
  Serial.print(", ");
  Serial.print(left);
  Serial.print(", ");
  Serial.println(button);
}