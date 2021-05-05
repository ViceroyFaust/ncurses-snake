#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

enum Direction {
        d_up,
        d_down,
        d_left,
        d_right,
};
// Because x and y are very widely used in this program
// I decided to make it its own struct
struct Point {
    int x{};
    int y{};
};

struct BodyPart {
    Direction movDirection{};
    Point coord{};
};

#endif // STRUCTURES_H_INCLUDED
