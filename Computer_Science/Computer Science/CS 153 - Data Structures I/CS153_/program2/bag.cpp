#include "StdAfx.h"
#include ".\bag.h"
#include "BagItem.h"

bag::bag(void)
{
	used_ = 0;
	totalWeight = 0;
}

bag::~bag(void)
{
}

void bag::add(const BagItem)
{
	if (BagItem.weight_ + totalWeight > MAX_WEIGHT)&&(used_ < 10)
	{
		MessageBox("Cannot add this item because it violates ");
      MessageBox("the max weight/items");
	}
	else 
	{
		data_[used_].SetItem(weight, description);
		used_++;
	}

}

bool bag::erase_one(const Cstring description)
{
	bool check = false;
	for (int i = 0; i < used_; i++)
	{
		if(description == data_[i].getDescription())
		{
			data_[i] = data_[used_ -1]; 
			check = true;
			used_--;
		}
		else 
		{
			return check;
		}
}
 
bool bag::erase_all()
{
	bool test = false;
	trashBagListBox.ResetContent();
	BagItem.weight_ = 0;
	BagItem.description_= "None";
	used_ = 0;


}

int bag::getNumItems() const
{
	return used_;
	
}

BagItem bag::getItemByIndex(int i) const
{

}


}