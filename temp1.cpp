

CString Buffer;
Buffer.Format(_T("START SOCKET SE ND OK! %d\n"), 0);
std::string st("START SOCKET SEND OK! ");
cout << st << endl;

int buflen = st.length();

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
  //     i++;
  //     si = std::to_string(i);
  //     sk = st + si;
  //     std::cout << sk <<endl;
  buflen = sizeof(spline[i]);
  //      buflen = sk.length();
   //     if (echoClient.SendTo(sk.c_str(), buflen, 514, (LPCTSTR)L"localhost", 0) != buflen)
  if (echoClient.SendTo((const void*)&spline[i++], buflen, 514, (LPCTSTR)L"localhost", 0) != buflen)
    AfxMessageBox(L"SendTo() sent a different number of bytes than expected", MB_OK | MB_ICONSTOP);
  Sleep(1000);
}
echoClient.Close();
std::cout << "Without errors: GetModuleHandle" << endl;
return nRetCode;
}
