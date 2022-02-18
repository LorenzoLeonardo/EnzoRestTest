// EnzoRestTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "CStock.h"
#include "CJSONParser.h"

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



/*
{"stock":
    [
        {"name" :"Banco de Oro",
        "price" :
                {
	                "currency":"PHP",
		                "amount" : 134.50
                },
        "percent_change" : -0.37,
        "volume" : 1294530,
        "symbol" : "BDO"
        }
    ], 
    "as_of":"2022-02-18T12:50:00+08:00"

}*/

#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BPI     _T("https://phisix-api4.appspot.com/stocks/BPI.json")
#define STOCK_CHIB    _T("https://phisix-api4.appspot.com/stocks/CHIB.json")
#define STOCK_COL     _T("https://phisix-api4.appspot.com/stocks/COL.json")
#define STOCK_EW      _T("https://phisix-api4.appspot.com/stocks/EW.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_BDO     _T("https://phisix-api4.appspot.com/stocks/BDO.json")
#define STOCK_ALL      _T("https://phisix-api4.appspot.com/stocks.json")

inline map<string_t, CStock> JSONToStock(string_t sJSON)
{
    CJSONParser parse;
    CStock cstock;
    string_t sTemp;
    float fTemp;
    unsigned long ulTemp;
    map<string_t, string_t> m_mapLst;
    map<string_t, CStock> m_stockList;
    map<string_t, string_t>::iterator it;
    parse.SetJSONString(sJSON);

    m_mapLst = parse.GetParsedStrings();
    it = m_mapLst.begin();
    while (it != m_mapLst.end())
    {
        parse.GetValue(it->second, _T("\"name\""), sTemp);
        cstock.SetCompanyName(sTemp);

        parse.GetValue(it->second, _T("\"currency\""), sTemp);
        cstock.SetCurrency(sTemp);

        parse.GetValue(it->second, _T("\"symbol\""), sTemp);
        cstock.SetStockSymbol(sTemp);

        parse.GetValue(it->second, _T("\"amount\""), fTemp);
        cstock.SetPricePerShare(fTemp);

        parse.GetValue(it->second, _T("\"percent_change\""), fTemp);
        cstock.SetPercentChange(fTemp);

        parse.GetValue(it->second, _T("\"volume\""), ulTemp);
        cstock.SetVolume(ulTemp);

        parse.GetValue(_T("\"as_of\""), sTemp);
        cstock.SetDate(sTemp);

        m_stockList[cstock.GetStockSymbol()] = cstock;
        it++;
    }

    return m_stockList;
}
void TestHTTP()
{
    string_t sJSON;
    http_client client(STOCK_ALL);//(STOCK_BDO);
    ULONGLONG prev = 0, current = 0;
    while (!_kbhit())
    {
              // client.base_uri() = STOCK_BDO;
        auto resp = client.request(_T("GET")).get();

       
        sJSON = resp.extract_string(true).get();
        prev = GetTickCount64();
        map<string_t, CStock> cstock = JSONToStock(sJSON);
        current = GetTickCount64();
        wcout << _T("BULK PARSING TIME: ") << current - prev << _T(" ms ") << cstock.size()<<_T("stocks")<<endl;
      /*    wcout << _T("Name: ") << cstock.GetCompanyName() << _T(" ");
        wcout << _T("Symbol: ") << cstock.GetStockSymbol() << _T(" ");
        wcout << _T("Currency: ") << cstock.GetCurrency() << _T(" ");
        wcout << _T("Price: ") << cstock.GetPricePerShare() << _T(" ");
        wcout << _T("Change: ") << cstock.GetPercentChange() << _T(" ");
        wcout << _T("Volume: ") << cstock.GetVolume() << _T(" ");
        wcout << _T("Date: ") << cstock.GetDate() << _T("\r\n");
        wcout << _T("PARSING TIME: ") << current - prev << _T(" ms") << endl;*/
       
        
        Sleep(1000);
    }
}

int main()
{
    string_t s;
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
