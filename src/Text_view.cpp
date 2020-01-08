#include "Text_view.h"
#include "Model.hxx"

Text_view::Text_view(Model const& model, std::istream& in, std::ostream& out)
        : model_{model}
        , in_{in}
        , out_{out}
        , player1_{"A"}
        , player2_{"B"}
{ }

Model::Move Text_view::get_move() const
{
    out_ << "Player " << player_name_(model_.whose_turn());
    out_ << ", how would you like to move?\n";

    for (;;) {
        out_ << "> ";
        out_.flush();

        auto mv = read_raw_move_();

        if (in_) {
            auto moves = model_.get_moves(model_.whose_turn());
            if(std::find(moves[0], moves[-1], mv) != moves.end()) {
                if(model_.move_comparison(std::find(moves[0], moves[1], mv), moves.end()))
                return mv;
            } else {
                //mv is not a valid move;
                out_ << "!\nPlease enter a valid move.\n";
            }
        }
        else if (in_.eof()) {
            throw Quit{};
        } else {
            // Read bad input, so clear it out and try again:
            in_.clear();
            std::string dummy;
            std::getline(in_, dummy);
            out_ << "Please enter numbers.\n";
        }
    }
}

void Text_view::display_welcome() const
{
    out_ << "Welcome to IPD HexaPawn\n\n";
}

void Text_view::display_move() const{
    auto moves = model_.get_moves(model_.whose_turn());
    int i = 0;
    for(auto x:moves) {
        out_ <<"move "<<i << "source:" <<x.source_i<<x.source_j << "  destination:" << x.dest_i<<x.dest_j;
        out_<<" \n";
    }
}

void Text_view::display_board() const {
    auto const &board = model_.get_matrix();
    out_ << "   |";

    for (size_t j = 0; j < board[0].size(); ++j) {
        out_ << " " << static_cast<char>(97 + j) << " |";
    }

    out_ << " \n";

    for (size_t j = 0; j < board[0].size() - 1; ++j) {
        out_ << "---+";
    }
    out_ << "---";
    out_ << " \n";
    for (size_t i = 0; i < board.size(); i++) {
        out_ << " " << i << " |";
        for (size_t j = 0; j < board[0].size(); j++) {
            if (board[i][j] == Model::Player::A) { //pawn a
                out_ << " " << "A" << " |";
            }
            if (board[i][j] == Model::Player::B) { //pawn b there
                out_ << " " << "B" << " |";
            } else { //empty
                out_ << " " << " " << " |";
            }
            out_ << " \n";
        }
    }
}

void Text_view::display_winner()
{
    out_ << "Player " << player_name_(model_.is_winner()) << " wins!\n";
}

Model::Move Text_view::read_raw_move_() const
{
    int which_move;


    in_ >> which_move;

    return {which_move};
}

std::string const& Text_view::player_name_(Model::Player p) const
{
    if (p == Model::Player::A) {
        return player1_;
    } else {
        return player2_;
    }
}
