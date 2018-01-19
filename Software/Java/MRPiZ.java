// Version : 0.1
// Date : 17/01/2017

import com.pi4j.io.serial.*;
import com.pi4j.util.CommandArgumentParser;
import com.pi4j.util.Console;
import java.io.IOException;
import java.util.Date;
import  java.util.concurrent.TimeUnit;

public class MRPiZ {   


  final Serial serial = SerialFactory.createInstance();
  String dataReception = "";
  boolean b_data_reception  = false;
  
  
  /******************************/
  public MRPiZ() throws InterruptedException, IOException {
	  
	  
	// create serial config object
  SerialConfig config = new SerialConfig();
  
 
  config.device("/dev/ttyAMA0")
              .baud(Baud._230400)
              .dataBits(DataBits._8)
              .parity(Parity.NONE)
              .stopBits(StopBits._1)
              .flowControl(FlowControl.NONE);
			  
  
 	serial.addListener(new SerialDataEventListener() {
            public void dataReceived(SerialDataEvent event) {
			int c=0;
			String data="";

				 try {
					 
					 
					 b_data_reception = false;
					 dataReception = "";
					 
					 // lecture data
					 data = event.getAsciiString();
					 
					 
				
				     // supprimé caractère '$'
					 for (c=0;c < data.length();c++)
					 {
						 if (data.charAt(c) != '$')
						 {
						   dataReception = dataReception + data.charAt(c);
						 }
					 }
					 
					 b_data_reception = true;
					 
                } catch (IOException e) {
                    System.out.println("Erreur !!");
                }
			
            }
        }); 
	 
	
	serial.open(config);
			  


	} 
  
  /******************************/
  public void forward(int speed) throws IOException {
	StringBuilder sb = new StringBuilder();
	String command;
		
		sb.append("#MF,");
		sb.append(speed);
		sb.append("!");
		
		command = sb.toString();
		
        this.serial.write(command);
	}
	
  /******************************/
  public void back(int speed) throws IOException {
	StringBuilder sb = new StringBuilder();
	String command;
		
		sb.append("#MB,");
		sb.append(speed);
		sb.append("!");
		
		command = sb.toString();
		
        this.serial.write(command);
	}
	
  /******************************/
  public void turnLeft(int speed) throws IOException {
	StringBuilder sb = new StringBuilder();
	String command;
		
		sb.append("#TL,");
		sb.append(speed);
		sb.append("!");
		
		command = sb.toString();
		
        this.serial.write(command);
	}
	
  /******************************/
  public void turnRight(int speed) throws IOException {
	StringBuilder sb = new StringBuilder();
	String command;
		
		sb.append("#TR,");
		sb.append(speed);
		sb.append("!");
		
		command = sb.toString();
		
        this.serial.write(command);
	}
	
  /**
     * This method stop motors
     * @return none
  */
  public void stop() throws IOException {
        this.serial.write("#STP!");
	}

	
  /**
     * This method returns battery voltage
     * @return float
  */
  public float battery() throws IOException {
	  float tension;
	  
        this.serial.write("#BAT!");
		
		// attendre réception
		while (b_data_reception != true)
		{
        }
		b_data_reception = false;

		tension = Float.parseFloat(dataReception);

		return (tension);

	}
	
	
  /**
     * This method returns the firmwareVersion
     * @return float
  */
  public float firmwareVersion() throws IOException {
	  float version;
	  
        this.serial.write("#FV!");
		
		// attendre réception
		while (b_data_reception != true)
		{
        }
		b_data_reception = false;

		version = Float.parseFloat(dataReception);

		return (version);

	}
	
  /**
     * This method returns the distance sensor value
     * @return float
  */
  public float proxSensor(int sensor) throws IOException {
	  float distance;
	  String comm ="";
	    
	   comm = "#PROX," + sensor + "!";
		
      this.serial.write(comm);
		
      // attendre réception
	  while (b_data_reception != true)
	  {
      }
	  b_data_reception = false;

	  distance = Float.parseFloat(dataReception);
	  return (distance); 

	}
	
	/**
     * This method returns the encoder value
     * @return float
  */
  public float encoderLeft() throws IOException {
	  float encoder;

      this.serial.write("#EDL!");
		
      // attendre réception
	  while (b_data_reception != true)
	  {
      }
	  b_data_reception = false;

	  encoder = Float.parseFloat(dataReception);
	  return (encoder); 

	}
	
   /**
     * This method returns the encoder value
     * @return float
  */
  public float encoderRight() throws IOException {
	  float encoder;

      this.serial.write("#EDR!");
		
      // attendre réception
	  while (b_data_reception != true)
	  {
      }
	  b_data_reception = false;

	  encoder = Float.parseFloat(dataReception);
	  return (encoder); 

	}
	
  /**
     * This method returns the usb tension
     * @return float
  */
  public float readVusb() throws IOException {
	  float tension;

      this.serial.write("#VUSB!");
		
      // attendre réception
	  while (b_data_reception != true)
	  {
      }
	  b_data_reception = false;

	  tension = Float.parseFloat(dataReception);
	  return (tension); 

	}
	
  /**
     * This method returns the robot position
     * @return float
  */
  public float robotPositionX() throws IOException {
	  float position;

      this.serial.write("#POX!");
		
      // attendre réception
	  while (b_data_reception != true)
	  {
      }
	  b_data_reception = false;

	  position = Float.parseFloat(dataReception);
	  return (position); 

	}
	
	/**
     * This method returns the robot position
     * @return float
  */
  public float robotPositionY() throws IOException {
	  float position;

      this.serial.write("#POY!");
		
      // attendre réception
	  while (b_data_reception != true)
	  {
      }
	  b_data_reception = false;

	  position = Float.parseFloat(dataReception);
	  return (position); 

	}
	
  /**
     * This method returns the robot orientation
     * @return float
  */
  public float robotPositionO() throws IOException {
	  float position;

      this.serial.write("#POO!");
		
      // attendre réception
	  while (b_data_reception != true)
	  {
      }
	  b_data_reception = false;

	  position = Float.parseFloat(dataReception);
	  return (position); 

	}
	
  /**
     * 
     * @return None
  */
  public void controlEnable() throws IOException {
this.serial.write("#CRD!");
        this.serial.write("#CRE!");
	}
	
	  /**
     * 
     * @return None
  */
  public void controlDisable() throws IOException {

        this.serial.write("#CRD!");
	}
	
		  /**
     * 
     * @return None
  */
  public void forwardC(int speed, int distance) throws IOException {
	StringBuilder sb = new StringBuilder();
	String command;
		
		sb.append("#MFC,");
		sb.append(distance);
		sb.append(",");
		sb.append(speed);
		sb.append("!");
		
		command = sb.toString();
		
        this.serial.write(command);
	}
	
   /**
     * 
     * @return None
  */
  public void turnRightC(int speed, int distance) throws IOException {
	StringBuilder sb = new StringBuilder();
	String command;
		
		sb.append("#TRC,");
		sb.append(distance);
		sb.append(",");
		sb.append(speed);
		sb.append("!");
		
		command = sb.toString();
		
        this.serial.write(command);
	}
	
	   /**
     * 
     * @return None
  */
  public void turnLeftC(int speed, int distance) throws IOException {
	StringBuilder sb = new StringBuilder();
	String command;
		
		sb.append("#TLC,");
		sb.append(distance);
		sb.append(",");
		sb.append(speed);
		sb.append("!");
		
		command = sb.toString();
		
        this.serial.write(command);
	}
	
		   /**
     * 
     * @return None
  */
  public void turnRight_degree(int speed, int degree) throws IOException {
       turnRightC(speed, degree*546/90);
	}
	
	
  
}