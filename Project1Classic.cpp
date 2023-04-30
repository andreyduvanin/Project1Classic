// Project1Classic.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "framework.h"
#include "Project1Classic.h"
#include <iostream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Единственный объект приложения

CWinApp theApp;

using namespace std;


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
 
  

    CString Buffer;
    Buffer.Format(_T("START SOCKET SE ND OK! %d\n"), 0);
    std::string st("START SOCKET SEND OK! ");
    std::cout << st << endl;

    size_t buflen = st.length();

    AfxSocketInit(NULL);
    CSocket echoClient;
    if (echoClient.Create(0, SOCK_DGRAM, NULL) == 0) 
    {
      AfxMessageBox(L"Create() failed", MB_OK | MB_ICONSTOP);
    }
    int i = 0;
    std::string si = std::to_string(i);
    std::string sk;
    while (i < 25)
    {
      i++;
      si = std::to_string(i);
      sk = st + si;
      std::cout << sk <<endl;
      buflen = sk.length();
      if (echoClient.SendTo(sk.c_str(), buflen, 514, (LPCTSTR)L"localhost", 0) != buflen)
          AfxMessageBox(L"SendTo() sent a different number of bytes than expected", MB_OK | MB_ICONSTOP);
      Sleep(1000);
    }
    echoClient.Close();
    std::cout << "Without errors: GetModuleHandle" << endl;
    return nRetCode;
}
