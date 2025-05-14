#pragma once

#include <iostream>
#include "mylib.h"

using namespace std;

const int setupTimeCB = 2880;        //2880 phut = 2 ngay -> Thoi gian toi thieu de setup mot chuyen bay moi
const int setupTimeSHMB = 7200;        //7200 phut = 5 ngay -> Thoi gian toi thieu de setup mot chuyen bay

struct thoiGian{
    int hour;
    int minute;
    int day;
    int month;
    int year;
};

typedef thoiGian TIME;