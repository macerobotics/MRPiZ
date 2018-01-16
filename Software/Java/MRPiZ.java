import com.pi4j.io.serial.*;
import com.pi4j.util.CommandArgumentParser;
import com.pi4j.util.Console;
import java.io.IOException;
import java.util.Date;

public class MRPiZ {   


  final Serial serial = SerialFactory.createInstance();
  
  
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
				System.out.println("RECEPTION !!!!!");
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
	
  /******************************/
  public void stop() throws IOException {

        this.serial.write("#STP!");
	}
	
	  /******************************/
  public void battery() throws IOException {

        this.serial.write("#BAT!");
	}
  
}