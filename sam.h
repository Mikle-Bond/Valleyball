#ifndef SAM_H
#define SAM_H 

#include "player.h"
#include "manager.h"
#include "ball.h"

class SamThePlayer : public Player
{
    //false - right side, true - left side;
    bool side;

    double were();

    Vector2D How();

public:
    SamThePlayer();
    SamThePlayer(const Vector2D &left, const Vector2D &right, bool Side);
    virtual ~SamThePlayer();
    virtual void init(const Vector2D &left, const Vector2D &right,
            double height, double max_speed, double max_force,
            double curr);


    Vector2D get_force();
    virtual bool move() override;
    virtual void idle(void);
    // virtual Vector2D push(void);
};


#endif // SAM_H

