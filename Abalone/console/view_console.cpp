#include "view_console.h"
#include "game.h"
std::string View_Console::readInPut(){
    std::cout<< "Entrez le move en ABA-PRO : " ;
    std::string input ;
    std::cin >> input ;

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    return input;
}
std::ostream & operator<<(std::ostream & out,std::optional<bool>  s){
    out << model::toString(s);
    return out;
}


void View_Console::printAbaloneBoard(std::map<model::HexCell,std::optional<bool>>& board){
    unsigned nbEspace = 5 ;
    static std::vector<char> lines {'I','H','G','F','E','D','C','B','A',};
    std::cout << std :: string(nbEspace+3,' ') ;
    for(unsigned i = 0;i<nbEspace;i++){
        std::cout << "_ " ;
    }
    std::cout << std::endl;
    auto boardIter = board.cbegin();
    for(unsigned i =1 ;i<=lines.size();i++){
        std::optional<bool> status ;
        int line = nbEspace-i;
        std::string tmp = i == nbEspace?"(":i > nbEspace? "\\":"/" ;
        std::cout << std::string(abs(line),' ') << lines.at(i-1)<< "--" << tmp ;
        if(i-1<lines.size()/2){
            for (unsigned nbVal = 0; nbVal < nbEspace+(i-1) ;nbVal++ ) {
                std::string val = nbVal==(nbEspace+i-2)?"":" ";
                status= boardIter->second;
                std::cout << boardIter->second <<val;

                boardIter++;
            }
            std::cout << "\\";
        }else if(i==nbEspace){
            for (unsigned nbVal = 0; nbVal < nbEspace+(i-1) ;nbVal++ ) {
                std::string val = nbVal==(nbEspace+i-2)?"":" ";
                status= boardIter->second;
                std::cout <<boardIter->second<<val;

                boardIter++;
            }
              std::cout << ")";
        }else{
            for (unsigned nbVal = 0; nbVal < lines.size()-abs(line) ;nbVal++ ) {
                std::string val = nbVal==(lines.size()-abs(line)-1)?"":" ";
                if(lines[i-1] == 'A' && nbVal!=(lines.size()-abs(line)-1)){
                    val = "_";
                }
                status= boardIter->second;
                std::cout <<boardIter->second<<val;

                boardIter++;
            }
            std::cout << "/";
            std::cout <<"\\"<< (i>nbEspace+1? " " +std::to_string(lines.size()-abs(line)+2):" ");

        }

        std::cout << std::endl;
    }
    std::cout << std :: string(nbEspace+4,' ') ;
    for(unsigned i = 0;i<nbEspace;i++){
        std::cout << "\\ " ;
    }
    std::cout << nbEspace+1<< std::endl;
    std::cout << std :: string(nbEspace+4,' ') ;
    for(unsigned i = 0;i<nbEspace;i++){
        std::cout << " "<<i+1 ;
    }
    std::cout << std::endl;

}
void View_Console::printPlayers(model::Player& currentPlayer,model::Player& player1,model::Player& player2){

    std::string p1 = player1.getState().value() == true ? "White": "Black";
    std::cout<<"Player 1 is playing with "<< p1 << " and has " <<player1.getNbBallsOut() << " opposite balls out "<<std::endl ;

    std::string p2 = player2.getState().value() == true ? "White": "Black";
    std::cout<<"Player 2 is playing with "<< p2 << " and has " <<player2.getNbBallsOut() << " opposite balls out "<<std::endl ;

    std::string curPlayer = currentPlayer.getState().value() == true ? "White": "Black";
    std::cout<<"Current player is playing with "<< curPlayer <<std::endl ;
}
void View_Console::update(model::GameData& gameData){
    std::cout<<"update ..."<< std::endl;

    printAbaloneBoard(gameData.board);
    printPlayers(gameData.currentPlayer,gameData.firstPlayer, gameData.secondPlayer);

}
void View_Console::update(std::string messageError){
    std::cout<<messageError<< std::endl;
    std::cout<<"Please try again "<< std::endl;
}
