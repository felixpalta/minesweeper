#ifndef INPUT_LOOP_H
#define INPUT_LOOP_H
#include <string>
#include <sstream>


// Input loop algorithm.
// Print an input_prompt to ost,
// then in a loop try to input an object of type T from ist,
// until it was inputed successfully AND the condition is true.
// Case when output to ost is unsuccessfull is not considered here.
// T must have a default constructor.
template <typename T, typename Callable>
T input_loop(
    std::istream& ist, std::string input_prompt, std::ostream& ost, Callable cond)
{
    T temp;
    ost << input_prompt;
    while (!(ist >> temp) || !cond(temp))
    {
        ist.clear();
        ist.ignore(std::numeric_limits<int>::max(), '\n');
        ost << input_prompt;
    }
    if (ist.peek() != '\n')
        ist.ignore(std::numeric_limits<int>::max(), '\n');

    return temp;
}


// Input loop for reading two values and checking them with two separate condititon functors.
template <typename T1, typename T2, typename Callable1, typename Callable2>
void input_loop(
    std::istream& ist, std::string input_prompt, std::ostream& ost, Callable1 cond1, Callable2 cond2, T1& x1, T2& x2)
{
    T1 temp1;
    T2 temp2;
    ost << input_prompt;
    while (!(ist >> temp1) || !(ist >> temp2) || !cond1(temp1) || !cond2(temp2))
    {
        ist.clear();
        ist.ignore(std::numeric_limits<int>::max(), '\n');
        ost << input_prompt;
    }
    if (ist.peek() != '\n')
        ist.ignore(std::numeric_limits<int>::max(), '\n');

    x1 = temp1;
    x2 = temp2;
}

// Input loop for reading two values and checking them with one single condition functor.
template <typename T1, typename T2, typename Callable>
void new_input_loop(
    std::istream& ist, std::string input_prompt, std::ostream& ost, Callable cond, T1& x1, T2& x2)
{
    T1 temp1;
    T2 temp2;
    ost << input_prompt;
    while (!(ist >> temp1) || !(ist >> temp2) || !cond(temp1, temp2))
    {
        ist.clear();
        ist.ignore(std::numeric_limits<int>::max(), '\n');
        ost << input_prompt;
    }
    if (ist.peek() != '\n')
        ist.ignore(std::numeric_limits<int>::max(), '\n');

    x1 = temp1;
    x2 = temp2;
}

#endif // INPUT_LOOP_H
