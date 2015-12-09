﻿#ifndef SAM_H
#define SAM_H 

#include "player.h"
#include "manager.h"
#include "ball.h"

class SamThePlayer : public Player
{
    //false - right side, true - left side;
    bool side;

    double were(Ball& ball);
    Vector2D How();

public:
    SamThePlayer(const Vector2D &left, const Vector2D &right, bool Side);
	~SamThePlayer();
    Vector2D get_force(Manager &Mng);
    virtual bool move(double dt);
	virtual void idle(void);
    virtual Vector2D push(void);
};


#endif // SAM_H

