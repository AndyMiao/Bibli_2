#!/usr/bin/env python
from flask import Flask, render_template, Response
import base
import play_video
import time


# emulated camera
#from camera import Camera

# Raspberry Pi camera module (requires picamera package)
from camera_pi import Camera

app = Flask(__name__)

movedir = base.MoveCtrl()
movie_1 = play_video.Play_vdo()
#pan =servo.ServoController(25)
#pan.setAngle(0)

#tilt =servo.ServoController(24)
#tilt.setAngle(0)

#motorA = motor.MotorController(8,7)
#motorB = motor.MotorController(10,9)

@app.route('/')
def index():
    """Video streaming home page."""
    return render_template('index.html')

def gen(camera):
    """Video streaming generator function."""
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')
					
@app.route("/<direction>")
def moveon(direction):
	# Choose the direction of the request
	#print direction
	if direction == 'f':
		movedir.move('f')
        
	elif direction == 'l':
		movedir.move('l')

	elif direction == 'r':
		movedir.move('r')

	elif direction == 'b':
		movedir.move('b')

	elif direction =='s':
		movedir.move('s')

	elif direction =='v':
		movedir.move('v')
	elif direction == 'p':
		movie_1.play()
	elif direction == 'o':
		movie_1.stop_play()
			
	return direction

@app.route("/<movie>")
def play_movie(movie):
	print movie 
	if movie == 'p':
		movie_1.play()
	elif movie == 'o':
		movie_1.stop_play()
	return movie 

if __name__ == '__main__':
	app.run(host='192.168.1.137', threaded=True)
