#include "catch.hpp"
#include "solver.hpp"

namespace Catch {
    template<typename T, std::size_t N>
    struct StringMaker<std::array<T, N> > {
        static std::string convert( std::array<T,N> const& v ) {
            return ::Catch::Detail::rangeToString( v.begin(), v.end() );
        }
    };
}

TEST_CASE("Is the puzzle solved?", "[is_solved]") 
{
	{
		solver::Puzzle p = {0,1,2,3,4,5,6,7,8};
		REQUIRE(solver::IsSolved(p) == true);
	}

	{
		solver::Puzzle p = {0,2,3,5,6,7,8,4,1};
		REQUIRE(solver::IsSolved(p) == false);
	}
}

TEST_CASE("Is the puzzle solvable?", "[is_solvable]")
{
	{
		solver::Puzzle p = {0,1,2,3,4,5,6,8,7};
		REQUIRE(solver::IsSolvable(p) == false);
	}
	
	{
		solver::Puzzle p = {0,1,2,3,4,5,6,7,8};
		REQUIRE(solver::IsSolvable(p) == true);
	}

	{
		solver::Puzzle p = {0,8,2,3,4,5,6,1,7};
		REQUIRE(solver::IsSolvable(p) == true);
	}

	{
		solver::Puzzle p = {0,8,2,3,4,5,6,7,1};
		REQUIRE(solver::IsSolvable(p) == false);
	}

	{
		solver::Puzzle p = {1,8,2,3,4,5,6,7,0};
		REQUIRE(solver::IsSolvable(p) == true);
	}

	{
		solver::Puzzle p = {1,8,3,2,4,5,6,7,0};
		REQUIRE(solver::IsSolvable(p) == false);
	}
	
	{
		solver::Puzzle p = {1,8,2,3,4,5,6,0,7};
		REQUIRE(solver::IsSolvable(p) == true);
	}
}

TEST_CASE("Depth-first search solve", "[dfs]")
{
	const solver::Puzzle solved = {0,1,2,3,4,5,6,7,8};
	{
		solver::Puzzle p = {0,1,2,3,4,5,6,7,8};
		const auto result = solver::SolveDFS(p);
		REQUIRE(result.has_value() == true);
		REQUIRE(result.value() == solved);
	}

	{
		solver::Puzzle p = {0,1,2,3,4,5,6,8,7};
		const auto result = solver::SolveDFS(p);
		REQUIRE(result.has_value() == false);
	}

	{
		solver::Puzzle p = {1,0,2,3,4,5,6,7,8};
		const auto result = solver::SolveDFS(p);
		REQUIRE(result.has_value() == true);
		REQUIRE(result.value() == solved);
	}
// Uncomment to test but can take a while
//	{
//		solver::Puzzle p = {0,8,2,3,4,5,6,1,7};
//		const auto result = solver::SolveDFS(p);
//		REQUIRE(result.has_value() == true);
//		REQUIRE(result.value() == solved);
//	}
}
