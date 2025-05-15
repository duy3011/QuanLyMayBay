#pragma once

#include "Var.h"
#include "MayBay.h"
#include "mylib.h"
//--------------------------------------------CHUYEN BAY----------------------------//
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

//--------------------------------------------In PTRCB trong ngay----------------------------------//
void DSCBKHTN(PTRCB , DSMB);
int DSCBNgay(PTRCB , TIME );
void adjustSLbay(PTRCB ,DSMB& );

//-------------------IN DSCB TRONG NGAY--------------------/

int nhapNgayKH(TIME &date, int current, int x)
{
    SetColor(LIGHTBLUE);
    int maxDay;

DAY:
    ;
    SetColor(LIGHTBLUE);
    clearError(8, 4);
    gotoxy(8, 4);
    cout<<"NHAP NGAY:";
    
    gotoxy(x + 54, current);
    char day[3];
    nhapSo(day, 2);
    if (day[0]==ESC)
        return -1;
    date.day = atoi(day);
    if(date.day >31 || date.day < 1){
        cout<<"\b \b";
        cout<<"\b \b";
        clearError(8, 4);
        alertError("NGAY KHONG HOP LE VUI LONG NHAP LAI", 8, 4);
        goto DAY;
    }

MONTH:
    ;
    clearError(8, 4);
    gotoxy(8, 4);
    cout<<"NHAP THANG:";
    
    gotoxy(x + 59, current);
    char month[3];
    nhapSo(month, 2);
    if (month[0]==ESC)
        return -1;
    date.month = atoi(month);
    
    if(date.month < 1 || date.month > 12){
        cout<<"\b \b";
        cout<<"\b \b";
        clearError(8, 4);
        alertError("THANG KHONG HOP LE VUI LONG NHAP LAI", 8, 4);
        goto MONTH;
    }
    else{
        switch(date.month){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                maxDay = 31;
                break;
                
            case 4:
            case 6:
            case 9:
            case 11:
                maxDay = 30;
                break;
                
            case 2:
                if(checkYear(date.year) == true){
                    maxDay = 29;
                }
                else{
                    maxDay = 28;
                }
                break;
        }
        if(date.day > maxDay){
            clearError(8, 4);
            alertError("VUI LONG KIEM TRA LAI SO NGAY TRONG THANG", 8, 4);
            gotoxy(x + 54, current);
            goto DAY;
        }
    }

YEAR:
    clearError(8, 4);
    gotoxy(8, 4);
    cout<<"NHAP NAM:";
    
    gotoxy(x + 64, current);
    char year[5];
    nhapSo(year, 4);
    if (year[0]==ESC)
        return -1;
    date.year = atoi(year);
    
    tm* crt = currentTime();
    int currentDay = crt->tm_mday;
    int currentMonth = crt->tm_mon + 1;
    int currentYear = crt->tm_year + 1900;
}

int DSCBNgay(PTRCB listCB, TIME time)
{
    SetColor(LIGHTBLUE);
    ShowCur(false);
    rectangle(5, 0, 12, 2);
    gotoxy(7, 1);
    cout<<"ESC: BACK";
    
    rectangle(23, 0, 67, 2);
    gotoxy(25, 1);
    cout<<"TRANG THAI: 0 - HUY CHUYEN, 1 - CON VE, 2 - HET VE, 3 - HOAN TAT";
    gotoxy(45, 7);
    cout<<"DANH SACH CHUYEN BAY KHOI HANH TRONG NGAY "<<time.day<<"/"<<time.month<<"/"<<time.year<<" DEN SAN BAY "<<listCB->info.sbd;
    
    int current=0;
    int n=countCB(listCB);
    gotoxy(1,9);
    cout<<"    STT     |    Ma Chuyen Bay   |     Ngay Khoi Hanh     |      San Bay Den      | Trang Thai | So Hieu May Bay | So Ve Da Dat | So Luong Ve | So ve trong"<<endl;
    gotoxy(1,10);
    cout<<"    -------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    normal();
    if(!emptyCB(listCB))
    {

        PTRCB p;
        int i=0;
        for(p=listCB; p!=NULL; p=p->next)
        {
            gotoxy(5, i+11);
            int veTrong = p->DSVE.soLuongVe-p->DSVE.soLuongDat;
            printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d|    %-9d",i+1,p->info.maCB,p->info.time.hour,p->info.time.minute,p->info.time.day,p->info.time.month,p->info.time.year,
                   p->info.sbd,p->info.status,p->info.soHieuMB,p->DSVE.soLuongDat,p->DSVE.soLuongVe, veTrong);
            i++;
        }

        int key;
        do
        {
            key = getch();
            if(key==ESC)
                return -1;
        }
        while(1);
    }
}

void DSCBKHTN(PTRCB listCB, DSMB listMB)
{
START:
    ;
    TIME date;
    normal();
    system("cls");
    ShowCur(true);
    gotoxy(20,7);
    SetColor(WHITE);
    cout <<"DANH SACH CAC CHUYEN BAY KHOI HANH TRONG NGAY     /    /      SAN BAY DEN: ";
 
    if(nhapNgayKH(date, 7, 13)==-1)
    {
        rectangle(6,3,29,2);
        gotoxy(7,4);
        cout<<"ESC: EXIT || ENTER: NHAP LAI";
        int confirm = getch();
        if (confirm == ESC)
            return;
        else if (confirm == ENTER)
            goto START;
    }

    char sanBayDen[50];
    gotoxy (7, 4);
    cout << "NHAP VAO SAN BAY DEN:";
    fflush(stdin);
    gotoxy(95,7);
    SetColor(WHITE);
    nhapChu(sanBayDen,50);

    normal();
    system("cls");
    PTRCB newLCB;
    initCB(newLCB);
    if(!emptyLCB(listCB))
    {
        PTRCB p;
        for(p = listCB; p!=NULL; p = p->next)
        {
            if(p->info.time.day == date.day && p->info.time.month==date.month && p->info.time.year==date.year && strcmp(p->info.sbd,sanBayDen)==0)
            {
                insertLast(newLCB,*p);
            }
        }
    }
    else
    {
        gotoxy(55,7);
        SetColor(RED);
        cout <<"KHONG CO CHUYEN BAY NAO TRONG DANH SACH CHUYEN BAY!!!";
        getch();
    }

    if(!emptyLCB(newLCB))
    {
        if(DSCBNgay(newLCB,date) == -1)
            goto START;
    }
    else
    {
        SetColor(RED);
        rectangle(53,6,35,2);
        gotoxy(55,7);
        cout <<"KHONG TIM THAY CHUYEN BAY NAO!!!";
        Sleep(2000);
        goto START;
    }
}