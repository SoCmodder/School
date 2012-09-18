#ifndef parsedTokens_h
#define parsedTokens_h

#include <string>
#include <vector>

class ParsedTokens
{
   public:
      ParsedTokens();
      ~ParsedTokens();

      void ParseAndAddTokens(char * commandLine);

      void StartIterator();
      bool GetNextToken(std::string &inToken);

      void Clear();

   private:
      bool IsDelimiter(char ch);
      bool IsSpecialCharacter(char ch, bool addToContainer);

      std::vector<std::string> tokens;
      unsigned int iterCount;

};

#endif
