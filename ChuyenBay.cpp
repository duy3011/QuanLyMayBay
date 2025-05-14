#pragma once
#include <iostream>
#include "GlobalVar.h"
#include <mylib.h>
#include "MayBay.h"
#include "ChuyenBay.h"
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