#include <array>
#include <optional>

namespace solver
{
    using Puzzle = std::array<unsigned, 9>;

    bool IsSolved(Puzzle const& puzzle);

    bool IsSolvable(Puzzle const& puzzle);

    std::optional<Puzzle> SolveDFS(Puzzle const& puzzle);
}
