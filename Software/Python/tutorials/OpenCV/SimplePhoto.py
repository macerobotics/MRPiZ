#!/usr/bin/python
import picamera

print "simple photo"

camera = picamera.PiCamera()

# initialisation de la resolution 
camera.resolution = (1920, 1080)

# capture d'une imag
camera.capture('image.jpg')