#include <algorithm>
#include "../headers/utils.h"

// Assumes that entities (and entity types) are sparse
// compared to the overall grid of spaces 

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
    for (WeakEntityPtr& weak_e_ptr : getEntitiesAt(coords)) 
    {
        std::shared_ptr<DiscreteEntity> e_ptr = weak_e_ptr.lock();
        if (!e_ptr)
        {
            return;
        }
    }
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
    void maybeCleanupAt(Coords coords, unsigned int dead_count, unsigned int live_count);

public: 
    DiscreteEngine() : world() {}
    DiscreteEngine(World _world) : world(_world) {}
    DiscreteEngine(Coords widths) : world(widths) {}


    void spawn(const DiscreteEntity entity);
    void despawn(const DiscreteEntity entity);

    std::vector<EntityPtr> getEntitiesAt(Coords coords);
    std::vector<WeakEntityPtr> getWeakEntitiesAt(Coords coords) { return world.getEntitiesAt(coords); }
};

template <typename E, unsigned int Dim, typename Index>
void DiscreteEngine<E, Dim, Index>::maybeCleanupAt(Coords coords, unsigned int dead_count, unsigned int live_count) {
    if (dead_count > live_count * 2)
    {
        world.cleanUpAt(coords);
    }
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteEngine<E, Dim, Index>::spawn(const DiscreteEntity entity) {
    EntityPtr e_ptr = std::make_shared<DiscreteEntity>(entity);
    entities.push_back(e_ptr);
    world.spawn(WeakEntityPtr(e_ptr));
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteEngine<E, Dim, Index>::despawn(const DiscreteEntity entity) 
{
    std::vector<WeakEntityPtr> entities_at_same_coords = world.getEntitiesAt(entity.coords);

    for (WeakEntityPtr& weak_ptr : entities_at_same_coords) 
    {
        if (EntityPtr e_ptr = weak_ptr.lock()) {
            if (e_ptr->coords == entity.coords)
            {
                entities.erase(std::remove(entities.begin(), entities.end(), e_ptr), entities.end());
                e_ptr.reset();
            }
        }
    }
}

template <typename E, unsigned int Dim, typename Index>
std::vector<std::shared_ptr<Entity<E, Dim, Index>>> DiscreteEngine<E, Dim, Index>::getEntitiesAt(Coords coords) 
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