#include <Arduino.h>
#include <analogWrite.h>
#include <ESP32Wiimote.h>

#define LeftMotor_IN1  14
#define LeftMotor_IN2  27
#define LeftMotor_EN   12
//#define LeftMotor_ECA  2
//#define LeftMotor_ECB  16

#define RightMotor_IN1  26
#define RightMotor_IN2  25
#define RightMotor_EN   33
//#define RightMotor_ECA  17
//#define RightMotor_ECB  4

#define DDRIVE_MIN -126 //The minimum value x or y can be.
#define DDRIVE_MAX 126  //The maximum value x or y can be.
#define MOTOR_MIN_PWM -255 //The minimum value the motor output can be.
#define MOTOR_MAX_PWM 255 //The maximum value the motor output can be.

ESP32Wiimote wiimote;

void setup() 
{
  
  //Serial.begin(115200);
  //Serial.println("Running");

  pinMode(LeftMotor_IN1, OUTPUT);
  pinMode(LeftMotor_IN2, OUTPUT);
  pinMode(LeftMotor_EN, OUTPUT);
 // pinMode(LeftMotor_ECA,INPUT);

  pinMode(RightMotor_IN1, OUTPUT);
  pinMode(RightMotor_IN2, OUTPUT);
  pinMode(RightMotor_EN, OUTPUT);
//  pinMode(LeftMotor_ECA,INPUT);
  
  wiimote.init();
  
}


int speed = 250;

void loop() {

    wiimote.task();
    if (wiimote.available() > 0) 
    {
        NunchukState nunchuk = wiimote.getNunchukState();

        int x=nunchuk.xStick-128;
        int y=nunchuk.yStick-128;
        if (x < -126)
        {
          x=-126;
        }
       
        if (y > 126)
        {
          y=126;
        }
        Serial.printf("x: %3d y: %3d \n", x, y);
        if (y < -126)
        {
          y=-126;
        }
      
        CalculateDrive(x,y);
    }
    else
    {
        delay(10);
    }
}


void runMotor(int input1,int input2,int enablePin, int _pwm) 
{    
    if(_pwm >= 0) 
    { 
      digitalWrite(input1,HIGH);
      digitalWrite(input2,LOW);
      analogWrite(enablePin,_pwm);
    }
    else 
    {

      digitalWrite(input1,LOW);
      digitalWrite(input2,HIGH);
      analogWrite(enablePin,0 - _pwm);         
    }
   
}

void CalculateDrive(int x, int y)
{
 int leftSpeed = y + x; 
 int rightSpeed = y - x; 

 leftSpeed = map(leftSpeed, -126, 126, -255, 255);
 rightSpeed = map(rightSpeed, -126, 126, -255, 255);

 
 //Serial.printf("x: %3d y: %3d  leftSpeed: %3d rightSpeed: %3d\n",x,y,leftSpeed,rightSpeed);
 runMotor(LeftMotor_IN1,LeftMotor_IN2,LeftMotor_EN,leftSpeed);
 runMotor(RightMotor_IN1,RightMotor_IN2,RightMotor_EN,rightSpeed);
 
 
}
