#include "Riego.h"

Riego::Riego() {
    randomSeed(analogRead(0));
    umbral = random(40, 61); // genera entre 40 y 60%
}

float Riego::getHumedadUmbral() {
    return umbral;
}
