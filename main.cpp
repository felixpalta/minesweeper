#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>

struct Mine_cell
{
    int row;
    int column;
    int value;
    Mine_cell(int r, int c, int v)
        :row(r), column(c), value(v) {}
};

class Mine_field
{
public:
    Mine_field(int n);
    int size() const { return sz; }
    Mine_cell get_cell(int r, int c) const;

    static const int MIN_FIELD_SIZE = 2;

private:
    int sz;
    std::vector<Mine_cell> mines;

};

Mine_cell Mine_field::get_cell(int r, int c) const
{
    for (unsigned int i = 0; i < mines.size(); ++i)
    {
        if (mines[i].row == r && mines[i].column == c)
            return mines[i];
    }
    throw std::runtime_error("Tried to get impossible cell");
}

Mine_field::Mine_field(int n)
: sz(n)
{
    int k = 0;
    for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
        {
            mines.push_back(Mine_cell(i, j, k));
            ++k;
        }
}

void drawMineField(const Mine_field& m)
{
    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m.size(); ++j)
        {
            std::cout << m.get_cell(i, j).value << '\t';
        }
        std::cout << std::endl;
    }
}

int main()
try
{
    int field_size = 0;


    do
    {
        std::cout << "Input field size, N >= " << Mine_field::MIN_FIELD_SIZE << ": ";
        std::cin >> field_size;
    } while (!std::cin || field_size < Mine_field::MIN_FIELD_SIZE);

    std::cout << "Your input is " << field_size << std::endl;

    Mine_field m(field_size);
    drawMineField(m);
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
