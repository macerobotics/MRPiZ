#!/usr/bin/python
import picamera
import cv2
import time

print "HSV conversion"

camera = picamera.PiCamera()

# initialisation de la resolution
camera.resolution = (1920, 1080)

print "reso"

# capture d'une image
camera.capture('image.jpg')


# lecture de l'image
frame = cv2.imread('image.jpg')

# conversion RGB en HSV de l'image
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

# enregistrer image hsv
cv2.imwrite('image_hsv.png', hsv)
