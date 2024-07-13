// Chess 
#include "Chess.h"
#include "Game.h"
#include <iostream>
#include "ChessAlgorithm.h"

int main()
{
    string board = "R##PK##RPPPPPPPP###################P############Rppppppp####k###"; 
    //std::string board = "########R###K##############################r###k########"

    //std::string board = std::string( // for testing purposes
    //    "R###Kbr#") + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "########" + 
    //    "r###k##r";



    Game game;
    game.initialize(board);
    ChessAlgorithm chessAlgorithm(game, game.getBoard(), 0);
    Chess a(chessAlgorithm, board);

    int codeResponse = 0;
    bool gameOver = false;



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


            codeResponse = game.getMoveResponseCode(srcRow, srcCol, destRow, destCol);
            
            if (game.isMoveLegal(codeResponse))
            {

                codeResponse = game.movePiece(srcRow, srcCol, destRow, destCol);
                if (codeResponse == PawnPromotionException().getResponseCode())
				{
                    char piece = a.pawnPromotionUI();
					game.promotePawn(destRow, destCol, piece);
				}
                

                if (game.lastCastleMove() != "didnt Castle")
                    codeResponse = CastlingException().getResponseCode();

                if (game.isCheck(game.getCurrentPlayerColor())) 
                    codeResponse = MoveChecksOpponentException().getResponseCode(); // Move is legal and causes check


                gameOver = game.isGameOver();
                if(gameOver)
                    codeResponse = CheckmateException().getResponseCode();
            }

           


        }
        catch (const ChessException& e) 
        {
			std::cout << e.what() << std::endl;
			codeResponse = e.getResponseCode();
            if (e.getResponseCode() == 0)
                break;
		}

        catch (const std::exception& e) 
        {
            std::cout << "An unexpected error occurred: " << e.what() << std::endl;
            codeResponse = 0;
        }

        a.setCodeResponse(codeResponse);


        res = a.getInput();
        if(gameOver)
			break;

    }

    std::cout << std::endl << "Exiting " << std::endl;
    return 0;
}
