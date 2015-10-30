#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"
#include "block.h"

class Player
{
    double max_force;
    double max_speed;
public:
    Player(
            Vector2D left,
            Vector2D right,
            double height,
            double max_speed,
            double max_force,
            double curr = 0.5);
    ~Player();

    class pos : public Block
    {
        Vector2D lt_edge;
        Vector2D rt_edge;
        double pos_mul;
        double height;
        // here we understend position as
        // lt_edge + (rt_edge - lt_edge) * pos_mul;
    public:
        Vector2D get_pos(void);
        Vector2D get_head(void);
    };

    virtual void idle(void);
    virtual Vector2D get_force();
};

#endif // PLAYER_H
