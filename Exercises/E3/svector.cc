/*
 * Class SVector: implementation.
 */

#include "svector.h"

SVector::SVector(size_t size) {
    v = new int[n = size];
}

SVector::~SVector() {
    delete[] v;
}

int SVector::size() const {
    return n;
}

int SVector::get(int i) const {
    return v[i];
}

void SVector::set(int i, int value) {
    v[i] = value;
}
