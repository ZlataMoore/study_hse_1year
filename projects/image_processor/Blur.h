#include "image_processor.h"

class Blur : public Filter {
public:
    Blur(float s);
    void Apply(Image &image) override;
    float sigma;

};
