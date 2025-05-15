#pragma once

#define MAC_DINH 0
#define HUY_CHUYEN 0
#define CON_VE 1
#define HET_VE 2
#define HOAN_TAT 3
const int MAXPLANE = 300;

//Setup cac nut chuc nang can su dung trong bai
//const int UP = 72;
//const int DOWN = 80;
//const int LEFT = 75;
//const int RIGHT = 77;
//const int ESC = 27;
//const int ENTER = 13;
//const int F2 = 60;
//const int F3 = 61;
//const int F4 = 62;
//const int F5 = 63;


const int SODAYMAX = 5;                //So day toi da tren 1 may bay
const int SOHANGMAX = 20;            //So hang toi da tren 1 may bay
const int PAGECB = 10;                //Tong so CB co the hien thi trong 1 trang
const int PAGEMB = 10;                //Tong so MB co the hien thi trong 1 trang
const int numPageCBHK = 10;


const int setupTimeCB = 2880;        //2880 phut = 2 ngay -> Thoi gian toi thieu de setup mot chuyen bay moi
const int setupTimeSHMB = 7200;        //7200 phut = 5 ngay -> Thoi gian toi thieu de setup mot chuyen bay
                                    //                        co cung so hieu may bay voi chuyen bay khac
char *FileDSMB = "DSMB.txt";
char *FileDSCB=  "DSCB.txt";
char *FileDSHK = "DSHK.txt";

struct thoiGian{
    int hour;
    int minute;
    int day;
    int month;
    int year;
};

typedef thoiGian TIME;

struct mayBay{
    char soHieuMB[16];
    char loaiMB[41];
    int soDay;
    int soHang;
    int slBay = 0;                    //So luot bay cua 1 may bay
};

typedef mayBay MB;

struct listMB{
    int soMB = 0;
    mayBay *nodes[MAXPLANE];
};

typedef listMB DSMB;

struct Ve{
    char CCCD[13];
    char soGhe[5];//(A->G)

    
};

struct listVe{
    int soLuongVe; //Read only, ko go tay
    int soLuongDat = 0;
    Ve *nodes; //nodes = new Ve[sl_ve]
};

struct chuyenBay{
    char maCB[16];
    TIME time;
    char sbd[16];//San bay den
    int status = CON_VE;//Dung define o tren
    char soHieuMB[16];
};

typedef chuyenBay CB;

struct nodeChuyenBay{
    CB info;
    nodeChuyenBay *next = NULL;
    listVe DSVE;
};

typedef nodeChuyenBay* PTRCB;

struct hanhKhach{
    char CCCD[13];
    char Ho[50];
    char Ten[10];
    char Phai[4];//Nam - Nu
};

typedef hanhKhach HK;

struct nodeHK{
    HK info;
    nodeHK *left = NULL;
    nodeHK *right = NULL;
};

typedef nodeHK *TREEHK;        //Binary search tree hanh khach