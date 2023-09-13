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
#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_
#include <iostream>
#include <string>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
namespace sdds {

   extern std::deque<CustomerOrder> g_pending;   
   extern std::deque<CustomerOrder> g_completed;  
   extern std::deque<CustomerOrder> g_incomplete;  

   class Workstation :public Station {
      std::deque<CustomerOrder> m_orders;  
      Workstation* m_pNextStation{};
   public:
      Workstation(const std::string& str);
      Workstation(const Workstation& src) = delete;
      Workstation& operator=(const Workstation& src) = delete;
      Workstation(Workstation&& src) = delete;
      Workstation& operator=(Workstation&& src) = delete;
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station = nullptr);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder&& newOrder);
   };
}
#endif
