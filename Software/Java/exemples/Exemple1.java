import java.io.IOException;
import java.util.Date;
import java.util.concurrent.TimeUnit;

public class Exemple1 {

/****************/
public static void main(String args[]) throws InterruptedException, IOException
{
float tension_batterie;
float distance_sensor1;
float distance_sensor2;

MRPiZ robot = new MRPiZ();

// Lecture de la tension de la batterie
tension_batterie = robot.proxSensor(1);
System.out.println("Batterie = " + tension_batterie);

// avancer le robot pendant 1 seconde
robot.forward(30);

TimeUnit.SECONDS.sleep(2);

// reculer le robot pendant 1 seconde
robot.back(30);

TimeUnit.SECONDS.sleep(2);

// tourner à droite
robot.turnRight(30);

TimeUnit.SECONDS.sleep(1);

// arret du robot
robot.stop();

// Lecture du capteur de proximitè n°1 et n°2
distance_sensor1 = robot.proxSensor(1);
distance_sensor2 = robot.proxSensor(2);

// afficher les valeurs
System.out.println("Sensor 1 = " + distance_sensor1);
System.out.println("Sensor 2 = " + distance_sensor2);

}
}
