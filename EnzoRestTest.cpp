// EnzoRestTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#ifdef _DEBUG
#pragma comment(lib,"cpprest141_2_10d.lib")
#else
#pragma comment(lib,"cpprest141_2_10.lib")
#endif
using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;



void TestHTTP()
{
    while (!_kbhit())
    {
        http_client client(_T("https://phisix-api4.appspot.com/stocks/BDO.json"));
        auto resp = client.request(_T("GET")).get();

        wcout << _T("STATUS :") << resp.status_code() <<_T("\033[F")<< endl;
        wcout << _T("content-type : ") << resp.headers().content_type() << _T("\033[F") << endl;
        wcout << resp.extract_string(true).get() << _T("\033[F") << endl;
        Sleep(1000);
    }
}

int main()
{
    TestHTTP();
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
