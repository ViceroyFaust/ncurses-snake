#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

enum Direction {
        d_up,
        d_down,
        d_left,
        d_right,
    };

struct BodyPart {
    Direction movDirection{};
    int x{};
    int y{};
};

class Snake {
private:
    BodyPart m_head;
    std::list<BodyPart> m_body;

public:
    Snake(Direction startDir, int startx, int starty);

    void grow();
    void move();
    void setDirection();

    int getSize();

};

#endif // SNAKE_H_INCLUDED
