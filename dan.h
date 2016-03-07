#ifndef DAN
#define DAN



#include "player.h"
#include "manager.h"
#include "ball.h"

class DanThePlayer : public Player // it is rather similar with sam
{
    //false - right side, true - left side;
    bool side;

    double were();
    Vector2D How();

public:
    DanThePlayer();
    DanThePlayer(const Vector2D &left, const Vector2D &right, bool Side);
    virtual ~DanThePlayer();
    void init(const Vector2D &left, const Vector2D &right,
            double height, double max_speed, double max_force,
            double curr);

    Vector2D get_force();
    virtual bool move();
    virtual void idle(void);
    // virtual Vector2D push(void);
};


#endif // DAN

