#pragma once
#include<MayBay.h>
#include<ChuyenBay.h>
#include <GlobalVar.h>
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

//Xoa may bay
int deleteItemMB(DSMB &LMB, int i){
    if(i < 0 || i >= LMB.soMB || LMB.soMB == 0){
        return 0;
    }
    delete LMB.nodes[i];
    for(int j = i + 1; j < LMB.soMB; j++){
        LMB.nodes[j-1] = LMB.nodes[j];
    }
    LMB.soMB--;
    saveFileDSMB(FileDSMB, LMB);
    return 1;
}

void deleteMB(DSMB &LMB, PTRCB LCB, int i){
        SetBGColor(0);
    PTRCB p;
    for(p = LCB; p != NULL; p = p->next){
        if(strcmp(LMB.nodes[i]->soHieuMB, p->info.soHieuMB) == 0){
            alertError("KHONG THE XOA VI MAY BAY DA DUOC TAO CHUYEN BAY", 15, 4);
            return ;
        }
    }
    
    ShowCur(true);
CONFIRM:
    ;
    char confirm[4];
    gotoxy(15, 4);
    SetColor(9);
    cout<<"BAN CO THUC SU MUON XOA MAY BAY? NHAN \"YES\" DE XAC NHAN, NHAN \"NO\" DE HUY CHUC NANG";
    gotoxy(100, 4);
    nhapChu(confirm, 5);
    if(strcmp(confirm, "YES") != 0 && strcmp(confirm, "NO") != 0){
        clearError(8, 4);
        gotoxy(8, 4);
        cout<<"VUI LONG NHAP DUNG YEU CAU DE CHUC NANG DUOC THUC HIEN!";
        Sleep(5000);
        clearError(8, 4);
        gotoxy(100, 4);
        cout<<"     ";
        goto CONFIRM;
    }
    
    if(strcmp(confirm, "YES") == 0){
        int result = deleteItemMB(LMB, i);
        if(result == 0){
            clearError(15, 4);
            alertError("XOA MAY BAY THAT BAI", 15, 4);
        }
        else{
            clearError(15, 4);
            alertError("XOA MAY BAY THANH CONG", 15, 4);
        }
    }
    else{
        clearError(15, 4);
        alertError("HUY CHUC NANG XOA MAY BAY THANH CONG", 15 ,5);
    }
    system("cls");
}
//Tim may bay
int searchMB(DSMB LMB, char *sohieuMB){
    for(int i = 0; i < LMB.soMB; i++){
        if(stricmp(LMB.nodes[i]->soHieuMB, sohieuMB) == 0){
            return i;
        }
    }
    return -1;
}
//Kiem tra so hieu may bay
int ktsh(DSMB dsmb ,char s[]){
    for(int i = 0; i < dsmb.soMB; i++){
        if(stricmp(dsmb.nodes[i]->soHieuMB, s) == 0){
            return 1;
        }
    }
    return 0;
}
//Kiem tra danh sach may bay da day hay chua
bool fullMB(DSMB dsmb){
    return dsmb.soMB == MAXPLANE;
}
//Kiem tra danh sach may bay co trong hay khong
int emptyMB(DSMB dsmb){
    return dsmb.soMB == 0;
}
//Hieu chinh may bay
void editMB(DSMB &LMB, PTRCB LCB, int i){
    SetBGColor(0);
//    ShowCur(true);
    PTRCB p;
    for(p = LCB; p != NULL; p = p->next){
        if(strcmp(LMB.nodes[i]->soHieuMB, p->info.soHieuMB) == 0){
            normal();
            alertError("KHONG THE HIEU CHINH VI MAY BAY DA DUOC TAO CHUYEN", 15, 4);
            return ;
        }
        
    }
START:
    ;
    SetColor(12);
    rectangle(119, 5, 30, 10);
    SetColor(12);
    rectangle(116,19,44,2);
    gotoxy(118,20);
    cout<<"ESC + ESC: EXIT || ESC + ENTER: NHAP LAI";
    gotoxy(120, 6);
    cout<<"EDIT MAY BAY";
    ShowCur(true);
    gotoxy(120, 8);
    cout<<"SO HIEU MAY BAY MOI: "<<LMB.nodes[i]->soHieuMB;
    gotoxy(120, 10);
    cout<<"LOAI MAY BAY MOI:  ";
    fflush(stdin);
    gotoxy(139, 10);
    nhapChuoi(LMB.nodes[i]->loaiMB, 41);
    if (LMB.nodes[i]->loaiMB[0]==ESC)
    {
        int confirm = getch();
        if (confirm == ESC)
            return;
        else if (confirm == ENTER)
            goto START;
    }
    
SODAYNEW:
    ;
    SetColor(12);
    gotoxy(120, 12);
    cout<<"SO DAY MOI: ";
    gotoxy(132, 12);
    char soDayNew[2];
    nhapSo(soDayNew, 1);
    if (soDayNew[0]==ESC)
    {
        int confirm = getch();
        if (confirm == ESC)
            return;
        else if (confirm == ENTER)
            goto START;
    }
    if(atoi(soDayNew) > SODAYMAX){
        //alertError("SO DAY KHONG DUOC VUOT QUA 5",120,4);
        gotoxy(120, 4);
        cout<<"SO DAY KHONG DUOC VUOT QUA 5";
        Sleep(3000);
        gotoxy(120, 4);
        cout<<"                            ";
        gotoxy(132, 12);
        cout<<" ";
        goto SODAYNEW;
    }
    LMB.nodes[i]->soDay = atoi(soDayNew);
    
SOHANGNEW:
    ;
    SetColor(12);
    gotoxy(120, 14);
    cout<<"SO HANG MOI: ";
    gotoxy(133, 14);
    char soHangNew[3];
    nhapSo(soHangNew, 2);
    if (soHangNew[0]==ESC)
    {
        int confirm = getch();
        if (confirm == ESC)
            return;
        else if (confirm == ENTER)
            goto START;
    }
    if(atoi(soHangNew) > SOHANGMAX){
//        alertError("SO HANG KHONG DUOC VUOT QUA 20",120, 4);
        gotoxy(120, 4);
        cout<<"SO HANG KHONG DUOC VUOT QUA 20";
        Sleep(3000);
        gotoxy(120, 4);
        cout<<"                              ";
        gotoxy(133, 14);
        cout<<"   ";
        goto SOHANGNEW;
    }
    LMB.nodes[i]->soHang = atoi(soHangNew);
    saveFileDSMB(FileDSMB, LMB);
    system("cls");
}
//Cap nhat may bay
void updateMB(DSMB &LMB, PTRCB LCB){
    
    int soLuongMenu = 2;
    char menuUpdateMB[2][70] =
    {
        "THEM MAY BAY",
        "CAP NHAT MAY BAY"
    };
    
    int m;
    do{
        SetBGColor(0);
        system("cls");
        SetColor(9);
        rectangle(69, 35, 32, 2);
        SetColor(9);
        gotoxy(70, 36);
        cout<<"ESC: QUAY LAI | ENTER: XAC NHAN"<<endl;
            
        m = menu(55, 10, menuUpdateMB, soLuongMenu);
        switch(m){
            case 0:{
                system("cls");
                nhapDSMB(LMB);
            }
                break;
            
            case 1:{
                system("cls");
                inDSMB(LMB, LCB);
            }
                break;
                
            case ESC:
                return ;
        }
    }while(m != -1);
}
//In danh sach may bay
int inDSMB(DSMB &LMB, PTRCB &LCB){
    int currentPage = 1;                //So trang mac dinh
    ShowCur(false);
BEGIN:
    ;
    system("cls");
    SetColor(LIGHTBLUE);
    SetBGColor(0);
    
    rectangle(15, 0, 15, 2);
    gotoxy(17, 1);
    cout<<"F3: EDIT";
    
    rectangle(55, 0, 15, 2);
    gotoxy(57, 1);
    cout<<"F4: DELETE";
    
    rectangle(95, 0, 15, 2);
    gotoxy(97, 1);
    cout<<"ESC: EXIT";
    
    gotoxy(55, 7);
    cout<<"DANH SACH MAY BAY";
    gotoxy(15, 9);
    cout<<"STT       |    SO HIEU MAY BAY      |   LOAI MAY BAY            |    SO DAY     |   SO HANG"<<endl;
    gotoxy(15, 10);
    cout<<"-------------------------------------------------------------------------------------------"<<endl;        //Co the thay the bang ham ve duong thang

LR:                                    //Left and right
    ;
    SetBGColor(0);
    SetColor(LIGHTBLUE);
    rectangle(55, 25, 10, 2);
    gotoxy(57, 26);
    cout<<"PAGE "<<currentPage;
    
    normal();
    int current = 0;
    int page = LMB.soMB / PAGEMB;
    if(LMB.soMB % PAGEMB > 0){
        page++;
    }
    

    int y = 11;
    if(!emptyMB(LMB)){
        for(int i = (currentPage - 1) * PAGEMB; i < currentPage * PAGEMB; ){
            gotoxy(15, y++);
            printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d\n",i+1,LMB.nodes[i]->soHieuMB, LMB.nodes[i]->loaiMB, LMB.nodes[i]->soDay,LMB.nodes[i]->soHang);
            if(++i == LMB.soMB){
                break;
            }
        }
        //In ra khung highlight cho dong dau tien
        gotoxy(15, 11);
        highlight();
        int f = (currentPage - 1) * PAGEMB;
        printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",f+1,LMB.nodes[f]->soHieuMB, LMB.nodes[f]->loaiMB, LMB.nodes[f]->soDay, LMB.nodes[f]->soHang);
        
        //int key;
        
        do{
            switch(getKey()){
                case UP:
                    if(current > 0){
                        normal();
                        gotoxy(15, 11 + current);            //In lai dong hien tai
                        printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current + f + 1,LMB.nodes[current + f]->soHieuMB, LMB.nodes[current + f]->loaiMB, LMB.nodes[current + f]->soDay, LMB.nodes[current + f]->soHang);
                        current--;
                        
                        highlight();
                        gotoxy(15, 11 + current);            //In khung highlight o dong tren
                        printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current + f + 1,LMB.nodes[current + f]->soHieuMB, LMB.nodes[current + f]->loaiMB, LMB.nodes[current + f]->soDay, LMB.nodes[current + f]->soHang);
                    }
                    break;
                    
                case DOWN:
                    if((currentPage == page && current + 1 < PAGEMB - (page * PAGEMB - LMB.soMB)) || (currentPage < page && current + 1 < PAGEMB) ){
                        normal();
                        gotoxy(15, 11 + current);            //In lai dong hien tai
                        printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current + f + 1,LMB.nodes[current + f]->soHieuMB, LMB.nodes[current + f]->loaiMB, LMB.nodes[current + f]->soDay, LMB.nodes[current + f]->soHang);
                        current++;
                        
                        highlight();                        //In khung highlight o dong duoi
                        gotoxy(15, 11 + current);
                        printf("%-10d|     %-20s|     %-22s|     %-10d|     %-10d",current + f + 1,LMB.nodes[current + f]->soHieuMB, LMB.nodes[current + f]->loaiMB, LMB.nodes[current + f]->soDay, LMB.nodes[current + f]->soHang);
                    }
                    break;
                    
                case RIGHT:
                    if(currentPage < page){
                        currentPage++;
                        normal();
//                        gotoxy(15, 11 + current);
//                        SetBGColor(0);
//                        for(int i = 0; i < PAGEMB; i++){
//                            clearError(15, 11 + i);
//                        }
                        system("cls");
                        goto BEGIN;
                    }
                    break;
                
                case LEFT:
                    if(currentPage > 1){
                        currentPage--;
                        normal();
//                        for(int i = 0; i < PAGEMB; i++){
//                            SetBGColor(0);
//                            clearError(15, 11 + i);
//                        }
                        system("cls");
                        goto BEGIN;
                    }
                    break;
                    
                case F3:
                    editMB(LMB, LCB, current + f);
                    goto BEGIN;
                    break;
                                                              
                case F4:
                    deleteMB(LMB, LCB, current + f);
                    gotoxy(57, 30);
                    cout<<"TEST MAY BAY "<< LMB.soMB;
                    if(LMB.soMB % PAGEMB == 0 && page > 1){
                        currentPage--;
                    }
                    goto BEGIN;
                    break;
                                
                case ESC:
                    return ESC;
            }
        }while(1);
    }
    
    else{
        gotoxy(15, y);
        cout<<"DANH SACH MAY BAY RONG, VUI LONG NHAP DANH SACH TRUOC KHI HIEU CHINH";
    }
    getch();
}
//Luu danh sach may bay ra file
void saveFileDSMB(char *fileName, DSMB LMB)
{
    FILE * f;
    f = fopen(fileName,"w");
    if(f)
    {
        fprintf(f,"%-5d\n\n", LMB.soMB);
        for(int i=0; i<LMB.soMB; i++)
        {
            fprintf(f,"%s\n%s\n%d\n%d\n%d\n\n",LMB.nodes[i]->soHieuMB, LMB.nodes[i]->loaiMB, LMB.nodes[i]->soDay, LMB.nodes[i]->soHang, LMB.nodes[i]->slBay);
        }
        fclose(f);
    }
    else
    {
        alertError("Khong mo duoc file \"DSMB.txt\" de ghi!", 8, 1);
    }
}
//Doc danh sach may bay tu file
void loadFileDSMB(char *fileName, DSMB &LMB)
{
    MB plane;

    FILE * f;

    f = fopen(fileName,"r");
    if(f)
    {
        fseek(f, 0, SEEK_END);// di chuyen vi tri con tro den vi tri cuoi
        if(ftell(f)==0) // tráº£ ve so ki tu trong file
        {
            fclose(f);
            return;
        }
        fseek(f, 0, SEEK_SET);
        
        if(!feof(f))
        {
            fscanf(f,"%5d",&LMB.soMB);    //    cout<<LMB.n<<endl;
            for(int i=0; i<LMB.soMB; i++)
            {
                fscanf(f,"%s",&plane.soHieuMB);
                fgets(plane.loaiMB, 40, f); // doc mot dong
                fgets(plane.loaiMB, 40, f);
                deleteEnter(plane.loaiMB);
                fscanf(f,"%d",&plane.soDay);
                fscanf(f,"%d",&plane.soHang);
                fscanf(f,"%d",&plane.slBay);
                LMB.nodes[i] = new MB;
                *LMB.nodes[i] = plane;
            }
        }
        fclose(f);
    }
    else
    {
        alertError("Khong mo duoc file \"DSMB.txt\"!", 8, 1);
    }
}