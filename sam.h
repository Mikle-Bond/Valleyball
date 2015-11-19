#ifndef SAM_H
#define SAM_H 

#include "player.h"

class SamThePlayer : public Player
{
public:
	SamThePlayer(const Vector2D &left, const Vector2D &right);
	~SamThePlayer();

	virtual void idle(void);
	virtual Vector2D get_force(void);
};


#endif // SAM_H

