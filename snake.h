#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

struct BodyPart {
    enum Direction {
        d_up;
        d_down;
        d_left;
        d_right;
    };

    Direction movDirection{};
    int x{};
    int y{};
};

#endif // SNAKE_H_INCLUDED
