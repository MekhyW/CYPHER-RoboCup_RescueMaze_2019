# Untitled - By: dell 1 - ter fev 12 2019

import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.SIF)
sensor.set_auto_exposure(True)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
sensor.set_contrast(3)

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.draw_circle(176, 120, 90)
    print(clock.fps())
