#!/usr/bin/env python

import csv

FIELD_URL   = 0
FIELD_COLOR = 1
FIELD_SIZE  = 2
FIELD_QUANTITY = 3
FIELD_PRICE    = 4
FIELD_OWNER    = 5


with open('sample.csv', 'rb') as csvfile:
    csv_reader = csv.reader(csvfile, delimiter=',')
    sorted_list = sorted(csv_reader, key=lambda x: x[FIELD_OWNER])
    # csvfile.seek(0)
    for row in sorted_list:
        print "URL: "+row[FIELD_URL]
        print "COLOR: "+row[FIELD_COLOR]
        print "SIZE: "+row[FIELD_SIZE]
        print "QUANTITY: "+row[FIELD_QUANTITY]
        print "PRICE: "+row[FIELD_PRICE]
        print "OWNER: "+row[FIELD_OWNER]

