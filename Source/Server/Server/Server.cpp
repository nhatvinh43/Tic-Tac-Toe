// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "afxsock.h"
#include <string>
#include <conio.h>
#define col 79
#define row 24
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

//Cac ham check dieu kien thang thua
short  m, n, m1, n1;
char a[col][row];




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
			CSocket Server;
			AfxSocketInit();
			unsigned short port = 1234;

			//Du lieu tro choi
			char symbol;
			int inputData[6]; //Chua thong tin toa do X, Y va symbol cua client khi danh vao 1 o

			//Tao va lang nghe
			Server.Create(port);
			Server.Listen(100);


			CSocket Clients[2];
			short connectedPlayersCount = 0;
			for (int i = 0; i < 2; i++)
			{
				if (i == 0) //Client nao ket noi truoc thi symbol se la X, sau thi la O
				{
					if (Server.Accept(Clients[i]))
					{
						cout << "Da ket noi nguoi choi 1.\n";
						symbol = 'X';
						Clients[i].Send((char*)& symbol, sizeof(char), 0); //Send ky hieu cho client
						connectedPlayersCount++;
					}
					else {
						cout << "Ket noi nguoi choi 1 khong thanh cong!\n";
					}
				}
				else
				{
					if (Server.Accept(Clients[i]))
					{
						cout << "Da ket noi nguoi choi 2.\n";
						symbol = 'O';
						Clients[i].Send((char*)& symbol, sizeof(char), 0); //Send ky hieu cho client
						connectedPlayersCount++;
					}
					else {
						cout << "Ket noi nguoi choi 2 khong thanh cong!\n";
					}
				}
			}
			short res;
			if (connectedPlayersCount == 2)
			{
				res = 1;

			}
			else
			{
				res = 0;
			}
			Clients[0].Send(&res, sizeof(res));
			Clients[1].Send(&res, sizeof(res));

			int i = 1;
			int arrSize = 6; //So phan tu co dinh cua mang truyen va nhan
			int resCode = 0; //Server tra code ket qua sau moi luot danh ve 2 client code so 0 neu chua co ai thang, 1 neu nguoi choi 1 thang,...
			while (1)
			{

				if (i % 2 == 1) //Luot choi cua nguoi thu nhat
				{

					for (int i = 0; i < arrSize; i++)
					{
						Clients[0].Receive((char*)& inputData[i], sizeof(inputData[i])); //Nhan thong tin ma tran hien tai va gui cho client tiep theo
						Clients[1].Send((char*)& inputData[i], sizeof(inputData[i]));
					}
					if (inputData[5] != 0)
					{
						if (inputData[5] == 1)
						{
							cout << "Chuc mung nguoi choi 1 da chien thang! Nhan phim bat ky de thoat.\n";
							_getch();
							break;
						}
						else
						{
							cout << "Chuc mung nguoi choi 2 da chien thang! Nhan phim bat ky de thoat.\n";
							_getch();
							break;

						}
					}

				}
				else
				{
					for (int i = 0; i < arrSize; i++)
					{
						Clients[1].Receive((char*)& inputData[i], sizeof(inputData[i]), 0); //Nhan thong tin ma tran hien tai va gui cho client tiep theo
						Clients[0].Send((char*)& inputData[i], sizeof(inputData[i]));
					}
					if (inputData[5] != 0)
					{
						if (inputData[5] == 1)
						{
							cout << "Chuc mung nguoi choi 1 da chien thang! Nhan phim bat ky de thoat.\n";
							_getch();
							break;
						}
						else
						{
							system("pause");
							cout << "Chuc mung nguoi choi 2 da chien thang! Nhan phim bat ky de thoat.\n";
							_getch();
							break;

						}
					}

				}
				i++;
			}
			Clients[0].Close();
			Clients[1].Close();
			Server.Close();
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
