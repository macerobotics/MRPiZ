/**
  ******************************************************************************
  * @file    MRPiZ.c
  * @author  Mace Robotic - www.macerobotics.com
  * @version V1.2
  * @date    15/10/2020
  * @brief
  *
 *******************************************************************************/
#include "MRPiZ.h"


static void writeCommand2parm(char *cmd, unsigned int param1, int param2);
static void writeCommand3parm(char *cmd, unsigned int param1, int param2, int param3);
static void writeCommand1parm(char *cmd, unsigned int param1);
static void writeCommand(char *cmd);
static int readInt(void);
static float readFloat(void);
static char readChar(void);

int uart_file;
 
/**********************************************************
 * @brief  initialisation robot communication
 * @param  None
 * @retval None
**********************************************************/
int init(void)
{
struct termios serial, options;

  uart_file = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);

  if (uart_file == -1)
  {
    printf("error init");
    return -1;
  }

  tcgetattr(uart_file, &options);
  options.c_cflag = B230400 | CS8 | CLOCAL | CREAD;		//<Set baud rate
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart_file, TCIFLUSH);
  tcsetattr(uart_file, TCSANOW, &options);
  
  // control disable
  controlDisable();
  
  stop();

}


/**********************************************************
 * @brief  forward the robot
 * @param  speed (0 to 100)
 * @retval None
**********************************************************/
void forward(unsigned int speed)
{
  if(speed <= 100)
  {
    writeCommand1parm("MF",speed);
  }
  else
  {
    printf("Error speed. \n");
  }
}


/**********************************************************
 * @brief  back
 * @param  Speed (0 to 100)
 * @retval None
**********************************************************/
void back(unsigned int speed)
{
  if(speed <= 100)
  {
    writeCommand1parm("MB",speed);
  }
  else
  {
    printf("Error speed. \n");
  }
}


/**********************************************************
 * @brief  stop the robot
 * @param  None
 * @retval None
**********************************************************/
void stop(void)
{
  writeCommand("STP");
}


/**********************************************************
 * @brief  turnRight
 * @param  speed : 0 to 100
 * @retval None
**********************************************************/
void turnRight(unsigned int speed)
{
  if(speed <= 100)
  {
    writeCommand1parm("TR",speed);
  }
  else
  {
    printf("Error speed. \n");
  }
}


/**********************************************************
 * @brief  turnLeft 
 * @param  speed : 0 to 100
 * @retval None
**********************************************************/
void turnLeft(unsigned int speed)
{
  if(speed <= 100)
  {
    writeCommand1parm("TL",speed);
  }
  else
  {
    printf("Error speed. \n");
  }
}


/**********************************************************
 * @brief  motorRight 
 * @param  direction and speed : 0 to 100
 * @retval None
**********************************************************/
void motorRight(MotorDirection direction, unsigned int speed)
{
char str[100];
char s_id[100];
char s_state[100];

  if( ((direction == FORWARD)||(direction == BACK)) &&(speed <= 100) )
  {
    writeCommand2parm("MOTR",direction,speed);
  }
  else
  {
    printf("Error parameter. \n");
  }
}


/**********************************************************
 * @brief  motorLeft 
 * @param  direction and speed : 0 to 100
 * @retval None
**********************************************************/
void motorLeft(MotorDirection direction, unsigned int speed)
{
  if( ((direction == FORWARD)||(direction == BACK)) &&(speed <= 100) )
  {
    writeCommand2parm("MOTL",direction,speed);
  }
  else
  {
    printf("Error parameter. \n");
  }
}


/**********************************************************
 * @brief  firmwareVersion 
 * @param  None
 * @retval float firmware version
**********************************************************/
float firmwareVersion(void)
{
float version;

  // Send the command
  writeCommand("FV");
  
  // Read the firmware version
  version = readFloat();
 
  return version;
}


/**********************************************************
 * @brief  Switch 
 * @param  None
 * @retval switch state (0 or 1)
**********************************************************/
unsigned int Switch(void)
{
unsigned int state;

  // Send the command
  writeCommand("SW");
  
  // Read the switch
  state = readInt();
 
  return state;
}


/**********************************************************
 * @brief  read the battery tension 
 * @param  None
 * @retval None
**********************************************************/
float battery(void)
{
float tension;

  // Send the command
  writeCommand("BAT");
  
  // Read version
  tension = readFloat();
 
  return tension;
  
}


/**********************************************************
 * @brief  read the proximity sensor
 * @param  sensor number
 * @retval distance value
**********************************************************/
unsigned int proxSensor(unsigned int sensor)
{
unsigned int prox=0;

  if((sensor <= NUMBER_PROX_SENSORS)&&(sensor > 0))
  {
    // Send the command
    writeCommand1parm("PROX", sensor);
  
    // Read prox sensor
    prox = readInt();
  }
  else
  {
   printf("Error sensor number \n");
  }
 
  return prox;
}


/**********************************************************
 * @brief  read the encoder left
 * @param  none
 * @retval counter
**********************************************************/
int encoderLeft()
{
int counter=0;

  // Send the command
  writeCommand("EDL");
  
  // Read encoder
  counter = readInt();
  
  return -counter;
}


/**********************************************************
 * @brief  read the encoder right
 * @param  none
 * @retval counter
**********************************************************/
int encoderRight()
{
int counter=0;

  // Send the command
  writeCommand("EDR");
  
  // Read encoder
  counter = readInt();
  
  return -counter;
}


/**********************************************************
 * @brief  controle enable
 * @param  none
 * @retval value
**********************************************************/
void controlEnable(void)
{
  // Send the command
  writeCommand("CRE");
}


/**********************************************************
 * @brief  controle enable
 * @param  none
 * @retval value
**********************************************************/
void controlDisable(void)
{
  // Send the command
  writeCommand("CRD");
}


/**********************************************************
 * @brief  forward with control
 * @param  none
 * @retval value
**********************************************************/
void forwardC(unsigned int speed, unsigned int distance)
{
int value=0;

  writeCommand2parm("MFC",distance,speed);
  
  while(value != 3)
  {
    usleep(10);
    writeCommand("TGS,1");    
    value = readInt();
    
    if(value == 4)
    {
      printf("error : speed to hight\n");
      value = 3;
    }
  }
 
}


/**********************************************************
 * @brief  forward with control 
 * @param  speed (0 to 100), distance (mm)
 * @retval value
**********************************************************/
void forward_mm(unsigned int speed, unsigned int distance_mm)
{
  forwardC(speed,distance_mm*4);
}


/**********************************************************
 * @brief  back with control 
 * @param  speed (0 to 100), distance (mm)
 * @retval value
**********************************************************/
void back_mm(unsigned int speed, unsigned int distance_mm)
{
  backC(speed,distance_mm*4);
}


/**********************************************************
 * @brief  turnRight_degree 
 * @param  angle (degree)
 * @retval value
**********************************************************/
void turnRight_degree(unsigned int speed, unsigned int angle)
{
  turnRightC(speed,angle*546/90);
}


/**********************************************************
 * @brief  turnRight_degree 
 * @param  angle (degree)
 * @retval value
**********************************************************/
void turnLeft_degree(unsigned int speed, unsigned int angle)
{
  turnLeftC(speed,angle*546/90);
}


/**********************************************************
 * @brief  back with control
 * @param  none
 * @retval value
**********************************************************/
void backC(unsigned int speed, unsigned int distance)
{
int value=0;

  writeCommand2parm("MBC",distance,speed);
  
  while(value != 3)
  {
    usleep(10);
    writeCommand("TGS,1");    
    value = readInt();
    
    if(value == 4)
    {
      printf("error : speed to hight\n");
      value = 3;
    }
  }
 
}

/**********************************************************
 * @brief  turnRightC
 * @param  none
 * @retval value
**********************************************************/
void turnRightC(unsigned int speed, unsigned int distance)
{
int value=0;

  writeCommand2parm("TRC",distance,speed);
  
  while(value != 3)
  {
    usleep(10);
    writeCommand("TGS,2");    
    value = readInt();
    
    if(value == 4)
    {
      printf("error : speed to hight\n");
      value = 3;
    }
  }
 
}


/**********************************************************
 * @brief  turnRightC
 * @param  none
 * @retval value
**********************************************************/
void turnLeftC(unsigned int speed, unsigned int distance)
{
int value=0;

  writeCommand2parm("TLC",distance,speed);
  
  while(value != 3)
  {
    usleep(10);
    writeCommand("TGS,2");    
    value = readInt();
    
    if(value == 4)
    {
      printf("error : speed to hight\n");
      value = 3;
    }
  }
 
}


/**********************************************************
 * @brief  read USB voltage
 * @param  None
 * @retval usb tension
**********************************************************/
float readVusb(void)
{
float tension=0;

  // Send the command
  writeCommand("VUSB");
  
  // Read version
  tension = readFloat();
 
  return tension;
  
}


/**********************************************************
 * @brief  robotPositionX
 * @param  None
 * @retval robot position (mm units)
**********************************************************/
float robotPositionX(void)
{
float pos=0;

  // Send the command
  writeCommand("POX");
  
  // Read position
  pos = readFloat();
 
  return pos;
  
}


/**********************************************************
 * @brief  robotPositionY
 * @param  None
 * @retval robot position (mm units)
**********************************************************/
float robotPositionY(void)
{
float pos=0;

  // Send the command
  writeCommand("POY");
  
  // Read position
  pos = readFloat();
 
  return pos;
  
}


/**********************************************************
 * @brief  robotPositionO
 * @param  None
 * @retval robot orientation 
**********************************************************/
float robotPositionO(void)
{
float orientation=0;

  // Send the command
  writeCommand("POO");
  
  // Read orientation
  orientation = readFloat();
 
  return orientation;
  
}


/**********************************************************
 * @brief  buzzer
 * @param  None
 * @retval  
**********************************************************/
void buzzer(unsigned int frequency)
{
  // Send the command
  writeCommand1parm("BUZ", frequency);
 
}


/**********************************************************
 * @brief  buzzerStop
 * @param  None
 * @retval  
**********************************************************/
void buzzerStop(void)
{
  // Send the command
  writeCommand("BUZS");	
}


/**********************************************************
 * @brief  ledRGB
 * @param  None
 * @retval  
**********************************************************/
void ledRGB(unsigned int red,unsigned int green, unsigned int blue )
{
  writeCommand3parm("RGB", red, green, blue);
}


/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************
Private functions
**********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/

/**********************************************************
 * @brief  write command with 2 parameters
 * @param  Command , parameter 1 and parameter 2
 * @retval None
**********************************************************/
static void writeCommand2parm(char *cmd, unsigned int param1, int param2)
{
char str[100];
char s_param1[100];
char s_param2[100];

  // Conv int to char
  sprintf (s_param1, "%d", param1);
  sprintf (s_param2, "%d", param2);
  
  strcpy(str, "#");
  strcat(str, cmd);
  strcat(str,",");
  strcat(str, s_param1);
  strcat(str,",");
  strcat(str, s_param2);
  strcat(str,"!");
  
  write(uart_file, str, strlen(str));
  
}

/**********************************************************
 * @brief  write command with 1 parameters
 * @param  Command , parameter 1 
 * @retval None
**********************************************************/
static void writeCommand1parm(char *cmd, unsigned int param1)
{
char str[100];
char s_param1[100];

  // Conv int to char
  sprintf (s_param1, "%d", param1);
  
  strcpy(str, "#");
  strcat(str, cmd);
  strcat(str,",");
  strcat(str, s_param1);
  strcat(str,"!");
  
  write(uart_file, str, strlen(str));  
}

/**********************************************************
 * @brief  write command without parameter
 * @param  Command
 * @retval None
**********************************************************/
static void writeCommand(char *cmd)
{
char str[100];
  
  strcpy(str, "#");
  strcat(str, cmd);
  strcat(str,"!");
  
  write(uart_file, str, strlen(str));  
}


/**********************************************************
 * @brief  write command with 3 parameters
 * @param  Command , parameter 1, parameter 2, parameter 3
 * @retval None
**********************************************************/
static void writeCommand3parm(char *cmd, unsigned int param1, int param2, int param3)
{
char str[100];
char s_param1[100];
char s_param2[100];
char s_param3[100];

  // Conv int to char
  sprintf (s_param1, "%d", param1);
  sprintf (s_param2, "%d", param2);
  sprintf (s_param3, "%d", param3);

  
  strcpy(str, "#");
  strcat(str, cmd);
  strcat(str,",");
  strcat(str, s_param1);
  strcat(str,",");
  strcat(str, s_param2);
  strcat(str,",");
  strcat(str, s_param3);
  strcat(str,"!");
  
  write(uart_file, str, strlen(str));
  
}

/**********************************************************
 * @brief  read data type int
 * @param  Command
 * @retval None
**********************************************************/
static int readInt(void)
{
unsigned char buffer[SIZE_BUFFER_READ];
char cara=0;
int rx_length=0, data;
char * pch;

  buffer[rx_length] = 0;
  
  while(cara != '$')
  {
	cara = readChar();
  }
	  
  
  while(cara != '\n')
  {
    buffer[rx_length] = readChar();
	cara = buffer[rx_length];
	rx_length++;
  }
  
  // Convert string to integer
  data = atoi(buffer);
  
  return data ;
}


/**********************************************************
 * @brief  read data type float
 * @param  Command
 * @retval None
**********************************************************/
static float readFloat(void)
{
char buffer[10];
unsigned int rx_length=0,c;
float data=0.0;
char cara=0;
char* pEnd;

  buffer[rx_length] = 0;
  
  while(cara != '$')
  {
	cara = readChar();
  }
  
  while(cara != '\n')
  {
    buffer[rx_length] = readChar();
	cara = buffer[rx_length];
	rx_length++;
  }

  // Convert string to float
  data = strtof(buffer, &pEnd);
  
  return data ;
  
}

static char readChar(void)
{
char buffer[1];
unsigned int rx_length=0;

 // read 1 char
 while(rx_length != 1)
 {
     rx_length = read(uart_file, buffer, 1);
 }
 
 return buffer[0];

}
 
 // End Of file