import picamera

camera = picamera.PiCamera()

camera.resolution = (640, 480)

camera.capture('image.jpg')

