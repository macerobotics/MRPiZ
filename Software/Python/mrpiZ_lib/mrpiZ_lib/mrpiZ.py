#!/usr/bin/python

######################################################
#  Python API
#  This library is used for the MRPiZ robot.
#  http://www.macerobotics.com
#  Date : 14/12/2022
#  Version : 1.6
# 
#  Modif : suppression controleEnable, gerer direct dans lib
#  Fonctionnne avec Python 3
#
#  MIT Licence

######################################################
from math import*

import serial
import time
import os

###############################################################
###############################################################

__all__ = ['firmwareVersion'] # OK
__all__ = ['switch']# OK
__all__ = ['battery']# OK
__all__ = ['proxSensor']# OK
__all__ = ['forward']# OK
__all__ = ['controlEnable']# OK
__all__ = ['controlDisable']# OK
__all__ = ['forwardC']# OK
__all__ = ['back']# OK
__all__ = ['backC']# OK
__all__ = ['stop']# OK
__all__ = ['turnRight']# OK
__all__ = ['turnRightC']# OK
__all__ = ['turnLeft']# OK
__all__ = ['turnLeftC']# OK
__all__ = ['turnRight_degree']# OK
__all__ = ['turnLeft_degree']# OK
__all__ = ['forward_mm']# OK
__all__ = ['back_mm']# OK
__all__ = ['motorRight']# OK
__all__ = ['motorLeft']# OK
__all__ = ['motorsWrite']# OK
__all__ = ['robotPositionX']# OK
__all__ = ['robotPositionY']# OK
__all__ = ['robotPositionO']# OK
__all__ = ['encoderLeft']# OK
__all__ = ['encoderRight']# OK
__all__ = ['readVusb']# OK
__all__ = ['resetUc']# OK
__all__ = ['robotGo']# OK
__all__ = ['writeCommand']# OK
__all__ = ['readData']# OK
__all__ = ['forwardmm']# OK
__all__ = ['backmm']# OK
__all__ = ['turnRightDegree']# OK
__all__ = ['turnLeftDegree']# OK
__all__ = ['motorLeftSpeed']# OK
__all__ = ['motorRightSpeed']# OK
__all__ = ['motorsDisable']
__all__ = ['motorsEnable']
__all__ = ['init_gripper']
__all__ = ['buzzer']
__all__ = ['buzzerStart']
__all__ = ['buzzerStop']
__all__ = ['ledRGB']
###############################################################
###############################################################




# init serial port, baud rate = 230400
port = serial.Serial('/dev/ttyAMA0', 230400)
time.sleep(0.5)


# Read firmware version of the microcontroller
def firmwareVersion():
  """
        Read the firmware version (microcontroller)
        Exemple:
        >> firmwareVersion()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"FV")
  value = readData()
  return float(value)
  
 
def robotGo():
  print("En cours de dévelopement")
#---------------------------------------------------------------------
#-------------[ MRPI1 switch methods]---------------------------------
  
# Read switch 
def switch():
  """
        Read the switch state
        return switch()
        Exemple:
        >> switch()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"SW")
  value = readData()
  return __convListToUint(value)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 class sensors methods]--------------------------

# get battery tension (volt unit)
def battery():
  """
        Read battery tension
        return tension (volt)
        Exemple:
        >> battery()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"BAT")
  value = readData()
  return float(value)
  
# read proximity sensor
def proxSensor(sensor):
  """
        Read proximity sensor
        parameter : 1 to 5
        return proximity sensor (0 to 2000), millimeter unit
        Exemple, read sensor 2:
        >> proxSensor(2)
  """
  if( sensor not in(1,2,3,4,5) ) :
    print ("error parameter")
  else:
    liste = []
    value = 0
    port.flushInput() # reset serial receive buffer
    port.write(b"#PROX,")
    sensor = bytes(str(sensor), 'utf-8')
    port.write(sensor)
    port.write(b"!")
    value = readData()
    return int(value)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 move robot methods]------------

# the robot move forward
def forward(speed):
  """
        move forward mrpi1
        parameter : 0 to 100
        Exemple:
        >> forward(20)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write(b"#MF,")
    speed = bytes(speed, 'utf-8')
    port.write(speed)
    port.write(b"!")
  else:
    print("error speed value")

# control robot enable
def controlEnable():
  """
        control robot enable
        Exemple:
        >> controlEnable()
  """
  global control_robot
  if control_robot == False :
    control_robot = True
    writeCommand(b"CRE")
  else:
    print("error : control is already enable !")

# control robot disable  
def controlDisable():
  """
        control robot disable
        Exemple:
        >> controlDisable()
  """
  global control_robot
  
  if (control_robot == True) or  (control_robot == False):
    control_robot = False
    writeCommand(b"CRD")

# the robot move forward with control
def forwardC(speed, distance):
  """
        move forward mrpi1 with control
        Exemple:
        >> forwardC(20, 4000)
  """
  speed = float(speed)
  distance = float(distance)
  
  if check_speed(speed,distance) == 0:
    return 0
	
  #if control_robot == True:

  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  distance = bytes(distance, 'utf-8')
  speed = bytes(speed, 'utf-8')
  port.write(b"#MFC,")
  port.write(distance)
  port.write(b",")
  port.write(speed)
  port.write(b"!")

  port.flushInput() # reset serial receive buffer

  while True:
    time.sleep(0.1)
    state = 0
    port.flushInput() # reset serial receive buffer
    writeCommand(b"TGS,1")
    state = readData()
    state = int(state)
    if((state == 3) or (state == 4)):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == 4):
        print("error : speed to hight")
        return 0
      chaine = 0
      return 1# end while 1

  
# the robot move forward with control
def forwardmm(speed, distance):
  """
        move forward mrpiZ with control (mm = millimeter distance) with no pulling
        Exemple:
        >> forwardmm(20, 200)
  """
  controlEnable()
  if check_speed(speed,distance*4) == 0:
    return 0
	
  #if control_robot == True:
  
  print("Forward with control enable")

  distance = int(distance)
  speed = str(speed)
  distance = str(distance*4)#conversion en mm
  port.write(b"#MFC,")
  distance = bytes(distance, 'utf-8')
  port.write(distance)
  port.write(b",")
  speed = bytes(speed, 'utf-8')
  port.write(speed)
  port.write(b"!")


# the robot move forward with control
def backmm(speed, distance):
  """
        move forward mrpi1 with control
        Exemple:
        >> forwardC(20, 4000)
  """
  controlEnable()
  if check_speed(speed,distance*4) == 0:
    return 0
	
  #if control_robot == True:
  
  print("Forward with control enable")

  distance = int(distance)
  speed = str(speed)
  distance = str(distance*4)#conversion en mm
  port.write(b"#MBC,")
  distance = bytes(distance, 'utf-8')
  port.write(distance)
  port.write(b",")
  speed = bytes(speed, 'utf-8')
  port.write(speed)
  port.write(b"!")

# the robot move forward with control (distance : millimeter)
def forward_mm(speed, distance):
  controlEnable()
  speed = str(speed)
  distance = str(distance*4) 
  forwardC(speed, distance)

# the robot move back
def back(speed):
  """
        move back mrpi1
        parameter : 0 to 100
        Exemple:
        >> forward(20)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write(b"#MB,")
    speed = bytes(speed, 'utf-8')
    port.write(speed)
    port.write(b"!")
  else:
    print("error speed value")
	

'''def back(speed):
  __backControl(speed, 99999)# distance infini (avance toujours)
'''
  
# the robot move back with control
def backC(speed, distance):
  """
        move forward mrpi1 with control
        Exemple:
        >> backC(20, 4000)
  """
  speed = float(speed)
  distance = float(distance)
  
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  distance = bytes(distance, 'utf-8')
  speed = bytes(speed, 'utf-8')
  port.write(b"#MBC,")
  port.write(distance)
  port.write(b",")
  port.write(speed)
  port.write(b"!")
  
  port.flushInput() # reset serial receive buffer
  
  while True:
    time.sleep(0.1)
    writeCommand(b"TGS,1")
    state = readData()
    state = int(state)
    if((state == 3) or (state == 4)):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == 4):
        print("error : speed to hight")
      chaine = 0
      break # end while 1 
	  
# the robot move back with control (distance : millimeter)
def back_mm(speed, distance):
  controlEnable()
  backC(speed, distance*4)

# the robot stop
def stop():
  """
        stop the robot
        Exemple:
        >> stop()
  """
  writeCommand(b"STP")
 
# the robot turn right
def turnRight(speed):
  """
        turn right
        parameter : speed (0 to 100)
        max speed = 100
        min speed = 0
        Exemple:
        >> turnRight(30)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write(b"#TR,")
    speed = bytes(speed, 'utf-8')
    port.write(speed)
    port.write(b"!")
  else:
    print("error speed value")



# the robot turn right with control
def turnRightDegree(speed, distance):

  controlEnable()
  if check_speed(speed,distance*546/90) == 0:
    return 0
	
  distance = int(distance*546/90)
  speed = str(speed)
  distance = str(distance)
  distance = bytes(distance, 'utf-8')
  speed = bytes(speed, 'utf-8')  
  port.write(b"#TRC,")
  port.write(distance)
  port.write(b",")
  port.write(speed)
  port.write(b"!")
  
  port.flushInput() # reset serial receive buffer

# the robot turn right with control
def turnLeftDegree(speed, distance):
  controlEnable()
  if check_speed(speed,distance*546/90) == 0:
    return 0
	
  distance = int(distance*546/90)
  speed = str(speed)
  distance = str(distance)
  distance = bytes(distance, 'utf-8')
  speed = bytes(speed, 'utf-8')  
  port.write(b"#TLC,")
  port.write(distance)
  port.write(b",")
  port.write(speed)
  port.write(b"!")
  
  port.flushInput() # reset serial receive buffer

  
# the robot turn right with control
def turnRightC(speed, distance):
  """
        turn right with control
        parameter 1 : speed (0 to 100)
        max speed = 100
        min speed = 0
        parameter 2 : degree angle
        546 = 90 degree 
        Exemple:
        >> turnRightC(10, 546)
  """
  
  speed = float(speed)
  distance = float(distance)
  
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  distance = bytes(distance, 'utf-8')
  speed = bytes(speed, 'utf-8')
  port.write(b"#TRC,")
  port.write(distance)
  port.write(b",")
  port.write(speed)
  port.write(b"!")
  
  port.flushInput() # reset serial receive buffer

  while True:
    time.sleep(0.1)
    writeCommand(b"TGS,2")
    state = readData()
    state = int(state)
    if((state == 3) or (state == 4)):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == 4):
        print("error : speed to hight")
      chaine = 0
      break # end while 1 
	  
# the robot turn right with control 
def turnRight_degree(speed, degree):
  controlEnable()
  turnRightC(speed, degree*546/90)

# the robot turn left
def turnLeft(speed):
  """
        turn left
        parameter : speed (0 to 100)
        max speed = 100
        min speed = 0
        Exemple:
        >> turnLeft(30)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write(b"#TL,")
    speed = bytes(speed, 'utf-8')
    port.write(speed)
    port.write(b"!")
  else:
    print("error speed value")


# the robot turn left with control
def turnLeftC(speed, distance):
  """
        turn left with control
        parameter 1 : speed (0 to 100)
        max speed = 100
        min speed = 0
        parameter 2 : degree angle
        546 = 90 degree
        Exemple:
        >> turnLeftC(10, 546)
  """
  speed = float(speed)
  distance = float(distance)  
  
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  distance = bytes(distance, 'utf-8')
  speed = bytes(speed, 'utf-8')
  port.write(b"#TLC,")
  port.write(distance)
  port.write(b",")
  port.write(speed)
  port.write(b"!")
  
  port.flushInput() # reset serial receive buffer
  
  while True:
    time.sleep(0.1)
    writeCommand(b"TGS,2")
    state = readData()
    state = int(state)
    if((state == 3) or (state == 4)):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == 4):
        print("error : speed to hight")
      chaine = 0
      break # end while 1 
	  
# the robot turn right with control 
def turnLeft_degree(speed, degree):
  controlEnable()
  turnLeftC(speed, degree*546/90)
  
# the robot turn with control (0 to 360 degree) 
def turn_degree(speed, degree):
  #lecture angle actuelle du robot
  angle_robot = robotPositionO() 
  print("angle_robot = ", angle_robot)
  
  if (degree == 0.0)and(angle_robot > 180):
    print("degree == 0)and(angle_robot > 180")
    degree = 360
  elif (angle_robot == 0.0)and(degree > 180) :
    print("angle_robot == 0.0)and(degree > 180")
    angle_robot = 360
  
  
  if degree > angle_robot:
    error = degree - angle_robot
    if error <= 180:
      turnLeft_degree(speed, error)
    else:
      error = 360 - error
      turnRight_degree(speed, error)
  else:
    error = angle_robot - degree
    if error <= 180:
      turnRight_degree(speed, error)
    else:
      error = 360 - error
      turnLeft_degree(speed, error)
  
  
# the motor right
def motorRight(direction, speed):
  """
        motor right control
        parameter 1 : direction (0 or 1)
        parameter 2 : speed ( 0 to 100)     
        Exemple:
        >> motorRight(1, 50)
  """
  dir = bytes(str(direction), 'utf-8')
  pwm = bytes(str(speed), 'utf-8')
  port.write(b"#MOTR,")
  port.write(dir)
  port.write(b",")
  port.write(pwm)
  port.write(b"!")

# the motor left
def motorLeft(direction, speed):
  """
        motor left control
        parameter 1 : direction (0 or 1)
        parameter 2 : speed ( 0 to 100)     
        Exemple:
        >> motorLeft(1, 50)
  """
  dir = bytes(str(direction), 'utf-8')
  pwm = bytes(str(speed), 'utf-8')
  port.write(b"#MOTL,")
  port.write(dir)
  port.write(b",")
  port.write(pwm)
  port.write(b"!")
  
# the motor left
def motorsWrite(dirMotorRight, dirMotorLeft, speedMotorRight, speedMotorLeft):
  """
        motor left and right control
        parameter 1 : direction right motor (0 : forward or 1 : back)
        parameter 2 : direction right motor (0 : forward or 1 : back)
        parameter 3 : speed right motor (0 to 100)
        parameter 4 : speed left motor (0 to 100)
        Exemple:
        >> motorsWrite(1,0,50,40)
  """
  if dirMotorRight == 1:
    speedRight = speedMotorRight + 100
  else:
    speedRight = speedMotorRight

  if dirMotorLeft == 1:
    speedLeft = speedMotorLeft + 100
  else:
    speedLeft = speedMotorLeft

  speedLeft = str(speedLeft)
  speedRight = str(speedRight)
  speedLeft = bytes(speedLeft, 'utf-8')
  speedRight = bytes(speedRight, 'utf-8')
  port.write(b"#MOTS,")
  port.write(speedRight)
  port.write(b",")
  port.write(speedLeft)
  port.write(b"!")

  
########################################
# robot go (X and Y Coordinate),
# speed : speed of the robot (0 to 100)
# cordX : Coordinate axe X (millimeter)
# cordY : Coordinate axe Y (millimeter)

  
# read robot position axe X
def robotPositionX():
  """
        Read robot position axe X
        return position (units : mm)
        Exemple:
        >> robotPositionX()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"POX")
  value = readData()
  value = float(value) 
  return (value/4) # conversion mm
  
  
# read robot position axe Y
def robotPositionY():
  """
        Read robot position axe Y
        return position (units : mm)
        Exemple:
        >> robotPositionY()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"POY")
  value = readData()
  value = float(value) 
  return (value/4) 
  
# read robot orientation
def robotPositionO():
  """
        Read robot orientation
        return degree orientation 
        Exemple:
        >> robotPositionO()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"POO")
  value = readData()
  value = float(value) 
  
  # conversion en degree
  value = ((value*180.0)/(3.14159))
  
  # conversion entre 0 et 360 degree
  if abs(value) >= 360.0:
    m = int(value/360)
    modulo = value%360
    value = modulo
  elif value < 0.0:
    value = 360 + value

  return value# conv to degree
  
# read robot orientation
def motorLeftSpeed():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"MLS")
  value = readData()
  value = float(value) 
  return (value)
  
# read robot orientation
def motorRightSpeed():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"MRS")
  value = readData()
  value = float(value) 
  return (value)
  
  
# motors disable
def motorsDisable():
  writeCommand(b"MDI")
  
# motors enable
def motorsEnable():
  writeCommand(b"MEN")
  
# init gripper of MRPiZ
def init_gripper():
  print("init gripper")

#---------------------------------------------------------------------
#-------------[ MRPiZ buzzer methods]-------------------------

# buzzer control
def buzzer(frequency):
  """
        buzzer control
        parameter : 0 to 20000 Hz
        Exemple:
        >> buzzer(200)
  """
  if frequency > -1 and frequency < 20001:
    frequency = bytes(str(frequency), 'utf-8')
    port.write(b"#BUZ,")
    port.write(frequency)
    port.write(b"!")
  else:
    print("error frequency value")

# buzzer start
def buzzerStart():
  writeCommand(b"BUZD")
  
# buzzer stop
def buzzerStop():
  writeCommand(b"BUZS")
  
# led RGB
def ledRGB(red,green,blue):
  red = bytes(str(red), 'utf-8')
  green = bytes(str(green), 'utf-8')
  blue = bytes(str(blue), 'utf-8')
  port.write(b"#RGB,")
  port.write(red)
  port.write(b",")
  port.write(green)
  port.write(b",")
  port.write(blue)
  port.write(b"!")
#---------------------------------------------------------------------
#-------------[ MRPiZ encoders robot methods]-------------------------

# the encoderleft
def encoderLeft():
  """
        read the encoder left value  
        Exemple:
        >> encoderLeft()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"EDL")
  value = readData()
  return int(value)
  
# the encoderleft
def encoderRight():
  """
        read the encoder right value  
        Exemple:
        >> encoderRight()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"EDR")
  value = readData()
  return int(value)
 
#---------------------------------------------------------------------
#-------------[ MRPiZ usb robot methods]------------------------------

# get usb tension
def readVusb():
  """
        Read usb tension
        return tension (volt)
        Exemple:
        >> readVusb()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand(b"VUSB")
  value = readData()
  return float(value) 
 
#---------------------------------------------------------------------
#-------------[ MRPiZ reset uc robot methods]------------------------------

# reset microcontroller
def resetUc():
  """
        Reset microcontroller
        Exemple:
        >> resetUc()
  """
  writeCommand(b"RST")
  control_robot = False

  
#---------------------------------------------------------------------
#-------------[ MRPiZ serial2 methods]----------------------------
  
# 
def serial2Write(data):
  """
        serial 2 write 
        Exemple:
        >> serial2Write("HELLO")
  """
  port.write(b"#SRLW,")
  port.write(data)
  port.write(b"!")
  

#------------------------------------------------------------
#-------------[ MRPiZ class utils private methods]------------

# check 
def check_speed(speed, distance):
  acceleration = 0.5 # acceleration in the STM32 (trapezoid generator)
  check1 = distance*acceleration
  check2 = speed*speed
  
  if(distance == 0):
    return 1
  
  if check1 > check2:
      return 1
  else:
    print("Error speed to hight !")
    return 0
  

# convert list to unsigned int
def __convListToUint(liste):
  a=''
  i=0
  result=0
  while i < (len(liste)):
    a = a + liste[i]
    i = i + 1
  try:
    result = int(a)
    return(result)
  except ValueError:
    pass
  

# write command
def writeCommand(command):
  port.write(b'#')
  port.write(command)
  port.write(b'!')
  
# read data
def readData():
  chaine = port.readline()
  pos1 = chaine.find(b'$')
  pos2 = chaine.find(b'\n')
  chaine = chaine[pos1+1:pos2]
  return chaine 
  
# convert list to float
def __convListToFloat(liste):
  a=''
  i=0
  while i < (len(liste)):# minus '?'
    a = a + liste[i]
    i = i + 1
  return(float(a))
  
# the robot move forward with control (pas d'attente de la fin du trapeze)
def forwardControl(speed, distance):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print("Forward with control enable")
    distance = int(distance)
    speed = str(speed)
    distance = str(distance)
    port.write(b"#MFC,")
    port.write(distance)
    port.write(b",")
    port.write(speed)
    port.write(b"!")
    port.flushInput() # reset serial receive buffer
  else:
    print("error : control robot disable")
  
# the robot move forward with control (pas d'attente de la fin du trapeze)
def __backControl(speed, distance):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print("Forward with control enable")
    distance = int(distance)
    speed = str(speed)
    distance = str(distance)
    port.write(b"#MBC,")
    port.write(distance)
    port.write(b",")
    port.write(speed)
    port.write(b"!")
    port.flushInput() # reset serial receive buffer
  else:
    print("error : control robot disable")

	
# the robot move forward with control (pas d'attente de la fin du trapeze)
def __turnLeftControl(speed, angle):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print("Forward with control enable")
    angle = int(angle)
    speed = str(speed)
    angle = str(angle)
    port.write(b"#TLC,")
    port.write(angle)
    port.write(b",")
    port.write(speed)
    port.write(b"!")
    port.flushInput() # reset serial receive buffer
  else:
    print("error : control robot disable")


# the robot move forward with control (pas d'attente de la fin du trapeze)
def __turnRightControl(speed, angle):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print("Forward with control enable")
    angle = int(angle)
    speed = str(speed)
    angle = str(angle)
    port.write(b"#TRC,")
    port.write(angle)
    port.write(b",")
    port.write(speed)
    port.write(b"!")
    port.flushInput() # reset serial receive buffer
  else:
    print("error : control robot disable")


# control robot (postion/orientation disable)
control_robot = False

# reset Uc
resetUc()
 
# end file