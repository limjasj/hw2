#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "util.h"

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(std::string rawWords)
{
  std:: set<std::string> parsedWords;
  int begin=0;
  int wordSize=0;

  for(unsigned int i=0; i<rawWords.size(); i++) //iterate through each char in string
  {
    //if there is a space, then make the word before it a substring
    //reset begin to the index after the space, reset the size to 0

    if(rawWords[i]==' ' || !(std::isalnum(rawWords[i])))
    //if the char is a space, or not between: 0-9, A-Z, a-z
    {
      if(wordSize>=2)
      {
        parsedWords.insert(convToLower(rawWords.substr(begin,wordSize)));
        begin=i+1;
        wordSize=0;
      }
      else
      {
        begin=i+1;
        wordSize=0;
      }
    }
    else
    {
      wordSize++;
    }
  }
//after done iwht loop, don't add whatever is left over
  std::string lastWord= rawWords.substr(begin,(wordSize));
  parsedWords.insert(convToLower(lastWord));

  return parsedWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
