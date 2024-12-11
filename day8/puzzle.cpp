#include "../headers/solver.h"
#include "../headers/utils.h"
#include <array>

#include "../source/recursive.cpp"

namespace day8
{
    template <typename EntityType, typename coord_type, unsigned int Dim>
    class Entity
    {
    private:
        EntityType entity;
        Vec<coord_type, Dim> coords;

    public:
        // Constructor
        explicit Entity(const Vec<coord_type, Dim> &coordinates, const EntityType &tile_entity) : coords(coordinates), entity(tile_entity) {}

        // Getter - returns const reference to avoid copying
        const Vec<coord_type, Dim> &getCoords() const { return coords; }
        const EntityType &getEntity() const { return entity; }

    private:
        friend std::ostream &operator<<(std::ostream &os, const Entity &tile);
    };

    template <typename EntityType, typename coord_type, unsigned int Dim>
    std::ostream &operator<<(std::ostream &os, const Entity<EntityType, coord_type, Dim> &tile)
    {
        os << tile.getEntity() << ": " << tile.getCoords() << std::endl;
        return os;
    }

    ///
    template <typename BaseEntity, typename coord_type, unsigned int Dim>
    class GridWorld
    {
    private:
        NVector<std::shared_ptr<BaseEntity>, Dim> world;
        std::vector<std::shared_ptr<BaseEntity>> entities;

    public:
        void spawn(BaseEntity);
        void despawn(BaseEntity);
    };

    template <typename BaseEntity, typename coord_type, unsigned int Dim>
    void GridWorld<BaseEntity, coord_type, Dim>::spawn(BaseEntity entity)
    {
        std::shared_ptr<BaseEntity> p_entity = std::make_shared<BaseEntity>(entity);
        world.putElement(p_entity);
        entities.push_back(p_entity);
    }

    ///

    // template <typename EntityType, typename coord_type, unsigned int Dim>
    // class TileGrid
    // {
    // public:
    //     TileGrid();

    // private:
    //     unsigned int dim = Dim;
    //     Matrix<TileEntity<EntityType, coord_type, Dim>, Dim, coord_type> grid;
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