#include "poly.h"
#include <cmath>

Poly::Poly() {
    poly_[0] = 0;
}

Poly::Poly(const std::vector<std::vector<int>> &poly) {
    for (int64_t index = 0; index != static_cast<int64_t>(poly.size()); ++index) {
        poly_[poly[index][0]] = poly[index][1];
    }
}

Poly::Poly(const std::vector<int> &poly) {
    for (int64_t index = 0; index != static_cast<int64_t>(poly.size()); ++index) {
        if (poly[index] != 0) {
            poly_[index] = poly[index];
        }
    }
}

Poly Poly::operator=(const Poly &poly) {

    if (this == &poly) {
        return *this;
    }

    this->poly_.clear();
    for (const auto &pair : poly.poly_) {
        this->poly_[pair.first] = pair.second;
    }

    return *this;
}

Poly operator-(const Poly &poly) {
    Poly result;
    result.poly_.clear();
    for (const auto &pair : poly.poly_) {
        result.poly_[pair.first] = -pair.second;
    }
    return result;
}

Poly operator*(const Poly &poly1, const Poly &poly2) {
    Poly result;
    result.poly_.clear();
    std::set<int> degrees;
    for (const auto &pair1 : poly1.poly_) {
        for (const auto &pair2 : poly2.poly_) {
            result.poly_[pair1.first + pair2.first] += pair1.second * pair2.second;
        }
    }
    if (result.poly_.empty()) {
        result.poly_[0] = 0;
    }
    return result;
}

bool operator==(const Poly &poly1, const Poly &poly2) {
    return poly1.poly_ == poly2.poly_;
}

bool operator!=(const Poly &poly1, const Poly &poly2) {
    return !(poly1 == poly2);
}

int64_t Poly::operator()(int x) const {
    int64_t answer = 0;
    for (const auto &pair : this->poly_) {
        answer += pair.second * static_cast<int64_t>(pow(static_cast<int64_t>(x), static_cast<int64_t>(pair.first)));
    }
    return answer;
}

void Poly::operator+=(const Poly &poly) {

    std::set<int> degrees;
    for (auto &pair : this->poly_) {
        degrees.insert(pair.first);
    }
    for (auto &pair : poly.poly_) {
        degrees.insert(pair.first);
    }
    for (auto &degree : degrees) {
        if (this->poly_.count(degree) != 0 && poly.poly_.count(degree) != 0) {
            this->poly_[degree] += poly.poly_.at(degree);
        } else if (poly.poly_.count(degree) != 0) {
            this->poly_[degree] = poly.poly_.at(degree);
        }
        if (this->poly_[degree] == 0) {
            this->poly_.erase(degree);
        }
    }
    if (this->poly_.empty()) {
        this->poly_[0] = 0;
    }
}

void Poly::operator-=(const Poly &poly) {
    *this += (-poly);
}

Poly Poly::operator+(const Poly &poly) {
    Poly result;
    *this += poly;
    result = *this;
    *this -= poly;
    return result;
}

Poly Poly::operator-(const Poly &poly) {
    Poly result = *this + (-poly);
    return result;
}

bool CompareByDegrees(const std::pair<int, int> &pair1, const std::pair<int, int> &pair2) {
    return pair1.first > pair2.first;
}

std::ostream &operator<<(std::ostream &out, const Poly &poly) {
    std::string poly_string = "y =";
    if (poly.poly_.count(0) != 0) {
        if (poly.poly_.at(0) == 0) {
            poly_string = "y = 0";
            out << poly_string;
            return out;
        }
    }
    std::vector<std::pair<int, int>> poly_vector;
    for (const auto &pair : poly.poly_) {
        poly_vector.push_back(pair);
    }
    sort(poly_vector.begin(), poly_vector.end(), CompareByDegrees);
    for (const auto &pair : poly_vector) {
        std::string coeff = std::to_string(pair.second);
        std::string degree = std::to_string(pair.first);
        if (pair.first == poly_vector[0].first) {
            if (pair.first >= 2) {
                poly_string += ' ';
                poly_string += coeff;
                poly_string += "x^";
                poly_string += degree;
            } else if (pair.first == 1) {
                poly_string += ' ';
                poly_string += coeff;
                poly_string += "x";
            } else {
                poly_string += ' ';
                poly_string += coeff;
            }
        } else {
            if (pair.first >= 2 && pair.second > 0) {
                poly_string += " + ";
                poly_string += coeff;
                poly_string += "x^";
                poly_string += degree;
            } else if (pair.first >= 2 && pair.second < 0) {
                poly_string += ' ';
                poly_string += coeff;
                poly_string += "x^";
                poly_string += degree;
            } else if (pair.first == 1 && pair.second > 0) {
                poly_string += " + ";
                poly_string += coeff;
                poly_string += "x";
            } else if (pair.first == 1 && pair.second < 0) {
                poly_string += ' ';
                poly_string += coeff;
                poly_string += "x";
            } else if (pair.second > 0) {
                poly_string += " + ";
                poly_string += coeff;
            } else {
                poly_string += ' ';
                poly_string += coeff;
            }
        }
    }
    out << poly_string;

    return out;
}
