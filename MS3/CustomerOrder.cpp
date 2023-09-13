/***********************************************************************
// OOP345 MS2:
// File	CustomerOrder.cpp
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
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
using namespace std;

namespace sdds{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const string& str){
		Utilities temp;
		bool more = false;
		size_t pos = 0u;
		//If the string str is empty ---> set to empty state
		if (str.empty()){
			m_name = "";
			m_product = "";
			m_cntItem = 0;
			m_lstItem = nullptr;
		}
		else{
			//Otherwise, the m_name is extracted from the string str
			m_name = temp.extractToken(str, pos, more);
			if (more){
				m_product = temp.extractToken(str, pos, more);
			}
			string newItems = str.substr(pos, str.length() - pos);
			m_cntItem = (count(newItems.begin(), newItems.end(), temp.getDelimiter())) + 1;
			//DMA for the list of Items
			m_lstItem = new Item * [m_cntItem]; 
			for (size_t i = 0u; i < m_cntItem && more; i++)
				m_lstItem[i] = new Item(temp.extractToken(str, pos, more));  //DMA
			if (m_widthField < temp.getFieldWidth())
				m_widthField = temp.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src){
		throw "Error!";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src)noexcept{
		*this = std::move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src)noexcept{
		if (this != &src){
			for (auto i = 0u; i < m_cntItem; i++){
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			//shallow copy
			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			//set to empty state
			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		if (m_lstItem) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}
	}

	bool CustomerOrder::isOrderFilled() const {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os){
		bool isItemFound = false;
		//check every items in the order
		for (unsigned int i = 0; i < m_cntItem && !isItemFound; i++){
			if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {
				if (station.getQuantity() > 0){
					//substract 1 from the inventory
					station.updateQuantity(); 
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					isItemFound = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}

			}
		}
	}
	
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i{ 0 }; i < m_cntItem; i++) {
			os << setfill('0');
			os << "[" << setw(6) << right << m_lstItem[i]->m_serialNumber << "] ";
			os << setfill(' ') << std::left;
			os << setw(m_widthField) << m_lstItem[i]->m_itemName;
			os << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
			os << endl;
		}
		os << std::resetiosflags(std::ios::adjustfield);
	}
}