#pragma once

#include <iterator>
#include <forward_list>
#include <string>

template<typename iter1, typename iter2>
class Iterator {
public:

    Iterator(auto cur1, auto cur2) {
        cur1_ = cur1;
        cur2_ = cur2;
    }

    auto operator++() {
        cur1_ ++;
        cur2_ ++;
        return *this;
    }

    auto operator*() const {
        auto result = std::make_pair(*cur1_, *cur2_);
        return result;
    }

    bool operator!=(const Iterator& other) const {
        return (cur1_ != other.cur1_ && cur2_ != other.cur2_);
    }

    iter1 cur1_;
    iter2 cur2_;

};

template<class Iter>
class Zipped {
public:
    Zipped(Iter begin, Iter end) : begin_(begin), end_(end) {}

    Iter begin() const {
        return begin_;
    }

    Iter end() const {
        return end_;
    }

private:
    Iter begin_;
    Iter end_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {

    using std::begin;
    using std::end;
    using std::iterator;

    auto begin_seq1  = begin(sequence1);
    auto begin_seq2  = begin(sequence2);
    auto end_seq1  = end(sequence1);
    auto end_seq2  = end(sequence2);

    Iterator<decltype(begin_seq1), decltype(begin_seq2)> Begin(begin_seq1, begin_seq2);
    Iterator<decltype(begin_seq1), decltype(begin_seq2)> End(end_seq1, end_seq2);
    return Zipped(Begin, End);

}
