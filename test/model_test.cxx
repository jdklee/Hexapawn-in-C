#include "Model.hxx"
#include <catch.h>

TEST_CASE("Example test")
{
    CHECK(true);
}

TEST_CASE("A small game")
{
    Model m(3,3);
    CHECK(m.get_matrix().size() == 3);
    CHECK(m.get_matrix()[0].size() == 3);
    CHECK(m.get_moves(Model::Player::A).size() == 3);
    CHECK(m.get_moves(Model::Player::B).size() == 3);
    CHECK(m.whose_turn() == Model::Player::A);
    m.play_move(Model::Move{0,0,1,0});

    CHECK(m.whose_turn() == Model::Player::B);
    m.play_move(Model::Move{2,1,1,1});

    CHECK(m.whose_turn() == Model::Player::A);
    m.play_move(Model::Move{1,0,1,1});

    CHECK(m.whose_turn() == Model::Player::B);
    m.play_move(Model::Move{2,2,2,1});

    CHECK(m.whose_turn() == Model::Player::A);
    CHECK(m.get_moves(Model::Player::A).size() == 2);
    m.play_move(Model::Move{1,1,2,0});

    CHECK(m.is_winner() == Model::Player::A);
}

TEST_CASE("Test1"){
    Model model(5,5);
    CHECK(model.get_matrix().size()==5);
    CHECK(model.get_matrix()[1].size()==5);
    CHECK (model.get_moves(Model::Player::A).size()==model.get_moves(Model::Player::B).size());
    CHECK(model.get_moves(Model::Player::A).size()==5);
    CHECK(model.is_winner() == Model::Player::O);
}

TEST_CASE("Test2"){
    Model model(10,5);
    CHECK(model.get_matrix().size()==5);
    CHECK(model.get_matrix()[0].size()==10);
    CHECK(model.get_moves(Model::Player::A).size() == 10);
    CHECK(model.get_moves(Model::Player::B).size() == 10);
    CHECK(model.whose_turn() == Model::Player::A);
    model.play_move(Model::Move{0,0,1,0});
    model.play_move(Model::Move{1,0,2,0});
    model.play_move(Model::Move{2,0,3,0});
    model.play_move(Model::Move{3,0,4,1});

    CHECK(model.get_matrix()[4][1]==Model::Player::A);
    CHECK(model.is_winner() == Model::Player::A);
}