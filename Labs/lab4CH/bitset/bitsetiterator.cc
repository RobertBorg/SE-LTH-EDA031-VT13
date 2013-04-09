#include "bitsetiterator.h"

namespace cpp_lab4 {
	BitsetIterator& BitsetIterator::operator=(const BitsetIterator& bsi) {
		p_bits = bsi.p_bits;
		pos = bsi.pos;
		return *this;
	}
	
    bool BitsetIterator::operator!=(const BitsetIterator& bsi) const {
        bool bits = false;
        if(p_bits == bsi.p_bits)
            bits = true;
        bool pos = false;
        if(pos == bsi.pos) 
            pos = true;
        return !(bits && pos);
    }
    
    BitsetIterator& BitsetIterator::operator++() {
        ++pos;
        return *this;
    }
    
    BitReference BitsetIterator::operator*() {
        return BitReference(p_bits, pos);
    }
}
