#ifndef STCKEXCP_H
#define STCKEXCP_H

class popOnEmpty { /* ... */ };
class pushOnFull { 
public:
        pushOnFull( int i ) : _value( i ) { }
        int value() { return _value; }
private:
        int _value;
};

#endif
