#include "Model.hxx"
#include <cstdlib>
#include <iostream>

void display_move(const Model& model_){
    auto moves = model_.get_moves(model_.whose_turn());
    int i = 0;
    for(auto x:moves) {
        std::cout <<"move "<<i+1 << ":\tsource:" <<x.src.x+1 <<x.src.y+1 << "  destination:" << x.dest.x+1<<x.dest.y+1;
        std::cout<<" \n";
        i++;
    }
}
std::string player_name_(Model::Player p)
{
    if (p == Model::Player::A) {
        return "A";
    } else {
        return "B";
    }
}

Model::Move get_move(const Model& model_) {
    int index;
    std::cout << "How would you like to move, Player " << player_name_(model_.whose_turn()) << "?\n";
    std::cin >> index;
    auto moves = model_.get_moves(model_.whose_turn());
    while(index-1 >= moves.size()){
        std::cout << "Dont make me ask again. Need a valid move. How would you like to move?\n "; //<< player_name_(model_.whose_turn());
        std::cin >> index;
    }
    return moves[index-1];
}

void display_board(const Model& model_) {
    auto const &board = model_.get_matrix();
    std::cout << "   |";

    for (size_t j = 1; j <= board[0].size(); ++j) {
        std::cout << " " << j<< " |";
    }

    std::cout << " \n";

    for (size_t j = 0; j <= board[0].size(); ++j) {
        std::cout << "---+";
    }
    std::cout << "---";
    std::cout << " \n";
    size_t i = 1;
    for (size_t k = 0; k < board.size(); k++) {
        std::cout << " " << i << " |";
        for (size_t j = 0; j < board[0].size(); j++) {
            if (board[k][j] == Model::Player::A) { //pawn a
                std::cout << " " << "A" << " |";
            } else if (board[k][j] == Model::Player::B) { //pawn b there
                std::cout << " " << "B" << " |";
            } else { //empty
                std::cout << " " << " " << " |";
            }
            if (j == board[0].size() - 1) {
                std::cout << " " << i;
                std::cout << " \n";
                for (size_t p = 0; p <= board[0].size(); ++p) {
                    std::cout << "---+";
                }
                std::cout << "---";
                std::cout << " \n";
            }
        }
        if (i != board.size())
            i++;
    }
    std::cout << "   |";

    for (size_t j = 1; j <= board[0].size(); ++j) {
        std::cout << " " << j << " |";
    }
    std::cout << " \n";
}

int main(int argc, char* argv[])
{
    //Text_controller hexapawn;
    int column, row;
    std::cout << "Please choose number between 3 and 8 for column: \n";
    std::cin >> column;
    std::cout << "Please choose number between 3 and 8 for row: \n";
    std::cin >> row;
    for(;;){
        if (column<3 || column>8){
            std::cout << "Please choose number between 3 and 8 for column: ";
            std::cin >> column;
        }
        if (row<3 || row>8){
            std::cout << "Please choose number between 3 and 8 for row: ";
            std::cin >> row;
        }
        if (row>=3 && row<=8 && column>=3 && column <=8)
            break;
    }
    auto m = Model(column, row);
    while(m.is_winner()==Model::Player::O){
        display_board(m);
        display_move(m);
        auto mv = get_move(m);
        m.play_move(mv);
    }
    display_board(m);
    if (m.is_winner()==Model::Player::A){
        std::cout << "Player A is the winner!!";
    }

    if (m.is_winner()==Model::Player::B){
        std::cout<< "Player B is the winner!!";
    }
    return 0;
}
