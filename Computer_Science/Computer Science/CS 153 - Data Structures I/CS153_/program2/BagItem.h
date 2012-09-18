#pragma once

class BagItem
{
	public:
		BagItem(void);
		~BagItem(void);
		CString toString( ) const;
		void SetItem (int weight_, CString description_);
		CString getDescription();
	private:
		int weight_ ;
		CString description_;


};

