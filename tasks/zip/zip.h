#pragma once

#include <forward_list>
#include <string>

using Value = std::string;
using Iterator = std::forward_list<std::string>::const_iterator;
using ZippedPair = std::pair<const Value&, const Value&>;

class ZipIterator {
public:
    ZipIterator(Iterator cur_a, Iterator cur_b);

    ZipIterator& operator++();

    std::pair<const std::string&, const std::string&> operator*() const;

    bool operator!=(const ZipIterator& other) const;

private:
    Iterator cur_a_;
    Iterator cur_b_;

};

class Zipped {
public:
    Zipped(ZipIterator begin, ZipIterator end) : begin_(begin), end_(end) {}

    ZipIterator begin() const;

    ZipIterator end() const;

private:
    ZipIterator begin_;
    ZipIterator end_;
};

Zipped Zip(Iterator a_begin, Iterator a_end, Iterator b_begin, Iterator b_end);
