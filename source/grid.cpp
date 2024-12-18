#include <algorithm>
#include <unordered_set>
#include <iostream>
#include "../headers/utils.h"
// #include "narray.cpp"

// Assumes that entities (and entity types) are sparse
// compared to the overall grid of spaces 

// coming from narray.cpp
template<typename E, unsigned int Dim, typename Index>
class Entity;

template <typename E, unsigned int Dim, typename Index = unsigned long>
class DiscreteGrid {
    using DiscreteEntity = Entity<E, Dim, Index>;
    using WeakEntityPtr = std::weak_ptr<DiscreteEntity>;
    using Coords = Array<Index, Dim>;

private:
    NArray<std::vector<WeakEntityPtr>, Dim, Index> world; 

public:
    DiscreteGrid() : world() {}
    DiscreteGrid(Coords widths) : world(widths) {}

    void spawn(const WeakEntityPtr& entity);

    std::vector<WeakEntityPtr> getEntitiesAt(Coords coords);

    void replaceCell(Coords coords, std::vector<WeakEntityPtr> newCell);
    void cleanUpAt(Coords coords);
};

template <typename E, unsigned int Dim, typename Index>
void DiscreteGrid<E, Dim, Index>::spawn(const WeakEntityPtr& weak_e_ptr) {
    if (auto e_ptr = weak_e_ptr.lock()) {
        world.getElement(e_ptr->coords).push_back(weak_e_ptr);
    }
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::weak_ptr<Entity<E, Dim, Index>>> DiscreteGrid<E, Dim, Index>::getEntitiesAt(Coords coords) {
    return world.getElement(coords);
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteGrid<E, Dim, Index>::cleanUpAt(Coords coords) 
{
    std::vector<WeakEntityPtr> new_cell;
    std::vector<WeakEntityPtr> cell = getEntitiesAt(coords);
    for (WeakEntityPtr& weak_e_ptr : cell) 
    {
        if (auto& e_ptr = weak_e_ptr.lock())
        {
            new_cell.push_back(weak_e_ptr);
        }
    }
    replaceCell(coords, new_cell);
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteGrid<E, Dim, Index>::replaceCell(Coords coords, std::vector<WeakEntityPtr> newCell) 
{
    world.putElement(coords, newCell);
}

///
///
///

template <typename E, unsigned int Dim, typename Index = unsigned long>
class DiscreteEngine
{
    using DiscreteEntity = Entity<E, Dim, Index>;
    using EntityPtr = std::shared_ptr<DiscreteEntity>;
    using WeakEntityPtr = std::weak_ptr<DiscreteEntity>;
    using Coords = Array<Index, Dim>;
    using World = DiscreteGrid<E, Dim, Index>;

private:
    World world;
    std::vector<EntityPtr> entities;

public: 
    DiscreteEngine() : world() {}
    DiscreteEngine(World _world) : world(_world) {}
    DiscreteEngine(Coords widths) : world(widths) {}

    void spawn(const DiscreteEntity entity);
    void despawn(const DiscreteEntity entity);

    // for testing
    std::vector<EntityPtr> getEntities() { return entities; }

    std::vector<WeakEntityPtr> getEntitiesAt(Coords coords) { return world.getEntitiesAt(coords); }
    std::vector<WeakEntityPtr> getEntitiesOf(const E& entity_type);
};

template <typename E, unsigned int Dim, typename Index>
void DiscreteEngine<E, Dim, Index>::spawn(const DiscreteEntity entity) {
    EntityPtr e_ptr = std::make_shared<DiscreteEntity>(entity);
    entities.push_back(e_ptr);
    world.spawn(WeakEntityPtr(e_ptr));
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteEngine<E, Dim, Index>::despawn(const DiscreteEntity to_despawn) 
{
    std::vector<WeakEntityPtr> valid_ptrs;
    std::vector<WeakEntityPtr> entities_at_same_coords = world.getEntitiesAt(to_despawn.coords);
    
    // First pass - collect valid pointers and reset invalid ones
    for (WeakEntityPtr& weak_ptr : entities_at_same_coords) 
    {
        if (EntityPtr e_ptr = weak_ptr.lock()) 
        {
            if (e_ptr->entity == to_despawn.entity)
            {
                // Mark for deletion by resetting
                // e_ptr.reset();
            }
            else 
            {
                valid_ptrs.push_back(weak_ptr);
            }
        }
    }

    // Remove expired entities from main entities vector
    auto it = std::remove_if(entities.begin(), entities.end(), 
        [&to_despawn](const EntityPtr e) { 
            return (e->entity == to_despawn.entity) && (e->coords == to_despawn.coords);
        });
    
    entities.erase(it, entities.end());
    
    // Update the world grid with remaining valid entities
    world.replaceCell(to_despawn.coords, valid_ptrs);

    /*
    std::vector<WeakEntityPtr> invalid_ptrs;
    std::vector<WeakEntityPtr> valid_ptrs;
    std::vector<WeakEntityPtr> entities_at_same_coords = world.getEntitiesAt(entity.coords);
    for (WeakEntityPtr& weak_ptr : entities_at_same_coords) 
    {
        if (EntityPtr e_ptr = weak_ptr.lock()) 
        {
            if (e_ptr->entity == entity.entity)
            {
                invalid_ptrs.push_back(e_ptr);
                e_ptr.reset();
            }
            else 
            {
                valid_ptrs.push_back(weak_ptr);
            }
        }
    }

    // Create a set for faster lookups
    std::unordered_set<int> invalid_set(invalid_ptrs.begin(), invalid_ptrs.end());

    // Use remove_if to mark elements for removal
    auto it = std::remove_if(entities.begin(), entities.end(), 
        [&invalid_set](std::shared_ptr<DiscreteEntity> e) { 
            return invalid_set.find(e) != invalid_set.end(); 
        });

    // Actually remove the elements
    entities.erase(it, entities.end());
    world.replaceCell(entity.coords, valid_ptrs);
    */


    // auto it_to_end = entities.end();

    // std::vector<WeakEntityPtr> valid_ptrs;
    // std::vector<WeakEntityPtr> entities_at_same_coords = world.getEntitiesAt(entity.coords);
    // for (WeakEntityPtr& weak_ptr : entities_at_same_coords) 
    // {
    //     if (EntityPtr e_ptr = weak_ptr.lock()) 
    //     {
    //         if (e_ptr->entity == entity.entity)
    //         {
    //             it_to_end = std::remove(entities.begin(), it_to_end, e_ptr);
    //             e_ptr.reset();
    //         }
    //         else 
    //         {
    //             valid_ptrs.push_back(weak_ptr);
    //         }
    //     }
    // }
    // entities.erase(it_to_end);
    // world.replaceCell(entity.coords, valid_ptrs);
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::weak_ptr<Entity<E, Dim, Index>>> DiscreteEngine<E, Dim, Index>::getEntitiesOf(const E& entity_type) {
    std::vector<WeakEntityPtr> entities_of;
    std::copy_if(entities.begin(), entities.end(), std::back_inserter(entities_of), 
                [&entity_type](const WeakEntityPtr& weak_e_ptr) {
                    if (auto e_ptr = weak_e_ptr.lock()) {
                        return e_ptr->entity == entity_type;
                    }
                    return false;
                });
    return entities_of;
    
    // std::vector<WeakEntityPtr> entities_of;
    // for (WeakEntityPtr weak_e_ptr : entities)
    // {
    //     {
    //         if (EntityPtr e_ptr = weak_e_ptr.lock()) 
    //         {
    //             if (e_ptr->entity == entity_type)
    //             {
    //                 entities_of.push_back(weak_e_ptr);
    //             }
    //         }
    //     }
    // }
    // return entities_of;
}

/*
template <typename E, unsigned int Dim, typename Index>
void DiscreteEngine<E, Dim, Index>::maybeCleanupAt(Coords coords, unsigned int dead_count, unsigned int live_count) {
    if (dead_count > live_count * 2)
    {
        world.cleanUpAt(coords);
    }
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::shared_ptr<Entity<E, Dim, Index>>> DiscreteEngine<E, Dim, Index>::getEntityPtrsAt(Coords coords) 
{
    std::vector<EntityPtr> e_ptrs;
    std::vector<WeakEntityPtr> weak_e_ptrs = world.getEntitiesAt(coords);
    int live_count = 0;
    int dead_count = 0;
    for (WeakEntityPtr& weak_e_ptr : weak_e_ptrs) 
    {
        if (EntityPtr e_ptr = weak_e_ptr.lock()) 
        {
            e_ptrs.push_back(e_ptr);
            live_count++;
        }
        else
        {
            dead_count++;
        }
    }
    
    maybeCleanupAt(coords, dead_count, live_count);
    return e_ptrs;
}
*/