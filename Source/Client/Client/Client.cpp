// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "afxsock.h"
#include <windows.h>
#include <conio.h>
#include <string>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define col 79
#define row 24

// The one and only application object

CWinApp theApp;

using namespace std;

short x, y, i, m, n, m1, n1, turnCount = 1;
char symbol;
char a[col][row], key;
typedef struct moveInfo
{
	int X = 0;
	int Y = 0;
	int m = 0;
	int n = 0;
} moveInfo;
//Cac ham ho tro tro choi

void MoDau(short);
void Choi2Nguoi();
void ChoiVoiMayDangXayDung();
void ChoiVoiMay(short);
void ThongTin();
void Thoat();
void HuongDan(short);
void VeKhung(short);
void ChoiLai();

void Goto(int x, int y) {
	COORD co = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), co);
}

void TextColor(int x)//Xac dinh mau cua chu
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
//Tro Choi
short Chan(short i) {// Kiem tra chan le de phuc vu cho chia luot
	if (i % 2 == 0) return 1;
	else return 0;
}

char OX(short i) {
	if (Chan(i) == 1) return 'O';
	else return 'X';
}

moveInfo VeOX(short x, short y) {//Ve O, X theo luot
	moveInfo info;
	if (a[x][y] != 'X' && a[x][y] != 'O') {
		if (Chan(i) == 1) TextColor(11); else TextColor(12);
		a[x][y] = symbol;
		cout << a[x][y];
		info.X = x;
		info.Y = y;
		info.m = m;
		info.n = n;
		return info;
	}
	else a[n][m];
	TextColor(7);
	return info;


}

void AnSangTrai() {
	x -= 1;
	if (x < 13) x = 13;
}

void AnSangPhai() {
	x += 1;
	if (x >= 77) x = 77;
}

void AnLenTren() {
	y -= 1;
	if (y < 3) y = 3;
}

void AnXuongDuoi() {
	y += 1;
	if (y >= 24) y = 24;
}

void ConTro(short x, short y) {  //Phuc vu cho di chuyen
	Goto(x, y);
	n = x; m = y;
}

void ThongTinTranDau() {
	TextColor(7);
	//Thong tin
	Goto(0, 0); cout << "Toa Do: " << x - 12 << "-" << y - 2 << endl << "Luot thu: " << turnCount;
	//Trang tri
	cout << "     E: danh co.";
	TextColor(12); cout << "           B15D44-b2tind44.tk";
	Goto(0, 4); TextColor(11); cout << "Di chuyen: " << endl << "A,D,W,S" << endl << endl;
	TextColor(14); cout << "p/s:" << endl << "Chan dau," << endl << "chan duoi " << endl; TextColor(12); cout << "khong"; TextColor(14); cout << " tinh" << endl << endl;
	TextColor(10); cout << endl << "Luot choi \ncua: " << OX(turnCount);
	TextColor(7);
}

void TuongTacPhim(moveInfo & info) {
	key = _getch();
	if (key == 'a' || key == 'A' || int(key == 75)) AnSangTrai(); else
		if (key == 'd' || key == 'D' || int(key == 77)) AnSangPhai(); else
			if (key == 'w' || key == 'W' || int(key == 72)) AnLenTren(); else
				if (key == 's' || key == 'S' || int(key == 80)) AnXuongDuoi(); else
					if (key == 'e' || key == 'E' || key == 'm' || key == 'M') info = VeOX(n, m);
}
void VeKhung(short n) {
	short i;
	Goto(12, 2);
	for (i = 0; i <= 65; i++) {
		cout << "*"; Sleep(n);
	}
	for (i = 0; i <= 22; i++) {
		Goto(12, i + 2);
		Sleep(n);
		cout << "*";
	}
	Goto(12, 24);
	for (i = 0; i <= 65; i++) {
		cout << "*"; Sleep(n);
	}

	for (i = 0; i <= 22; i++) {
		Goto(78, i + 2);
		Sleep(n);
		cout << "*";
	}
}

void BatDau() {
	system("cls");
	HuongDan(2);
	system("cls");
	VeKhung(3);
}
void HuongDan(short k) {
	cout << endl << endl << "                             HUONG DAN" << endl << endl;
	cout << "Dung";
	TextColor(12); cout << " phim di chuyen";
	TextColor(7);  cout << " hoac";
	TextColor(12); cout << " A,D,W,S";
	TextColor(7);  cout << " de di chuyen. Dung phim";
	TextColor(12); cout << " E";
	TextColor(7);  cout << " va";
	TextColor(12); cout << " M";
	TextColor(7);  cout << " de choi." << endl << "Chuc vui!" << endl;;
	system("pause");
}


void Thoat() {
	TextColor(10);
	Goto(31, 11); cout << "Xin Chao! Hen Gap lai!";
	Goto(31, 12); cout << " http://b2tind44.tk/";
	_getch();
	ExitProcess(0);
}

short DKOChienThang() {//Dieu kien de ben O chien thang
	//Theo hang ngang
	m1 = m; n1 = n;
	while (a[n1][m] == 'O')
		n1++;
	n1--;
	//Doan tren nham muc dich chuen con tro den vi tri 'O' dau hang de tien cho viec xet vi neu 'O' duoc nhap o giau hang se khong xet
	if ((a[n1][m] == 'O') && (a[n1 + 1][m] == 'O') && (a[n1 + 2][m] == 'O') && (a[n1 + 3][m] == 'O') && (a[n1 + 4][m] == 'O') && ((a[n1 + 5][m] != 'X') || (a[n1 - 1][m] != 'X'))) return 1; else
		if ((a[n1][m] == 'O') && (a[n1 - 1][m] == 'O') && (a[n1 - 2][m] == 'O') && (a[n1 - 3][m] == 'O') && (a[n1 - 4][m] == 'O') && ((a[n1 - 5][m] != 'X') || (a[n1 + 1][m] != 'X'))) return 1;
	//Theo hang doc
	m1 = m; n1 = n;
	while (a[n][m1] == 'O')
		m1++;
	m1--;
	//Theo duong cheo chinh
	if ((a[n][m1] == 'O') && (a[n][m1 + 1] == 'O') && (a[n][m1 + 2] == 'O') && (a[n][m1 + 3] == 'O') && (a[n][m1 + 4] == 'O') && ((a[n][m1 + 5] != 'X') || (a[n][m1 - 1] != 'X'))) return 1; else
		if ((a[n][m1] == 'O') && (a[n][m1 - 1] == 'O') && (a[n][m1 - 2] == 'O') && (a[n][m1 - 3] == 'O') && (a[n][m1 - 4] == 'O') && ((a[n][m1 - 5] != 'X') || (a[n][m1 + 1] != 'X'))) return 1;
	//Theo duong cheo phu
	m1 = m; n1 = n;
	while (a[n1][m1] == 'O') {
		m1++; n1++;
	}
	m1--; n1--;
	if ((a[n1][m1] == 'O') && (a[n1 + 1][m1 + 1] == 'O') && (a[n1 + 2][m1 + 2] == 'O') && (a[n1 + 3][m1 + 3] == 'O') && (a[n1 + 4][m1 + 4] == 'O') && ((a[n1 + 5][m1 + 5] != 'X') || (a[n1 - 1][m1 - 1] != 'X'))) return 1; else
		if ((a[n1][m1] == 'O') && (a[n1 - 1][m1 - 1] == 'O') && (a[n1 - 2][m1 - 2] == 'O') && (a[n1 - 3][m1 - 3] == 'O') && (a[n1 - 4][m1 - 4] == 'O') && ((a[n1 - 5][m1 - 5] != 'X') || (a[n1 + 1][m1 + 1] != 'X'))) return 1;
	m1 = m; n1 = n;
	while (a[n1][m1] == 'O') {
		n1++; m1--;
	}
	n1--; m1++;
	if ((a[n1][m1]) == 'O' && (a[n1 + 1][m1 - 1]) == 'O' && (a[n1 + 2][m1 - 2]) == 'O' && (a[n1 + 3][m1 - 3]) == 'O' && (a[n1 + 4][m1 - 4] == 'O') && ((a[n1 + 5][m1 - 5] != 'X') || (a[n1 - 1][m1 + 1] != 'X'))) return 1; else
		if ((a[n1][m1]) == 'O' && (a[n1 - 1][m1 + 1]) == 'O' && (a[n1 - 2][m1 + 2]) == 'O' && (a[n1 - 3][m1 + 3]) == 'O' && (a[n1 - 4][m1 + 4] == 'O') && ((a[n1 - 5][m1 + 5] != 'X') || (a[n1 + 1][m1 - 1] != 'X'))) return 1;

	return 0;
}

short DKXChienThang() { //Dieu kien de ben X chien thang
	//THeo hang ngang
	m1 = m; n1 = n;
	while (a[n1][m] == 'X') {
		n1++;
	}
	n1--;
	//Doan tren nham muc dich chuen con tro den vi tri 'O' dau hang de tien cho viec xet vi neu 'O' duoc nhap o giau hang se khong xet duoc
	if ((a[n1][m] == 'X') && (a[n1 + 1][m] == 'X') && (a[n1 + 2][m] == 'X') && (a[n1 + 3][m] == 'X') && (a[n1 + 4][m] == 'X') && ((a[n1 + 5][m] != 'O') || (a[n1 - 1][m] != 'O'))) return 1; else //Theo Hang ngang
		if ((a[n1][m] == 'X') && (a[n1 - 1][m] == 'X') && (a[n1 - 2][m] == 'X') && (a[n1 - 3][m] == 'X') && (a[n1 - 4][m] == 'X') && ((a[n1 - 5][m] != 'O') || (a[n1 + 1][m] != 'O'))) return 1;
	//Theo hang doc
	m1 = m; n1 = n;
	while (a[n][m1] == 'X') {
		m1++;
	}
	m1--;
	if ((a[n][m1] == 'X') && (a[n][m1 + 1] == 'X') && (a[n][m1 + 2] == 'X') && (a[n][m1 + 3] == 'X') && (a[n][m1 + 4] == 'X') && ((a[n][m1 + 5] != 'O') || (a[n][m1 - 1] != 'O'))) return 1; else //Theo Hang doc
		if ((a[n][m1] == 'X') && (a[n][m1 - 1] == 'X') && (a[n][m1 - 2] == 'X') && (a[n][m1 - 3] == 'X') && (a[n][m1 - 4] == 'X') && ((a[n][m1 - 5] != 'O') || (a[n][m1 + 1] != 'O'))) return 1;
	//Theo duong cheo chinh
	m1 = m; n1 = n;
	while (a[n1][m1] == 'X') {
		m1++; n1++;
	}
	m1--; n1--;
	if ((a[n1][m1] == 'X') && (a[n1 + 1][m1 + 1] == 'X') && (a[n1 + 2][m1 + 2] == 'X') && (a[n1 + 3][m1 + 3] == 'X') && (a[n1 + 4][m1 + 4] == 'X') && ((a[n1 + 5][m1 + 5] != 'O') || (a[n1 - 1][m1 - 1] != 'O'))) return 1; else //Theo Duong cheo chinh
		if ((a[n1][m1] == 'X') && (a[n1 - 1][m1 - 1] == 'X') && (a[n1 - 2][m1 - 2] == 'X') && (a[n1 - 3][m1 - 3] == 'X') && (a[n1 - 4][m1 - 4] == 'X') && ((a[n1 - 5][m1 - 5] != 'O') || (a[n1 + 1][m1 + 1] != 'O'))) return 1;
	//Theo duong cheo phu
	m1 = m; n1 = n;
	while (a[n1][m1] == 'X') {
		n1++; m1--;
	}
	n1--; m1++;
	if ((a[n1][m1]) == 'X' && (a[n1 + 1][m1 - 1]) == 'X' && (a[n1 + 2][m1 - 2]) == 'X' && (a[n1 + 3][m1 - 3]) == 'X' && (a[n1 + 4][m1 - 4] == 'X') && ((a[n1 + 5][m1 - 5] != 'O') || (a[n1 + 1][m1 + 1] != 'O'))) return 1; else //Theo Duong cheo phu
		if ((a[n1][m1]) == 'X' && (a[n1 - 1][m1 + 1]) == 'X' && (a[n1 - 2][m1 + 2]) == 'X' && (a[n1 - 3][m1 + 3]) == 'X' && (a[n1 - 4][m1 + 4] == 'X') && ((a[n1 - 5][m1 + 5] != 'O') || (a[n1 - 1][m1 - 1] != 'O'))) return 1;
	//Khong chien thang
	return 0;
}

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			CSocket Client;
			AfxSocketInit(); //Khoi tao windows socket
			Client.Create();
			char ip[100];
			string temp;
			cout << "Vui long nhap dia chi IP server (mac dinh la 127.0.0.1)" << endl;
			cin >> temp;
			int numOfChars = temp.size();
			for (int i = 0; i < numOfChars; i++)
			{
				ip[i] = temp.at(i);
				if (i == numOfChars - 1)
				{
					ip[i + 1] = '\0';
				}
			}

			//Ket noi voi server
			if (Client.Connect(CA2W(ip), 1234))
			{
				cout << "Vui long cho tin hieu san sang tu server!\n";
				Client.Receive((char*)& symbol, sizeof(char));
				if (symbol == 'X')
				{
					i = 1;
				}
				else
				{
					i = 2;
				}
				short connectSignal = 0;
				Client.Receive(&connectSignal, sizeof(connectSignal));
				if (connectSignal == 1)
				{
					cout << "Ket noi san sang, nhan phim bat ky de tiep tuc!\n";
					_getch();
				}
				else
				{
					cout << "Ket noi nguoi choi that bai!\n";
					system("pause");
					return 0;
				}


				system("cls");
				VeKhung(3);
				x = n = 13; y = m = 3;
				int count = 1;
				int resCode = 0;
				do {

					ThongTinTranDau();
					moveInfo info;


					int arrSize = 6; //Kich thuoc mang thong tin can gui di cho server
					int dataToServer[6]; //Mang chua thong tin gui den server
					int dataFromServer[6];//Mang chua thong tin nhan tu server
					//Nhan thong tin luot danh truoc do roi hien len tren ban co, sau do moi danh va gui thong tin
					if (symbol == 'O' && count == 1 || count >= 2) //Luot dau tien cua nguoi choi 1 khong nhan thong tin, chi gui thong tin
					{
						for (int x = 0; x < arrSize; x++)
						{
							Client.Receive((char*)& dataFromServer[x], sizeof(dataFromServer[x]));
						}

						int X = dataFromServer[0];
						int Y = dataFromServer[1];
						turnCount = dataFromServer[4];
						//Kiem tra xem o da danh chua, tranh tinh trang danh de len o da danh
						if (a[X][Y] != 'O' && a[X][Y] != 'X')
						{
							a[X][Y] = (symbol == 'O') ? 'X' : 'O';
							Goto(X, Y);
							if (symbol == 'O')
							{
								TextColor(12);
							}
							else
							{
								TextColor(11);
							}
							cout << a[X][Y];
							Goto(n, m);

							int tempm = m;
							int tempn = n;

							m = dataFromServer[2];
							n = dataFromServer[3];

							if (DKOChienThang() || DKXChienThang())
							{
								Goto(27, 3);
								if (DKOChienThang())
								{
									resCode = 2;
									TextColor(11);
									cout << "Nguoi choi 2 (O) chien thang!\n" << endl;
								}
								else if (DKXChienThang())
								{
									resCode = 1;
									TextColor(12);
									cout << "Nguoi choi 1 (X) chien thang!\n" << endl;
								}
								break;
							}

							m = tempm;
							n = tempn;
						}

						while (info.X == 0 && info.Y == 0 && info.m == 0 && info.n == 0)
						{
							ThongTinTranDau();
							ConTro(x, y);
							TuongTacPhim(info);
						}

					}

					else if (symbol == 'X' && count == 1)
					{
						while (info.X == 0 && info.Y == 0 && info.m == 0 && info.n == 0)
						{
							ThongTinTranDau();
							ConTro(x, y);
							TuongTacPhim(info);
						}
					}

					if (DKOChienThang() || DKXChienThang())
					{
						Goto(27, 3);
						if (DKOChienThang())
						{
							TextColor(11);
							resCode = 2;
							cout << "Nguoi choi 2 (O) chien thang!\n" << endl;
						}
						else if (DKXChienThang())
						{
							TextColor(12);
							resCode = 1;
							cout << "Nguoi choi 1 (X) chien thang!\n" << endl;
						}
					}

					turnCount++;
					ThongTinTranDau();

					dataToServer[0] = info.X;
					dataToServer[1] = info.Y;
					dataToServer[2] = info.m;
					dataToServer[3] = info.n;
					dataToServer[4] = turnCount;
					dataToServer[5] = resCode;

					for (int x = 0; x < arrSize; x++)
					{
						Client.Send((char*)& dataToServer[x], sizeof(dataToServer[x]));
					}
					if (resCode != 0)
					{
						break;
					}

					count++;
				} while (1);
				Goto(27, 3);
				if (resCode == 1)
				{
					TextColor(12);
					cout << "Nguoi choi 1 (X) chien thang!\n" << endl;
				}
				else if (resCode == 2)
				{
					TextColor(11);
					cout << "Nguoi choi 2 (O) chien thang!\n" << endl;
				}
				Thoat();
				Client.Close();
			}

		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode;
}
