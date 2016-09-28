#include "TextUtils.h"

namespace CEGUI
{

const String TextUtils::DefaultWhitespace(" \n\t\r");
const String TextUtils::DefaultAlphanumerical("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
const String TextUtils::DefaultWrapDelimiters(" \n\t\r");

String TextUtils::getNextWord(const String &str, String::size_type start_idx, const String &delimeters)
{
	String::size_type word_start = str.find_first_not_of(delimeters, start_idx);
	if (word_start==String::npos)
	{
		word_start = start_idx;
	}
	if (word_end==String::npos)
	{
		word_end = str.length();
	}
	return str.substr(start_idx, (word_end-start_idx));
}
//return the index of the first character of the word at 'idx'
String::size_type TextUtils::getWordStartIdx(const String &str, String::size_type idx)
{
	String temp = str.substr(0, idx);
	trimeTrailingChars(temp, DefaultWhitespace);
	if (temp.length()<=1)
	{
		return 0;
	}
	if (String::npos != DefaultAlphanumerical.find(temp[temp.length()-1]))
	{
		idx = temp.find_last_not_of(DefaultAlphanumerical);
	} 
	else
	{
		idx = temp.find_last_of(DefaultAlphanumerical+DefaultWhitespace);
	}
	if (idx == String::npos)
	{
		return 0;
	} 
	else
	{
		return idx+1;
	}
}

String::size_type TextUtils::getNextWordStartIdx(const String &str, String::size_type idx)
{
	String::size_type str_len = str.length();
	if ((idx>=str_len) || (str_len==0))
	{
		return str_len;
	}
}

void TextUtils::trimLeadingChars(String &str, const String &chars)
{
	String::size_type idx = str.find_first_not_of(chars);
	if (idx != String::npos)
	{
		str.erase(0, idx);
	} 
	else
	{
		str.erase();
	}
}

void TextUtils::trimeTrailingChars(String &str, const String &chars)
{
	String::size_type idx = str.find_last_not_of(chars);
	if (idx != String::npos)
	{
		str.resize(idx+1);
	} 
	else
	{
		str.erase();
	}
}

}