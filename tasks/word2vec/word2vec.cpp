#include "word2vec.h"

#include <vector>

int InnerProduct(const std::vector<int>& vector1, const std::vector<int>& vector2) {

    int64_t len = vector1.size();
    int64_t inner_product = 0;

    for (int64_t i = 0; i != len; ++i) {
        inner_product += vector1[i] * vector2[i];
    }

    return inner_product;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {

    int64_t length = words.size();

    if (length < 2) {
        return {};
    }

    int64_t max_measure = InnerProduct(vectors[0], vectors[1]);
    std::vector<std::string> result;

    for (int64_t index = 1; index != length; index++) {
        if (InnerProduct(vectors[0], vectors[index]) > max_measure) {
            max_measure = InnerProduct(vectors[0], vectors[index]);
            result.clear();
            result.push_back(words[index]);
        } else if (InnerProduct(vectors[0], vectors[index]) == max_measure) {
            result.push_back(words[index]);
        }
    }

    return result;
}
