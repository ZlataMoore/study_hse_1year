#include "zip.h"
#include <sstream>

ZipIterator::ZipIterator(Iterator cur_a, Iterator cur_b) {
    cur_a_ = cur_a;
    cur_b_ = cur_b;
}

ZipIterator& ZipIterator::operator++() {
    cur_a_ ++;
    cur_b_ ++;
    return *this;
}

std::pair<const std::string&, const std::string&> ZipIterator::operator*() const {
    return ZippedPair(*cur_a_, *cur_b_);
}

bool ZipIterator::operator!=(const ZipIterator& other) const {
    return (cur_a_ != other.cur_a_ && cur_b_ != other.cur_b_);
}

ZipIterator Zipped::begin() const {
    return begin_;
}

ZipIterator Zipped::end() const {
    return end_;
}

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end) {
    ZipIterator begin(a_begin, b_begin);
    ZipIterator end(a_end, b_end);
    return Zipped(begin, end);
}
