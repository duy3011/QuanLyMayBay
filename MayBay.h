//==================== maybay.h ====================
#pragma once
#include <iostream>
// using namespace std;

struct MayBay {
    char soHieuMB[16];
    char loaiMB[41];
    int soDay;
    int soHang;
    int slBay = 0;
};

#define MAX_MB 300
struct DSMB {
    MayBay* nodes[MAX_MB];
    int n = 0;
};

int timMB(DSMB ds, const char* soHieu);
void themMB(DSMB &ds);
void xoaMB(DSMB &ds, const char* soHieu);
void saveFileDSMB(const char* filename, const DSMB &ds);
void loadFileDSMB(const char* filename, DSMB &ds);