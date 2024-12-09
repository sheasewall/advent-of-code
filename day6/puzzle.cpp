#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>

#include "../headers/solver.h"
#include "../headers/utils.h"

enum TileType
{
    Unexplored,
    Explored,
    Obstacle,
    Offsite
};

enum Direction
{
    North,
    East,
    South,
    West,
    Undef
};

struct TileEntity
{
    TileType type;
    bool has_visited[4]; // Array to track visits from each direction

    // Constructor for convenience
    TileEntity(TileType t = TileType::Unexplored)
        : type(t)
    {
        for (int i = 0; i < 4; ++i)
        {
            has_visited[i] = false;
        }
    }
};

struct Turtle
{
    std::vector<std::vector<TileEntity>> map;
    int x;
    int y;
    Direction facing;
    int visited = 0;
    int loopers = 0;
    int initial_x;
    int initial_y;
    std::vector<std::vector<TileEntity>> initial_map;

    bool hasBeenHere(TileEntity *ahead)
    {
        return ahead->has_visited[facing];
    }

    TileEntity *checkAhead()
    {
        switch (facing)
        {
        case North:
            return &map[y - 1][x];
        case East:
            return &map[y][x + 1];
        case South:
            return &map[y + 1][x];
        case West:
            return &map[y][x - 1];
        default:
            std::throw_with_nested(std::runtime_error("Turtle needs a direction to check ahead"));
            break;
        }
    }

    void rotate()
    {
        facing = static_cast<Direction>((facing + 1) % 4);
    }

    void advance()
    {
        switch (facing)
        {
        case North:
            y--;
            break;
        case East:
            x++;
            break;
        case South:
            y++;
            break;
        case West:
            x--;
            break;
        default:
            std::throw_with_nested(std::runtime_error("Turtle needs a direction to advance"));
            break;
        }
    }

    bool move()
    {
        TileEntity *ahead = checkAhead();
        switch (ahead->type)
        {
        case TileType::Offsite:
            return false;
        case TileType::Explored:
            if (hasBeenHere(ahead))
            {
                loopers++;
                return false;
            }
            advance();
            break;
        case TileType::Obstacle:
            rotate();
            break;
        case TileType::Unexplored:
            visited++;
            ahead->type = TileType::Explored;
            advance();
            break;
        }
        ahead->has_visited[facing] = true;
        return true;
    }

    // TileEntity placeObstruction()
    // {
    //     TileEntity saved = *checkAhead();
    //     TileEntity *to_change = checkAhead();
    //     *to_change = TileEntity(TileType::Obstacle);
    //     return saved;
    // }

    // void removeObstruction(TileEntity to_replace)
    // {
    //     TileEntity *to_change = checkAhead();
    //     *to_change = to_replace;
    // }

    void testObstruction()
    {
        TileEntity *ahead = checkAhead();
        if (ahead->type == TileType::Explored)
        {
            return;
        }

        int save_x = x;
        int save_y = y;
        int save_visited = visited;
        std::vector<std::vector<TileEntity>> save_map = map;
        Direction save_direction = facing;

        x = initial_x;
        y = initial_y;
        // This operation is probably expensive
        map = initial_map;
        ahead->type = TileType::Obstacle;
        facing = Direction::North;
        while (move())
        {
            ;
        }

        x = save_x;
        y = save_y;
        visited = save_visited;
        map = save_map;
        facing = save_direction;
    }

    friend std::ostream &operator<<(std::ostream &os, const Turtle &turtle)
    {
        for (size_t y = 0; y < turtle.map.size(); y++)
        {
            for (size_t x = 0; x < turtle.map[y].size(); x++)
            {
                if (x == turtle.x && y == turtle.y)
                {
                    // Show turtle with its facing direction
                    switch (turtle.facing)
                    {
                    case North:
                        os << '^';
                        break;
                    case East:
                        os << '>';
                        break;
                    case South:
                        os << 'v';
                        break;
                    case West:
                        os << '<';
                        break;
                    default:
                        os << '?';
                        break;
                    }
                }
                else
                {
                    // Show map tiles
                    const TileEntity &tile = turtle.map[y][x];
                    if (tile.type == TileType::Unexplored)
                    {
                        os << '.';
                    }
                    else if (tile.type == TileType::Explored)
                    {
                        if (tile.has_visited[North] && tile.has_visited[East] && tile.has_visited[South] && tile.has_visited[West])
                        {
                            os << "╬"; // All directions
                        }
                        else if (tile.has_visited[North] && tile.has_visited[South] && tile.has_visited[East])
                        {
                            os << "╠"; // North, South, East
                        }
                        else if (tile.has_visited[North] && tile.has_visited[South] && tile.has_visited[West])
                        {
                            os << "╣"; // North, South, West
                        }
                        else if (tile.has_visited[East] && tile.has_visited[South] && tile.has_visited[West])
                        {
                            os << "╦"; // East, South, West
                        }
                        else if (tile.has_visited[North] && tile.has_visited[East] && tile.has_visited[West])
                        {
                            os << "╩"; // North, East, West
                        }
                        else if (tile.has_visited[North] && tile.has_visited[South])
                        {
                            os << "║"; // North, South
                        }
                        else if (tile.has_visited[East] && tile.has_visited[West])
                        {
                            os << "═"; // East, West
                        }
                        else if (tile.has_visited[North] && tile.has_visited[East])
                        {
                            os << "╚"; // North, East
                        }
                        else if (tile.has_visited[North] && tile.has_visited[West])
                        {
                            os << "╝"; // North, West
                        }
                        else if (tile.has_visited[South] && tile.has_visited[East])
                        {
                            os << "╔"; // South, East
                        }
                        else if (tile.has_visited[South] && tile.has_visited[West])
                        {
                            os << "╗"; // South, West
                        }
                        else if (tile.has_visited[North])
                        {
                            os << "↑"; // North
                        }
                        else if (tile.has_visited[East])
                        {
                            os << "→"; // East
                        }
                        else if (tile.has_visited[South])
                        {
                            os << "↓"; // South
                        }
                        else if (tile.has_visited[West])
                        {
                            os << "←"; // West
                        }
                        else
                        {
                            os << "X"; // Default for explored
                        }
                    }
                    else if (tile.type == TileType::Obstacle)
                    {
                        os << '#';
                    }
                    else if (tile.type == TileType::Offsite)
                    {
                        os << ' ';
                    }
                }
            }
            os << '\n';
        }
        return os;
    }
};

namespace day6
{
    class Day6Solver : public solve::Solver<Turtle, int>
    {
    public:
        Day6Solver(std::string name, int puzzle_index) : Solver(name, 6, puzzle_index) {}

        Turtle parseInputFile(std::string file_name) override
        {
            Direction north = Direction::North;

            Turtle turtle = Turtle();
            // To be padded later
            turtle.map.push_back(std::vector<TileEntity>());
            int input_x = 1;
            int input_y = 1;

            std::ifstream file(file_name);
            std::string line;

            while (std::getline(file, line))
            {
                TileEntity starting_explored = TileEntity(TileType::Explored);
                starting_explored.has_visited[Direction::North] = true;
                input_y++;
                input_x = 0;
                std::vector<TileEntity> row = {TileEntity(TileType::Offsite)};
                for (char c : line)
                {
                    input_x++;
                    switch (c)
                    {
                    case '#':
                        row.push_back(TileEntity(TileType::Obstacle));
                        break;
                    case '.':
                        row.push_back(TileEntity(TileType::Unexplored));
                        break;
                    case '^':
                        turtle.x = input_x;
                        turtle.y = input_y - 1;
                        turtle.initial_x = turtle.x;
                        turtle.initial_y = turtle.y;
                        row.push_back(starting_explored);
                        turtle.visited++;
                        break;
                    default:
                        std::throw_with_nested(std::runtime_error("Invalid char: " + std::to_string(c)));
                        break;
                    }
                }
                row.push_back(TileEntity(TileType::Offsite));
                turtle.map.push_back(row);
            }
            turtle.map.push_back(std::vector<TileEntity>(turtle.map[1].size(), TileEntity(TileType::Offsite)));
            // Padding the first line now that we know how long a row should be
            turtle.map[0] = std::vector<TileEntity>(turtle.map[1].size(), TileEntity(TileType::Offsite));
            // This is the most expensive operation for problem 1.
            turtle.initial_map = turtle.map;
            return turtle;
        }
    };

    class Puzzle1Solver : public Day6Solver
    {
    public:
        Puzzle1Solver() : Day6Solver("puzzle 1", 1) {}

        int computeSolution(Turtle turtle) override
        {
            while (turtle.move())
                ;
            return turtle.visited;
        }
    };

    class Puzzle2Solver : public Day6Solver
    {
    public:
        Puzzle2Solver() : Day6Solver("try to trap", 2) {}

        int computeSolution(Turtle turtle) override
        {
            if (turtle.checkAhead()->type != TileType::Obstacle && turtle.checkAhead()->type != TileType::Offsite)
            {
                turtle.testObstruction();
            }
            while (turtle.move())
            {
                if (turtle.checkAhead()->type != TileType::Obstacle && turtle.checkAhead()->type != TileType::Offsite)
                {
                    turtle.testObstruction();
                }
            }
            return turtle.loopers;
        }
    };
}