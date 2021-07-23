#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include "console.h"
#include <cstdio>


enum step_results {
	err, ok, checkmate, written,
};

class Chess{
public:
	Chess();
	explicit Chess(const std::string& game);
	explicit Chess(const char* fname);
	Chess(const Chess& item);

	bool get_turn() const { return turn; }
	bool is_check() const { return (CheckBlack || CheckWhite); }
	
	//void test();
	void to_file(const char* fname) const;
	void print() const;
	step_results make_step(const std::string &str);
	
	friend std::ostream& operator<<(std::ostream& stream, const Chess& game);
private:
	enum COLOUR {
		black = 66, white = 87, none = 45
	};
	enum PIECE {
		K = 75, Q = 81, R = 82, N = 78, P = 80, empty = 45, B = 66
	};
	struct CELL {
		COLOUR colour = none;
		PIECE type = empty;
	};
	const CELL nothing = { none, empty };
	

	CELL board[8][8];
	bool CheckWhite = false;
	bool CheckBlack = false;
	std::pair<int, int> en_passant = { -1, -1 };
	std::pair<int, int> blackKing = { 7, 4 }, whiteKing = { 0 , 4 };
	bool turn = true; //white = true, black = false

	void e_pCheck();
	int correct_str(const std::string& str);
	bool tryMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest); //when we know, that the piece can be noved to the position 
	//we use it to check, if the king will be checked after the movement
	void check();

	bool move(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool attack(const std::pair<int, int>& curr, const std::pair<int, int>& dest);

	bool pawnMove(const std::pair<int, int> &curr, const std::pair<int, int> &dest);
	bool pawnAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool knightMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool knightAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool rookMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest); 
	bool rookAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool bishopMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool bishopAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool queenMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool queenAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool kingMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest);
	bool kingAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest);	
};

