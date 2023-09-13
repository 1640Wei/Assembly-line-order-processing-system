/***********************************************************************
// OOP345 MS3:
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
#ifndef SDDS_LINEMANAGER_H_
#define SDDS_LINEMANAGER_H_
#include <iostream>
#include <string>
#include <vector>
#include "Workstation.h"
namespace sdds {
   class LineManager {
      std::vector<Workstation*> m_activeLine; 
      size_t m_cntCustomerOrder;  
      Workstation* m_firstStation{};  
   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);
      void reorderStations();
      bool run(std::ostream& os);
      void display(std::ostream& os) const;
   };
}
#endif