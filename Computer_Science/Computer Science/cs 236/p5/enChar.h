//  File Name:  enChar.h
//  Function:   Define an enumeration type for characters
//              only used in lexical analyzer/scanner, not parser
//  Author:     Franck Xia
//  Creation:   Nov. 3, 2001

enum enChar
{
    DIGIT,
    DOT,          // in floating point
    LETTER,
    UNDERSCORE,
    BLANK,
    ENDCODE,       // we use $ for the end of program
    ENDLINE,       // currently not used
    GENERAL        // for other types. No interest to distinguish them here
};
