#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <functional>
#include <iterator>
#include "stringutil.hpp"
#include "matrix.hpp"
#include "Hirschberg_JS.cpp"

/**
* main method for the Hirschberg algorithm
* use hello and hallo as input for example. The longest common subsequence is hllo.
*/
int main(int argc, char **argv)
{
			std::string input1;
			std::cout <<"Enter first sequence : ";
			std::cin >> input1;

            std::string input2;
			std::cout <<"Enter second sequence : ";
			std::cin >> input2;

			using convert_t = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_t, wchar_t> strconverter;
            std::wstring winput1 = strconverter.from_bytes(input1);
            std::wstring winput2 = strconverter.from_bytes(input2);

			auto *hirschberg = new Hirschberg_JS<std::wstring, wchar_t>(
            // define predicate as Lambda expression
				[](wchar_t a, wchar_t b) { 
            // possible extention for the extensibility of the function 
					// ö and o are handled equal as predicate example
					return (a == 0xf6 && b == 0x6f) || (a == 0x6f && b == 0xf6) || a == b;
					}
			);

			std::wcout << L"The longest common subsequence of " << winput1 << L" and " << winput2 << L" is " << hirschberg->hirschbergAlgoC(winput1.length(), winput2.length(), winput1, winput2) << std::endl;

			delete hirschberg;
      return 0;
}
