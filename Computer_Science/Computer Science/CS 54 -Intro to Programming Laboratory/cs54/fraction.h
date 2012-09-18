class CFraction
{
 public:
 CFraction();
 void readIn();
 void print();
 CFraction recipricol();
 short getNumer() const;
 short getDenom() const;
 void setNumer(const short ksiVal);
 void setDenom(const short ksiVal);
 void unreduce(const short ksiNum);
 
 private:
  short m_siNumer;
  short m_siDenom;
 
};
