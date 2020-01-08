#include "Text_controller.h"
#include "Model.hxx"

Text_controller::Text_controller(std::istream &in, std::ostream &out, Model model,int column, int row)
        : view_{Model{column, row}, in, out} , model_ (model)
        { }

Text_controller::Text_controller()
        : Text_controller{std::cin, std::cout, Model(3,3), 3, 3}
{ }

void Text_controller::play_game(int column, int row) {

        view_.display_welcome();
        Model m = Model(column,row);
        while (m.is_winner() == Model::Player::O) {
            view_.display_board();
            view_.display_move();
            Model::Move mv = view_.get_move();
            m.play_move(mv);
        }
        view_.display_winner();
}