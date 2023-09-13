/***********************************************************************
// OOP345 MS1:
// File	Station.cpp
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
#include "Station.h"

using namespace std;
namespace sdds {

   size_t Station::m_widthField = 0;
   int Station::id_generator = 0;

   Station::Station(const std::string& str) {
      m_stationID = ++id_generator;

      Utilities u;
      bool more = true;
      size_t pos = 0u;

      m_itemName = u.extractToken(str, pos, more);
      m_nextSerial = stoi(u.extractToken(str, pos, more));
      m_stock = stoi(u.extractToken(str, pos, more));
      if (m_widthField < u.getFieldWidth())
         m_widthField = u.getFieldWidth();
      m_description = u.extractToken(str, pos, more);
   }

   //returns the name of the current Station object
   const std::string& Station::getItemName() const {
      return m_itemName;
   }

   //returns the next serial number to be used on the assembly line and increments m_serialNumber
   size_t Station::getNextSerialNumber() {
      return m_nextSerial++;
   }

   //returns the remaining quantity of items in the Station object
   size_t Station::getQuantity() const {
      return m_stock;
   }

   //subtracts 1 from the available quantity; should not drop below 0.
   void Station::updateQuantity() {
      if (m_stock >= 1)
         m_stock -= 1;
   }

   void Station::display(std::ostream& os, bool full) const {
      os << setw(3) << setfill('0') << m_stationID << " | " << left;
      os << setw(m_widthField + 1) << setfill(' ') << m_itemName << "| " << right;
      os << setw(6) << setfill('0') << m_nextSerial << " | " << setfill(' ');
      if (full){
         os << setw(4) << m_stock << " | "
            << m_description;
      }
      os << endl;
   }
}