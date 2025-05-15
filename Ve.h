#pragma once

#include <iostream>
#include "mylib.h"
#include "ChuyenBay.h"

struct Ve{
    char CCCD[13];
    char soGhe[5];//(A->G)

    
};

struct listVe{
    int soLuongVe; //Read only, ko go tay
    int soLuongDat = 0;
    Ve *nodes; //nodes = new Ve[sl_ve]
};


//--------------------------------------------Cac module ve----------------------------//
int searchVe(PTRCB , char [5]);
void DSVeTrong(PTRCB );
void DSVeDaDat(PTRCB );
void veDSVeDaDat(PTRCB );
void inDSVeDaDat(PTRCB );
void nhapVe(PTRCB &, PTRCB &, PTRCB , int , int , int , int , TREEHK );
void DSVT(PTRCB, DSMB);


//--------------------------------------------Dat ve-----------------------------------//
void DSVeCuaMotCB(PTRCB , PTRCB , int , DSMB , TREEHK );
void datVe(PTRCB , DSMB , TREEHK );


//--------------------------------------------Huy ve-----------------------------------//
void huyVe(PTRCB &);