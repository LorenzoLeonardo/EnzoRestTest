#include "CJSONParser.h"

CJSONParser::CJSONParser()
{
	m_sJSONstring = _T("");
}
CJSONParser::CJSONParser(string_t sJSON) 
{
	m_sJSONstring = trim(sJSON);
}
CJSONParser::~CJSONParser() 
{
}

void CJSONParser::SetJSONString(string_t sJSON)
{
	m_sJSONstring = trim(sJSON);
}

void CJSONParser::GetValue(string_t sTag, unsigned long& data)
{
	string_t str = m_sJSONstring.substr(m_sJSONstring.find(sTag) + sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T(':') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex + 1;
		}
		else if ((str[nIndex] == _T(',') || str[nIndex] == _T('}')) && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	string_t sTemp = str.substr(nStart, nIndex);
	data = _tcstoul(sTemp.c_str(),NULL,0);
}
void CJSONParser::GetValue(string_t sTag, float& data) 
{
	string_t str = m_sJSONstring.substr(m_sJSONstring.find(sTag) + sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T(':') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex + 1;
		}
		else if ((str[nIndex] == _T(',') || str[nIndex] == _T('}')) && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	string_t sTemp = str.substr(nStart, nIndex);
	data = _ttof(sTemp.c_str());
}
void CJSONParser::GetValue(string_t sTag, string_t& data)
{
	string_t str = m_sJSONstring.substr(m_sJSONstring.find(sTag)+ sTag.length());
	string_t sStack;
	int nIndex = 0, nStart = 0;
	while (nIndex < str.length())
	{
		if (str[nIndex] == _T('\"') && sStack.empty())
		{
			sStack.push_back(str[nIndex]);
			nStart = nIndex+1;
		}
		else if (str[nIndex] == _T('\"') && !sStack.empty())
		{
			sStack.pop_back();
			nIndex--;
			break;
		}
		nIndex++;
	}
	data = str.substr(nStart, nIndex-1);
//	_tprintf(_T("%s"), data.c_str());
}