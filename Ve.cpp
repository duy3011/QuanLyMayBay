#pragma once

#include "Ve.h"
#include "mylib.h"

int searchVe(PTRCB p, char seat[5]){
    for(int i = 0; i < p->DSVE.soLuongDat; i++){
        if(strcmp(p->DSVE.nodes[i].soGhe, seat) == 0){
            return i;                //Neu tim thay vi tri ghe tra ve vi tri tuong ung
        }
    }
    return -1;                        //Neu khong tim thay tra ve -1
}

void DSVeTrong(PTRCB p){
    char *seat;
    int alphabet, count, len;
    for(int i = 0; i < p->DSVE.soLuongDat; i++){
        seat = p->DSVE.nodes[i].soGhe;
        
        if(seat[0] >= 'a' && seat[0] <= 'z')
            alphabet = seat[0] - 64;
        
        count = 0;
        len = strlen(seat);
        
        for(int j = 1; j < strlen(seat); j++){
            count += (seat[j] - 48) * pow(10, len - 2);
            len--;
        }
        
        gotoxy(8 + count * 6 - 3, 11 + alphabet * 2);
        cout<<"   ";
    }
}
void DSVeDaDat(PTRCB p){
    gotoxy(50, 10);
    SetColor(LIGHTBLUE);
    cout<<"DANH SACH VE DA DAT CUA CHUYEN BAY "<<p->info.maCB<<endl;
    
    gotoxy(15, 11);
    for(int i = 0; i < p->DSVE.soLuongDat; i++){
        cout<<p->DSVE.nodes[i].soGhe<<"     ";
    }
}
void veDSVeDaDat(PTRCB p){
    char *seat;
    int alphabet, count, len;
    
    for(int i = 0; i < p->DSVE.soLuongDat; i++){
        seat = p->DSVE.nodes[i].soGhe;
        gotoxy(15, 28 + i);
        alphabet = seat[0] - 64;                //Vi tri day
        count = 0;                                //Vi tri hang
        len = strlen(seat);
        
        for(int j = 1; j < strlen(seat); j++){
            count += (seat[j]  - 48) * pow(10, len - 2);
            len--;
        }
        SetColor(9);
        gotoxy(8 + count * 6 - 3, 9 + alphabet * 2); //Min 11,12
        cout<<p->DSVE.nodes[i].soGhe;
    }
}

void inDSVeDaDat(PTRCB p){
    gotoxy(50, 10);
    SetColor(12);
    cout<<"DANH SACH VE DA DAT CUA CHUYEN BAY: "<<p->info.maCB<<endl;
    gotoxy(15, 11);
    for(int i = 0; i < p->DSVE.soLuongDat; i++){
        cout<<p->DSVE.nodes[i].soGhe<<"     ";
    }
}

void nhapVe(PTRCB &LCB, PTRCB &p, PTRCB temp, int x, int y, int soHang, int soDay, TREEHK LHK){
    for(int i = 0; i < 13; i++){
        clearError(8, 10 + soDay * 2 + 4 + i);
    }
    
    char vitringoi[5];
    sprintf(vitringoi,"%c%d", char(y + 64), x);
    gotoxy(8, 4);
    cout<<"VE DANG CHON MUA: ";
    SetColor(9);
    cout<<vitringoi;
    
//    gotoxy(8, 7);
    if(searchVe(p, vitringoi) != -1){
        alertError("VE NAY DA DUOC MUA", 8, 5);
        return;
    }
    
    SetColor(15);
    rectangle(8, 9 + soDay * 2 + 4, 30, 4);
    
CCCD:
    ;
    SetColor(14);
    gotoxy(11, 9 + soDay * 2 + 6);
    cout<<"NHAP CCCD: ";
    gotoxy(22, 9 + soDay * 2 + 6);
    nhapSo(p->DSVE.nodes[p->DSVE.soLuongDat].CCCD, 12);
    if (p->DSVE.nodes[p->DSVE.soLuongDat].CCCD[0]==ESC)
        return;
    
//    clearError(8, 4);
    for(int i = 0; i < p->DSVE.soLuongDat; i++){
        if(strcmp(p->DSVE.nodes[i].CCCD, p->DSVE.nodes[p->DSVE.soLuongDat].CCCD) == 0){
            alertError("KHACH HANG DA CO VE TREN CHUYEN BAY NAY", 8, 4);
            gotoxy(11, 9 + soDay * 2 + 6);
            cout<<"                         ";
            goto CCCD;
            break;
        }
    }
    
    PTRCB q;
    int checkTimeCBNow = time(p->info.time);
    int checkTimeDSCB;
    for(q = temp; q != NULL; q = q->next){
        if(strcmp(q->info.maCB, p->info.maCB) == 0 || strcmp(q->info.soHieuMB, p->info.soHieuMB) == 0){
            q = q->next;
        }
        checkTimeDSCB = time(q->info.time);
        for(int j = 0; j < q->DSVE.soLuongDat; j++){
            if(strcmp(q->DSVE.nodes[j].CCCD, p->DSVE.nodes[p->DSVE.soLuongDat].CCCD) == 0 && abs(checkTimeCBNow - checkTimeDSCB) < setupTimeCB){
                gotoxy(8, 4);
                cout<<"HANH KHACH DA CO VE TREN CHUYEN BAY: ";
                SetColor(9);
                cout<<q->info.maCB;
                
                SetColor(12);
                cout<<" CB PHAI CACH IT NHAT 2 NGAY";        //De mot nguoi khach dat mot chuyen bay khac thi phai can
                Sleep(4000);                                //it nhat 2 ngay
                clearError(8, 4);
                gotoxy(11, 9 + soDay * 2 + 6);
                cout<<"                         ";
                goto CCCD;
                break;
            }
        }
    }
    
    TREEHK khach = searchHK(LHK, p->DSVE.nodes[p->DSVE.soLuongDat].CCCD);
    
    if(khach != NULL){
        int toaDoX = soHang * 7 + 20;
        gotoxy(toaDoX, 7);
        SetColor(14);
        cout<<"THONG TIN HANH KHACH";
        
        SetColor(15);
        rectangle(toaDoX, 9, 20, 8);
        
        gotoxy(toaDoX + 2, 10);
        cout<<"CCCD : "<<khach->info.CCCD;
        
        gotoxy(toaDoX + 2, 12);
        cout<<"HO : "<<khach->info.Ho;
        
        gotoxy(toaDoX + 2, 14);
        cout<<"TEN : "<<khach->info.Ten;
        
        gotoxy(toaDoX + 2, 16);
        cout<<"PHAI : "<<khach->info.Phai;
    }
    else{
        if(nhapHK(LHK, p->DSVE.nodes[p->DSVE.soLuongDat].CCCD, soDay)==-1)
            return;
    }

CONFIRM:
    ;
    char confirm[4];
    gotoxy(8, 4);
    normal();
    cout<<"NHAN \"YES\" DE XAC NHAN DAT VE, NHAN \"NO\" DE HUY DAT VE: ";
    gotoxy(63, 4);
    nhapChu(confirm, 5);
    if(strcmp(confirm, "YES") != 0 && strcmp(confirm, "NO") != 0){
        clearError(8, 4);
        gotoxy(8, 4);
        cout<<"VUI LONG NHAP DUNG YEU CAU DE HOAN TAT THU TUC DAT VE!";
        Sleep(5000);
        clearError(8, 4);
        gotoxy(63, 4);
        cout<<"     ";
        goto CONFIRM;
    }
    
    int k = 8 + soDay * 2 + 4;
    if(strcmp(confirm, "YES") == 0){
//        for(int y = 7; y < 20; y++){
//            clearErrTTHK(soHang * 7 + 20, y);
//            clearError(8, k);
//            k++;
//        }
        
        strcpy(p->DSVE.nodes[p->DSVE.soLuongDat].soGhe, vitringoi);
        p->DSVE.soLuongDat++;
        if(p->DSVE.soLuongDat == p->DSVE.soLuongVe){
            p->info.status = 2;
            
            clearError(8, 4);
            SetColor(10);
            alertError("CHUYEN BAY DA FULL VE", 8, 4);
        }
        veDSVeDaDat(p);
        saveFileDSCB(FileDSCB, LCB);
        clearError(8, 4);
        alertError("DAT VE THANH CONG", 8, 4);
    }
    else{
        alertError("DA HUY YEU CAU DAT VE", 8, 5);
        clearError(8, 4);
        
        int k = 8 + soDay * 2 + 4;
        for(y = 7; y < 20; y++){
            clearErrTTHK(soHang * 7 + 20, y);
            clearError(8, k);
            k++;
        }
    }
}

void DSVT(PTRCB LCB, DSMB LMB)
{
     
BEGIN:
    ;
    normal();
    system("cls");
    char MaCB[15];
    int key;
    
    SetColor(LIGHTBLUE);
        gotoxy(120, 9);
        cout<<"DANH SACH MA CHUYEN BAY"<<endl;
        gotoxy(120, 10);
        cout<<"-------------------------"<<endl;
        int k = 11;
        PTRCB q;
        for(q = LCB; q != NULL; q = q->next ){
            gotoxy(130, k++);
            cout<<q->info.maCB<<endl;
        }

MACB:
    ;
    int x=11;
    int y=11;
    clearError(10,7);
    gotoxy(10,7);
    SetColor(15);
    ShowCur(true);
    cout<<"NHAP VAO MA CHUYEN BAY: ";
    gotoxy(35,7);
    nhapChuoi(MaCB,10);
        if(MaCB[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto MACB;
            }

    PTRCB p = searchCB(LCB,MaCB);
    if(p==NULL)
    {
        //clearError(10,4);
        alertError("MA CHUYEN BAY KHONG TON TAI!",10,4);
      gotoxy(15,7);
      cout<<"           ";
        goto MACB;

    }
    else
    {
        SetColor(LIGHTBLUE);
        rectangle(8,0,20,2);
        gotoxy(10,1);
        SetColor(LIGHTBLUE);
        cout<<"ESC: EXIT";
        rectangle(35,0,35,2);
        gotoxy(37,1);
        cout<<"F5: XEM VE TREN CHUYEN BAY KHAC";

        int i = searchMB(LMB,p->info.soHieuMB);
        gotoxy(25,9);
        SetColor(LIGHTBLUE);
        cout<<"DANH SACH VE CON TRONG CUA CHUYEN BAY : "<<p->info.maCB<<endl;
        SetColor(15);
        int soHang = LMB.nodes[i]->soHang;
        int soDay = LMB.nodes[i]->soDay;
        gotoxy(11,13);
        
        SetColor(15);                                                //Ve bang vi tri ngoi tren may bay
        rectangle(7, 9, soHang * 6 + 4, soDay * 2 + 2);
        gotoxy(11, 11);
        for(int day = 1; day <= soDay; day++){
        for(int hang = 1; hang <= soHang; hang++){
            printf("%c%-5d", char(day + 64), hang);
        }
        y = y + 2;
        gotoxy(11, y);
    }
       
       //VeTrong(p);
      veDSVeDaDat(p);
        do
        {
            key = getch();
            //if(key <=0) key = getch();
            switch(key)
            {
            case F5:
            {
                goto BEGIN;
                break;
            }
            case ESC:
                return;
            }
        }
        while(1);

    }

}


//--------------------------------------------------Dat ve----------------------------------------------//

void DSVeCuaMotCB(PTRCB LCB, PTRCB temp, int current, DSMB LMB, TREEHK LHK){

RESTART:
    ;
    normal();
    system("cls");
    
    SetColor(LIGHTBLUE);
    rectangle(35, 0 , 27, 2);
    gotoxy(37, 1);
    cout<<"ENTER: TIEN HANH DAT VE";
    
    int x = 11;
    int y = 11;
    
    PTRCB q = temp;
    int flag = 0;
    while(flag < current){
        q = q->next;
        flag++;
    }
    
    PTRCB p = LCB;
    while(p != NULL && strcmp(p->info.maCB, q->info.maCB) != 0){
        p = p->next;
    }
    
    int i = searchMB(LMB, q->info.soHieuMB);
    gotoxy(10, 7);
    SetColor(10);
    cout<<"DANH SACH VE CUA CHUYEN BAY "<<q->info.maCB<<endl;

    int soDay = LMB.nodes[i]->soDay;
    int soHang = LMB.nodes[i]->soHang;
    
    SetColor(LIGHTBLUE);
    rectangle(8, 0, 20, 2);
    gotoxy(10, 1);
    SetColor(LIGHTBLUE);
    cout<<"VE CON TRONG: ";
    SetColor(9);
    cout<<(soDay * soHang) - p->DSVE.soLuongDat;
    
    SetColor(15);                                                //Ve bang vi tri ngoi tren may bay
    rectangle(8, 9, soHang * 6 + 4, soDay * 2 + 2);
    gotoxy(11, 11);
    for(int day = 1; day <= soDay; day++){
        for(int hang = 1; hang <= soHang; hang++){
            printf("%c%-5d", char(day + 64), hang);
        }
        y = y + 2;
        gotoxy(11, y);
    }
    
    gotoxy(68, 7);
    SetColor(15);
    veDSVeDaDat(p);
    
//    x = 11;
    y = 11;
    int currentX = 1;
    int currentY = 1;
    
    SetColor(LIGHTBLUE);
    gotoxy(x, y);
    printf("%c%-2d",char(currentX+64),currentY);
    
    int key;
    do{
        
        key = getch();
        if(key <= 0){
            key = getch();
        }
        
        switch(key){
            case UP:
                if(currentY > 1){
                    SetColor(15);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d",char(currentY + 64),currentX);
                    currentY--;
                    y -= 1;
                    
                    veDSVeDaDat(p);
                    SetColor(LIGHTBLUE);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d", char(currentY + 64), currentX);
                }
                break;
                
            case DOWN:
                if(currentY < LMB.nodes[i]->soDay){
                    SetColor(15);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d", char(currentY + 64), currentX);
                    currentY++;
                    y += 1;
                    
                    SetColor(LIGHTBLUE);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d", char(currentY + 64), currentX);
                }
                break;
                
            case LEFT:
                if(currentX > 1){
                    SetColor(15);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d", char(currentY + 64), currentX);
                    currentX--;
                    x -= 5;
                    
                    veDSVeDaDat(p);
                    SetColor(LIGHTBLUE);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d", char(currentY + 64), currentX);
                }
                break;
                
            case RIGHT:
                if(currentX < LMB.nodes[i]->soHang){
                    SetColor(15);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d", char(currentY + 64), currentX);
                    currentX++;
                    x += 5;
                    
                    veDSVeDaDat(p);
                    SetColor(LIGHTBLUE);
                    gotoxy(currentX + x - 1, currentY + y - 1);
                    printf("%c%-2d", char(currentY + 64), currentX);
                }
                break;
                
            case ENTER:
                nhapVe(LCB, p, temp, currentX, currentY, soHang, soDay, LHK);
                goto RESTART;
                break;
                
            case ESC:
                return;
        }
    }while(1);
}

void datVe(PTRCB LCB, DSMB LMB, TREEHK LHK){
    SetBGColor(0);
BEGIN:
    ;
    normal();
    system("cls");
    PTRCB q = LCB, temp;
    nodeChuyenBay tempFlight;
    initCB(temp);
    for(q = LCB; q != NULL; q = q->next){
        if(q->info.status == CON_VE){
            tempFlight.info = q->info;
            tempFlight.DSVE = q->DSVE;
            insertOrder(temp, tempFlight);
        }
    }
    
    SetColor(LIGHTBLUE);
    gotoxy(55, 7);
    cout<<"DANH SACH CAC CHUYEN BAY CO THE DAT VE";
    
    int current = 0;
    int demCB = countCB(temp);
    
    gotoxy(5, 9);
    cout<<"STT     |    Ma Chuyen Bay   |     Ngay Khoi Hanh     |      San Bay Den      | Trang Thai | So Hieu May Bay | So Ve Da Dat | So Luong Ve "<<endl;
    gotoxy(5, 10);
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    normal();
    
    if(temp != NULL){
        PTRCB p;
        int i = 0;
        for(p = temp; p != NULL; p = p->next){
            gotoxy(5, i + 11);
            printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d", i+1, p->info.maCB, p->info.time.hour, p->info.time.minute, p->info.time.day, p->info.time.month, p->info.time.year,
                   p->info.sbd, p->info.status, p->info.soHieuMB, p->DSVE.soLuongDat, p->DSVE.soLuongVe);
            i++;
        }
        
        p = temp;
        highlight();                //In highlight dong dau tien
        gotoxy(5, 11);
        printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d", 1, p->info.maCB, p->info.time.hour, p->info.time.minute, p->info.time.day, p->info.time.month, p->info.time.year,
                p->info.sbd, p->info.status, p->info.soHieuMB, p->DSVE.soLuongDat, p->DSVE.soLuongVe);
    
        int key;
        do{
            key = getch();
            if(key <= 0){
                key = getch();
            }
            switch(key){
                case UP:
                    if(current > 0){
                        normal();
                        gotoxy(5, current + 11);
                        inMotCB(temp, current);
                        current--;
                        
                        highlight();
                        gotoxy(5, current + 11);
                        inMotCB(temp, current);
                    }
                    break;
                    
                case DOWN:
                    if(current + 1 < demCB){
                        normal();
                        gotoxy(5, current + 11);
                        inMotCB(temp, current);
                        current++;
                        
                        highlight();
                        gotoxy(5, current + 11);
                        inMotCB(temp, current);
                    }
                    break;
                
                case ENTER:
                    DSVeCuaMotCB(LCB, temp, current, LMB, LHK);
                    goto BEGIN;
                    break;
                    
                case ESC:
                    deleteDSCB(temp);
                    SetBGColor(0);
                    return;
            }
        }while(1);
    }
    else{
        gotoxy(5, 11);
        SetColor(12);
        cout<<"DANH SACH CHUYEN BAY TRONG, VUI LONG TAO CHUYEN BAY DE DAT VE";
    }
    getch();
}

void huyVe(PTRCB &listCB)
{
MACB:
    ;
    system("cls");
    char maCB[20];
    char veHuy[5];
    char key;
    if(DSCBHuy(listCB)==-1)
    {
        normal();
        return;
    }
    normal();
    SetColor(LIGHTBLUE);
    gotoxy(10, 5);
    cout<<"NHAP MA CHUYEN BAY CO VE CAN HUY: ";
    nhapChuoi(maCB,20);
    if (maCB[0]==ESC)
        goto MACB;
    
    PTRCB p = searchCB(listCB, maCB);
    if (p == NULL)
    {
        SetColor(RED);
        alertError("===== KHONG THE HUY VE VI MA CHUYEN BAY KHONG TON TAI =====", 10, 5);
        goto MACB;
    }
    else if (p->info.status == 0)
    {
        SetColor(RED);
        alertError("===== KHONG THE HUY VE VI CHUYEN BAY NAY DA BI HUY =====", 10, 5);
        goto MACB;
    }
    else if (p->info.status == 3)
    {
        SetColor(RED);
        alertError("===== KHONG THE HUY VE VI CHUYEN BAY NAY DA HOAN THANH =====", 10, 5);
        goto MACB;
    }
    else if (p->DSVE.soLuongDat==0)
    {
        SetColor(RED);
        alertError("===== KHONG THE HUY VE VI CHUYEN BAY NAY CHUA CO VE DUOC DAT =====", 10, 5);
        goto MACB;
    }
    else
    {
VE:
        ;
        system("cls");
        normal();
        inDSVeDaDat(p);
        
        SetColor(LIGHTBLUE);
        rectangle(5, 0, 14, 2);
        gotoxy(7, 1);
        cout<<"ESC: CANCEL";
        
        gotoxy(10,6);
        SetColor(LIGHTBLUE);
        cout<<"NHAP VE CAN HUY: ";
        nhapChuoi(veHuy, 5);
        if (veHuy[0]==ESC)
        {
            rectangle(54, 24, 37, 2);
            gotoxy(56, 25);
            cout<<"===== DA HUY YEU CAU HUY VE =====";
                            
            gotoxy(10, 3);
            SetColor(LIGHTBLUE);
                
            rectangle(31, 29, 80, 2);
            gotoxy(33, 30);
            cout<<"VUI LONG CHON --> F4 : DE CHON LAI || F5 : CHON CHUYEN BAY MOI || ESC : THOAT";
            do
            {
                key = getch();
                if(key <=0)
                    key = getch();
                if (key==F4)
                {
                    clearError(10,2);
                    clearError(10,3);
                    clearError(10,6);
                    goto VE;
                }
                else if(key==F5)
                {
                    system("cls");
                    SetColor(15);
                    goto MACB;
                }
                else if(key==ESC)
                    return;
            }
            while(1);
        }
        
        int v=searchVe(p,veHuy);
        if (v==-1)
        {
            rectangle(44,24,52,2);
            SetColor(RED);
            alertError("====== VE KHONG TON TAI HOAC CHUA DUOC DAT ======", 46, 25);
            gotoxy(10, 3);
            SetColor(LIGHTBLUE);
            goto VE;
        }
        else
        {
            char confirm[5];
            rectangle(44,5,50,4);

            gotoxy(52, 6);
            SetColor(LIGHTBLUE);
            cout<<"BAN CO CHAC MUON HUY VE NAY KHONG?";
            
            gotoxy(46,7);
            SetColor(LIGHTBLUE);
            cout<<"NHAN \"YES\" DE XAC NHAN HUY VE \"NO\" DE HOAN TAC! ";
            
            gotoxy(68,8);
            SetColor(RED);
            do
            {
                nhapChu(confirm, 5);
                if (strcmp(confirm,"YES")==0 || strcmp(confirm,"NO")==0 || confirm[0]==ESC)
                    break;
                else
                {
                    for (int i=0;i<strlen(confirm);i++)
                        cout<<"\b \b";
                }
            }
            while (strcmp(confirm,"YES")!=0 || strcmp(confirm,"NO")!=0);
            
            if (confirm[0]==ESC)
                goto VE;
                
            else if (stricmp(confirm,"YES") == 0)
            {
                for (int i=v;i<p->DSVE.soLuongDat-1;i++)
                {
                    p->DSVE.nodes[i]=p->DSVE.nodes[i+1];
                }
                
                p->DSVE.soLuongDat--;
                p->info.status=1;
                
                saveFileDSCB(FileDSCB, listCB);
                rectangle(54, 24, 32, 2);
                gotoxy(56, 25);
                cout<<"===== HUY VE THANH CONG =====";
                            
                gotoxy(10, 3);
                SetColor(LIGHTBLUE);
                
                rectangle(31, 29, 80, 2);
                gotoxy(33, 30);
                cout<<"VUI LONG CHON --> F4 : DE CHON LAI || F5 : CHON CHUYEN BAY MOI || ESC : THOAT";
                
                do
                {
                    key = getch();
                    if(key <=0)
                        key = getch();
                    if (key==F4)
                    {
                        clearError(10,2);
                        clearError(10,3);
                        clearError(10,6);
                        goto VE;
                    }
                    else if(key==F5)
                    {
                        system("cls");
                        SetColor(15);
                        goto MACB;
                    }
                    else if(key==ESC)
                        return;
                }
                while(1);
            }
            else
            {
                rectangle(54, 24, 37, 2);
                gotoxy(56, 25);
                cout<<"===== DA HUY YEU CAU HUY VE =====";
                            
                gotoxy(10, 3);
                SetColor(LIGHTBLUE);
                
                rectangle(31, 29, 80, 2);
                gotoxy(33, 30);
                cout<<"VUI LONG CHON --> F4 : DE CHON LAI || F5 : CHON CHUYEN BAY MOI || ESC : THOAT";
                do
                {
                    key = getch();
                    if(key <=0)
                        key = getch();
                    if (key==F4)
                    {
                        clearError(10,2);
                        clearError(10,3);
                        clearError(10,6);
                        goto VE;
                    }
                    else if(key==F5)
                    {
                        system("cls");
                        SetColor(15);
                        goto MACB;
                    }
                    else if(key==ESC)
                        return;
                }
                while(1);
            }
        }
    }
}