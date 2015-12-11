#ifndef DAN
#define DAN



#include "player.h"
#include "manager.h"
#include "ball.h"

class DanThePlayer : public Player // it is rather similar with sam
{
    //false - right side, true - left side;
    bool side;

    double were(Ball& ball);
    Vector2D How();

public:
    DanThePlayer(const Vector2D &left, const Vector2D &right, bool Side);
    ~SamThePlayer();
    void init(const Vector2D &left, const Vector2D &right,
            double height, double max_speed, double max_force,
            double curr) = 0;

    Vector2D get_force();
    virtual bool move(double dt);
    virtual void idle(void);
    virtual Vector2D push(void);
};


#endif // DAN

