#include <cassert>
#include "Coord.h"

const Coord Coord::ZERO = Coord(0.0, 0.0, 0.0);

static double dist(double coord1, double coord2, double size) {
    double difference = fabs(coord1 - coord2);
    if (difference == 0)
        // NOTE: event if size is zero
        return 0;
    else {
        assert(size != 0);
        double dist = Coord::modulo(difference, size);
        return std::min(dist, size - dist);
    }
}

