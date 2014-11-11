#ifndef MINE_FIELD_H
#define MINE_FIELD_H

#include "matrix.h"
#include "mine_cell.h"

typedef Matrix<Mine_cell> MineMatrix;

class Mine_field
{
public:
    Mine_field(int r, int c)
        :mines(r, c)    {}

    int cells_number() const { return mines.rows() * mines.cols(); }
    void generate_mines(int N, int start_row, int start_col);
    void generate_neighbor_numbers();
    bool is_within_field(int row, int col);

    int rows() const {return mines.rows();}
    int cols() const {return mines.cols();}

    const Mine_cell& get_cell(int r, int c) const {return mines(r, c); }
private:
    MineMatrix mines;
};

#endif // MINE_FIELD_H
