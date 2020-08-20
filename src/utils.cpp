#include "utils.hpp"

bool even(int a)
{
    return a % 2 == 0;
}

unsigned int centered(int cols, const char *s)
{
    return ((cols - strlen(s)) / 2);
}
