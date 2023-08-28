#include "filters.h"
#include <random>

namespace filters {
class Crystallize : public filters::Filter {
public:
    explicit Crystallize(int64_t n);

    Image Apply(const Image &img) const override;

private:
    int64_t num_ = 0;
};
}  // namespace filters