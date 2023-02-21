#include "Game.h"
#include <stdlib.h>     
#include <time.h> 

std::string SquareTypeStringify(SquareType sq){
    switch(sq){
        case SquareType::Wall:
            return "❎";
        case SquareType::Dots:
            return "🟨";
        case SquareType::Pacman:
            return "😁";
        case SquareType::Treasure:
            return "🎁";
        case SquareType::Enemies:
            return "👻";
        case SquareType::Empty:
            return "⬜";
        case SquareType::PowerfulPacman:
            return "😇";
        case SquareType::Trap:
            return "🔥";
        case SquareType::EnemySpecialTreasure:
            return "🍒";
        default:
            return "Invalid";
    }

}

Board::Board(){
    pellets_ = 0;
    int rand_num = 0;
    std::srand(time(nullptr));//random num generator
    for (int i = 0; i < get_rows(); i++) {
        for (int j = 0; j < get_cols(); j++) {
            rand_num = std::rand()%100+1;//to generate numer between 1-100
            if(i == 0 && j == 0){
                arr_[i][j] = SquareType::Pacman;    //square(0,0) is pacman
            }
            else if(rand_num < 60){
                arr_[i][j] = SquareType::Dots;  //60% chance of Dots
                pellets_++;
            }
            else if(rand_num >= 60 && rand_num < 80){
                arr_[i][j] = SquareType::Wall;  //20% chance of walls
            }
            else if(rand_num >= 80 && rand_num < 85){
                arr_[i][j] = SquareType::Enemies;   //10 percent chance of Enemies
            }
            else if(rand_num >= 85 && rand_num < 90){
                arr_[i][j] = SquareType::Trap;   //5 percent chance of Enemies
            }
            else if(rand_num >= 90){    
                arr_[i][j] = SquareType::Treasure;  //10 percent chance of Treasure
            }
            else{
                arr_[i][j] = SquareType::Empty; //default to empty jus in case
            }
        }
    }
}
int Board::get_pellets(){
    return pellets_;
}
SquareType Board::get_square_value(Position pos) const{
    return arr_[pos.row][pos.col];
}

// set the value of a square to the given SquareType
void Board::SetSquareValue(Position pos, SquareType value){
    arr_[pos.row][pos.col] = value;
}

// get the possible Positions that a Player/Enemy could move to
// (not off the board or into a wall)
std::vector<Position> Board::GetMoves(Player *p){
    std::vector<Position>movesVec;
    Position current_Pos = p->get_position();   //getting current position
    current_Pos.row--;   //to check up
    if(current_Pos.row >= 0 && get_square_value(current_Pos) != SquareType::Wall){
        movesVec.push_back(current_Pos);
    }
    current_Pos.row++;  //back to original position
    current_Pos.row++; //to check down
    if(current_Pos.row < 10 && get_square_value(current_Pos) != SquareType::Wall){
        movesVec.push_back(current_Pos);
    }
    current_Pos.row--;  //back to original position
    current_Pos.col--;  //to check left
    if(current_Pos.col >= 0 && get_square_value(current_Pos) != SquareType::Wall){
        movesVec.push_back(current_Pos);
    }
    current_Pos.col++;  //back to original position
    current_Pos.col++;  //to check right
    if(current_Pos.col < 10 && get_square_value(current_Pos) != SquareType::Wall){
        movesVec.push_back(current_Pos);
    }
    current_Pos.col--;  //prob not needed but just in case to get back to original position
    return movesVec;
}

// Move a player to a new position on the board. Return
// true if they moved successfully, false otherwise.
bool Board::MovePlayer(Player *p, Position pos, std::vector<Player*> enemylist){
    SquareType posEmoji = get_square_value(pos);
    //if enemy is in position u wanna move
    if(posEmoji == SquareType::Enemies){
        //to see if we can kill enemy or not
        if(p->hasTreasure()){
            arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;    //make the previous square empty
            p->SetPosition(pos);    //set player position to new position
            //set the new position sqaure type to Pacman
            SetSquareValue(pos, SquareType::Pacman);
            p->setHasTreasure();    //doesn't have treasure
            p->incrementMoves();
            return true;
        }
        else{
            p->setLives();  //decrement lives
            if(p->getLives() == 0){ //check if lives is not at 0
                p->setIsDead(true); //if lives at 0 kill player
                p->incrementMoves();
                return false;
            }
            arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;    //make the previous square empty
            //make the previous square empty
            p->SetPosition(pos);    //set player position to new position
            //set the new position sqaure type to Pacman
            SetSquareValue(pos, SquareType::Pacman);
            p->incrementMoves();
            return true;
        }
    }
    if(posEmoji == SquareType::Trap){
        p->setLives();  //decrement lives
        if(p->getLives() == 0){ //check if lives is not at 0
            p->setIsDead(true); //if lives at 0 kill player
            p->incrementMoves();
            return false;
        }
    }
    //if move is treasure
    if(posEmoji == SquareType::Treasure){
        p->ChangePoints(100);   //add 100 points for finding treasure
        //if player doesn't have treasure change him to has treasure
        if(!p->hasTreasure()){ 
            p->setHasTreasure();    //set has_treasure_ to true
        }
        arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;    //make the previous square empty
        p->SetPosition(pos);    //set new position for player
        //change emoji of moved place to PowerfulPacman
        SetSquareValue(pos, SquareType::PowerfulPacman);
        p->incrementMoves();
        return true;
    }
    //if move is pellet
    if(posEmoji == SquareType::Dots){
        if(p->hasTreasure()){
            p->ChangePoints(1);
            arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;    //make the previous square empty
            p->SetPosition(pos);    //set new position for player
            //change emoji of moved place to PowerfulPacman
            SetSquareValue(pos, SquareType::PowerfulPacman);
            p->incrementMoves();
            pellets_--;
            return true;
        }
        p->ChangePoints(1);
        arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;    //make the previous square empty
        p->SetPosition(pos);    //set new position for player
        //change emoji of moved place to PowerfulPacman
        SetSquareValue(pos, SquareType::Pacman);
        p->incrementMoves();
        pellets_--;
        return true;
    }
    //if square if Empty
    if(posEmoji == SquareType::Empty){
        if(p->hasTreasure()){
            arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;    //make the previous square empty
            p->SetPosition(pos);    //set new position for player
            //change emoji of moved place to PowerfulPacman
            SetSquareValue(pos, SquareType::PowerfulPacman);
            p->incrementMoves();
            return true;
        }
        arr_[p->get_position().row][p->get_position().col] = SquareType::Empty;    //make the previous square empty
        p->SetPosition(pos);    //set new position for player
        //change emoji of moved place to PowerfulPacman
        SetSquareValue(pos, SquareType::Pacman);
        p->incrementMoves();
        return true;
    }
    return false;

}

// Move an enemy to a new position on the board. Return
// true if they moved successfully, false otherwise.
// bool Board::MoveEnemy(Player *p, Position pos){

// }
std::ostream& operator<<(std::ostream& os, const Board &b){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            os << SquareTypeStringify( b.get_square_value({i, j}) ) << " ";
        }
        os << std::endl;
    }
    return os;
}

// constructor
Game::Game(){
    board_ = new Board();
	turn_count_ = 0;
    dots_count_ = 0;
    GameOver = false;
}

// initialize a new game, given one human player and
// a number of enemies to generate
void Game::NewGame(Player *human,std::vector<Player*> enemylist, const int enemies){
    players_.push_back(human);
    dots_count_ = board_->get_pellets();
}

// have the given Player take their turn
void Game::TakeTurn(Player *p,std::vector<Player*> enemylist){
    std::vector<Position> possibleMoves = board_->GetMoves(p);
    std::vector<std::string> possibleMovesInLetter;
    std::cout << "Moves Key: UP = U, Down = D, Left = L, Right = R " << std::endl;
    std::cout << "You can go the following direction: ";
    for(unsigned i = 0; i < possibleMoves.size(); i++){
        std::cout << p->ToRelativePosition(possibleMoves[i]) << " ";
        possibleMovesInLetter.push_back(p->ToRelativePosition(possibleMoves[i]));   //pushed letter form of move to compare later
    }
    std::cout << std::endl;
    std::cout << "Enter your move:" << std::endl;
    char input;
    std::cin >> input;
    std::string compString;
    for(unsigned i = 0; i < possibleMovesInLetter.size(); i++){
        compString = possibleMovesInLetter[i];
        if(compString[0] == input || tolower(compString[0]) == input){
            std::cout << "Good move" << std::endl;
            board_->MovePlayer(p, possibleMoves[i], enemylist);
            turn_count_++;
            break;
        }
        else{
            continue;
        }
    }
    std::cout << "No possible move was made" << std::endl;
}

//have the enemy take turn
void Game::TakeTurnEnemy(Player *p){

}

bool Game::IsGameOver(Player *p){
    if(p->isDead() == true){
        return true;
    }
    else if(CheckifdotsOver() == true){
        return true;
    }
    return false;

}

// return true if all pellets have been collected
bool Game::CheckifdotsOver(){
    if(board_->get_pellets() == 0){
        return true;
    }
    else{
        return false;
    }
    return false;
}

// You probably want to implement these functions as well
// string info about the game's conditions after it is over
std::string Game::GenerateReport(Player *p){
    std::string report;
    if(p->isDead() == false){
        report = p->get_name() + " won the game with " + std::to_string(turn_count_) + " moves and " + std::to_string(p->get_points()) + " points";
    }
    else{
        report = p->get_name() + " lost the game with " + std::to_string(turn_count_) + " moves and " + std::to_string(p->get_points()) + " points";
    }
    return report;
}

std::ostream& operator<<(std::ostream& os, const Game &m){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
        os << SquareTypeStringify(m.board_->get_square_value({i,j})) <<" ";
        }
    os << std::endl;
  }
  return os;
}