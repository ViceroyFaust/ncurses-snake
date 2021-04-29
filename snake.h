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

class Snake {
private:
    BodyPart head;
    std::list<BodyPart> body;

public:
    Snake(int startx, int starty);

    void grow();
    void move();
    void setDirection();

    int getSize();

};

#endif // SNAKE_H_INCLUDED
