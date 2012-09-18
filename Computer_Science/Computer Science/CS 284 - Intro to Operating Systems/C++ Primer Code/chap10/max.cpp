#ifndef MAX_C
#define MAX_C

// generic template definition
template <class T>
        T max( T t1, T t2 ) {
                return (t1 > t2 ? t1 : t2);
}

#include <cstring>

// const char* explicit specialization:
// overrides instantiation from the generic template definition

typedef const char *PCC;
template<> PCC max< PCC >( PCC s1, PCC s2 ) {
        return ( strcmp( s1, s2 ) > 0 ? s1 : s2 );
}

#endif
