/***********************************************************************
// OOP345 MS2:
// File	Station.h
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
#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include <iostream>
#include <string>
#include "Utilities.h"
namespace sdds {
   class Station {
      int m_stationID{};
      std::string m_itemName{};
      std::string m_description{};
      unsigned int m_nextSerial{};
      unsigned int m_stock{};
      static size_t m_widthField;
      static int id_generator;
   public:
      Station(const std::string& str);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };
}
#endif
