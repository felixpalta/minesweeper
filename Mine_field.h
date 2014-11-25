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


    int rows() const {return mines.rows();}
    int cols() const {return mines.cols();}

    const Mine_cell& get_cell(int r, int c) const {return mines(r, c); }
    Mine_cell& get_cell(int r, int c) {return mines(r,c);}

    void start(int N, int start_row, int start_col);
    bool try_cell(int row, int col);
private:
    MineMatrix mines;
private:
    void generate_mines(int N, int start_row, int start_col);
    void generate_neighbor_numbers();
    void uncover_neighbours(int row, int col);
};

// Helper function

bool is_within_field(const Mine_field& m, int row, int col);



#endif // MINE_FIELD_H
