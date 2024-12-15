#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "../headers/utils.h"
// #include "narray.cpp"

// Assumes that entities (and entity types) are sparse
// compared to the overall grid of spaces 

// coming from narray.cpp
template <typename EntityType, unsigned int Dim, typename Index>
struct Entity;

template <typename EntityType, unsigned int Dim, typename Index = unsigned long>
struct HashEntity
{
    Index id;
    Entity<EntityType, Dim, Index> _entity;

    HashEntity(Index _id, Entity<EntityType, Dim, Index> __entity) : id(_id), _entity(__entity) {}
};

template <typename E, unsigned int Dim, typename Index = unsigned long>
class CellGrid {
    using DiscreteEntity = HashEntity<E, Dim, Index>;
    using WeakEntityPtr = std::weak_ptr<DiscreteEntity>;
    using Coords = Array<Index, Dim>;
    using Cell = std::unordered_map<Index, WeakEntityPtr>;

private:
    NArray<Cell, Dim, Index> world; 

public:
    CellGrid() : world() {}
    CellGrid(Coords widths) : world(widths) {}

    void spawn(const WeakEntityPtr& weak_e_ptr);
    void despawn(const WeakEntityPtr& to_despawn);
    Cell getCell(Coords coords);

    bool isInBounds(Coords coords) { return world.isInBounds(coords); }
};

template <typename E, unsigned int Dim, typename Index>
void CellGrid<E, Dim, Index>::spawn(const WeakEntityPtr& weak_e_ptr) 
{
    if (std::shared_ptr<DiscreteEntity> e_ptr = weak_e_ptr.lock()) 
    {
        world.getElement(e_ptr->_entity.coords)[e_ptr->id] = weak_e_ptr;
    }
}

template <typename E, unsigned int Dim, typename Index>
void CellGrid<E, Dim, Index>::despawn(const WeakEntityPtr& to_despawn)
{
    if (std::shared_ptr<DiscreteEntity> e_ptr = to_despawn.lock()) 
    {
        world.getElement(e_ptr->_entity.coords).erase(e_ptr->id);
    }
}

template <typename E, unsigned int Dim, typename Index>
std::unordered_map<Index, std::weak_ptr<HashEntity<E, Dim, Index>>> CellGrid<E, Dim, Index>::getCell(Coords coords) {
    return world.getElement(coords);
}

///
///
///

template <typename E, unsigned int Dim, typename Index = unsigned long>
class DiscreteUnorderedEngine
{
    using DiscreteEntity = Entity<E, Dim, Index>;
    using HashedEntity = HashEntity<E, Dim, Index>;
    using EntityPtr = std::shared_ptr<HashedEntity>;
    using WeakEntityPtr = std::weak_ptr<HashedEntity>;
    using Coords = Array<Index, Dim>;
    using World = CellGrid<E, Dim, Index>;
    using Cell = std::unordered_map<Index, EntityPtr>;
    using WeakCell = std::unordered_map<Index, WeakEntityPtr>;

private:
    World world;
    Index max_id;
    std::unordered_map<Index, EntityPtr> entities;
    std::unordered_map<E, std::unordered_map<Index, WeakEntityPtr>> entities_by_type;

public: 
    DiscreteUnorderedEngine() : world(), max_id(), entities(), entities_by_type() {}
    DiscreteUnorderedEngine(World _world) : world(_world), max_id(), entities(), entities_by_type() {}
    DiscreteUnorderedEngine(Coords widths) : world(widths), max_id(), entities(), entities_by_type() {}

    Index spawn(const DiscreteEntity& entity);
    void despawn(const HashedEntity& entity);
    void despawn(const Index& id);
    
    void moveEntityBy(const Index id, Coords displacement);
    void moveEntityTo(const Index id, Coords new_coords);

    // for testing
    std::unordered_map<Index, EntityPtr> getEntities() { return entities; }

    WeakEntityPtr getEntity(const Index id);
    WeakCell getEntitiesAt(Coords coords) { return world.getCell(coords); }
    WeakCell getEntitiesOf(const E& entity_type);
};

template <typename E, unsigned int Dim, typename Index>
Index DiscreteUnorderedEngine<E, Dim, Index>::spawn(const DiscreteEntity& entity) {
    HashedEntity hashed = HashedEntity(max_id, entity);
    max_id++;
    EntityPtr e_ptr = std::make_shared<HashedEntity>(hashed);
    entities[hashed.id] = e_ptr;
    WeakEntityPtr weak_e_ptr = WeakEntityPtr(e_ptr);
    entities_by_type[hashed._entity.entity][hashed.id] = weak_e_ptr;
    world.spawn(weak_e_ptr);
    return hashed.id;
}

template <typename E, unsigned int Dim, typename Index>
std::weak_ptr<HashEntity<E, Dim, Index>> DiscreteUnorderedEngine<E, Dim, Index>::getEntity(const Index id) {
    return WeakEntityPtr(entities[id]);
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine<E, Dim, Index>::despawn(const HashedEntity& to_despawn) 
{
    world.despawn(entities[to_despawn.id]);
    entities.erase(to_despawn.id);
    entities_by_type[to_despawn._entity.entity].erase(to_despawn.id);
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine<E, Dim, Index>::despawn(const Index& id) 
{
    EntityPtr to_despawn = entities[id];
    despawn(*to_despawn);
}

template <typename E, unsigned int Dim, typename Index>
std::unordered_map<Index, std::weak_ptr<HashEntity<E, Dim, Index>>> DiscreteUnorderedEngine<E, Dim, Index>::getEntitiesOf(const E& entity_type) {
    return entities_by_type[entity_type];
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine<E, Dim, Index>::moveEntityBy(const Index id, Coords displacement) 
{
    displacement.add(entities[id]->_entity.coords);
    moveEntityTo(id, displacement);
}

template <typename E, unsigned int Dim, typename Index>
void DiscreteUnorderedEngine<E, Dim, Index>::moveEntityTo(const Index id, Coords new_coords) 
{
    if (!world.isInBounds(new_coords))
    {
        throw std::invalid_argument("Coordinates out of bounds");
    }
    EntityPtr to_move = entities[id];
    world.despawn(to_move);
    to_move->_entity.coords = new_coords;
    world.spawn(to_move);
}