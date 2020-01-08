#include "Model.hxx"

Model::Model(int column, int row)
        : turn_{Player::A}
{
    //initialize board
    matrix_.emplace_back(column, Player::A);
    for(int x=1; x<row-1; x++){
        matrix_.emplace_back(column, Player::O);
    }
    matrix_.emplace_back(column, Player::B);
}

bool operator==(Model::Move const& m1, Model::Move const& m2) {
    return m1.dest.y == m2.dest.y && m1.dest.x == m2.dest.x && m1.src.y == m2.src.y && m1.src.x == m2.src.x;
}

std::vector<std::vector<Model::Player>>const& Model::get_matrix() const {
    return matrix_;
}

Model::Player Model::is_winner() const {
    int column = matrix_[0].size();
    int row = matrix_.size();
    // A player wins if:
    // 1: if his/her pawn reaches other end
    // 2: if all opponent pawns died
    // 3: if only 1 opponent pawn is left for which there are no possible moves
    for (int x = 0; x < column; x++)
    {
        if (matrix_[row - 1][x] == Player::A)
        {
            return Player::A;
        }
        if (matrix_[0][x] == Player::B)
        {
            return Player::B;
        }
    }
    if (get_moves(Player::A).empty())
    {
        return Player::B;
    }
    if (get_moves(Player::B).empty())
    {
        return Player::A;
    }
    else
        return Player::O;
}

Model::Player Model::whose_turn() const
{
    return turn_;
}

std::vector<Model::Move> Model::get_moves(Player p1) const
{
    int column = matrix_[0].size();
    int row = matrix_.size();
    std::vector<Model::Move> moves;
    if (p1==Player::A) {
        for (unsigned int i = 0; i < row - 1; i++){
            for (unsigned int j = 0; j < column; j++){
                if (matrix_[i][j] == p1){
                    if (matrix_[i + 1][j] == Player::O){
                        moves.push_back(Move{i, j, i + 1, j});
                    }
                    if (j != 0 && j != column - 1) {
                        if (matrix_[i + 1][j - 1] == other_player(p1)){
                            moves.push_back(Move{i, j, i + 1, j - 1});
                        }
                        if (matrix_[i + 1][j + 1] == other_player(p1)){
                            moves.push_back(Move{i, j, i + 1, j + 1});
                        }
                    }
                    if ((j == 0) && (matrix_[i + 1][j + 1] == other_player(p1))){
                            moves.push_back(Move{i, j, i + 1, j + 1});
                    }

                    if (j == column - 1 && matrix_[i + 1][j - 1] == other_player(p1)){
                            moves.push_back(Move{i, j, i + 1, j - 1});
                    }
                }
            }
        }
    }
    if (p1==Player::B){
        for (unsigned int i = 1; i < row; i++){
            for (unsigned int j = 0; j < column; j++){
                if (matrix_[i][j] == p1){
                    if (matrix_[i - 1][j] == Player::O){
                        moves.push_back(Move{i, j, i - 1, j});
                    }
                    if (j != 0 && j != column - 1)
                    {
                        if (matrix_[i - 1][j - 1] == other_player(p1)){
                            moves.push_back(Move{i, j, i - 1, j - 1});
                        }
                        if (matrix_[i - 1][j + 1] == other_player(p1)){
                            moves.push_back(Move{i, j, i - 1, j + 1});
                        }
                    }
                    if ((j == 0) && (matrix_[i - 1][j + 1] == other_player(p1))){
                        moves.push_back(Move{i, j, i - 1, j + 1});
                    }

                    if (j == column - 1 && matrix_[i - 1][j - 1] == other_player(p1)){
                        moves.push_back(Move{i, j, i - 1, j - 1});
                    }
                }
            }
        }
    }
    return moves;
}

void Model::play_move(Move mv)
{
    auto src_i = mv.src.x;
    auto src_j = mv.src.y;
    auto dst_i = mv.dest.x;
    auto dst_j = mv.dest.y;

    if(matrix_[src_i][src_j]==Player::A){
        matrix_[dst_i][dst_j]=Player::A;
        matrix_[src_i][src_j]=Player::O;
    }

    if(matrix_[src_i][src_j]==Player::B){
        matrix_[dst_i][dst_j]=Player::B;
        matrix_[src_i][src_j]=Player::O;
    }

    turn_ = other_player(turn_);
}

Model::Player other_player(Model::Player p){
    if (p == Model::Player::A) {
        return Model::Player::B;
    }
    else if (p == Model::Player::B) {
        return Model::Player::A;
    }
    return Model::Player::O;
}
