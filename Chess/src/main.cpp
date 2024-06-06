// Chess 
#include "Chess.h"
#include "Game.h"
#include <iostream>

int main()
{
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
    //std::string board = "########R###K##############################r###k########"

    //std::string board = std::string(
    //    "R###Kbr#") + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "r###k##r";



    Chess a(board);
    Game game;
    game.initialize(board);
    int codeResponse = 0;

    std::string res = a.getInput();
    while (res != "exit")
    {
        /*
        codeResponse value :
        Illegal movements :
        11 - there is not piece at the source
        12 - the piece in the source is piece of your opponent
        13 - there one of your pieces at the destination
        21 - illegal movement of that piece
        31 - this movement will cause you checkmate

        legal movements :
        41 - the last movement was legal and cause check
        42 - the last movement was legal, next turn
        */

        // Parse input
        if (res.length() != 4) {
            std::cout << "Invalid input format" << std::endl;
            res = a.getInput();
            continue;
        }



        try {
            auto [srcPos, destPos] = Game::parseMove(res);
            int srcCol = srcPos.first;
            int srcRow = srcPos.second;
            int destCol = destPos.first;
            int destRow = destPos.second;
            if(game.isLegalMove(srcRow, srcCol, destRow, destCol))
            {
                
                codeResponse = LegalMoveException().getErrorCode(); // Move is legal and does not cause check

                game.movePiece(srcRow, srcCol, destRow, destCol);
                if (game.isCheck(game.getCurrentPlayerColor()))
                    codeResponse = MoveChecksOpponentException().getErrorCode(); // Move is legal and causes check

                //if (game.lastCastleMove() != "didnt Castle")
                //    a.execute(game.lastCastleMove());
                // so apparently i cannot execute a move without passing a turn OR simply move a piece visually without sending a 42
                // and i implemented castling for no reason :'(
                // this is what the code would have been to move the rook visually in castling

                game.isGameOver();

            }
			else
			{
				codeResponse = IllegalMoveException().getErrorCode(); // Move is illegal
			}

        }
        catch (const ChessException& e) 
        {
			std::cout << e.what() << std::endl;
			codeResponse = e.getErrorCode();
            if (e.getErrorCode() == 0)
                break;
		}

        catch (const std::exception& e) 
        {
            std::cout << "An unexpected error occurred: " << e.what() << std::endl;
            codeResponse = 0;
        }

        a.setCodeResponse(codeResponse);
        res = a.getInput();

    }

    std::cout << std::endl << "Exiting " << std::endl;
    return 0;
}
