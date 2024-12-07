#include <exception>
#include <stdexcept>
#include <iostream>

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

struct Tile
{
    TileType type;
    Direction last_visited; // Use a pointer for optional direction

    // Constructor for convenience
    Tile(TileType t = TileType::Unexplored, Direction d = Direction::Undef)
        : type(t), last_visited(d) {}
};

struct Turtle
{
    std::vector<std::vector<Tile>> map;
    int x;
    int y;
    Direction facing;
    int visited = 0;
    int loopers = 0;

    bool hasBeenHere(Tile *ahead)
    {
        if (ahead->last_visited == facing)
        {
            return true;
        }
        return false;
    }

    Tile *checkAhead()
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
        switch (facing)
        {
        case North:
            facing = East;
            return;
        case East:
            facing = South;
            return;
        case South:
            facing = West;
            return;
        case West:
            facing = North;
            return;
        default:
            std::throw_with_nested(std::runtime_error("Turtle needs a direction to rotate"));
            break;
        }
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
        Tile *ahead = checkAhead();
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
            //ahead->last_visited = facing;
            advance();
            break;
        case TileType::Obstacle:
            rotate();
            break;
        case TileType::Unexplored:
            visited++;
            ahead->type = TileType::Explored;
            ahead->last_visited = facing;
            advance();
            break;
        }
        return true;
    }

    Tile placeObstruction()
    {
        Tile saved = *checkAhead();
        Tile *to_change = checkAhead();
        *to_change = Tile(TileType::Obstacle, Direction::Undef);
        return saved;
    }
    void removeObstruction(Tile to_replace)
    {
        Tile *to_change = checkAhead();
        *to_change = to_replace;
    }

    int testObstruction()
    {
        int save_x = x;
        int save_y = y;
        int save_visited = visited;
        Direction save_direction = facing;

        Tile saved = placeObstruction();
        while (move())
        {
            ;
        }
        removeObstruction(saved);

        x = save_x;
        y = save_y;
        visited = save_visited;
        facing = save_direction;

        return 0;
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
                    switch (turtle.map[y][x].type)
                    {
                    case TileType::Unexplored:
                        os << '.';
                        break;
                    case TileType::Explored:
                        os << 'X';
                        break;
                    case TileType::Obstacle:
                        os << '#';
                        break;
                    case TileType::Offsite:
                        os << ' ';
                        break;
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
            turtle.map.push_back(std::vector<Tile>());
            int input_x = 1;
            int input_y = 1;

            std::ifstream file(file_name);
            std::string line;

            while (std::getline(file, line))
            {
                input_y++;
                input_x = 0;
                std::vector<Tile> row = {Tile(TileType::Offsite)};
                for (char c : line)
                {
                    input_x++;
                    switch (c)
                    {
                    case '#':
                        row.push_back(Tile(TileType::Obstacle));
                        break;
                    case '.':
                        row.push_back(Tile(TileType::Unexplored));
                        break;
                    case '^':
                        turtle.x = input_x;
                        turtle.y = input_y - 1;
                        row.push_back(Tile(TileType::Explored, Direction::North));
                        turtle.visited++;
                        break;
                    default:
                        std::throw_with_nested(std::runtime_error("Invalid char: " + std::to_string(c)));
                        break;
                    }
                }
                row.push_back(Tile(TileType::Offsite));
                turtle.map.push_back(row);
            }
            turtle.map.push_back(std::vector<Tile>(turtle.map[1].size(), Tile(TileType::Offsite)));
            // Padding the first line now that we know how long a row should be
            turtle.map[0] = std::vector<Tile>(turtle.map[1].size(), Tile(TileType::Offsite));

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
            std::vector<std::vector<Tile>> saved_map = turtle.map;
            int possible_obstructions = turtle.testObstruction();
            turtle.map = saved_map;
            while (turtle.move())
            {
                std::vector<std::vector<Tile>> saved_map = turtle.map;
                possible_obstructions += turtle.testObstruction();
                turtle.map = saved_map;
            }
            return turtle.loopers;
        }
    };
}