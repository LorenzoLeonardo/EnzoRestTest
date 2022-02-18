#pragma once
#include <string>
#include <functional>
#include <tchar.h>
using namespace std;

#ifndef string_t
#ifdef UNICODE
#define string_t std::wstring
#else
#define string_t std::string
#endif
#endif


class CJSONParser
{
public:
    typedef enum
    {
        JSONstring=0,
        JSONfloat,
        JSONulong,
        JSONint
    }JSON_DATA_TYPE;
protected:
	string_t m_sJSONstring;

    inline string_t& ltrim(string_t& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }
    inline string_t& rtrim(string_t& s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }
    inline string_t& trim(string_t& s)
    {
        return ltrim(rtrim(s));
    }
    inline string_t& removespaces(string_t& sMain)
    {
        sMain.erase(std::remove(sMain.begin(), sMain.end(), _T(' ')), sMain.end());
        return sMain;
    }

public:
    CJSONParser();
    CJSONParser(string_t sJSON);
    ~CJSONParser();
    void SetJSONString(string_t sJSON);
    void GetValue(string_t sTag, unsigned long &data);
    void GetValue(string_t sTag, float& data);
    void GetValue(string_t sTag, string_t& data);
};

