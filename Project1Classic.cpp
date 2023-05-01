// Project1Classic.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "framework.h"
#include "Project1Classic.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Единственный объект приложения

CWinApp theApp;
void EnablePrintfAtMFC()
{
  if (AttachConsole(ATTACH_PARENT_PROCESS))
  {
    FILE* pCout;
    freopen_s(&pCout, "CONOUT$", "w", stdout);
    std::cout.clear();
    std::wcout.clear();
  }
}

int main()
{

    EnablePrintfAtMFC();
    int nRetCode = 0; 
    wprintf(L"start ok!\n");
    HMODULE hModule = ::GetModuleHandle(nullptr);
    if (hModule != nullptr)
    {
        // инициализировать MFC, а также печать и сообщения об ошибках про сбое
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            wprintf(L"Критическая ошибка: сбой при инициализации MFC\n");
            nRetCode = 1;
        }
        else
        {
          wprintf(L"Инициализации MFC выполнена успешно\n");
        }
    }
    else
    {
        // TODO: измените код ошибки в соответствии с потребностями
        wprintf(L"Критическая ошибка: сбой GetModuleHandle\n");
        nRetCode = 1;
    }
 

    unsigned int spl;
    unsigned char spline[6200];
    ifstream file4("Real_array_Fout.txt");
    if (file4.is_open()) // вызов метода is_open()
    {
      for (int i = 0; i < 6200; i++)
      {
        file4 >> spl;
        spline[i] = spl;
      }
    }
    //       cout <<  (int)spline[i] << "   " <<i << endl;
    else
    {
      cout << "File no open! - file4" << endl;
    }
    file4.close();
    int k = 0;
  
    unsigned char send[1035];
    unsigned char sendk[1035];
    for (int i = 0; i < 6200; i+=6)
    {
      send[k++] = spline[i];
    }
    cout << "k = " << k << endl;
    random_device dev;
    mt19937 rng(dev());

    uniform_int_distribution<std::mt19937::result_type> dist2(1, 2); // distribution in range [1, 1600]
    
    AfxSocketInit(NULL);
    CSocket echoClient;
    if (echoClient.Create(0, SOCK_DGRAM, NULL) == 0)
    {
      AfxMessageBox(L"Create() failed", MB_OK | MB_ICONSTOP);
    }
    int i = 0;
    while (i < 1250)
    {
      for (k = 0; k < 1024; k++)
        sendk[k] = send[k] + dist2(rng);
      cout << i++ << endl;
      if (echoClient.SendTo((const void*)sendk, 1024, 514, (LPCTSTR)L"localhost", 0) != 1024)
        AfxMessageBox(L"SendTo() sent a different number of bytes than expected", MB_OK | MB_ICONSTOP);
      Sleep(200);
    }
    echoClient.Close();
    std::cout << "Without errors: GetModuleHandle" << endl;
    return nRetCode;
}
