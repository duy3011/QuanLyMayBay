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

void initTree(TREEHK &);
int compareCCCD(HK , HK );
void insertHK(TREEHK &, HK );
void preorder(TREEHK );
void clearErrTTHK(int , int );
TREEHK searchHK(TREEHK , char [13]);
int nhapHK(TREEHK &, char [13], int );
void saveFileDSHK(char *, TREEHK );
void loadFileDSHK(char *, TREEHK &);