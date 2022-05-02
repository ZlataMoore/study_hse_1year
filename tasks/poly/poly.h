#pragma once
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>

class Poly {
public:
    Poly(const std::vector<std::vector<int>> &poly);
    Poly(const std::vector<int> &poly);
    Poly();
    friend Poly operator*(const Poly &poly1, const Poly &poly2);
    friend Poly operator-(const Poly &poly);
    friend bool operator==(const Poly &poly1, const Poly &poly2);
    friend bool operator!=(const Poly &poly1, const Poly &poly2);
    int64_t operator()(int x) const;
    void operator+=(const Poly &poly);
    void operator-=(const Poly &poly);
    Poly operator=(const Poly &poly);
    Poly operator+(const Poly &poly);
    Poly operator-(const Poly &poly);
    friend std::ostream &operator<<(std::ostream &out, const Poly &poly);

private:
    std::map<int, int> poly_;
};
