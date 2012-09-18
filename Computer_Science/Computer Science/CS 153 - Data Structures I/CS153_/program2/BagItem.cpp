#include "StdAfx.h"
#include "bag.h"
#include ".\bagitem.h"

BagItem::BagItem(void)
{
   weight_ = 0;
   description_ = "none";
}

BagItem::~BagItem(void)
{
}

CString BagItem::toString( ) const 
{
  char buffer[100];  // 100 is overkill, but better safe than sorry
  itoa(weight ,buffer, 10);  // 10 specifies that we want a decimal number
  CString weightAsString = buffer;
  return(description + "  " + weightAsString);
}

void BagItem::SetItem (int weight, CString description)
{
	weight_ = weight;
	description_ = description;

}
CString getDescription()
{
	return description_;
}
