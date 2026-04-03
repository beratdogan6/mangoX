#ifndef CIRCLE_H
#define CIRCLE_H

#include "../physics/body.h"
#include <stdbool.h>

bool circle_intersects(Body circleA, Body circleB);
void circle_resolve(Body *circleA, Body *circleB);

#endif // !CIRCLE_H
