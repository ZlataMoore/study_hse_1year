#include "Blur.h"
#include "iostream"

Blur::Blur(float s) : sigma(s) {}



float coeff(float x0, float y0, float x, float y, float sigma) {
    float one = 1 / (sqrt(2 * M_PI * pow(sigma, 2)));
    float degree = - (pow((x - x0), 2) + pow((y - y0), 2)) / (2 * pow(sigma, 2));
    float result = one * pow(M_E, degree);
    return result;

}


void Blur::Apply(Image &image) {
    Image copy = image;
    int a = int(3 * sigma);
    for (int y = 0; y != image.height_; ++y) {
        for (int x = 0; x != image.width_; ++x) {

            float pixel_r = 0;
            float pixel_g = 0;
            float pixel_b = 0;
            float matrix_sum = 0;
            int begin = std::max(0, x - a);
            for (begin; begin != std::min(x + a, copy.width_ - 1); ++begin) {
                matrix_sum += coeff(x, y, begin, y, sigma);
                pixel_r += coeff(x, y, begin, y, sigma) * copy.colors_[begin][y].r;
                pixel_b += coeff(x, y, begin, y, sigma) * copy.colors_[begin][y].b;
                pixel_g += coeff(x, y, begin, y, sigma) * copy.colors_[begin][y].g;
            }

            pixel_r /= matrix_sum;
            pixel_b /= matrix_sum;
            pixel_g /= matrix_sum;
            image.colors_[x][y].r = pixel_r;
            image.colors_[x][y].b = pixel_b;
            image.colors_[x][y].g = pixel_g;
        }
    }
    Image copy1 = image;
    for (int y1 = 0; y1 != image.height_; ++y1) {
        for (int x1 = 0; x1 != image.width_; ++x1) {

            float pixel_r1 = 0;
            float pixel_g1 = 0;
            float pixel_b1 = 0;
            float matrix_sum1 = 0;
            int begin = std::max(0, y1 - a);
            for (begin; begin != std::min(y1 + a, image.height_ - 1); ++begin) {
                matrix_sum1 += coeff(x1, y1, x1, begin, sigma);
                pixel_r1 += coeff(x1, y1, x1, begin, sigma) * copy1.colors_[x1][begin].r;
                pixel_g1 += coeff(x1, y1, x1, begin, sigma) * copy1.colors_[x1][begin].g;
                pixel_b1 += coeff(x1, y1, x1, begin, sigma) * copy1.colors_[x1][begin].b;
            }


            pixel_r1 /= matrix_sum1;
            pixel_b1 /= matrix_sum1;
            pixel_g1 /= matrix_sum1;

            image.colors_[x1][y1].r = pixel_r1;
            image.colors_[x1][y1].b = pixel_b1;
            image.colors_[x1][y1].g = pixel_g1;

        }
    }
    std::cout << image.width_ << " " << image.height_ << "\n";

}