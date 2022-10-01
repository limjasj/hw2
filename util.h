#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> intersection;

  typename std::set<T>::iterator it;
  for(it=s1.begin(); it != s1.end(); ++it)  //iterate through all items in s1
  {
    if(s2.find(*it) != s2.end())       //if the item in s1 also exists in s2
    {
      intersection.insert(*it);   //add item into intersection set
    }
  }


  return intersection;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> un;
  un=s1; //copy s1 into union
  typename std::set<T>::iterator it;
  for(it=s2.begin(); it != s2.end(); ++it)  //iterate through all items in s2
  {
    if(s1.find(*it) == s1.end())       //if the item in s2 doesn't exists in s1
    {
      un.insert(*it);   //add item into union set
    }
  } 

  return un;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
