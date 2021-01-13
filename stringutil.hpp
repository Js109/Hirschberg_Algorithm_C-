#pragma once

#ifndef STRINGUTIL_HPP
#define STRINGUTIL_HPP

#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <algorithm>

/**
* This headerfile provides some methods to work with wstrings
*/
class StringUtil {
public:
    /**
    * converts the value to a wstring
    *
    * @param reference to the object being converted
    * @return converted wstring
    */
    template<typename T>
    static std::wstring toString(const T &object) {
        std::wostringstream ss;
        ss << object;
        return ss.str();
    }

    /**
    * reverses a word and returns the reversed word
    *
    * @param toReverse The word to be reversed
    * @return reversed word
    */
    static std::wstring reverseString(const std::wstring &toReverse) {
        std::wstring result = L"";

        for (int i = toReverse.length() - 1; i >= 0; i--) {
            result = result + StringUtil::toString(toReverse[i]);
        }

        return result;
    }
};

#endif
