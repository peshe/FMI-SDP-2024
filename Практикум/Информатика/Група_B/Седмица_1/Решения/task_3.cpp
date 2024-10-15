#include "week1.h"

#include <iostream>
#include <string>

/*----------------------------------------------------------------------------*/

bool isPalindrome(const std::string& str, int start, int end)
{
  if (start >= end) {
    // At most 1 letter - definitely a palindrome.
    return true;
  }
  if (str[start] != str[end]) {
    return false;
  }
  // else str[start] == str[end]
  return isPalindrome(str, start + 1, end - 1);
}

bool isPalindrome(const std::string& str)
{
  int end = int(str.size()) - 1;
  return isPalindrome(str, 0, end);
}

void Week1::task3()
{
  std::string str;
  std::cout << "Enter a string:\t";
  std::cin >> str;
  std::cout << str << " is " <<
    (isPalindrome(str) ? "" : "not ") << "a palindrome" << std::endl;
}
