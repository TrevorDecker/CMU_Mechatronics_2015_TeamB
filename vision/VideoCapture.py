import numpy as np
import cv2

cap = cv2.VideoCapture(1)

#TODO add state of the robot 
#TODO add model of the window
#TODO make faster
#TODO reject small groups 
#TODO fit to a box 

height = 200
width = 200
#creates an array to store the value of pixels to keep
output = np.zeros((height,width,3))


while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    frame = resized_image = cv2.resize(frame, (height,width)) 

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    hsv  = cv2.cvtColor(frame, cv2.COLOR_RGB2HSV)
    h = hsv[0:height,0:width,0]
    s = hsv[0:height,0:width,1]
    v = hsv[0:height,0:width,2]


    for i in xrange(0,height-1):
       for j in xrange(0,width-1):
           # tests each pixel if it passes all requeirments then we 
           # set it to 1
           if( h[i,j] >= 0 and h[i,j] <= 40 and \
               s[i,j] >= 100   and s[i,j] <= 256 and \
               v[i,j] >= 127   and s[i,j] <= 256):
               pass
              # output[i,j,0] = frame[i,j,0];
              # output[i,j,1] = frame[i,j,1];
              # output[i,j,2] = frame[i,j,2];
           else:
               frame[i,j,0] = 0;
               frame[i,j,1] = 0;
               frame[i,j,2] = 0;
               

            

    # Display the resulting frame
    cv2.imshow('frame',frame)#output)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
        
    #Threashold the image 
    #TODO



    #template matching and gradient decent 
    #TODO


# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
