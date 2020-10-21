/**
  ******************************************************************************
  * @file    MRPiZ.h
  * @author  Mace Robotic - www.macerobotics.com
  * @version V1.2
  * @date    15/10/2020
  * @brief	
  *
 *******************************************************************************/
#ifndef _MRPiZ_H
#define _MRPiZ_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER_PROX_SENSORS 5
#define SIZE_BUFFER_READ 100

typedef enum
{
FORWARD,
BACK
}MotorDirection;

int init();

// move robot
void forward(unsigned int speed); 
void back(unsigned int speed); 
void stop(void); 
void turnRight(unsigned int speed); 
void turnLeft(unsigned int speed);
void forwardC(unsigned int speed, unsigned int distance); 
void forward_mm(unsigned int speed, unsigned int distance_mm);
void backC(unsigned int speed, unsigned int distance);
void back_mm(unsigned int speed, unsigned int distance_mm);
void turnRightC(unsigned int speed, unsigned int angle);
void turnLeftC(unsigned int speed, unsigned int angle);  
void turnRight_degree(unsigned int speed, unsigned int angle);
void turnLeft_degree(unsigned int speed, unsigned int angle);  

// control
void controlEnable(void);
void controlDisable(void);
 
// motor control
void motorRight(MotorDirection direction, unsigned int speed); 
void motorLeft(MotorDirection direction, unsigned int speed);  

// Firmware
float firmwareVersion(void);

// Battery
float battery(void);

// Switch
unsigned int Switch(void);

// proximity sensor
unsigned int proxSensor(unsigned int sensor);

// encoder sensor
int encoderLeft();
int encoderRight();

// read USB voltage
float readVusb(void);

// robot position X
float robotPositionX();

// robot position Y
float robotPositionY();

// read robot orientation
float robotPositionO();

// buzzer
void buzzer(unsigned int frequency);
void buzzerStop(void);

// led rgb
void ledRGB(unsigned int red,unsigned int green, unsigned int blue );

#endif
// End Of File
