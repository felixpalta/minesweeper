#ifndef MINE_CELL_H
#define MINE_CELL_H

class Mine_cell
{
public:
    int value;

    explicit Mine_cell(int v = EMPTY)
        :value(v) {}

    bool is_a_mine() const { return value == MINE; }
    bool is_empty() const { return value == EMPTY; }


    // A cell either shows, that there is a mine present in it,
    // or how many mines are surrounding thic cell (from 0 to 8).
    enum Cell_value
    {
        MINE = -1,
        EMPTY = 0,
        MAX_VALUE = 8,
    };

};

#endif // MINE_CELL_H
