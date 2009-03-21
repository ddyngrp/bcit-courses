#ifndef DEFS_H

#define GRID_EMPTY       0
#define GRID_BOMB        1
#define GRID_DBLOCK      2
#define GRID_UBLOCK      3
#define GRID_POWUP_NUM   4
#define GRID_POWUP_RAD   5
#define GRID_POWUP_SPIKE 6

#define TYPE_MOVE        0
#define TYPE_QUIT        1
#define TYPE_PLANT       2
#define TYPE_EXPLODE     3
#define TYPE_DIE         4
#define TYPE_POWERUP     5
#define TYPE_JOIN        6
#define TYPE_ADDYOU      7
/* TYPE_ADDYOU tells the client what it's id
   is so that it can send packets.  its
   a really shitty name sry */

#define MOVE_UP          0
#define MOVE_DOWN        1
#define MOVE_LEFT        2
#define MOVE_RIGHT       3

#define POWUP_NUMBER     0
#define POWUP_RADIUS     1
#define POWUP_SPIKE      2

#define UNITS_PER_MOVE   10

#define MAX_PLAYERS      8

#define DEFS_H
#endif
