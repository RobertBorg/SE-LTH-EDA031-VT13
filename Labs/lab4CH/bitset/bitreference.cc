#include "bitreference.h"
#include "bitset.h"

namespace cpp_lab4 {
    BitReference& BitReference::operator=(bool x) {
        if (x)
            *p_bits |= 1L << pos;
        else
            *p_bits &= ~ (1L << pos);
        return *this;
    }
    
    BitReference& BitReference::operator=(const BitReference& bsr) {
        bool toCopy = bsr;
        operator=(toCopy);
        return *this;
    }
    
    BitReference::operator bool() const {
        return (*p_bits & (1L << pos)) != 0;
    }
}
