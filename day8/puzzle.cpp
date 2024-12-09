#include "../headers/solver.h"
#include "../headers/utils.h"
#include <array>

namespace day8
{
    template <typename TileEntityType, typename coord_type, unsigned int Dim>
    class TileEntity
    {
    private:
        TileEntityType entity;
        std::array<coord_type, Dim> coords;

    public:
        // Constructor
        explicit TileEntity(const std::array<coord_type, Dim> &coordinates, const TileEntityType &tile_entity) : coords(coordinates), entity(tile_entity) {}

        // Getter - returns const reference to avoid copying
        const std::array<coord_type, Dim> &getCoords() const { return coords; }
        const TileEntityType &getEntity() const { return entity; }

    private:
        friend std::ostream &operator<<(std::ostream &os, const TileEntity &tile);
    };

    template <typename TileEntityType, typename coord_type, unsigned int Dim>
    std::ostream &operator<<(std::ostream &os, const TileEntity<TileEntityType, coord_type, Dim> &tile)
    {
        os << tile.getEntity() << ": " << tile.getCoords() << std::endl;
        return os;
    }

    // template <typename TileEntityType, typename coord_type, unsigned int Dim>
    // class TileGrid
    // {
    // public:
    //     TileGrid();

    // private:
    //     unsigned int dim = Dim;
    //     Matrix<TileEntity<TileEntityType, coord_type, Dim>, Dim, coord_type> grid;
    // };

    // class Day8Solver : public solve::Solver<TileGrid<Tile<char, 2>, 2>, int>
    // {
    // public:
    //     Day8Solver(std::string name, int puzzle_index) : Solver(name, 8, puzzle_index) {}

    //     TileGrid<2, char> parseInputFile(std::string file_name) override
    //     {
    //         return TileGrid<2, char>();
    //     }
    // };

    // class Puzzle1Solver : public Day8Solver
    // {
    // public:
    //     Puzzle1Solver() : Day8Solver("puzzle 1", 1) {}

    //     int computeSolution(TileGrid<2, char> data) override
    //     {
    //         return int();
    //     }
    // };

    // class Puzzle2Solver : public Day8Solver
    // {
    // public:
    //     Puzzle2Solver() : Day8Solver("puzzle 2", 2) {}

    //     int computeSolution(TileGrid<2, char> data) override
    //     {
    //         return int();
    //     }
    // };
}