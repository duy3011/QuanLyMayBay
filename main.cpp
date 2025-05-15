#pragma once

#include<iostream>
#include "mylib.h"
#include "Var.h"
#include "MayBay.h"
#include "ChuyenBay.h"
#include "Ve.h"
#include "HanhKhach.h"
#include <ctime>
#include <iomanip>
#include <math.h>
using namespace std;

//--------------------------------------------Ham main--------------------------------------------//
int main(){
    
    resizeConsole(2000, 2000);
    DSMB LMB;
    LMB.soMB = 0;
    loadFileDSMB(FileDSMB, LMB);
    
    PTRCB LCB;
    initCB(LCB);
    loadFileDSCB(FileDSCB, LCB);
    
    TREEHK LHK;
    initTree(LHK);
    loadFileDSHK(FileDSHK, LHK);
    
     int soluongmenu = 8;// so luong menu

    char a [8][70] =     { "1. QUAN LI MAY BAY",
                          "2. QUAN LI CHUYEN BAY",
                          "3. DAT VE",
                          "4. HUY VE",
                          "5. IN DANH SACH HANH KHACH TREN MOT CHUYEN BAY",
                          "6. IN DANH SACH CAC CHUYEN BAY KHOI HANH TRONG NGAY",
                          "7. IN DANH SACH CAC VE CON TRONG CUA MOT CHUYEN BAY",
                          "8. THONG KE SO LUOT THUC HIEN CHUYEN BAY CUA TUNG MAY BAY"
                      };
    // goi ham menu trong menu.h
    int m;
    do
    {

        ShowCur(false);
        SetColor(LIGHTBLUE);
        system("cls");
        SetColor(2);
        vekhung(68,35,1,30);
        PutCharXY(70,36,"ESC: THOAT | ENTER: XAC NHAN",GREEN);
        m = menu(55,10,a,soluongmenu);
        switch(m)
        {
        case  0 :
        {
            updateMB(LMB,LCB);
            break;
        }
        case 1:
        {
            updateCB(LCB, LMB);
            break;
        }
        case 2:
        {
            datVe(LCB,LMB, LHK);
            break;
        }
        case 3:
        {
            huyVe(LCB);
            break;

        }
        case 4:
        {
            inDSHK(LCB, LHK);
            break;
        }
        case 5:
        {

            DSCBKHTN(LCB, LMB);
            break;
        }
        case 6:
        {
            DSVT(LCB, LMB);
            break;
        }
        case 7:
            TKCB(LMB);
            break;
        }
    }
    while(m!=-1);

    delete[] LMB.nodes;
    return 0;
}
