#ifndef MINE_FIELD_H
#define MINE_FIELD_H

#include <vector>

struct Mine_cell
{
    int row;
    int column;
    int value;
    Mine_cell(int r, int c, int v)
        :row(r), column(c), value(v) {}
    Mine_cell(int r, int c)
        :row(r), column(c), value(0) {}

    bool is_a_mine() const { return value == MINE; }
    bool is_empty() const { return value == EMPTY; }

    enum Cell_type
    {
        MINE = -1,
        EMPTY = 0
    };
    static const int MAX_VALUE = 8; // a cell, surrounded by mines will have 8 neighbours, i.e. it is max value of the cell.

};

bool operator==(const Mine_cell& left, const Mine_cell& right);
bool operator!=(const Mine_cell& left, const Mine_cell& right);

class Mine_field
{
public:
    explicit Mine_field(int n);
    Mine_cell get_cell(int r, int c) const;

    int side_size() const { return side_sz; }
    int cell_number() const { return mines.size(); }
    bool cell_is_present_in_field(int row, int col) const;
    void generate_mines(int N, int row, int col);
    void generate_neighbor_numbers();
    static const int MIN_FIELD_SIZE = 2;

private:
    int side_sz;
    std::vector<Mine_cell> mines;

};

#endif // MINE_FIELD_H
