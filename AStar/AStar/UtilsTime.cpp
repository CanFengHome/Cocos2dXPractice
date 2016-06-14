//
//  UtilsTime.cpp
//  Test
//
//  Created by ccf on 16/6/12.
//  Copyright © 2016年 mfp. All rights reserved.
//

#include "UtilsTime.h"
#include <sys/time.h>

double UtilsTime::gettime()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    
    return (double)tv.tv_sec + (double)tv.tv_usec/1000000;
}

long long UtilsTime::getTimeInMilliseconds()
{
    struct timeval tv;
    gettimeofday (&tv, nullptr);
    return tv.tv_sec * 1000l + tv.tv_usec / 1000l;
}
















