#pragma once

#include "Var.h"
#include "ChuyenBay.h"
#include "Ve.h"
#include "mylib.h"
//--------------------------------------------Cac module ve hanh khach----------------------------//
void initTree(TREEHK &);
int compareCCCD(HK , HK );
void insertHK(TREEHK &, HK );
void preorder(TREEHK );
void clearErrTTHK(int , int );
TREEHK searchHK(TREEHK , char [13]);
int nhapHK(TREEHK &, char [13], int );
void saveFileDSHK(char *, TREEHK );
void loadFileDSHK(char *, TREEHK &);

//--------------------------------------------DSHK tren chuyen bay--------------------------------//
void DSHKCB(PTRCB , TREEHK , int );
void inDSHK(PTRCB , TREEHK );

//--------------------------------------------------Dinh nghia cac module hanh khach--------------------//

void initTree(TREEHK &LHK){
    LHK = NULL;
}

int compareCCCD(HK khach1, HK khach2){
    return strcmp(khach1.CCCD, khach2.CCCD);
}

void insertHK(TREEHK &LHK, HK khach){

    if(LHK == NULL){
        LHK = new nodeHK;
        LHK->info = khach;
        LHK->left = NULL;
        LHK->right = NULL;
    }
    else{
        if(compareCCCD(LHK->info, khach) == 1){
            insertHK(LHK->left, khach);
        }
        else if(compareCCCD(LHK->info, khach) == -1){
            insertHK(LHK->right, khach);
        }
    }
}

void preorder(TREEHK LHK){                //Duyet cay theo thu tu NLR
    if(LHK != NULL){
        cout<<LHK->info.CCCD<<endl;
        preorder(LHK->left);
        preorder(LHK->right);
    }
}

void clearErrTTHK(int x, int y){
    gotoxy(x,y);
    cout<<"                        ";
}


TREEHK searchHK(TREEHK root, char CCCD[13]){
    TREEHK p;
    p = root;
    while(p != NULL && (strcmp(p->info.CCCD, CCCD) != 0)){
        if(strcmp(p->info.CCCD, CCCD) == 1){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }
    return (p);
}

int nhapHK(TREEHK &LHK, char CCCD[13], int soDay){
    HK khach;
    strcpy(khach.CCCD, CCCD);
    int y = 9 + soDay * 2;
    gotoxy(37, y + 10);
    SetColor(LIGHTBLUE);
START:
    ;
    cout<<"THEM THONG TIN HANH KHACH";
    
    gotoxy(11, y + 12);
    cout<<("        CCCD        |           Ho           |        Ten        |     Phai");
    gotoxy(11, y + 13);
    cout<<"------------------------------------------------------------------------------"<<endl;
    
    gotoxy(11, y + 14);
    SetColor(15);
    cout<<"                    |                        |                   |             "<<endl;
    
    gotoxy(17, y + 14);
    cout<<CCCD;
    
    gotoxy(60, y + 8);
    SetColor(LIGHTBLUE);
    fflush(stdin);
    cout<<"VUI LONG NHAP HO";
    SetColor(15);
    gotoxy(34, y + 14);
    fflush(stdin);
    nhapChu(khach.Ho, 51);
    if (khach.Ho[0]==ESC)
    {
        int confirm=getch();
        if (confirm==ESC)
            return -1;
        if (confirm==ENTER)
            goto START;
    }
    deleteEnter(khach.Ho);
    
    SetColor(LIGHTBLUE);
    gotoxy(60, y + 8);
    cout<<"VUI LONG NHAP TEN";
    SetColor(15);
    gotoxy(62, y + 14);
    nhapChu(khach.Ten, 11);
    if (khach.Ten[0]==ESC)
    {
        int confirm=getch();
        if (confirm==ESC)
            return -1;
        if (confirm==ENTER)
            goto START;
    }


GT:
    ;
//    clearError(60, y + 8);
    SetColor(LIGHTBLUE);
    gotoxy(60, y + 8);
//    fflush(stdin);
    cout<<"VUI LONG NHAP GIOI TINH";
    SetColor(15);
    gotoxy(82, y + 14);
    nhapChu(khach.Phai, 5);
    if (khach.Phai[0]==ESC)
    {
        int confirm=getch();
        if (confirm==ESC)
            return -1;
        if (confirm==ENTER)
            goto START;
    }
//    nhapGT(khach.Phai, 82, y + 14);
    if(strcmp(khach.Phai, "NAM") == 0 || strcmp(khach.Phai, "NU") == 0){
        insertHK(LHK, khach);
        saveFileDSHK(FileDSHK, LHK);
    }
    else{
    //    alertError("GIO TINH PHAI LA NAM HOAC NU", 60, y + 8);
        gotoxy(60, y + 8);
        cout<<"GIOI TINH PHAI LA NAM HOAC NU";
        Sleep(3000);
        gotoxy(60, y + 8);
        cout<<"                                     ";
        gotoxy(82, y + 14);
        cout<<"    ";
        goto GT;
    }
}


void saveFileDSHK(char *filename, TREEHK LHK){    //Duyet theo preorder - NLR
    FILE *f;
    f = fopen(filename, "w");
    
    if(f){
        const int STACKSIZE = 300;
        TREEHK Stack[STACKSIZE];
        
        int sp = -1;
        TREEHK p = LHK;                    //LHK = root
        
        while(p != NULL){
            fprintf(f,"%s\n%s\n%s\n%s\n\n", p->info.CCCD, p->info.Ho, p->info.Ten, p->info.Phai);
            if(p->right != NULL){
                Stack[++sp] = p->right;
            }
            if(p->left != NULL){
                p = p->left;
            }
            else if(sp == -1){
                break;
            }
            else{
                p = Stack[sp--];
            }
        }
        fclose(f);
    }
    else{
        alertError("KHONG THE MO file \"DSHK.txt\"", 8, 4);
    }
}

void loadFileDSHK(char *filename, TREEHK &LHK){
    HK khach;
    
    FILE *f;
    f = fopen(filename, "r");
    if(f){
        fseek(f, 0, SEEK_END);
        if(ftell(f) == 0){
            fclose(f);
            return;
        }
        fseek(f, 0, SEEK_SET);
        while(!feof(f)){
            fscanf(f, "%s", &khach.CCCD);
            fgets(khach.Ho, 250, f);
            fgets(khach.Ho, 250, f);
            deleteEnter(khach.Ho);
            fscanf(f, "%s", &khach.Ten);
            fscanf(f, "%s", &khach.Phai);
            
            if(!feof(f)){
                insertHK(LHK, khach);
            }
        }
        fclose(f);
    }
    else{
        alertError("KHONG THE MO FILE \"DSHK.txt\"", 8, 4);
    }
}
//------------------------------------------------------------------------------------------------------//
//----------------------------------DSHK TREN CHUYEN BAY----------------------------------//

void DSHKCB(PTRCB p, TREEHK listHK)
{
    fflush(stdin);
    normal();
    system("cls");
    SetColor(LIGHTBLUE);
    
    rectangle(5, 0, 12, 2);
    gotoxy(7, 1);
    cout<<"ESC: BACK";

    gotoxy(50,5);
    cout<<"    DANH SACH HANH KHACH THUOC CHUYEN BAY: "<<p->info.maCB;
    
    gotoxy(35,7);
    printf("        NGAY GIO KHOI HANH: %02d/%02d/%04d %02d:%02d           NOI DEN: %s", p->info.time.day, p->info.time.month, p->info.time.year, p->info.time.hour, p->info.time.minute, p->info.sbd);
    
    gotoxy(25,9);
    cout<<"STT     |    So Ve    |        So CCCD        |                     Ho                    |     Ten     |      Phai      "<<endl;
    
    gotoxy(25,10);
    cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
    
    normal();
    TREEHK HK;
    for(int i=0; i<p->DSVE.soLuongDat; i++)
    {
        gotoxy(25,11+i);
        HK=searchHK(listHK, p->DSVE.nodes[i].CCCD);
        printf("%-8d|     %-8s|       %-16s|       %-36s|   %-10s|     %-7s",i+1, p->DSVE.nodes[i].soGhe, p->DSVE.nodes[i].CCCD, HK->info.Ho, HK->info.Ten, HK->info.Phai);
    }
    int key;
    do
    {
        key =getch();
        if(key==ESC)
        {
            system("cls");
            return;
        }
    }
    while(1);
}

void inDSHK(PTRCB listCB, TREEHK listHK)
{
    int count=0;
    int crtPage = 1;
    
DSHK:
    ;
    normal();
    system("cls");
    SetColor(LIGHTBLUE);
    
    gotoxy(55,7);
    cout<<"DANH SACH CHUYEN BAY";
    
    gotoxy(5,9);
    cout<<"STT     |    Ma Chuyen Bay   |     Ngay Khoi Hanh     |      San Bay Den      | Trang Thai | So Hieu May Bay | So Ve Da Dat | So Luong Ve "<<endl;
    
    gotoxy(5,10);
    cout<<"------------------------------------------------------------------------------------------------------------------------------------------"<<endl;

    rectangle(33, 29, 70, 2);
    gotoxy(35, 30);
    cout<<"TRANG THAI: 0 - HUY CHUYEN, 1 - CON VE, 2 - HET VE, 3 - HOAN TAT";

    int n = countCB(listCB);
LR:
    ;
    SetColor(LIGHTBLUE);
    rectangle(60,39,10,2);
    gotoxy(62,40);
    cout<<"PAGE :"<<crtPage;
    SetColor(WHITE);
    int current = 0;
    int pages = n/numPageCBHK;
    if(n%numPageCBHK>0)
        pages++;
    if(!emptyCB(listCB))
    {
        PTRCB p,q;
        p=listCB;
        q=p;
        int i=(crtPage-1)*numPageCBHK;
        int c=0;
        while(c<i)
        {
            p=p->next;
            q=p;
            c++;
        }
        int y=11;
        for(; p!=NULL && i<crtPage*numPageCBHK; p=p->next)
        {
            gotoxy(5,y++);
            printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",i+1,p->info.maCB,p->info.time.hour,p->info.time.minute,p->info.time.day,p->info.time.month,p->info.time.year,
                   p->info.sbd,p->info.status,p->info.soHieuMB,p->DSVE.soLuongDat,p->DSVE.soLuongVe);
            i++;
        }
        gotoxy(5,11);
        highlight();
        printf("%-8d|     %-15s| %02d:%02d - %02d / %02d / %04d |    %-19s|     %-7d|    %-13s|      %-8d|    %-9d",(crtPage-1)*15+1,q->info.maCB,q->info.time.hour,q->info.time.minute,q->info.time.day,q->info.time.month,q->info.time.year,
               q->info.sbd,q->info.status,q->info.soHieuMB,q->DSVE.soLuongDat,q->DSVE.soLuongVe);
        int f = (crtPage-1)*numPageCBHK;// d?nh v? vi tri dau phan tu trang
        int key;
        do
        {
            key = getch();
            if(key <=0)
                key = getch();
            switch(key)
            {
            case UP:
                if(current > 0)
                {
                    normal();
                    gotoxy(5,current+11);
                    inMotCB(listCB,current+f);
                    current--;
                    highlight();
                    gotoxy(5,current+11);
                    inMotCB(listCB,current+f);
                };
                break;
            case DOWN:
                if((crtPage==pages && current+1 <numPageCBHK-(pages*numPageCBHK-n)) || (crtPage<pages && current+1 <numPageCBHK))
                {
                    normal();
                    gotoxy(5,current+11);
                    inMotCB(listCB,current+f);
                    current++;
                    highlight();
                    gotoxy(5,current+11);
                    inMotCB(listCB,current+f);
                }
                break;

            case RIGHT:
                if(crtPage<pages)
                {
                    crtPage++;
                    normal();
                    for(int i =0; i< numPageCBHK; i++)
                        clearError(1,11+i);
                    goto DSHK;
                }
                break;
            case LEFT:
                if(crtPage>1)
                {
                    crtPage--;
                    normal();
                    for(int i =0; i< numPageCBHK; i++)
                        clearError(1,11+i);
                    goto DSHK;
                }
                break;
            case ENTER:
            {
                count = 0;
                PTRCB p;
                p=listCB;
                while(count < current)
                {
                    p=p->next;
                    count++;
                }

                if (p->DSVE.soLuongDat==0)
                {
                    normal();
                    SetColor(RED);
                    rectangle(40, 24, 55, 2);
                    gotoxy(42, 25);
                    cout<<"===== CHUYEN BAY NAY CHUA CO HANH KHACH DAT VE =====";
                    Sleep(1500);
                }
                else
                    DSHKCB(p,listHK);
                    
                goto DSHK;
                break;
            }
            case ESC:
                SetBGColor(0);
                return;
            }
        }
        while(1);
    }
    getch();
}