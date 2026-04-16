#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "../physics/body.hpp"

namespace Collision {
bool circle_intersects(Body &a, Body &b);
void circle_resolve(Body &a, Body &b);
} // namespace Collision

#endif // !CIRCLE_HPP
