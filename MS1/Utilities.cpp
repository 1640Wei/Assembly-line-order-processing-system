/***********************************************************************
// OOP345 MS1:
// File	Utilities.cpp
// Version 1.0
// Author	Ching Wei Lai
// Student ID 136893211
// Email  cwlai6@myseneca.ca
//
// Authenticity Declaration:
// I declare this submission is the result of my own work and has not been
// shared with any other student or 3rd party content provider. This submitted
// piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> 
#include "Utilities.h"

using namespace std;
namespace sdds {

   char Utilities::m_delimiter{};

   //sets the field width of the current object to the value of parameter newWidth
   void Utilities::setFieldWidth(size_t newWidth) {
      if(newWidth)
         m_widthField = newWidth;
   }

   //returns the field width of the current object
   size_t Utilities::getFieldWidth() const {
      return m_widthField;
   }

   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
      string nextToken;
      size_t pos = 0;
      size_t start = 0;
      size_t end = 0;
      const string WHITESPACE = " \n\r\t\f\v";

      //retrieves the delimiter character used to separate data.
      char delim = getDelimiter();

      //searches for the character delim; starting from the position next_pos, and stores the index
      pos = str.find(delim, next_pos); 

      //std::string::npos ---> the absence or failure to find a specified substring within a string.
      if (pos == std::string::npos) {   
         nextToken = str.substr(next_pos);   
         start = nextToken.find_first_not_of(WHITESPACE);
         end = nextToken.find_last_not_of(WHITESPACE);
         nextToken = nextToken.substr(start, end - start + 1);   
         more = false;

         //f the length of nextToken is greater than the current value of m_widthField ---> updated to the length
         if (m_widthField < nextToken.length())
            m_widthField = nextToken.length();
      }
      else if (pos == next_pos) {   
         more = false;
         throw next_pos;
      }
      else {  
         nextToken = str.substr(next_pos, pos - next_pos);
         start = nextToken.find_first_not_of(WHITESPACE);
         end = nextToken.find_last_not_of(WHITESPACE);
         nextToken = nextToken.substr(start, end - start + 1);   
         more = true;
         next_pos = pos + 1;
         if (m_widthField < nextToken.length())
            m_widthField = nextToken.length();  
      }
      return nextToken;
   }

   //sets the delimiter for this class to the character received
   void Utilities::setDelimiter(char newDelimiter) {
      if(newDelimiter)
         m_delimiter = newDelimiter;
   }
   
   //returns the delimiter for this class.
   char Utilities::getDelimiter() {
      return m_delimiter;
   }
}