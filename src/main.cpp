#include <Arduino.h>
#include <Servo.h>
#include <SunPosition.h>

Servo myservo1; // create servo object to control a servo
Servo myservo2; // create servo object to control a servo
SunPosition sun;
// twelve servo objects can be created on most boards

int pos1 = 30; // variable to store the servo position
int pos2 = 30; // variable to store the servo position

void setup()
{
    Serial.begin(9600);
    myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
    myservo2.attach(10); // attaches the servo on pin 9 to the servo object
}

void loop()
{
    sun = SunPosition(52.17, 104.18, 1780997999, 8);
    parsing();
    if (pos1 > 130)
        pos1 = 130;
    if (pos2 > 170)
        pos2 = 170;
    myservo1.write(pos1); // tell servo to go to position in variable 'pos'
    myservo2.write(pos2); // tell servo to go to position in variable 'pos'
}

void parsing()
{ // Удобная установка значений через COM порт // a10   b20.33 ...
    if (Serial.available() > 0)
    {
        char incoming = Serial.read();
        int value = Serial.parseInt(); //;Serial.parseFloat();
        switch (incoming)
        {
        case 's':
            Serial.print("s1 = ");
            pos1 = value;
            Serial.println(value);
            break;
        case 'd':
            Serial.print("d2 = ");
            pos2 = value;
            Serial.println(value);
            break;
        case 'f':
            Serial.println(sun.altitude());
            Serial.println(sun.azimuth());
            break;
        }
    }
}