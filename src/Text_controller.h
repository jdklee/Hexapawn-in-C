
#ifndef HEXAPAWN_TEXT_CONTROLLER_H
#define HEXAPAWN_TEXT_CONTROLLER_H


#pragma once

#include "Model.hxx"
#include "Text_view.h"

#include <iostream>

class Text_controller
{
public:
    // Constructs a controller with input from cin and output to cout.
    Text_controller();

    // Constructs a controller with I/O from/to the given streams.
    Text_controller(std::istream &in, std::ostream &out, Model model, int column, int row);

    // Sets the names of both players.
    void set_player_names(std::string const& name1,
                          std::string const& name2);

    // Runs the game.
    void play_game(int column, int row);

private:
    Model model_;
    Text_view view_;
};

#endif //HEXAPAWN_TEXT_CONTROLLER_H
