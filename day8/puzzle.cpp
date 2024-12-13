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
        VecArrayR<coord_type, Dim> coords;

    public:
        // Constructor
        explicit Entity(const VecArrayR<coord_type, Dim> &coordinates, const EntityType &tile_entity) : coords(coordinates), entity(tile_entity) {}

        // Getter - returns const reference to avoid copying
        const VecArrayR<coord_type, Dim> &getCoords() const { return coords; }
        const EntityType &getEntity() const { return entity; }

    private:
        friend std::ostream& operator<<(std::ostream& os, const Entity<EntityType, coord_type, Dim>& entity) {
            VecArrayR<coord_type, Dim> coords = entity.getCoords();
            os << "Entity: " << entity.getEntity() << " at " << VecArrayR<coord_type, Dim>::toString(coords);
            return os;  
        }
    };

    // template <typename EntityType, typename coord_type, unsigned int Dim>
    // std::ostream &operator<<(std::ostream &os, const Entity<EntityType, coord_type, Dim> &tile)
    // {
    //     os << tile.getEntity() << ": " << tile.getCoords() << std::endl;
    //     return os;
    // }



    
template <typename BaseEntity, unsigned int Dim, typename Index>
class GridWorld
{
private:
    NVector<std::vector<BaseEntity>, Dim, Index> world;
    std::vector<VecArrayR<Index, Dim>> positions;

public:
    void spawn(BaseEntity);
    void despawn(BaseEntity);
};

template <typename BaseEntity, unsigned int Dim, typename Index>
void GridWorld<BaseEntity, Dim, Index>::spawn(BaseEntity entity)
{
    VecArrayR<Index, Dim> coords = entity.getCoords();
    positions.push_back(coords);
    std::vector<BaseEntity> at_pos = world.getElement(VecArrayR<Index, Dim>::toArray(coords));
}

// template <typename BaseEntity, typename coord_type, unsigned int Dim, typename Index>
// class GridWorld {
// private:
//     NVector<std::shared_ptr<BaseEntity>, Dim, Index> world;
//     std::vector<std::shared_ptr<BaseEntity>> entities;
//     mutable std::mutex mutex; // For thread safety

// public:
//     GridWorld() = default;
    
//     ~GridWorld() {
//         std::lock_guard<std::mutex> lock(mutex);
//         // Clear entities first to ensure no dangling references
//         entities.clear();
//         // Null out world elements
//         for (const auto& entity : entities) {
//             if (entity) {
//                 try {
//                     auto coords = entity->getCoords();
//                     auto coord_arr = VecArrayR<coord_type, Dim>::toArray(coords);
//                     world.putElement(coord_arr, nullptr);
//                 } catch (...) {
//                     // Ignore errors during cleanup
//                 }
//             }
//         }
//     }

//     void spawn(BaseEntity entity) {
//         std::lock_guard<std::mutex> lock(mutex);
//         try {
//             VecArrayR<coord_type, Dim> coords = entity.getCoords();
//             auto p_entity = std::make_shared<BaseEntity>(std::move(entity));
//             if (!p_entity) return;
            
//             auto coord_arr = VecArrayR<coord_type, Dim>::toArray(coords);
//             world.putElement(coord_arr, p_entity);
//             entities.push_back(p_entity);
//         } catch (...) {
//             // Handle allocation failures
//         }
//     }

//     void despawn(const BaseEntity& entity) {
//         std::lock_guard<std::mutex> lock(mutex);
//         try {
//             VecArrayR<coord_type, Dim> coords = entity.getCoords();
//             auto coord_arr = VecArrayR<coord_type, Dim>::toArray(coords);
            
//             auto element = world.getElement(coord_arr);
//             if (element) {
//                 // Store iterator before modification
//                 auto it = std::remove_if(entities.begin(), entities.end(),
//                     [&element](const std::shared_ptr<BaseEntity>& e) {
//                         return e && element && e == element;
//                     });
                
//                 // First null out the world element
//                 world.putElement(coord_arr, nullptr);
                
//                 // Then safely erase from entities
//                 if (it != entities.end()) {
//                     entities.erase(it, entities.end());
//                 }
//             }
//         } catch (...) {
//             std::cout << "r";
//             // Handle errors gracefully
//         }
//     }

//     void clearAll() {
//         std::lock_guard<std::mutex> lock(mutex);
//         try {
//             // Clear entities first
//             std::vector<std::shared_ptr<BaseEntity>> temp_entities;
//             entities.swap(temp_entities);
            
//             // Then null out world elements
//             for (const auto& entity : temp_entities) {
//                 if (entity) {
//                     auto coords = entity->getCoords();
//                     auto coord_arr = VecArrayR<coord_type, Dim>::toArray(coords);
//                     world.putElement(coord_arr, nullptr);
//                 }
//             }
//         } catch (...) {
//             std::cout << "l";
//             // Handle cleanup errors
//         }
//     }
// };

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