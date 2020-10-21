#!/usr/bin/python

######################################################
#  Python API
#  This library is used for the MRPiZ robot.
#  http://www.macerobotics.com
#  Date : 12/10/2020
#  Version : 1.2.2
# 
#  Modif : suppression controleEnable, gerer direct dans lib
#
#  MIT Licence

######################################################
from math import*

import serial
import time
import os

###############################################################
###############################################################

__all__ = ['firmwareVersion']
__all__ = ['switch']
__all__ = ['battery']
__all__ = ['proxSensor']
__all__ = ['forward']
__all__ = ['controlEnable']
__all__ = ['controlDisable']
__all__ = ['forwardC']
__all__ = ['back']
__all__ = ['backC']
__all__ = ['stop']
__all__ = ['turnRight']
__all__ = ['turnRightC']
__all__ = ['turnLeft']
__all__ = ['turnLeftC']
__all__ = ['turnRight_degree']
__all__ = ['turnLeft_degree']
__all__ = ['forward_mm']
__all__ = ['back_mm']
__all__ = ['motorRight']
__all__ = ['motorLeft']
__all__ = ['motorsWrite']
__all__ = ['robotPositionX']
__all__ = ['robotPositionY']
__all__ = ['robotPositionO']
__all__ = ['encoderLeft']
__all__ = ['encoderRight']
__all__ = ['readVusb']
__all__ = ['resetUc']
__all__ = ['writeCommand']
__all__ = ['readData']
__all__ = ['forwardmm']
__all__ = ['backmm']
__all__ = ['turnRightDegree']
__all__ = ['turnLeftDegree']
__all__ = ['robotGo']
__all__ = ['motorLeftSpeed']
__all__ = ['motorRightSpeed']
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
  writeCommand("FV")
  value = readData()
  return __convListToFloat(value)
  
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
  writeCommand("SW")
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
  writeCommand("BAT")
  value = readData()
  return __convListToFloat(value) 
  
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
    port.write("#PROX,")
    port.write( str(sensor) )
    port.write("!")
    value = readData()
    return __convListToUint(value)
  
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
    port.write("#MF,")
    port.write(speed)
    port.write("!")
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
    writeCommand("CRE")
  else:
    print "error : control is already enable !"

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
    writeCommand("CRD")

# the robot move forward with control
def forwardC(speed, distance):
  """
        move forward mrpi1 with control
        Exemple:
        >> forwardC(20, 4000)
  """
  if check_speed(speed,distance) == 0:
    return 0
	
  #if control_robot == True:

  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  port.write("#MFC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")

  port.flushInput() # reset serial receive buffer

  while True:
    time.sleep(0.1)
    state = 0
    port.flushInput() # reset serial receive buffer
    writeCommand("TGS,1")
    state = readData()
    if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == '4'):
        print "error : speed to hight"
        return 0
      chaine = 0
      return 1# end while 1
  '''else:
  print "error : control robot disable"'''
  
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
  
  print "Forward with control enable"

  distance = int(distance)
  speed = str(speed)
  distance = str(distance*4)#conversion en mm
  port.write("#MFC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")


# the robot move forward with control
def backmm(speed, distance):
  """
        move forward mrpi1 with control
        Exemple:
        >> forwardC(20, 4000)
  """
  controlEnable()
  if check_speed(speed,distance) == 0:
    return 0
	
  #if control_robot == True:
  
  print "Forward with control enable"

  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  port.write("#MBC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")

# the robot move forward with control (distance : millimeter)
def forward_mm(speed, distance):
  controlEnable()
  forwardC(speed, distance*4)

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
    port.write("#MB,")
    port.write(speed)
    port.write("!")
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
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  port.write("#MBC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  print "move back with control"
  
  port.flushInput() # reset serial receive buffer
  
  while True:
    time.sleep(0.1)
    writeCommand("TGS,1")
    state = readData()
    if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == '4'):
        print "error : speed to hight"
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
  writeCommand("STP")
 
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
    port.write("#TR,")
    port.write(speed)
    port.write("!")
  else:
    print("error speed value")



# the robot turn right with control
def turnRightDegree(speed, distance):
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
  controlEnable()
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  port.write("#TRC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  port.flushInput() # reset serial receive buffer

# the robot turn right with control
def turnLeftDegree(speed, distance):
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
  controlEnable()
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  port.write("#TLC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  port.flushInput() # reset serial receive buffer

'''
def turnRight(speed):
  __turnRightControl(speed,99999)
'''  
  
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
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  port.write("#TRC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  port.flushInput() # reset serial receive buffer

  while True:
    time.sleep(0.1)
    writeCommand("TGS,2")
    state = readData()
    if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == '4'):
        print "error : speed to hight"
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
    port.write("#TL,")
    port.write(speed)
    port.write("!")
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
  if check_speed(speed,distance) == 0:
    return 0
	
  distance = int(distance)
  speed = str(speed)
  distance = str(distance)
  port.write("#TLC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  port.flushInput() # reset serial receive buffer
  
  while True:
    time.sleep(0.1)
    writeCommand("TGS,2")
    state = readData()
    if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == '4'):
        print "error : speed to hight"
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
  print "angle_robot = ", angle_robot
  
  if (degree == 0.0)and(angle_robot > 180):
    print "degree == 0)and(angle_robot > 180"
    degree = 360
  elif (angle_robot == 0.0)and(degree > 180) :
    print "angle_robot == 0.0)and(degree > 180"
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


# the robot turn right with control 
def turnLeftDegree(speed, degree):
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
  controlEnable()
  if check_speed(speed,degree) == 0:
    return 0
	
  degree = int(degree*6)
  speed = str(speed)
  degree = str(degree)
  port.write("#TLC,")
  port.write(degree)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  
# the motor right
def motorRight(direction, speed):
  """
        motor right control
        parameter 1 : direction (0 or 1)
        parameter 2 : speed ( 0 to 100)     
        Exemple:
        >> motorRigh(1, 50)
  """
  dir = str(direction)
  pwm = str(speed)
  port.write("#MOTR,")
  port.write(dir)
  port.write(",")
  port.write(pwm)
  port.write("!")

# the motor left
def motorLeft(direction, speed):
  """
        motor left control
        parameter 1 : direction (0 or 1)
        parameter 2 : speed ( 0 to 100)     
        Exemple:
        >> motorLeft(1, 50)
  """
  dir = str(direction)
  pwm = str(speed)
  port.write("#MOTL,")
  port.write(dir)
  port.write(",")
  port.write(pwm)
  port.write("!")
  
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
  port.write("#MOTS,")
  port.write(speedRight)
  port.write(",")
  port.write(speedLeft)
  port.write("!")

  
########################################
# robot go (X and Y Coordinate),
# speed : speed of the robot (0 to 100)
# cordX : Coordinate axe X (millimeter)
# cordY : Coordinate axe Y (millimeter)

def robotGo(MaxSpeed, cordX, cordY):
  posX = robotPositionX()
  posY = robotPositionY()
  posA = robotPositionOrientation()
  
  # calcul de la distance a parcourir
  consigneDistance = sqrt( pow(cordX-posX,2)+pow(cordY-posY,2) )
  
  # calcul de l'orientation de consigne du robot
  consigneOrientation = atan2( coord_Y-posY, coord_X-posX)
  
  # calcul erreur en distance
  erreurDistance = consigneDistance;
  if(erreurDistance > ERR_DIS_SAT):
    erreurDistance = ERR_DIS_SAT

  # calcul erreur en orientation
  erreurOrientation = consigneOrientation - posA;
  if(erreurOrientation > M_PI):
    erreurOrientation -= M_2PI
  if(erreurOrientation < -M_PI):
   erreurOrientation += M_2PI
  
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
  writeCommand("POX")
  value = readData()
  value = __convListToFloat(value) 
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
  writeCommand("POY")
  value = readData()
  value = __convListToFloat(value) 
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
  writeCommand("POO")
  value = readData()
  value = __convListToFloat(value) 
  
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
  writeCommand("MLS")
  value = readData()
  value = __convListToFloat(value) 
  return (value)
  
# read robot orientation
def motorRightSpeed():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("MRS")
  value = readData()
  value = __convListToFloat(value) 
  return (value)
  
  
# motors disable
def motorsDisable():
  writeCommand("MDI")
  
# motors enable
def motorsEnable():
  writeCommand("MEN")
  
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
    frequency = str(frequency)
    port.write("#BUZ,")
    port.write(frequency)
    port.write("!")
  else:
    print("error frequency value")

# buzzer start
def buzzerStart():
  writeCommand("BUZD")
  
# buzzer stop
def buzzerStop():
  writeCommand("BUZS")
  
# led RGB
def ledRGB(red,green,blue):
  red = str(red)
  green = str(green)
  blue = str(blue)
  port.write("#RGB,")
  port.write(red)
  port.write(",")
  port.write(green)
  port.write(",")
  port.write(blue)
  port.write("!")
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
  writeCommand("EDL")
  value = readData()
  return __convListToUint(value)
  
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
  writeCommand("EDR")
  value = readData()
  return __convListToUint(value)
 
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
  writeCommand("VUSB")
  value = readData()
  return __convListToFloat(value) 
 
#---------------------------------------------------------------------
#-------------[ MRPiZ reset uc robot methods]------------------------------

# reset microcontroller
def resetUc():
  """
        Reset microcontroller
        Exemple:
        >> resetUc()
  """
  writeCommand("RST")
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
  port.write("#SRLW,")
  port.write(data)
  port.write("!")
  

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
  while i < (len(liste)):
    a = a + liste[i]
    i = i + 1
  return(int(a))

# write command
def writeCommand(command):
  port.write('#')
  port.write(command)
  port.write('!')
  
# read data
def readData():
  chaine = port.readline()
  pos1 = chaine.find('$')
  pos2 = chaine.find('\n')
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
def __forwardControl(speed, distance):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print "Forward with control enable"
    distance = int(distance)
    speed = str(speed)
    distance = str(distance)
    port.write("#MFC,")
    port.write(distance)
    port.write(",")
    port.write(speed)
    port.write("!")
    port.flushInput() # reset serial receive buffer
  else:
    print "error : control robot disable"
  
# the robot move forward with control (pas d'attente de la fin du trapeze)
def __backControl(speed, distance):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print "Forward with control enable"
    distance = int(distance)
    speed = str(speed)
    distance = str(distance)
    port.write("#MBC,")
    port.write(distance)
    port.write(",")
    port.write(speed)
    port.write("!")
    port.flushInput() # reset serial receive buffer
  else:
    print "error : control robot disable"

	
# the robot move forward with control (pas d'attente de la fin du trapeze)
def __turnLeftControl(speed, angle):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print "Forward with control enable"
    angle = int(angle)
    speed = str(speed)
    angle = str(angle)
    port.write("#TLC,")
    port.write(angle)
    port.write(",")
    port.write(speed)
    port.write("!")
    port.flushInput() # reset serial receive buffer
  else:
    print "error : control robot disable"


# the robot move forward with control (pas d'attente de la fin du trapeze)
def __turnRightControl(speed, angle):
  """
        move forward mrpi1 with control
  """
  controlEnable()

  if control_robot == True:
    print "Forward with control enable"
    angle = int(angle)
    speed = str(speed)
    angle = str(angle)
    port.write("#TRC,")
    port.write(angle)
    port.write(",")
    port.write(speed)
    port.write("!")
    port.flushInput() # reset serial receive buffer
  else:
    print "error : control robot disable"


# control robot (postion/orientation disable)
control_robot = False

# reset Uc
resetUc()
 
# end file