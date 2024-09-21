import cv2
import time
import numpy as np
# Metal Minds WRO 2024 Future Engineers

print("Starting...")


draw_color = [0, 255, 0]  #color for drawing 
object_color = draw_color
ptime, ctime = 0, 0
camera = cv2.VideoCapture(0)
crop = 50 #cut image from right and left with pixels
color_name = 'null'
# --------------------------------------------|
# --------------------------------------------|

def set_pins(red, green):
    try:
        import RPi.GPIO as GPIO
        GPIO.setmode(GPIO.BCM)  
        GPIO.setup(19, GPIO.OUT)  #red for RGB led
        GPIO.setup(13, GPIO.OUT)  #green for RGB led
        GPIO.setup(26, GPIO.OUT)  #blue for RGB led
        GPIO.setup(5, GPIO.OUT)   #red for arduino
        GPIO.setup(6, GPIO.OUT)   #green for arduino

        if red and green:
            GPIO.output(19, GPIO.HIGH) 
            GPIO.output(26, GPIO.HIGH)
            GPIO.output(5, GPIO.HIGH)
            GPIO.output(6, GPIO.HIGH)
        elif red == False and green == False:   #turn off RGB led
            GPIO.output(19, GPIO.LOW)
            GPIO.output(13, GPIO.LOW)
            GPIO.output(26, GPIO.LOW)
            GPIO.output(5, GPIO.LOW)   
            GPIO.output(6, GPIO.LOW) 
        else:
            if red:
                GPIO.output(19, GPIO.HIGH)
                GPIO.output(5, GPIO.HIGH)
            else:
                GPIO.output(19, GPIO.LOW)
                GPIO.output(5, GPIO.LOW)

            if green:
                GPIO.output(13, GPIO.HIGH)
                GPIO.output(6, GPIO.HIGH)

            else:
                GPIO.output(13, GPIO.LOW)
                GPIO.output(6, GPIO.LOW)

    except:
        print("Its not RPI")

def detect_color(image, s):   #function for detecting color on image
    hsvc = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)  #converting BGR to HSV

    if s == 0:
        lowlimit1 = np.array([0, 120, 120])
        highlimit1 = np.array([5, 255, 255])
        lowlimit2 = np.array([175, 120, 120])
        highlimit2 = np.array([180, 255, 255])

        red_mask1 = cv2.inRange(hsvc, lowlimit1, highlimit1)
        red_mask2 = cv2.inRange(hsvc, lowlimit2, highlimit2)
        red_mask = cv2.bitwise_or(red_mask1, red_mask2)
        return red_mask
    elif s == 1:
        lowlimit_green = np.array([40, 50, 50])
        highlimit_green= np.array([90, 255, 255])
        green_mask = cv2.inRange(hsvc, lowlimit_green, highlimit_green)
        return green_mask
    elif s == 2:
        lowlimit_violet = np.array([110, 50, 50])
        highlimit_violet = np.array([140, 255, 255])
        violet_mask = cv2.inRange(hsvc, lowlimit_violet, highlimit_violet)
        return violet_mask 
    



while True:
    success, img = camera.read()
    height, width, _ = img.shape
    img = img[:, crop:width - crop]
    height, width, _ = img.shape

    mask = detect_color(image=img,  s = 0)
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) 
    if hierarchy is not None and len(contours)> 0:
        object_color = [0, 0, 255]
        color_name = 'red'
    else:
        mask = detect_color(image=img,  s = 1)
        contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if hierarchy is not None and len(contours)> 0:   
            object_color = [0, 255, 0]
            color_name = 'green'
        else:
            mask = detect_color(image=img,  s = 2)
            contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
            if hierarchy is not None and len(contours) > 0:  
                object_color = [255, 0, 255]
                color_name = 'violet'
            else:
                color_name = 'null'
                print("Not detecting...")
                set_pins(0, 0)

    for pic, contour in enumerate(contours): 
        area = cv2.contourArea(contour) 

        if(area > 600): 
            x, y, w, h = cv2.boundingRect(contour) 
            img = cv2.rectangle(img, (x, y),  (x + w, y + h), draw_color, 2) #draw rectangle around object
            cx, cy = int(x+w/2), int(y+h/2)                                     #center point for object
            img = cv2.line(img, (cx, 0), (cx, height), draw_color, thickness = 2)  
            img = cv2.rectangle(img, (width-40, 20), (width - 20, 80), object_color, thickness = -1)
            print(color_name)
            if color_name == 'green':
                set_pins(0, 1)
                print('left')
            elif color_name == 'red':
                set_pins(1, 0)
                print('right')
            elif color_name == 'violet':
                set_pins(0, 0)
                print('violet')
            else:
                set_pins(0, 0)

               
            break  
    else:
        color_name = 'null'
        print('Not detecting...')
        set_pins(0, 0)

#FPS Calculation
    ctime = time.time()
    fps = 1/(ctime-ptime)
    ptime = ctime
    cv2.putText(img, f"FPS: {int(fps)}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, draw_color, 2)
    
    
    cv2.imshow('mask',mask)      # mask
    cv2.imshow('Test', img)      #show image with detections
    k= cv2.waitKey(1) 
    if k ==  ord('q'):
        break
    
camera.release()
cv2.destroyAllWindows()
