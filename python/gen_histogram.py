#!/usr/bin/env python

def gen_histogram():
    values = [
    9.75,
    8.875,
    8.5,
    8.875,
    8.625,
    9.125,
    8.125,
    8.625,
    9.5,
    8.875,
    8.875,
    9.125,
    9.5,
    9.0,
    8.625,
    8.5,
    9.375,
    9.0,
    8.875,
    8.75,
    9.0,
    8.75,
    8.75,
    8.875,
    8.375,
    8.875,
    8.375,
    10.0,
    9.0,
    9.0,
    9.625,
    9.625,
    8.75,
    9.125,
    9.875,
    8.375,
    9.125,
    8.5,
    9.25,
    8.75,
    8.5,
    8.25,
    8.25,
    9.625,
    8.75,
    9.625,
    8.75,
    8.875,
    8.5,
    10.0
    ]
    uniq = []
    for i in values:
        if i not in uniq:
            uniq.append(i)
    j = 1
    uniq.sort()
    for i in uniq:
        print "%2d: %2.3f" %(j, i)
        j += 1
    count = [0 for x in uniq]
    print count
    for i in values:
        count[uniq.index(i)] += 1
    for i in xrange(0, len(uniq)):
        print "%.3f %d" %(uniq[i], count[i])


if __name__ == '__main__':
    gen_histogram()

