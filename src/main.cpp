#include <iostream>
#include "solver.hpp"

int main()
{
    solver::Puzzle p = {0,8,2,3,4,5,6,1,7};
    const auto result = solver::SolveDFS(p);
    if(result.has_value())
    {
        for(const auto i : result.value())
        {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
}

