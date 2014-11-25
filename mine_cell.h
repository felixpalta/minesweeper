#ifndef MINE_CELL_H
#define MINE_CELL_H

class Mine_cell
{
public:
    // A cell either shows, that there is a mine present in it,
    // or how many mines are surrounding thic cell (from 0 to 8).
    enum Cell_value
    {
        MINE = -1,
        EMPTY = 0,
        MAX_VALUE = 8,
    };

    enum Cover
    {
        NONE,
        FLAGGED
    };

public:
    explicit Mine_cell(int v = EMPTY)
        :value(v), covered(true), cover_value(NONE) {}

    bool is_a_mine() const { return value == MINE; }
    bool is_empty() const { return value == EMPTY; }
    bool is_covered() const {return covered;}

    void uncover() {covered = false;}

public:
    int value;
    bool covered;
    Cover cover_value;
};

#endif // MINE_CELL_H
