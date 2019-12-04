import sensor, image, time, math, os, nn
from pyb import LED,UART,Pin

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQSIF)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
sensor.set_auto_exposure(True)
sensor.skip_frames(time = 500)
sensor.set_contrast(3)
thresholds = (0, 50)
uart = UART(3, 9600, timeout_char=10)
uart.init(9600)
clock = time.clock()
ImageX = 88
ImageY = 60

net = nn.load('/fnt-chars74k.network')
labels = ['n/a', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
for i in range(ord('A'), ord('Z') + 1): labels.append(chr(i))
for i in range(ord('a'), ord('z') + 1): labels.append(chr(i))

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.cartoon(size=1, seed_threshold=1)
    img.binary([thresholds], zero=True)
    img.rotation_corr(0, 0, 180, 0, 0, 1)
    blobfound=False
    for blob in img.find_blobs([thresholds], area_threshold=100, merge=False):
        if(img.get_statistics(roi=blob.rect()).stdev()<50):
            continue
        if(max(blob.w(), blob.h())/min(blob.w(), blob.h())<2 and math.sqrt(((blob.cx()-(ImageX/2))*(blob.cx()-(ImageX/2)))+((blob.cy()-(ImageY/2))*(blob.cy()-(ImageY/2))))<(ImageY/3)):
            #print(img.get_statistics(roi=blob.rect()).stdev())
            blobfound=True
            out = net.forward(img, roi=blob.rect(), softmax=False)
            max_idx = out.index(max(out))
            score = int(out[max_idx]*100)
            score_H = int(out[18]*100)
            score_S = int(out[29]*100)
            score_U = int(out[31]*100)
    if(blobfound==True and (score_H>50 or score_S>50 or score_U>50)):
        img.draw_rectangle(blob.rect())
        if(score_S>=score_H and score_S>=score_U):
            uart.write('S')
            print("S:%d%% "%(score_S))
        elif(score_U>=score_H and score_U>=score_S):
            uart.write('U')
            print("U:%d%% "%(score_U))
        elif(score_H>=score_S and score_H>=score_U):
            uart.write('H')
            print("H:%d%% "%(score_H))
    else:
        print(clock.fps())
        uart.write('n')
