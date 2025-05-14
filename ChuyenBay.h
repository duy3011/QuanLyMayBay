#pragma once
#include <iostream>
#include <GlobalVar.h>
#include <mylib.h>
using namespace std;

int getslchoMB(DSMB, char []);
void tangslBay(DSMB& , char []);//Tang so luot bay cua 1 may bay
void giamslBay(DSMB&, char [],PTRCB);
bool xau_trung(char [], char []);
                                


void initCB(PTRCB &);
int countCB(PTRCB );
void deleteDSCB(PTRCB &);
void deleteFirst(PTRCB &);
void deleteAfter(PTRCB );
//tm *currentTime();
void outputCurrentTime();
bool checkYear(int );
int time(TIME date);
int nhapDate(TIME &, int , int );
PTRCB searchCB(PTRCB , char *);
void insertLast(PTRCB &, nodeChuyenBay);
void insertOrder(PTRCB &, nodeChuyenBay);
void nhapCB(PTRCB &, DSMB);
void insertOrderTime(PTRCB &, nodeChuyenBay);
void nhapCB(PTRCB &, DSMB );
void deleteCB(PTRCB &, int , DSMB& );
void editCB(PTRCB &, int , DSMB );
void updateCB(PTRCB &, DSMB );
void cancelCB(PTRCB &, int , DSMB& );
void inMotCB(PTRCB , int );
void inDSCB(PTRCB &, DSMB );
void saveFileDSCB(char *, PTRCB) ;
void loadFileDSCB(char *, PTRCB &);