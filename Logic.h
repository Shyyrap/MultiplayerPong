#pragma once
const int thickness = 10;
const int width_screen = 480;
const int height_screen = 240;
const int paddle_height = 5*thickness;
const int paddle_width = 2*thickness;
struct Vector2 
{
    int x;
    int y;
};
enum WALL_SIDES 
{
    NORTH_WALL,
    WEST_WALL,
    SOUTH_WALL,
    EAST_WALL,
    TOTAL_WALL
};

