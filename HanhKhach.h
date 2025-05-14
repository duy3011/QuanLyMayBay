#pragma once

#include <iostream>
#include "mylib.h"

using namespace std;

char *FileDSHK = "DSHK.txt";

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


//--------------------------------------------Cac module ve hanh khach----------------------------//
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