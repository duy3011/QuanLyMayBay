#pragma once
#include<MayBay.h>
#include <mylib.h>

int searchMB(DSMB LMB, char *sohieuMB){
    for(int i = 0; i < LMB.soMB; i++){
        if(stricmp(LMB.nodes[i]->soHieuMB, sohieuMB) == 0){
            return i;
        }
    }
    return -1;
}

int ktsh(DSMB dsmb ,char s[]){
    for(int i = 0; i < dsmb.soMB; i++){
        if(stricmp(dsmb.nodes[i]->soHieuMB, s) == 0){
            return 1;
        }
    }
    return 0;
}

bool fullMB(DSMB dsmb){
    return dsmb.soMB == MAXPLANE;
}

int emptyMB(DSMB dsmb){
    return dsmb.soMB == 0;
}

//Them may bay

void nhapDSMB(DSMB &LMB){
    MB plane;
    int key;
    int current = 7, stt = 1;
    SetColor(LIGHTBLUE);
    ShowCur(true);
    rectangle(68,35,44,2);
    gotoxy(70,36);
    cout<<"ESC + ESC: EXIT || ESC + ENTER: NHAP LAI";
    gotoxy(15, 5);
    cout<<"STT       |    SO HIEU MAY BAY      |       LOAI MAY BAY        |    SO DAY     |   SO HANG"<<endl;
    gotoxy(15, 6);
    cout<<"-------------------------------------------------------------------------------------------"<<endl;
//        Code xu ly graphic
SHMB:
    do{
        bool check_full = fullMB(LMB);
        if(check_full == true){
            alertError("DANH SACH DA FULL KHONG THE THEM MAY BAY || AN PHIM BAT KY DE THOAT", 8, 4);
        }
        else{
            //clearError(1, 2);
            gotoxy(15, current);
            SetColor(WHITE);
            printf("%-10d", stt);
            stt++;
            cout<<"|                         |                           |               |              "<<endl;
            //gotoxy(31, current);
            
            ;
            SetColor(LIGHTBLUE);
            clearError(8,4);
            gotoxy(8, 4);
            cout<<"NHAP SO HIEU MAY BAY: ";
            SetColor(WHITE);
            gotoxy(31, current);
            nhapChuoi(plane.soHieuMB, 10);
                if(plane.soHieuMB[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto SHMB;
            }
                
            for(int i = 0; i < LMB.soMB; i++)
            {
                if(strcmp(LMB.nodes[i]->soHieuMB, plane.soHieuMB)  == 0)
                {
                    alertError("SO HIEU MAY BAY BI TRUNG", 8, 4);
                    gotoxy(31, current);
                    cout<<"        ";
                    stt--;
                    goto SHMB;
                }
            }
            
            clearError(8, 4);
            gotoxy(8, 4);
            SetColor(LIGHTBLUE);
            cout<<"NHAP LOAI MAY BAY: ";
            //gotoxy(57, current);
            fflush(stdin);
            gotoxy(57, current);
            SetColor(WHITE);
            nhapChuoi(plane.loaiMB, 20);
            if(plane.loaiMB[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto SHMB;
            }
            
SODAY:
            ;
            clearError(8, 4);
            SetColor(LIGHTBLUE);
            gotoxy(8, 4);
            cout<<"NHAP SO DAY: ";
            gotoxy(86, current);
            SetColor(WHITE);
            char soDay[2];
            nhapSo(soDay, 1);
            if(soDay[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto SHMB;
            }
            plane.soDay = atoi(soDay);
            
            if(plane.soDay > SODAYMAX)
            {
                alertError("SO DAY KHONG DUOC VUOT QUA 5!", 8, 4);
//                clearError(8, 4);
                gotoxy(86, current);
                cout<<"         |";
                goto SODAY;
            }
            else if(plane.soDay  < 2){
                alertError("SO DAY PHAI LON HON 1", 8, 4);
                gotoxy(86, current);
                cout<<"         |";
                goto SODAY;
            }
            
            
SOHANG:
            ;
            clearError(8, 4);
            SetColor(LIGHTBLUE);
            gotoxy(8, 4);
            cout<<"NHAP SO HANG: ";
            gotoxy(100, current);
            SetColor(WHITE);
            char soHang[3];
            nhapSo(soHang, 2);
            if(soHang[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto SHMB;
            }
            plane.soHang = atoi(soHang);
            if(plane.soHang > SOHANGMAX){
                alertError("SO HANG KHONG DUOC VUOT QUA 20", 8, 4);
                gotoxy(100, current);
                cout<<"        ";
                goto SOHANG;
            }
            else if(plane.soHang < 10){
                alertError("SO HANG PHAI LON HON 10", 8, 4);
                gotoxy(100, current);
                cout<<"        ";
                goto SOHANG;
            }
                    
            LMB.nodes[LMB.soMB] = new mayBay;
            *LMB.nodes[LMB.soMB++] = plane;
            current++;
            
            saveFileDSMB(FileDSMB, LMB);
            
            clearError(8, 4);
            gotoxy(8, 4);
            SetColor(LIGHTBLUE);
            cout<<"THEM MAY BAY THANH CONG, NHAN ENTER DE TIEP TUC THEM, NHAN PHIM BAT KY DE THOAT";
        }
        key = getch();
    }while(key == ENTER);
    system("cls");
}