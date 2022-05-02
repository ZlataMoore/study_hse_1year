#include "image_processor.h"

class Negative : public Filter {
public:
    void Apply(Image &image) override;
};