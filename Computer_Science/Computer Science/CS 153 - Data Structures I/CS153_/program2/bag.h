#pragma once

#include "BagItem.h"
class bag
{
	public:
		bag(void);
		~bag(void);
		typedef BagItem value_type;
		static const int CAPACITY = 10;
		static const int MAX_WEIGHT = 30;
  		void add(const BagItem);
      bool erase_one(const Cstring description);
      bool erase_all();
		int getNumItems() const;
		BagItem getItemByIndex(int i) const;
		
	private:
		value_type data_[CAPACITY];
		unsigned int used_; 
		unsigned int totalWeight;

};

