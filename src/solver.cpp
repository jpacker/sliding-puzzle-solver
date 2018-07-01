#include "solver.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <set>
#include <vector>

namespace 
{
    enum class Move
    {
        Up,
        Left,
        Down,
        Right
    };

    constexpr std::array<Move, 4> AllMoves = 
        {Move::Up, Move::Left, Move::Down, Move::Right};

    static bool IsMoveLegal(Move m, std::ptrdiff_t zeroPos)
    {
        switch(m)
        {
            case Move::Up:
                return zeroPos > 2;
            case Move::Left:
                return zeroPos != 0 && zeroPos != 3 && zeroPos != 6;
            case Move::Down:
                return zeroPos < 6;
            case Move::Right:
                return zeroPos != 2 && zeroPos != 5 && zeroPos != 8;
            default:
                assert(false && "Didn't cover all cases");
        }
        return false;
    }

    static std::optional<solver::Puzzle>
        GenerateMove_(solver::Puzzle const& p, Move m)
    {
        using namespace std;
        auto b = begin(p);
        auto it = find(begin(p), end(p), 0);
        auto zeroPos = distance(b, it);
        if(!IsMoveLegal(m, zeroPos))
        {
            return {};
        }

        auto newP = p;

        switch(m)
        {
            case Move::Up:
                swap(newP[zeroPos], newP[zeroPos-3]);
                break;
            case Move::Left:
                swap(newP[zeroPos], newP[zeroPos-1]);
                break;
            case Move::Down:
                swap(newP[zeroPos], newP[zeroPos+3]);
                break;
            case Move::Right:
                swap(newP[zeroPos], newP[zeroPos+1]);
                break;
            default:
                assert(false && "Didn't cover all cases");
        }

        return newP;
    }
}

bool solver::IsSolved(Puzzle const& puzzle)
{
    using namespace std;
    return is_sorted(begin(puzzle), end(puzzle));
}

bool solver::IsSolvable(Puzzle const& puzzle)
{
    using namespace std;
    // http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
    // Count the number of inversions and if it is even 
    // (for odd puzzle size) then it is solvable
    // An inversion is a pair of tiles (a,b) such that a appears before
    // b and a > b.
    constexpr auto puzzleSize = std::tuple_size<Puzzle>::value;
    static_assert(puzzleSize % 2 == 1, "expect odd puzzle size");
    std::array<unsigned, puzzleSize> inversions;
    for(unsigned i = 0; i < puzzleSize - 1; ++i)
    {
        const auto current = puzzle[i];
        inversions[i] = count_if(begin(puzzle) + i + 1,
                end(puzzle),
                [current](const auto n) 
                {
                    return n != 0 && n < current;
                }
                );
    }
    const auto totalInversions = accumulate(begin(inversions),
            end(inversions), 0u);
    const auto isSolvable = totalInversions % 2 == 0;
    return isSolvable;
}

std::optional<solver::Puzzle> solver::SolveDFS(Puzzle const& puzzle)
{
    using namespace std;
    if(!IsSolvable(puzzle))
    {
        return optional<Puzzle>{};
    }

    if(IsSolved(puzzle))
    {
        return puzzle;
    }

    vector<Puzzle> frontier;
    set<Puzzle> explored;

    frontier.push_back(puzzle);

    while(!frontier.empty())
    {
        const auto p = frontier.back();
        frontier.pop_back();
        explored.insert(p);
        for(const auto move : AllMoves)
        {
            const auto newPuzzle = GenerateMove_(p, move);
            if(newPuzzle.has_value())
            {
                const auto& newP = newPuzzle.value();
                const auto itExplored = explored.find(newP);
                const auto isExplored = itExplored != end(explored);
                const auto itFront = find(begin(frontier), end(frontier), 
                        newP);
                const auto isFront = itFront != end(frontier);
                if(!isExplored && !isFront)
                {
                    if(IsSolved(newP))
                    {
                        return newP;
                    }
                    else
                    {
                        frontier.push_back(newP);
                    }
                }
            }
        }
    }

    return {};
}
