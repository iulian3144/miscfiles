#!/usr/bin/env python
import numpy as np
import cv2
import glob

# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((6*7,3), np.float32)
objp[:,:2] = np.mgrid[0:7,0:6].T.reshape(-1,2)

# Arrays to store object points and image points from all the images.
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

_WIDTH = 320
_HEIGHT = 240
capture = None
CAP_FROM_CAMERA = False
if CAP_FROM_CAMERA:
    capture = cv2.VideoCapture(0)
    capture.set(cv2.CAP_PROP_FRAME_WIDTH, _WIDTH)
    capture.set(cv2.CAP_PROP_FRAME_HEIGHT, _HEIGHT)

images = glob.glob('/home/ipaun1/Pictures/Webcam/*.jpg')


if CAP_FROM_CAMERA and not capture.isOpened():
    exit(-1)
# while True:
for fname in images:
    # _, img = capture.read()
    img = cv2.resize(cv2.imread(fname, 1), (512, 384))
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Find the chess board corners
    ret, corners = cv2.findChessboardCorners(gray, (6,6),None)

    # If found, add object points, image points (after refining them)
    # print ret
    if ret == True:
        objpoints.append(objp)

        corners2 = cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
        imgpoints.append(corners2)

        # Draw and display the corners
        img = cv2.drawChessboardCorners(img, (6,6), corners2,ret)
    cv2.imshow('img',img)
    delay = 50
    if ret:
        delay = 1000
    k = cv2.waitKey(delay) & 0xFF
    if k == 27:
        break



# cv2.destroyAllWindows()

img = cv2.imread(images[0])
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
print "Calibrate camera"
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)
print "Done calibrating"

h, w = img.shape[:2]
print "Get optimal camera matrix"
newcamera_mtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))
print "[get optimal camera matrix] done"

print "Undistort image"
dst = cv2.undistort(img, mtx, dist, None, newcamera_mtx)
print "[Undistort image] done"

cv2.imshow('undistorted', dst)
cv2.waitKey(0)


# print objpoints
cv2.destroyAllWindows()
