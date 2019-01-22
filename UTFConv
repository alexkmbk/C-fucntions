// RegExpLab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
/*#include <iostream>
#include <iostream>
#include <string>
//#include <regex>
#include <boost/regex.hpp>
#include <boost/regex/icu.hpp>
#include <boost/algorithm/string.hpp> 

//#include <iconv.h>
#include <codecvt>

#include <iostream>
#include <fstream>
*/

#include <iostream>
#include <fstream>


#include <string>
#include <algorithm>
#include <cwctype>
#include <fstream>

#include <boost/regex.hpp>
#include <boost/regex/icu.hpp>

using namespace std;

//#pragma execute_character_set ("utf-16");

#define UTF16  char16_t
#define UTF32  char32_t
/*
#ifdef _WINDOWS
#define WCHAR_T     wchar_t
#else
#define WCHAR_T     uint16_t
#endif //_WINDOWS

uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len = 0);
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len = 0);
uint32_t getLenShortWcharStr(const WCHAR_T* Source);
*/

int is_surrogate(char16_t uc) { return ((uc >= 0xd800) && (uc <= 0xdfff)); };

int is_high_surrogate(char16_t uc) { return (uc & 0xfffffc00) == 0xd800; }
int is_low_surrogate(char16_t uc) { return (uc & 0xfffffc00) == 0xdc00; }

char32_t surrogate_to_utf32(char16_t high, char16_t low) {
	return (high << 10) + low - 0x35fdc00;
}

void convert_utf16_to_utf32(const char16_t *input,
	size_t input_size,
	char32_t *output)
{
	const char16_t * const end = input + input_size;
	while (input < end) {
		const char16_t uc = *input++;
		if (!is_surrogate(uc)) {
			*output++ = uc;
		}
		else {
			if (is_high_surrogate(uc) && input < end && is_low_surrogate(*input))
				*output++ = surrogate_to_utf32(uc, *input++);
			//else
				// ERROR
		}
	}
	*output++ = 0;
}


int main()
{
	std::u16string str = u"VJ00000123D";
	char32_t* out = new char32_t[str.length()+1];
	convert_utf16_to_utf32(str.c_str(), str.length(), out);
	
	/*std::wstring str(L"VJ00000123D");
	std::wregex r(L"([A-Za-z]{2})0+([1-9]{1}[0-9]{2})D+"); // entire match will be 2 numbers
	std::wsmatch m;
	std::regex_search(str, m, r);
	std::wstring ws = m[0];*/

	std::u32string sOut = out;
	std::wstring ws;

	for (auto v : sOut) ws = ws + (wchar_t)v;

	std::wcout << ws.c_str() << std::endl;
	//for (auto v : out) std::cout << v << std::endl;
	
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
