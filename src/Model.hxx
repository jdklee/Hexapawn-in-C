#pragma once

#pragma once

#include <initializer_list>
#include <stdexcept>
#include <vector>

// The model of the Hexapawn game.
class Model
{
public:

    //hexapawn players
    enum class Player { A, B, O };

    struct Loc {
        unsigned int x, y;
    };
    struct Move
    {
        Loc src;
        Loc dest;
    };

    std::vector<std::vector<Player>>const& get_matrix() const;

    // constructs a model of size (column,row) where `A` is the player
    // PRE: 3 <= column <= 8
    // PRE: 3 <= row    <= 8
    Model(int column, int row);

    // Returns the winner
    Model::Player is_winner() const ;

    // returns all of the possible moves of `p1`
    std::vector<Move> get_moves(Player p1) const;

    // Returns whose turn it is.
    Player whose_turn() const;

    // Plays a move.
    void play_move(Move mv);

private:
    std::vector<std::vector<Player>> matrix_;
    Player turn_;
};

bool operator==(Model::Move const& m1, Model::Move const& m2);

// Returns the other player.
Model::Player other_player(Model::Player);

