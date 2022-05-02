#include "associative_operation.h"
#include <vector>

bool IsAssociative(const std::vector<std::vector<size_t>>& table) {

    int64_t size = table.size();

    for (int x = 0; x != size; ++x) {
        for (int y = 0; y != size; ++y) {
            for (int z = 0; z != size; ++z) {
                if (table[table[x][y]][z] != table[x][table[y][z]]) {
                    return false;
                }
            }
        }
    }

    return true;
}
