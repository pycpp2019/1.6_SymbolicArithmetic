#pragma once

#include <utility>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Rng {
private:
    uint32_t state;
    double last_normal;
    bool last_normal_stored;

public:
    Rng(uint32_t seed) : state(seed), last_normal_stored(false) {}

    uint32_t rand_int() {
        return (this->state = 1103515245*this->state + 12345);
    }

    double uniform() {
        return double(this->rand_int())/0x100000000;
    }

    double normal() {
        if (this->last_normal_stored) {
            this->last_normal_stored = false;
            return this->last_normal;
        } else {
            double phi = 2.0*M_PI*this->uniform();
            double r = -log(0.5*(1.0 - this->uniform()));
            this->last_normal = r*sin(phi);
            this->last_normal_stored = true;
            return r*cos(phi);
        }
    }
};


