
#ifndef HEXAPAWN_TEXT_VIEW_H
#define HEXAPAWN_TEXT_VIEW_H


#pragma once

#include "Model.hxx"

#include <iostream>
#include <exception>

// Thrown by `get_move` to indicate that the user has asked to quit
// the game.
struct Quit : std::exception
{ };

// A text-based view for the Nim game.
class Text_view
{
public:
    // Constructs a view with I/O from/to the given streams.
    Text_view(Model const&, std::istream&, std::ostream&);

    // Sets the names of both players.
    void set_player_names(std::string const& name1,
                          std::string const& name2);

    // Displays a start-up message.
    void display_welcome() const;

    // Displays the state of the Nim heaps.
    void display_board() const;
    void display_move() const;

    // Displays the current winner.
    //
    // PRECONDITION: model_.is_game_over()
    void display_winner();

    // Reads a valid move from the user input and returns it.
    //
    // ERRORS: Throws `Quit` if the user ends the input instead of
    // entering a move.
    Model::Move get_move() const;

private:
    Model const& model_;
    std::string player1_, player2_;
    std::istream& in_;
    std::ostream& out_;

    Model::Move read_raw_move_() const;
    std::string const& player_name_(Model::Player) const;
};


#endif //HEXAPAWN_TEXT_VIEW_H
