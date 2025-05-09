#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <iomanip>
#include <ctime>
#include <cstring>

#define Enter 13
//const int WHITE=15;
#define PASSWORD "abcdef"
//const int WHITE=15;
#define LIGHTBLUE 11
#define RED 4
#define YELLOW 14
#define WHITE 15
#define GREEN 2
using namespace std;

//Setup cac nut chuc nang can su dung trong bai
const int UP = 72;					
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int ESC = 27;
const int ENTER = 13;
const int F2 = 60;
const int F3 = 61;
const int F4 = 62;
const int F5 = 63;



//Cac ham nhap va chuan hoa ky tu
void nhapSo(char *, int );
void nhapChuoi(char *, int );
void nhapChu(char *, int );
void Delete(char *, int );
void Trim(char *);
void deleteEnter(char * );
void deleteESC(char*);
int getKey();

//Cac ham thong bao
void alertError (char * , int , int );
void clearError(int , int );

//Cac ham ve va lien quan toi menu
int menu(int , int , char a[][70], int );
void rectangle(int , int , int , int );
void vekhung(int ,int , int ,int );
void highlight();
void normal();
void resizeConsole(int , int );
void ShowCur(bool );

void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(short x,short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  
void PutCharXY(int x, int y,const char* KyTu, int color)
{
    gotoxy(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf(KyTu);
}


int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( ) {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr() {
	system("cls");
}

void nhapSo(char *str, int max) // Nh?p chu?i ch? ch?a s?, không kho?ng tr?ng
{
    unsigned int i = 0;
    unsigned int a;
Nhap:
    i = 0;
    while (true)
    {
        a = getch();
        if (a == ESC)
        {
            deleteESC(str);
            str[0] = ESC;
            return;
        }
        else if (a >= '0' && a <= '9') // Là s?
        {
            if (i < max) {
                str[i] = char(a);
                cout << str[i];
                i++;
            } else {
                alertError("VUOT QUA SO KY TU GIOI HAN", 8, 3);
            }
        }
        else if (a == '\b') // Backspace
        {
            if (i > 0)
            {
                i--;
                str[i] = 0;
                cout << "\b \b";
            }
            // Không báo l?i khi xóa h?t chu?i
        }
        else if (a == 13) // Enter
        {
            str[i] = '\0';
            Trim(str);
            if (i == 0)
            {
                alertError("CHUOI TRONG", 8, 3);
                goto Nhap;
            }
            else if (i < max)
            {
                alertError("VUI LONG THEM KY TU", 8, 3);
                goto Nhap;
            }
            break;
        }
    }
}


void nhapChuoi(char *str, int max) // Dung de nhap chuoi chua ca chu lan so khong co khoang trang
{
	int i=0;
NHAP:
	do
	{
		str[i]=getch();
        if (str[i]==ESC)
        {    
        	deleteESC(str);
        	str[0]=ESC;
        	return;
    	}
		if ((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z') || (str[i]>='0' && str[i]<='9'))		// Kiem tra co phai la ki tu hay khong
		{
			if (str[i]>='a' && str[i]<='z')																		// Chuyen doi tu chu thuong sang chu in
				str[i]-=32;
			cout<<str[i];
			i++;
		}
		else if (str[i]==8 && i>0)																				// Kiem tru ki tu vua nhap co phai la backspace va truoc do da co ki tu da xoa hay chua
		{		
				Xoa:
				str[i-1]=0;																						// Xoa ki tu truoc do
				cout<<"\b \b";																					// Xoa ki tu truoc do tren man hinh hien thi
				i--;
		}
		if (i==max)
		{
			alertError("VUOT QUA GIOI HAN", 8, 3);
			while (getch()!=8)
			{
			}
			goto Xoa;
		}
	}
	while (str[i]!=13);																							// Neu ki tu nhap vao la Enter thi ket thuc qua trinh nhap
	if (str[0]==13)
	{
		alertError("CHUOI TRONG VUI LONG NHAP THEM KI TU", 8, 3);
		goto NHAP;
	}
	str[i] = '\0';																						
	Trim(str);
}

void nhapChu(char *str, int n)	// Dung de nhap chuoi chi chua chu cai va khoang trang
{
	int i=0;
	int space=0;
NHAP:
	do
	{
		str[i]=getch();
        if (str[i]==ESC)
        {    
        	deleteESC(str);
        	str[0]=ESC;
        	return;
    	}
if (str[i]==' ' && space==0 && i>0)											// Kiem tra ki tu vua nhap co phai la space, da co space truoc do hay chua va truoc do da co ki tu nao hay chua
		{
			cout<<' ';
			i++;
			space=1;																// Tang bien dem space
		}
		else if ((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z'))		// Kiem tra co phai la ki tu hay khong
		{
			if (str[i]>='a' && str[i]<='z')											// Chuyen doi tu chu thuong sang chu in
				str[i]-=32;
			cout<<str[i];
			i++;
			space=0;																// Tra bien dem space ve 0
		}
		else if (str[i]==8 && i>0)													// Kiem tru ki tu vua nhap co phai la backspace va truoc do da co ki tu da xoa hay chua
		{
				if (str[i-1]==' ')	
					space=0;														// Neu ki tu truoc do la space thi tra bien dem space ve 0
				Xoa:																
				str[i-1]=0;															// Xoa ki tu truoc do
				cout<<"\b \b";														// Xoa ki tu truoc do tren man hinh hien thi
				i--;
		}
		if (i==n-1)
		{
			alertError("VUOT QUA SO KY TU GIOI HAN", 8, 3);
			while (getch()!=8)
			{
			}
			goto Xoa;
		}
	}
	while (str[i]!=13 && str[0]!=13);														// Neu ki tu nhap vao la Enter thi ket thuc qua trinh nhap
	if (str[0]==13)
	{
		alertError("CHUOI TRONG VUI LONG NHAP THEM KI TU", 8, 3);
		goto NHAP;
	}
	str[i] = '\0';
	Trim(str);
}

void alertError (char *s, int newX, int newY)			//x, y la vi tri can di den tren man hinh
{
  int currentX=wherex() , currentY=wherey();			//currentX, currentY la vi tri hien tai cua con tro
  gotoxy(newX,newY);
  cout <<s;
  Sleep(2000);
  gotoxy(newX,newY);
  clreol();
  gotoxy(currentX, currentY);
}

void clearError(int x, int y){
	gotoxy(x, y);
	clreol();
}

void rectangle(int x, int y, int width, int height)
{
    gotoxy(x,y);
    cout<<char(218);
    gotoxy(x+width, y);
    cout<<char(191);
    gotoxy(x, y+height);
    cout<<char(192);
    gotoxy(x+width, y+height);
    cout<<char(217);

    gotoxy(x,y);
    for(int i = x+1; i<=(x+width-1); i++)
    {
        gotoxy(i,y);
        cout<<char(196);
    }
    gotoxy(x,y+height);
    for(int i = x+1; i<=(x+width-1); i++)
    {
        gotoxy(i,y+height);
        cout<<char(196);
    }
    gotoxy(x,y);
    for(int i = y+1; i<=(y+height-1); i++)
    {
        gotoxy(x,i);
        cout<<char(179);
    }
    gotoxy(x+width,y);
    for(int i = y+1; i<=(y+height-1); i++)
    {
        gotoxy(x+width,i);
        cout<<char(179);
    }
}

void vekhung(int x,int y,int h,int w)
{
    cout.fill(196);
    gotoxy(x,y);
    cout<<char(218)<<setw(w)<<char(196)<<char(191);
    cout.fill(' ');
    for(int i=1; i<=h; ++i)
    {
        gotoxy(x,y+i);
        cout<<char(179)<<setw(w)<<' '<<char(179);
    }
    gotoxy(x,y+h+1);
    cout.fill(196);
    cout<<char(192)<<setw(w)<<char(196)<<char(217);
}

void Delete(char *str, int q) // Dung de xoa ki tu
{
    int n = strlen(str);
    for (int i = q; i <= n; i++)
    {
        str[i] = str[i + 1];
    }
    n--;
}

void Trim(char *str) // Dung de cat khoang trang thua
{
int i, n=strlen(str);
    for (i = 0; i < n; i++)
    {
        if (str[0] == ' ')						// Neu ki tu dau la khoang trang thi xoa
        {
            Delete(str, 0);
            n--;
        }
        if (str[n-1] == ' ')					// Neu ki tu cuoi la khoang trang thi xoa
        {
            Delete(str, n-1);
            n--;
        }
        if (str[i] == ' ' && str[i + 1] == ' ')	// Neu 2 ki tu lien tiep la khoang trang thi xoa
        {
            Delete(str, i);
            i--;
            n--;
        }
    }
}

void deleteEnter(char *str)
{
    int length = strlen(str);// tinh do dai chuoi
    if(str[length - 1]=='\n')
        str[length - 1]='\0';
}

void deleteESC(char *str)
{
	for (int i=0;i<strlen(str);i++)
	{
		cout<<"\b \b";
	}
}

int getKey(){
	int key = getch();
	if(key == 224){
		key = getch();
	}
	else if(key == 0){
		key = getch();
	}
	return key;
	
}

int menu(int x, int y, char a[][70], int soLuongMenu){
	int key = 0;
	int selectedMenu = 0;								//Menu duoc chon
	
	do{
		SetColor(15);
		SetBGColor(0);
		for(int i = 0; i < soLuongMenu; i++){
//			rectangle(x - 1, y + 3 * i - 1, 1, 60);
			vekhung(x - 1, y + 3 * i - 1, 1, 60);
			gotoxy(x, y + 3 * i);
			cout<<a[i];
		}
		
		SetColor(9);
		gotoxy(x, y + 3 * selectedMenu);
		cout<<a[selectedMenu];
		
KEY:
	;		
	key = getch();
	if(key == 224){
		key = getch();
	}	
	else if(key == 0){
		key = getch();
	}
	switch(key){
		case UP:
			if(selectedMenu > 0){
				selectedMenu--;
			}
			break;
		
		case DOWN:
			if(selectedMenu < soLuongMenu - 1){
				selectedMenu++;
			}
			break;
	
		case ENTER:
			return selectedMenu;
			break;
	}
	
	}while(key != ESC);
	return -1;
}

void highlight(){
	SetColor(11);							//Cyan
	SetBGColor(8);							//Lightgray
}

void normal(){
	SetColor(15);
	SetBGColor(0);	
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

tm *currentTime(){
	time_t currentTime = time(0);
	tm *crt = localtime(&currentTime);
	return crt;
}
