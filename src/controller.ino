#define BTN_1 3
#define BTN_2 4
#define BT_TX 8
#define BT_RX 9
#define JOY_X A0
#define JOY_Y A1
#define JOY_Z A2

#include <stdio.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(BT_RX, BT_TX);

int led = 0;
int joyX, joyY, joyZ;
int top, right, bottom, left, button;
int btn_1, btn_2;

char commandBufferChar[10];

const int stickThresholdHigh = 1023 - 100;
const int stickThresholdLow = 100;
const int stickButtonThreshold = 10;

void setup()
{
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  Serial.begin(38400);
  BTSerial.begin(38400);
}

void loop()
{
  led = 0;
  top = 0;
  bottom = 0;
  right = 0;
  left = 0;
  button = 0;

  joyX = analogRead(JOY_X);
  joyY = analogRead(JOY_Y);
  joyZ = analogRead(JOY_Z);

  btn_1 = digitalRead(BTN_1);
  btn_2 = digitalRead(BTN_2);

  if (btn_2)
    bottom = 1;
  if (btn_1)
    top = 1;
  if (joyY < stickThresholdLow)
    left = 1;
  if (stickThresholdHigh < joyY)
    right = 1;
  if (joyZ < stickButtonThreshold)
    button = 1;

  int commandBuffer = 0;
  if (top)
    commandBuffer += (1 << 0);
  if (right)
    commandBuffer += (1 << 1);
  if (bottom)
    commandBuffer += (1 << 2);
  if (left)
    commandBuffer += (1 << 3);
  if (button)
    commandBuffer += (1 << 4);
  BTSerial.write(commandBuffer);

  Serial.println("Btns ");
  Serial.print(btn_1);
  Serial.print(", ");
  Serial.print(btn_2);
  Serial.print(", joyStick ");
  Serial.print(top);
  Serial.print(", ");
  Serial.print(right);
  Serial.print(", ");
  Serial.print(bottom);
  Serial.print(", ");
  Serial.print(left);
  Serial.print(", ");
  Serial.print(button);
  Serial.print(" buffer: ");
  Serial.print(commandBufferChar);
  Serial.println();
}