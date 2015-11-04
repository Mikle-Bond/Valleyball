#ifndef BLOCK_H
#define BLOCK_H
/* Here block means a flat plane in 2D (line, to be honest).
 * That's why here we need to know only two points to handle it.
 * Vectors to the ends are builded from the (0,0) point, or from the container
 * position, if there will be some.
 */

#include "vector2d.h"

struct Block
{
	explicit Block(
		double ax = 0.0,
		double ay = 0.0,
		double bx = 0.0,
		double by = 0.0);
	Block (const Vector2D &_a, const Vector2D &_b);
	// Default copy constructor is just fine.
	~Block();

	Vector2D a, b;
};

#endif // BLOCK_H
