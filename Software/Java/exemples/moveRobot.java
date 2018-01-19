
import java.io.IOException;
import java.util.Date;
import  java.util.concurrent.TimeUnit;


public class moveRobot {
	
	/****************/
    public static void main(String args[]) throws InterruptedException, IOException {
		 
		 MRPiZ robot = new MRPiZ();
		 
		 robot.forward(30);
		 
		 TimeUnit.SECONDS.sleep(2);
		 
		 robot.turnLeft(30);
		 
		 TimeUnit.SECONDS.sleep(1);
		 
		 robot.turnRight(30);
		 
		 TimeUnit.SECONDS.sleep(1);
		 
		 robot.stop();

    }
	
	
	
}

