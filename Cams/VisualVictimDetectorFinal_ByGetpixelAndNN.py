import sensor, image, time, math
from pyb import LED,UART,Pin,Servo
import sensor, image, time, os, nn
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQSIF)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
sensor.set_auto_exposure(True)
sensor.skip_frames(time=100)
sensor.set_contrast(3)
ImageX = 88
ImageY = 60
thresholds = (0, 50)
uart = UART(3, 9600, timeout_char=10)
uart.init(9600)
clock = time.clock()

net = nn.load('/fnt-chars74k.network')
labels = ['n/a', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
for i in range(ord('A'), ord('Z') + 1): labels.append(chr(i))
for i in range(ord('a'), ord('z') + 1): labels.append(chr(i))

blobHtop = 255
blobHbottom = 255
blobHleft = 0
blobHright = 0
blobHtopleft = 0
blobHtopright = 0
blobHbottomleft = 0
blobHbottomright = 0

blobStop = 0
blobSbottom = 0
blobSleft = 255
blobSright = 255
blobStopleft = 255
blobStopright = 255
blobSbottomleft = 255
blobSbottomright = 255

blobUtop = 255
blobUbottom = 0
blobUleft = 0
blobUright = 0
blobUtopleft = 0
blobUtopright = 0
blobUbottomleft = 255
blobUbottomright = 255


while(True):
    clock.tick()
    img = sensor.snapshot()
    img.binary([thresholds], zero=True)
    img.cartoon(size=1, seed_threshold=1)
    img.rotation_corr(0, 0, 180, 0, 0, 1)
    blobfound=False
    for blob in img.find_blobs([thresholds], area_threshold=100, merge=False):
        if(img.get_statistics(roi=blob.rect()).stdev()<30):
            continue
        if(max(blob.w(), blob.h())/min(blob.w(), blob.h())<2 and math.sqrt(((blob.cx()-(ImageX/2))*(blob.cx()-(ImageX/2)))+((blob.cy()-(ImageY/2))*(blob.cy()-(ImageY/2))))<(ImageY/3)):
            blobfound=True
            F1SimilarityH = 255-((abs(img.get_pixel(blob.cx(), blob.y())-blobHtop)+abs(img.get_pixel(blob.cx(), blob.y()+blob.h())-blobHbottom)+abs(img.get_pixel(blob.x(), blob.cy())-blobHleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.cy())-blobHright)+abs(img.get_pixel(blob.x(), blob.y())-blobHtopleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.y())-blobHtopright)+abs(img.get_pixel(blob.x(), blob.y()+blob.h())-blobHbottomleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.y()+blob.h())-blobHbottomright))/8)
            F1SimilarityS = 255-((abs(img.get_pixel(blob.cx(), blob.y())-blobStop)+abs(img.get_pixel(blob.cx(), blob.y()+blob.h())-blobSbottom)+abs(img.get_pixel(blob.x(), blob.cy())-blobSleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.cy())-blobSright)+abs(img.get_pixel(blob.x(), blob.y())-blobStopleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.y())-blobStopright)+abs(img.get_pixel(blob.x(), blob.y()+blob.h())-blobSbottomleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.y()+blob.h())-blobSbottomright))/8)
            F1SimilarityU = 255-((abs(img.get_pixel(blob.cx(), blob.y())-blobUtop)+abs(img.get_pixel(blob.cx(), blob.y()+blob.h())-blobUbottom)+abs(img.get_pixel(blob.x(), blob.cy())-blobUleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.cy())-blobUright)+abs(img.get_pixel(blob.x(), blob.y())-blobUtopleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.y())-blobUtopright)+abs(img.get_pixel(blob.x(), blob.y()+blob.h())-blobUbottomleft)+abs(img.get_pixel(blob.x()+blob.w(), blob.y()+blob.h())-blobUbottomright))/8)
            out = net.forward(img, roi=blob.rect(), softmax=False)
            max_idx = out.index(max(out))
            score = int(out[max_idx]*100)
            F2SimilarityH = int(out[18]*100)
            F2SimilarityS = int(out[29]*100)
            F2SimilarityU = int(out[31]*100)
            ScoreH = (F2SimilarityH+(F1SimilarityH*(100/255)))/2
            ScoreS = (F2SimilarityS+(F1SimilarityS*(100/255)))/2
            ScoreU = (F2SimilarityU+(F1SimilarityU*(100/255)))/2
    if(blobfound==True  and (ScoreH>50 or ScoreS>50 or ScoreU>50)):
        img.draw_rectangle(blob.rect())
        if(ScoreS>=ScoreH and ScoreS>=ScoreU):
            print('S')
            uart.write('S')
            #LED(1).off()
            #LED(2).on()
            #LED(3).off()
        elif(ScoreU>=ScoreH and ScoreU>=ScoreS):
            print('U')
            uart.write('U')
            #LED(1).off()
            #LED(2).off()
            #LED(3).on()
        else:
            print('H')
            uart.write('H')
            #LED(1).on()
            #LED(2).off()
            #LED(3).off()
    else:
        print(clock.fps())
        uart.write('n')
        #LED(1).off()
        #LED(2).off()
        #LED(3).off()
