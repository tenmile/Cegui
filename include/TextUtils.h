#pragma once

#include "Base.h"
#include "String.h"
#include <vector>

namespace CEGUI
{

class CEGUIEXPORT TextUtils
{
public:
	static const String DefaultWhitespace;			//The default set of whitespace
	static const String DefaultAlphanumerical;		//default set of alphanumericals that construct a word
	static const String DefaultWrapDelimiters;		//the default set of word-wrap delimeters

	static String getNextWord(const String &str, String::size_type start_idx=0, const String &delimiters=DefaultWrapDelimiters);
	static String::size_type getWordStartIdx(const String &str, String::size_type idx);
	static String::size_type getNextWordStartIdx(const String &str, String::size_type idx);
	static void trimLeadingChars(String &str, const String &chars);
	static void trimeTrailingChars(String &str, const String &chars);
private:
	static String d_delimiters;		//current set of delimiters
	static String d_whitespace;		//current set of whitespace

	TextUtils(void);
	~TextUtils(void);
};

}