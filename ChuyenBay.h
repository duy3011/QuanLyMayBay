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

//--------------------------------------------Dinh nghia cac module chuyen bay---------------------//

int emptyCB(PTRCB LCB){
    return (LCB == NULL);
}
int emptyLCB(PTRCB LCB)
{
    return (LCB==NULL ? true : false);
}
void initCB(PTRCB &LCB){                //Khoi tao danh sach chuyen bay
    LCB = NULL;
}

int countCB(PTRCB LCB){
    PTRCB p = LCB;
    int count = 0;
    for(p = LCB; p != NULL; p = p->next){
        count++;
    }
    return count;
}

void deleteDSCB(PTRCB &LCB){
    PTRCB p;
    while(LCB != NULL){
        p = LCB;
        LCB = LCB->next;
        delete p;
    }
//    LCB = NULL;
}


void deleteFirst(PTRCB &First){
    PTRCB p;
    if(First == NULL){
        cout<<"KHONG THE XOA VI DANH SACH RONG";
        return;
    }
	
	else if(First->next == NULL){
		p = First;
		delete p;
		First = NULL;
	}
	else{
		p = First;
    	First = p->next;
		delete p;	
		
	}
    return;
}

void deleteAfter(PTRCB p){
    PTRCB q;
    if(p == NULL || p->next == NULL){
        cout<<"KHONG THE XOA...";
        return;
    }
    q = p->next;
    p->next = q->next;
    delete q;
}


void outputCurrentTime(){                //Ham in ra thoi gian hien tai
    tm *crt = currentTime();
    int currentYear = crt->tm_year + 1900;
    int currentMonth = crt->tm_mon + 1;
    int currentDay = crt->tm_mday;
    int currentHour = crt->tm_hour;
    int currentMinute = crt->tm_min;
    SetColor(7);
    gotoxy(30, 1);
    cout<<"Thoi gian hien tai: "<<currentHour<<":"<<currentMinute<<"\t"<<currentDay<<"/"<<currentMonth<<"/"<<currentYear;
}

bool checkYear(int year){                //Kiem tra nam co nhuan hay khong?
    return ((year % 4 == 0 && year % 10 != 0) || (year % 4 == 0 && year % 10 == 0));
}

int time(TIME date){                    //Ham tinh thoi gian truoc khi chuyen bay khoi hanh
    int h = date.hour;                    //Gio khoi hanh
    int mte = date.minute;                //Phut khoi hanh
    int d = date.day;                    //Ngay khoi hanh
    int mth = date.month;                //Thang khoi hanh
    int y = date.year;                    //Nam khoi hanh
    
    tm *crt = currentTime();
    int hour = crt->tm_hour;            //Thoi gian hien tai
    int minute = crt->tm_min;
    int day = crt->tm_mday;
    int month = crt->tm_mon + 1;
    int year = crt->tm_year + 1900;
    
    int sumDay = 0;
    int sumMinute = 0;
    bool flag = false;
    while(y >= year){
        flag = true;
        if(y == year && mth ==  month){
            sumDay = sumDay + d - day;    //So ngay con lai truoc khi chuyen bay khoi hanh
            break;
        }
        else{
            if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month ==12){
                sumDay = sumDay  + 31 - day;
            }
            else if(month == 4 || month == 6 || month == 9 || month == 11){
                sumDay = sumDay + 30 - day;
            }
            else{
                if(checkYear(year) == true){
                    sumDay = sumDay + 29 - day;
                }
                else{
                    sumDay = sumDay + 28 - day;
                }
            }
        }
        month++;
        day = 0;
        if(month == 13){
            year++;
            month = 1;
        }
    }
    if(flag == true){
        sumMinute = sumDay * 24 * 60 + (h - hour) * 60 + mte - minute;        //Tong so phut truoc khi chuyen bay khoi hanh
    }
    return sumMinute;
}

int nhapDate(TIME &date, int current, int x){
    SetColor(WHITE);
    int maxDay;
    cout<<"   :   -    /    /     ";
    
HOUR:
    ;
    SetColor(WHITE);
    clearError(8, 4);
    gotoxy(8, 4);
    cout<<"NHAP GIO:";
    gotoxy(x + 46, current);
    char hour[3];
    nhapSo(hour, 2);
    if (hour[0]==ESC)
    {
        return -1;
    }
    date.hour = atoi(hour);
    gotoxy(x + 48, current);
    cout<<":   -    /    /     ";
    if(date.hour < 0 || date.hour > 23){
        clearError(8, 4);
        alertError("GIO PHAI TU 0H TOI 23H", 8, 4);
        gotoxy(x + 46, current);
        cout<<"  :   -    /    /     ";
        goto HOUR;
    }
    
MINUTE:
    ;
    SetColor(WHITE);
    clearError(8, 4);
    gotoxy(8, 4);
    cout<<"NHAP PHUT:";
    
    gotoxy(x + 49, current);
    char minute[3];
    nhapSo(minute, 2);
    if (minute[0]==ESC)
    {
        return -1;
    }
    date.minute = atoi(minute);
    
    if(date.minute < 0 || date.minute > 60){
        clearError(8, 4);
        alertError("SO PHUT PHAI TU 0 TOI 60", 8, 4);
        gotoxy(x + 49, current);
        cout<<"   -    /    /     ";
        goto MINUTE;
    }
    
DAY:
    ;
    SetColor(WHITE);
    clearError(8, 4);
    gotoxy(8, 4);
    cout<<"NHAP NGAY:";
    
    gotoxy(x + 54, current);
    char day[3];
    nhapSo(day, 2);
    if (day[0]==ESC)
    {
        return -1;
    }
    date.day = atoi(day);
    if(date.day >31 || date.day < 1){
        clearError(8, 4);
        alertError("NGAY KHONG HOP LE VUI LONG NHAP LAI", 8, 4);
        gotoxy(x + 54, current);
        cout<<"   /    /     ";
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
    {
        return -1;
    }
    date.month = atoi(month);
    
    if(date.month < 1 || date.month > 12){
        clearError(8, 4);
        alertError("THANG KHONG HOP LE VUI LONG NHAP LAI", 8, 4);
        gotoxy(x + 57, current);
        cout<<"/    /     ";
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
            cout<<"   /    /     ";
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
    {
        return -1;
    }
    date.year = atoi(year);
    
    tm* crt = currentTime();
    int currentDay = crt->tm_mday;
    int currentMonth = crt->tm_mon + 1;
    int currentYear = crt->tm_year + 1900;
    
    if(date.year < currentYear || date.year == currentYear && date.month < currentMonth || date.year == currentYear && date.month == currentMonth && date.day < currentDay){
        clearError(8, 4);
        alertError("NAM PHAI LON HON NAM HIEN TAI", 8, 4);
        gotoxy(x + 62, current);
        cout<<"/     ";
        goto YEAR;
    }
}

PTRCB searchCB(PTRCB LCB, char *maCB){
    PTRCB p;
    for(p = LCB; p != NULL; p = p->next){
        if(strcmp(p->info.maCB, maCB) == 0){
            return p;
        }
    }
    return NULL;                            //Khong tim thay ma chuyen bay
}

void insertLast(PTRCB &First, nodeChuyenBay flight){
    PTRCB p = new nodeChuyenBay;        // p = flight;
    p->info = flight.info;
    p->DSVE = flight.DSVE;
    p->next = NULL;
    if(First == NULL){
        First = p;
    }
    else{
        PTRCB Last = First;
        for( ; Last->next != NULL; Last = Last->next);
        Last->next = p;
    }
}

void insertOrder(PTRCB &LCB, nodeChuyenBay flight){
    PTRCB p,t,s;    //t: con tro truoc - s: con tro sau
    p = new nodeChuyenBay;
    p->info = flight.info;
    p->DSVE = flight.DSVE;
    
    for(s = LCB; s != NULL && strcmp(s->info.maCB, flight.info.maCB) < 0; t = s, s = s->next);
    if(s == LCB){
        p->next = LCB;
        LCB = p;
    }
    else{
        p->next = s;
        t->next = p;
    }
}

void insertOrderTime(PTRCB &LCB, CB flight){
    PTRCB p, t, s;     //t: con tro truoc - s: con tro sau
    p = new nodeChuyenBay;
    p->info = flight;
    int getTime = time(flight.time);
    
    for(s = LCB; s != NULL && time(s->info.time) < getTime; t = s, s = s->next);
    if(s == LCB){
        p->next = LCB;
        LCB = p;
    }
    else{
        p->next = s;
        t->next = p;
    }

}

void nhapCB(PTRCB &LCB, DSMB LMB){
    outputCurrentTime();
    
    SetColor(LIGHTBLUE);
    rectangle(45,35,44,2);
    gotoxy(47,36);
    cout<<"ESC + ESC: EXIT || ESC + ENTER: NHAP LAI";
    ShowCur(true);
    
    nodeChuyenBay flight;
    int key;
    int i;

MACB:
    ;
    gotoxy(8, 7);
    SetColor(LIGHTBLUE);
    cout<<"STT       |     MA CHUYEN BAY     |       NGAY KHOI HANH        |    SAN BAY DEN    |  SO HIEU MAY BAY  |"<<endl;
    gotoxy(8, 8);
    cout<<"--------------------------------------------------------------------------------------------------------|"<<endl;
    int current = 9;
    int stt = 1;
    do{
        clearError(8, 2);
        SetColor(LIGHTBLUE);
//        clearError(1, 2);
        gotoxy(8, current);
        SetColor(WHITE);
        printf("%-10d", stt);
        stt++;
        cout<<"|                       |                             |                   |                   |"<<endl;
        
        SetColor(LIGHTBLUE);
        clearError(8, 4);
        gotoxy(8, 4);
        cout<<"NHAP MA CHUYEN BAY:";
        gotoxy(25, current);
        SetColor(WHITE);
        nhapChuoi(flight.info.maCB, 10);
        if(flight.info.maCB[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto MACB;
            }
        if(searchCB(LCB, flight.info.maCB) != NULL){
            stt--;
			clearError(8, 4);
            alertError("MA CHUYEN BAY BI TRUNG!", 8, 4);
            gotoxy(25, current);
            cout<<"        ";
            goto MACB;
        }
        
DATE:
        ;
        SetColor(LIGHTBLUE);
        clearError(8, 4);
        gotoxy(8, 4);
        cout<<"NHAP THOI GIAN KHOI HANH:";
        //gotoxy(46, current);
        //cout<<"                          ";
        gotoxy(45, current);
        
    
//        clearError(8, 4);
        if (nhapDate(flight.info.time, current, 0)==-1)
        {
            int confirm;
            confirm=getch();
            if (confirm==ESC)
                return;
            if (confirm==ENTER)
                goto MACB;
        }
        SetColor(WHITE);
        int flightTime = time(flight.info.time);                //Tong thoi gian truoc khi chuyen bay khoi hanh
        if(flightTime <= setupTimeCB){
            clearError(8, 4);
//            alertError("GIO KHOI HANH CUA CHUYEN BAY PHAI CACH IT NHAT 2 NGAY", 8, 4);
            gotoxy(8, 4);
            cout<<"GIO KHOI HANH CUA CHUYEN BAY PHAI CACH IT NHAT 2 NGAY";
            Sleep(5000);
            gotoxy(8, 4);
            cout<<"													 	";
            gotoxy(45, current);
            cout<<"        ";
            goto DATE;
        }
        
SANBAYDEN:
        ;
        SetColor(LIGHTBLUE);
        clearError(8, 4);
        gotoxy(8, 4);
        cout<<"NHAP SAN BAY DEN:";
        gotoxy(76, current);
        cout<<"               ";
        gotoxy(76, current);
        SetColor(WHITE);
        
            nhapChu(flight.info.sbd, 16);
            if(flight.info.sbd[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto MACB;
            }
        SetColor(LIGHTBLUE);
        gotoxy(120, 7);
        cout<<"DANH SACH SO HIEU MAY BAY"<<endl;
        gotoxy(120, 8);
        cout<<"-------------------------"<<endl;
        int k = 9;
        for(int i = 0 ;  i < LMB.soMB; i++){
            gotoxy(130, k++);
            cout<<LMB.nodes[i]->soHieuMB<<endl;
        }
        
SHMB:
        ;
        SetColor(LIGHTBLUE);
        clearError(8, 4);
        gotoxy(8, 4);
        cout<<"NHAP SO HIEU MAY BAY:";
        gotoxy(98, current);
        SetColor(WHITE);
        nhapChuoi(flight.info.soHieuMB, 10);
        if(flight.info.soHieuMB[0] == ESC)
            {
                int confirm = getch();
                if (confirm == ESC)
                    return;
                else if (confirm == ENTER)
                    goto MACB;
            }
        i = searchMB(LMB, flight.info.soHieuMB);
        if(i == -1){
            clearError(8, 4);
            alertError("KHONG TIM THAY SO HIEU MAY BAY CAN TIM!", 8, 4);
            gotoxy(98, current);
            cout<<"        ";
            goto SHMB;
        }
        
        PTRCB q = LCB, tmpCheckCB;
        initCB(tmpCheckCB);
        for(q = LCB; q != NULL; q = q->next){
            if(strcmp(q->info.soHieuMB, flight.info.soHieuMB) == 0 && q->info.status == 1){
                insertOrderTime(tmpCheckCB, q->info);                            //Nhung chuyen bay co cung so hieu may bay
            }                                                                    //se duoc dua vao mang tam de xu ly
        }
        int count = countCB(tmpCheckCB);
        if(count != 0){
            PTRCB temp;
            for(temp = tmpCheckCB; temp != NULL; ){
                if(abs(time(temp->info.time) - flightTime)  < setupTimeSHMB){    //De tao nhieu chuyen bay co cung so hieu may bay
                    clearError(8, 4);                                            //thi thoi gian khoi khoi hanh cua moi chuyen bay phai cach nhau it nhat 5 ngay
//                    alertError("THOI GIAN KHOI HANH CUA HAI CHUYEN BAY CUNG SO HIEU MAY BAY PHAI CACH NHAU IT NHAT 5 NGAY", 8, 4);
                    gotoxy(8, 4);
                    cout<<"THOI GIAN KHOI HANH CUA HAI CHUYEN BAY CUNG SO HIEU MAY BAY PHAI CACH NHAU IT NHAT 5 NGAY";
                    Sleep(5000);
					gotoxy(8, 4);
                    cout<<"																							";
                    
					gotoxy(98, current);
                    cout<<"        ";
                    deleteDSCB(tmpCheckCB);
                    gotoxy(76, current);
                    cout<<"               ";
                    goto DATE;
                }
            
                temp = temp->next;
            }
        }
        
        flight.DSVE.soLuongVe = LMB.nodes[i]->soHang * LMB.nodes[i]->soDay; //So luong ve cua mot chuyen bay duoc tao tu dong = read only
        flight.DSVE.soLuongDat = 0;
        flight.DSVE.nodes = new Ve[flight.DSVE.soLuongVe];
        flight.info.status = CON_VE;
        current++;
        tangslBay(LMB,flight.info.soHieuMB);
        saveFileDSMB(FileDSMB, LMB);
    //    insertLast(LCB, flight);
        insertOrder(LCB, flight);
        saveFileDSCB(FileDSCB, LCB);
        SetColor(LIGHTBLUE);
        gotoxy(8, 2);

        cout<<"THEM CHUYEN BAY THANH CONG, NHAN ENTER DE TIEP TUC THEM CHUYEN BAY, NHAN PHIM BAT KY DE THOAT";
        delete []flight.DSVE.nodes;
        key = getch();
    }while(key == ENTER);
}

void deleteCB(PTRCB &LCB, int current, DSMB& LMB){
    PTRCB p = LCB;
    if(current > 0){                        //Truong hop chuyen bay can xoa la chuyen bay khac voi chuyen bay dau
        int flag = 0;                        //Hay co nghia la node can xoa khong phai la First
        while(flag < current - 1){            //Di den vi tri truoc node can xoa
            p = p->next;
            flag++;
        }
        if(p->next->DSVE.soLuongDat > 0 && p->next->info.status == CON_VE){
            alertError("KHONG THE XOA CHUYEN BAY NAY VI CHUYEN BAY DA CO VE DUOC DAT", 8, 5);
            return;
        }
    }
    else if(p->DSVE.soLuongDat > 0 && p->info.status == CON_VE){
        alertError("KHONG THE XOA CHUYEN BAY NAY VI CHUYEN BAY DA CO VE DUOC DAT", 8, 5);
        return;
    }
    
CONFIRM:
    ;
    char confirm[4];
    gotoxy(8, 4);
    normal();
    SetColor(LIGHTBLUE);
    cout<<"BAN CO THUC SU MUON XOA CHUYEN BAY "<<p->info.maCB<<" ?";
    gotoxy(8,5);
    cout<<"NHAN \"YES\" DE XAC NHAN, NHAN \"NO\" DE HUY CHUC NANG";
    SetColor(12);
    gotoxy(60, 5);
    nhapChu(confirm, 5);
    clearError(8, 4);
    clearError(8, 5);
    if(strcmp(confirm, "YES") == 0){
//		giamslBay(LMB,p->next->info.soHieuMB,LCB);
//      saveFileDSMB(FileDSMB, LMB);
        if(current > 0){
        	giamslBay(LMB,p->next->info.soHieuMB,LCB);
            deleteAfter(p);
            alertError("XOA CHUYEN BAY THANH CONG", 8, 5);
        }
        else if(current == 0){
			giamslBay(LMB,p->info.soHieuMB,LCB);
			deleteFirst(LCB);
            alertError("XOA CHUYEN BAY THANH CONG", 8, 5);
        }
        saveFileDSMB(FileDSMB, LMB);
        saveFileDSCB(FileDSCB, LCB);
        
        system("cls");
    }
    else if(strcmp(confirm, "NO") == 0){
        alertError("DA HUY YEU CAU XOA CHUYEN BAY!", 8, 5);
    }
    else
        goto CONFIRM;
}

void editCB(PTRCB &LCB, int current, DSMB LMB){
    normal();
    PTRCB p = LCB;
    int flag = 0;
    while(flag < current){
        p = p->next;
        flag++;
    }
    if(p->DSVE.soLuongDat > 0){
        alertError("KHONG THE SUA CHUYEN BAY VI CHUYEN BAY DA CO HANH KHACH", 8, 4);
        SetBGColor(0);
        return ;
    }
    else if(p->info.status == 0){
        alertError("KHONG THE SUA CHUYEN BAY VI CHUYEN BAY DA BI HUY", 8, 4);
        SetBGColor(0);
        return ;
    }
    SetColor(YELLOW);
    rectangle(51,43,44,2);
    gotoxy(53,44);
    cout<<"ESC + ESC: EXIT || ESC + ENTER: NHAP LAI";
    normal();
    SetColor(LIGHTBLUE);
    gotoxy(53, 28);
    cout<<"THONG TIN CHINH SUA CHUYEN BAY";
    gotoxy(15, 30);
    cout<<"        NGAY KHOI HANH        |                 SAN BAY DEN                 |        SO HIEU MAY BAY  "<<endl;
    gotoxy(15, 31);
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    gotoxy(15, 32);
    cout<<"                              |                                             |                               "<<endl;
    
DATE:
    ;
    gotoxy(18, 32);
    cout<<"                          ";
    SetColor(LIGHTBLUE);
    gotoxy(18, 32);
    if(nhapDate(p->info.time, 32, -27)==-1)
    {
        int confirm = getch();
        if (confirm == ESC)
            return;
        else if (confirm == ENTER)
            goto DATE;
    };
    int t = time(p->info.time);
    if(t <= setupTimeCB){
        alertError("GIO KHOI HANH CUA CHUYEN BAY PHAI CACH IT NHAT 2 NGAY SO VOI THOI DIEM HIEN TAI", 8, 4);
        clearError(18,32);
        goto DATE;
    }
    
    clearError(8, 4);
    gotoxy(8, 4);
    cout<<"NHAP SAN BAY DEN";
    gotoxy(55, 32);
    cout<<"                   ";
    gotoxy(50, 32);
    nhapChu(p->info.sbd, 16);
    if (p->info.sbd[0]==ESC)
    {
        int confirm = getch();
        if (confirm == ESC)
            return;
        else if (confirm == ENTER)
        {
            for (int i=0;i<strlen(p->info.sbd);i++)
                cout<<"\b \b";
            goto DATE;
        }
    }
    SetColor(LIGHTBLUE);
    gotoxy(130, 28);
    cout<<"DANH SACH SO HIEU MAY BAY"<<endl;
    gotoxy(130, 29);
    cout<<"-------------------------"<<endl;
    int k = 30;
    for(int i = 0; i < LMB.soMB; i++){
        gotoxy(135, k++);
        cout<<LMB.nodes[i]->soHieuMB<<endl;
    }
    
SHMB:
    ;
    clearError(8, 4);
    SetColor(LIGHTBLUE);
    gotoxy(8, 4);
    cout<<"NHAP SO HIEU MAY BAY";
    gotoxy(100, 32);
    nhapChuoi(p->info.soHieuMB, 7);
    if (p->info.soHieuMB[0]==ESC)
    {
        int confirm = getch();
        if (confirm == ESC)
            return;
        else if (confirm == ENTER)
            goto DATE;
    }
    //clearError(8, 4);
    int i = searchMB(LMB, p->info.soHieuMB);
    if(i == -1){
        alertError("SO HIEU MAY BAY KHONG TON TAI TRONG DANH SACH", 8, 4);
        gotoxy(100, 32);
        cout<<"            ";
        goto SHMB;
    }
    
    PTRCB q, tempCheckCB;
    initCB(tempCheckCB);                    //Khoi tao danh sach chuyen bay tam de kiem tra cac chuyen bay co cung so hieu may bay
    for(q = LCB; q != NULL; q = q->next){
        if( strcmp(q->info.soHieuMB, p->info.soHieuMB) == 0 && q->info.status == 1 && strcmp(q->info.maCB, p->info.maCB) != 0){
            insertOrderTime(LCB, q->info);
        }
    }
    int a = countCB(tempCheckCB);
    if(a != 0){
        PTRCB h;
        for(h = tempCheckCB; h != NULL; ){
            if(abs(time(h->info.time) - t) < setupTimeSHMB){
                alertError("THOI GIAN KHOI HANH CUA HAI CHUYEN BAY CUNG SO HIEU MAY BAY PHAI CACH NHAU IT NHAT 5 NGAY", 8, 4);
                deleteDSCB(tempCheckCB);
                clearError(100, 32);
                goto DATE;
            }
            h = h->next;
        }
    }
    
    p->DSVE.soLuongVe = LMB.nodes[i]->soHang * LMB.nodes[i]->soDay;
    saveFileDSCB(FileDSCB, LCB);
    system("cls");
}

void updateCB(PTRCB &LCB, DSMB LMB){
    int soLuongMenu = 2;
    char menuUpdateCB[][70] =
    {
        "THEM CHUYEN BAY",
        "CAP NHAT CHUYEN BAY"
    };
    int m;
    do{
        SetBGColor(0);
        ShowCur(true);
        system("cls");
        SetColor(9);
        rectangle(69, 35, 32, 2);
        gotoxy(70, 36);
        cout<<"ESC: QUAY LAI | ENTER: XAC NHAN";
        m = menu(55, 10, menuUpdateCB, soLuongMenu);
        switch(m){
            case 0:
                {
                system("cls");
                nhapCB(LCB,LMB);
                }
            break;
            case 1:{
                system("cls");
                inDSCB(LCB, LMB);
            
            }
            break;
            case ESC:
                return;
        }
    }while(m != -1);
}

void cancelCB(PTRCB &LCB, int current, DSMB& LMB){
        PTRCB p = LCB;
    int index = 0;
    while(index < current){
        p = p->next;
        index++;
    }
    
    if(p->info.status == 0){
        normal();
        alertError("KHONG THE HUY CHUYEN BAY NAY VI CHUYEN BAY DA DUOC HUY TRUOC DO", 8, 4);
        return;
    }
    
    normal();
    clearError(8, 4);
CONFIRM:
    ;
    gotoxy(8, 4);
    cout<<"BAN CO THUC SU MUON HUY CHUYEN BAY MANG SO HIEU "<<p->info.maCB<<" ?";
    gotoxy(8, 5);
    cout<<"NHAN \"YES\" DE XAC NHAN, NHAN \"NO\" DE HOAN TAC CHUC NANG";
    char confirm[4];
    gotoxy(65, 5);
    nhapChu(confirm, 5);
    if(strcmp(confirm, "YES") != 0 && strcmp(confirm, "NO") != 0){
        clearError(8, 4);
        gotoxy(8, 4);
        cout<<"VUI LONG NHAP DUNG YEU CAU DE CHUC NANG DUOC THUC HIEN";
        Sleep(5000);
        clearError(8, 4);
        gotoxy(65, 5);
        cout<<"     ";
        goto CONFIRM;
    }
    
    clearError(8, 4);
    clearError(8, 5);
    
    if(strcmp(confirm, "YES") == 0){
        giamslBay(LMB,p->info.soHieuMB,LCB);
        saveFileDSMB(FileDSMB, LMB);
        p->info.status = 0;
        saveFileDSCB(FileDSCB, LCB);
        SetColor(LIGHTBLUE);
        alertError("HUY CHUYEN BAY THANH CONG", 8, 4);
        system("cls");
    }
    else{
        alertError("HOAN TAC CHUC NANG HUY CHUYEN BAY THANH CONG", 8, 4);
    }
}

