#include "mylib.h"

#include "MayBay.h"
#include "HanhKhach.h"

#include <iostream>
using namespace std;

int main(){

    resizeConsole(2000, 2000);
    DSMB LMB;
    
    
    
    
    
    
    
    TREEHK LHK;
    // initTree(LHK);
    
    
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
        
    }
    while (m!=-1);
    

    return 0;
}