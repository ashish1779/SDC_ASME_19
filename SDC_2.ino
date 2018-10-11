#include <PS3BT.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>      //Serial Peripheral Interface and it is a way to send data between microcontrollers and other small devices

USB Usb;              //USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb);        // You have to create the Bluetooth Dongle instance like so
                      /* You can create the instance of the class in two ways */
PS3BT PS3(&Btd);    // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57);    // This will also store the bluetooth address - 
                                                        // this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;       //for measuring temperature NO USE


int motorSpeedA = 0;
int motorSpeedB = 0;
int motorSpeedC = 0;
int motorSpeedD = 0;

#define enA 8
#define in1 22
#define in2 23
#define enB 9
#define in3 24
#define in4 25
#define enC 10
#define in5 26
#define in6 27
#define enD 11
#define in7 28
#define in8 29


void setup() {
  Serial.begin(115200);

    #if !defined(__MIPSEL__)
          while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
    #endif
  
  if (Usb.Init() == -1) 
    {Serial.print(F("\r\nOSC did not start"));
      while (1); //halt
    }
    Serial.print(F("\r\nPS3 Bluetooth Library Started"));

    pinMode(enA, OUTPUT);   //driver 1
    pinMode(enB, OUTPUT);
    pinMode(enC, OUTPUT);   //driver 2
    pinMode(enD, OUTPUT);
    pinMode(in1, OUTPUT);   //driver 1
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);   
    pinMode(in4, OUTPUT);
    pinMode(in5, OUTPUT);   //driver 2
    pinMode(in6, OUTPUT);
    pinMode(in7, OUTPUT);   
    pinMode(in8, OUTPUT);
    
}


void loop() {
  Usb.Task();

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) 
  { Serial.println(PS3.getAnalogHat(RightHatY));Serial.println(PS3.getAnalogHat(RightHatX));
    //RightHatY (Y-Axis of Right) used for forward and backward control
    
    if (PS3.getAnalogHat(RightHatY) <= 115 && PS3.getAnalogHat(RightHatX)==127)     //Forward
    { Serial.println("Forward");
      digitalWrite(in1,LOW);   //MOTOR A    // Also 1-LOW and 2-High for clockwise (Set accordingly)
      digitalWrite(in2,HIGH);
      
      digitalWrite(in3,LOW);   //MOTOR B
      digitalWrite(in4,HIGH);
      
      digitalWrite(in5,LOW);   //MOTOR C
      digitalWrite(in6,HIGH);

      digitalWrite(in7,LOW);   //MOTOR D
      digitalWrite(in8,HIGH);

      
      motorSpeedA = map(RightHatY, 115,0,0,255);
      motorSpeedB = map(RightHatY, 115,0,0,255);
      motorSpeedC = map(RightHatY, 115,0,0,255);
      motorSpeedD = map(RightHatY, 115,0,0,255);
    }

    else if (PS3.getAnalogHat(RightHatY) >= 140 && PS3.getAnalogHat(RightHatX)==127)     //Backward
    { Serial.println("Backward");
      digitalWrite(in1,HIGH);   //MOTOR A
      digitalWrite(in2,LOW);
      
      digitalWrite(in3,HIGH);   //MOTOR B
      digitalWrite(in4,LOW);
      
      digitalWrite(in5,HIGH);   //MOTOR C
      digitalWrite(in6,LOW);

      digitalWrite(in7,HIGH);   //MOTOR D
      digitalWrite(in8,LOW);

      
      motorSpeedA = map(RightHatY, 140,0,0,255);
      motorSpeedB = map(RightHatY, 140,0,0,255);
      motorSpeedC = map(RightHatY, 140,0,0,255);
      motorSpeedD = map(RightHatY, 140,0,0,255);
    }

    // RightHatX (X-Axis of Right) is used for left and right control;
    else if (PS3.getAnalogHat(RightHatX) >= 140 && PS3.getAnalogHat(RightHatY)==127)     //Right
    { Serial.println("Right");
      digitalWrite(in1,LOW);   //MOTOR A   forward move
      digitalWrite(in2,HIGH);
      
      digitalWrite(in3,HIGH);   //MOTOR B  backward move
      digitalWrite(in4,LOW);
      
      digitalWrite(in5,HIGH);   //MOTOR C   backward move
      digitalWrite(in6,LOW);

      digitalWrite(in7,LOW);   //MOTOR D    forward move
      digitalWrite(in8,HIGH);

      
      motorSpeedA = map(RightHatX, 140,0,0,255);
      motorSpeedB = map(RightHatX, 140,0,0,255);
      motorSpeedC = map(RightHatX, 140,0,0,255);
      motorSpeedD = map(RightHatX, 140,0,0,255);
    }

    else if (PS3.getAnalogHat(RightHatX) < 115 && PS3.getAnalogHat(RightHatY)==127)     //Left
    { Serial.println("Left");
      digitalWrite(in1,HIGH);   //MOTOR A    backward
      digitalWrite(in2,LOW);
      
      digitalWrite(in3,LOW);   //MOTOR B    forward
      digitalWrite(in4,HIGH);
      
      digitalWrite(in5,LOW);   //MOTOR C    forward
      digitalWrite(in6,HIGH);

      digitalWrite(in7,HIGH);   //MOTOR D    backward
      digitalWrite(in8,LOW);

      
      motorSpeedA = map(RightHatX, 115,0,0,255);
      motorSpeedB = map(RightHatX, 115,0,0,255);
      motorSpeedC = map(RightHatX, 115,0,0,255);
      motorSpeedD = map(RightHatX, 115,0,0,255);
    }
    
    else if (PS3.getAnalogHat(RightHatX) < 127 && PS3.getAnalogHat(RightHatY) < 127)     //ForwardLeft
    { Serial.println("ForwardLeft");
      digitalWrite(in1,LOW);   //MOTOR A    stop
      digitalWrite(in2,LOW);
      
      digitalWrite(in3,LOW);   //MOTOR B    forward
      digitalWrite(in4,HIGH);
      
      digitalWrite(in5,LOW);   //MOTOR C    forward
      digitalWrite(in6,HIGH);

      digitalWrite(in7,LOW);   //MOTOR D    stop
      digitalWrite(in8,LOW);

      
      motorSpeedA = map(RightHatX, 127,0,0,0); //stop
      motorSpeedB = map(RightHatX, 127,0,0,255);
      motorSpeedC = map(RightHatX, 127,0,0,255);
      motorSpeedD = map(RightHatX, 127,0,0,0);
    }
    
      else if (PS3.getAnalogHat(RightHatX) > 127 && PS3.getAnalogHat(RightHatY) < 127)     //Forwardright
    { Serial.println("ForwardRight");
      digitalWrite(in1,LOW);   //MOTOR A    forward
      digitalWrite(in2,HIGH);
      
      digitalWrite(in3,LOW);   //MOTOR B    stop
      digitalWrite(in4,LOW);
      
      digitalWrite(in5,LOW);   //MOTOR C    stop
      digitalWrite(in6,LOW);

      digitalWrite(in7,LOW);   //MOTOR D    forward
      digitalWrite(in8,HIGH);

      
      motorSpeedA = map(RightHatX, 127,0,0,255); //stop
      motorSpeedB = map(RightHatX, 127,0,0,0);
      motorSpeedC = map(RightHatX, 127,0,0,0);
      motorSpeedD = map(RightHatX, 127,0,0,255);
    }

    /*if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    */

     else if (PS3.getAnalogButton(R2) > 0)     //clockwiseturn
    { Serial.println("Turn Clockwise");
      digitalWrite(in1,LOW);   //MOTOR A    forward
      digitalWrite(in2,HIGH);
      
      digitalWrite(in3,HIGH);   //MOTOR B    backward
      digitalWrite(in4,LOW);
      
      digitalWrite(in5,LOW);   //MOTOR C    forward
      digitalWrite(in6,HIGH);

      digitalWrite(in7,HIGH);   //MOTOR D    backward
      digitalWrite(in8,LOW);

      
      motorSpeedA = map(RightHatX, 255,0,0,255); //clockwise turn
      motorSpeedB = map(RightHatX, 255,0,0,255);
      motorSpeedC = map(RightHatX, 255,0,0,255);
      motorSpeedD = map(RightHatX, 255,0,0,255);
    }
    
    else
    { 
      motorSpeedA = 0;
      motorSpeedB = 0;
      motorSpeedC = 0;
      motorSpeedD = 0;
    }
        //Use of Right Joystick is done in moving forward,backward,left and right

    if (motorSpeedA < 70)       // Prevent buzzing of motor by stoping at slow speed 
    { motorSpeedA = 0; }
    if (motorSpeedB < 70) 
    { motorSpeedB = 0; }
    if (motorSpeedC < 70) 
    { motorSpeedC = 0; }
    if (motorSpeedD < 70) 
    { motorSpeedD = 0; }
    
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B    
    analogWrite(enC, motorSpeedC); // Send PWM signal to motor C
    analogWrite(enD, motorSpeedD); // Send PWM signal to motor D    
    Serial.println(motorSpeedA);
    Serial.println(motorSpeedB);
    Serial.println(motorSpeedC);
    Serial.println(motorSpeedD);
   /* 
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        Serial.print(F("\tRightHatX: "));
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.print(F("\tRightHatY: "));
        Serial.print(PS3.getAnalogHat(RightHatY));
      }
    }

    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }

    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTraingle"));
        PS3.setRumbleOn(RumbleLow);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.setRumbleOn(RumbleHigh);
      }
      if (PS3.getButtonClick(CROSS))
        Serial.print(F("\r\nCross"));
      if (PS3.getButtonClick(SQUARE))
        Serial.print(F("\r\nSquare"));

      if (PS3.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }
      }
      if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
      if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }
      }

      if (PS3.getButtonClick(L1))
        Serial.print(F("\r\nL1"));
      if (PS3.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS3.getButtonClick(R1))
        Serial.print(F("\r\nR1"));
      if (PS3.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    }
#if 0 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
#if 0 // Set this to 1 in order to enable support for the Playstation Move controller
  else if (PS3.PS3MoveConnected) {
    if (PS3.getAnalogButton(T)) {
      Serial.print(F("\r\nT: "));
      Serial.print(PS3.getAnalogButton(T));
    }
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect"));
        printTemperature = !printTemperature;
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS3.moveSetBulb(Red);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.moveSetBulb(Green);
      }
      if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS3.moveSetBulb(Blue);
      }
      if (PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS3.moveSetBulb(Yellow);
      }
      if (PS3.getButtonClick(MOVE)) {
        PS3.moveSetBulb(Off);
        Serial.print(F("\r\nMove"));
        Serial.print(F(" - "));
        PS3.printStatusString();
      }
    }
    
    
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    else if (printTemperature) {
      Serial.print(F("\r\nTemperature: "));
      Serial.print(PS3.getTemperature());
    }
    
  }
#endif
*/
}
}