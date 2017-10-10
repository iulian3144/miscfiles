#!/usr/bin/env python

import cv2
import numpy as np

vc = cv2.VideoCapture(0)

def nothing(x):
    pass

def region_of_interest(img, vertices):
    mask = np.zeros_like(img)

    if len(img.shape) > 2:
        channel_count = img.shape[2]  # i.e. 3 or 4 depending on your image
        ignore_mask_color = (255,) * channel_count
    else:
        ignore_mask_color = 255

    # filling pixels inside the polygon defined by "vertices" with the fill color
    cv2.fillPoly(mask, vertices, ignore_mask_color)

    # returning the image only where mask pixels are nonzero
    masked_image = cv2.bitwise_and(img, mask)

    return masked_image

def main():
    cv2.namedWindow('canny_edges')
    cv2.namedWindow('image')

    gray_image = cv2.imread('street_lanes.jpeg', cv2.IMREAD_GRAYSCALE)
    print "shape:", gray_image.shape
    height, width = gray_image.shape
    lower_left = [width/9, height]
    lower_right = [width-width/9,height]
    top_left = [width/2-width/8,height/2+height/10]
    top_right = [width/2+width/8,height/2+height/10]
    vertices = [np.array([lower_left,top_left,top_right,lower_right],dtype=np.int32)]
    # roi = region_of_interest(gray_image, vertices)
    # print "roi.shape:", roi.shape
    mask_white = cv2.inRange(gray_image, 200, 255)
    masked_image = cv2.bitwise_or(gray_image, mask_white)
    kernel_size = 5
    gauss_gray = cv2.GaussianBlur(masked_image, (kernel_size, kernel_size), 0)
    low_threshold = 70
    high_threshold = 100
    cv2.createTrackbar('Low_threshold', 'canny_edges', 0, 255, nothing)
    cv2.createTrackbar('High_threshold', 'canny_edges', 0, 255, nothing)
    cv2.createTrackbar('threshold', 'image', 0, 255, nothing)
    cv2.createTrackbar('max_linelen', 'image', 0, 255, nothing)
    cv2.createTrackbar('max_linegap', 'image', 0, 255, nothing)

    cv2.setTrackbarPos('Low_threshold', 'canny_edges', 130)
    cv2.setTrackbarPos('High_threshold', 'canny_edges', 210)
    while 1:
        _, img = vc.read(cv2.IMREAD_GRAYSCALE)
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        threshold = cv2.getTrackbarPos('threshold', 'image')
        gray_img = cv2.GaussianBlur(gray_img, (5,5), 0)
        low_threshold = cv2.getTrackbarPos('Low_threshold', 'canny_edges')
        high_threshold = cv2.getTrackbarPos('High_threshold', 'canny_edges')
        max_linelen = cv2.getTrackbarPos('max_linelen', 'canny_edges')
        max_linegap = cv2.getTrackbarPos('max_linegap', 'canny_edges')
        canny_edges = cv2.Canny(gray_img, low_threshold, high_threshold)
        # roi = region_of_interest(canny_edges, vertices)
        lines = cv2.HoughLinesP(canny_edges, 1, np.pi/180, threshold, max_linelen, max_linegap)
        if lines is not None:
            for x1,y1,x2,y2 in lines[0]:
                # print len(lines[0])
                # exit()
                cv2.line(img, (x1,y1), (x2,y2), (10,10,240), 2)

        # cv2.imshow("gaussian blur", gauss_gray)
        cv2.imshow("image", img)
        cv2.imshow("canny_edges", canny_edges)

        k = cv2.waitKey(1) & 0xFF
        if k == 27:
            break

if __name__ == "__main__":
    main()
