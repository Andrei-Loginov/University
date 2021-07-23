#include "Chess.h"


const std::string head = "   A  B  C  D  E  F  G  H";
const std::string left[] = { "1 ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 " };

bool operator==(const std::pair<int, int>& left, const std::pair<int, int>& right) {
	return (left.first == right.first && left.second == right.second);
}

Chess::Chess() {
	for (size_t i = 0; i < 8; ++i) {
		board[1][i].type =  P;
		board[6][i].type = P;
		board[0][i].colour = board[1][i].colour = white;
		board[7][i].colour = board[6][i].colour = black;
	}
	board[0][0].type = board[0][7].type = board[7][0].type = board[7][7].type = R;
	board[0][1].type = board[0][6].type = board[7][1].type = board[7][6].type = N;
	board[0][2].type = board[0][5].type = board[7][2].type = board[7][5].type = B;
	board[0][3].type = board[7][3].type = Q;
	board[0][4].type = board[7][4].type = K;
}

Chess::Chess(const std::string& game) {
	std::stringstream stream(game);
	std::string s;

	for (int i = 7; i >= 0; --i)
		for (int j = 0; j < 8; ++j) {
			stream >> s;
			board[i][j] = { static_cast<COLOUR>(int(s[0])) , static_cast<PIECE>(int(s[1])) };
			if (board[i][j].type == K) {
				if (board[i][j].colour == white) whiteKing = { i, j };
				else blackKing = { i, j };
			}
		}
	check();
}

Chess::Chess(const char* fname) {
	std::ifstream stream(fname);
	std::string s;
	for (int i = 7; i >= 0; --i)
		for (int j = 0; j < 8; ++j) {
			stream >> s;
			board[i][j] = { static_cast<COLOUR>(int(s[0])) , static_cast<PIECE>(int(s[1])) };
			if (board[i][j].type == K) {
				if (board[i][j].colour == white) whiteKing = { i, j };
				else blackKing = { i, j };
			}
		}
	stream.close();
	check();
}

Chess::Chess(const Chess& item): turn(item.turn), CheckWhite(item.CheckWhite), CheckBlack(item.CheckBlack), whiteKing(item.whiteKing), blackKing(item.blackKing) {
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			board[i][j] = item.board[i][j];
}

void Chess::check()  {
	CheckBlack = CheckWhite = false;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j) {
			if (board[i][j].type != K) {
				if (board[i][j].colour == white) {
					bool temp = turn;
					turn = true;
					if (attack({ i ,j }, blackKing)) CheckBlack = true;
					turn = temp;
				}else {
					bool temp = turn;
					turn = false;
					if (attack({ i ,j }, whiteKing)) CheckWhite = true;
					turn = temp;
				}
			}
		}
}


bool Chess::move(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (curr.first == dest.first && curr.second == dest.second) return false;
	if ((turn && board[curr.first][curr.second].colour != white) || (!turn && board[curr.first][curr.second].colour != black)) return false;

	switch (board[curr.first][curr.second].type) {
	case P: return pawnMove(curr, dest); break;
	case R: return rookMove(curr, dest); break;
	case N: return knightMove(curr, dest); break;
	case Q: return queenMove(curr, dest); break;
	case K: return kingMove(curr, dest); break;
	case B: return bishopMove(curr, dest); break;
	default: return false;
	}
}

bool Chess::attack(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (curr.first == dest.first && curr.second == dest.second) return false;
	if ((turn && board[curr.first][curr.second].colour != white) || (!turn && board[curr.first][curr.second].colour != black)) return false;

	switch (board[curr.first][curr.second].type) {
	case P: return pawnAttack(curr, dest); break;
	case R: return rookAttack(curr, dest); break;
	case N: return knightAttack(curr, dest); break;
	case Q: return queenAttack(curr, dest); break;
	case K: return kingAttack(curr, dest); break;
	case B: return bishopAttack(curr, dest); break;
	default: return false;
	}
}

bool Chess::pawnMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (curr.second != dest.second) return false;
	if (board[dest.first][dest.second].colour != none) return false;
	if (turn) {
		if (dest.first - curr.first == 1)
			return tryMove(curr, dest);
		else if (dest.first - curr.first == 2) {
			if (curr.first != 1) return false;
			if (board[2][dest.second].colour != none) return false;
			if (tryMove(curr, dest)) {
				en_passant = dest;
				return true;
			}
		}
		else return false;
	}
	else {
		if (dest.first - curr.first == -1)
			return tryMove(curr, dest);
		else if (dest.first - curr.first == -2) {
			if (curr.first != 6) return false;
			if (board[5][dest.second].colour != none) return false;
			if (tryMove(curr, dest)) {
				en_passant = dest;
				return true;
			}
		}
		else return false;
	}
	return false;
	
}

bool Chess::pawnAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	bool fl = false, e_p = false;
	CELL current = board[curr.first][curr.second], destination = board[dest.first][dest.second];
	if (abs(curr.second - dest.second) == 1) {
		if (destination.colour != current.colour &&
			destination.colour != empty) {
			int multiplier = (turn) ? 1 : -1;
			if (dest.first - curr.first == multiplier) fl = true;
		}
		else {
			if (curr.first == en_passant.first && dest.second == en_passant.second) fl = e_p = true;
		}
	}
	if (fl) {
		if (destination.type != K) {
			board[dest.first][dest.second] = current;
			if (!e_p) {
				board[curr.first][curr.second] = nothing;
			}
			else {
				board[curr.first][curr.second] = nothing;
				board[en_passant.first][en_passant.second] = nothing;
			}
			check();
			if ((turn && CheckWhite) || (!turn && CheckBlack)) {
				if (!e_p)
					board[dest.first][dest.second] = destination;
				else {
					board[dest.first][dest.second] = nothing;
					board[en_passant.first][en_passant.second].colour = (fl) ? black : white;
					board[en_passant.first][en_passant.second].type = P;
				}
				board[curr.first][curr.second] = current;
				check();
				fl = false;
			}
		}
		else return true;
	}
	return fl;
}

bool Chess::knightMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (board[dest.first][dest.second].colour == none) {
		//std::cout << abs(curr.first - dest.first) << " " << abs(curr.second - dest.second) << "\n";
		if ((abs(curr.first - dest.first) == 2 && abs(curr.second - dest.second) == 1) ||
			(abs(curr.first - dest.first) == 1 && abs(curr.second - dest.second) == 2)) 
		{
			return tryMove(curr, dest);
		}
		return false;
	}
	return false;
}

bool Chess::knightAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	CELL current = board[curr.first][curr.second], destination = board[dest.first][dest.second];

	if (current.colour != destination.colour && destination.colour != none) {
		if ((abs(curr.first - dest.first) == 2 && abs(curr.second - dest.second) == 1) ||
			(abs(curr.first - dest.first) == 1 && abs(curr.second - dest.second) == 2))
		{
			if (destination.type != K) {
				return tryMove(curr, dest);
			}
			else return true;
		}
		return false;
	}
	return false;
}

bool Chess::rookMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (curr.first != dest.first && curr.second != dest.second) return false;

	CELL current = board[curr.first][curr.second], destination = board[dest.first][dest.second];
	if (destination.colour != none) return false;

	int mult_rows = 0, mult_cols = 0;
	if (curr.first == dest.first)
		mult_cols = (curr.second < dest.second) ? 1 : -1;
	else
		mult_rows = (curr.first < dest.first) ? 1 : -1;
	for (int i = 1; !(curr.first + i * mult_rows == dest.first && curr.second + i * mult_cols == dest.second); ++i)
		if (board[curr.first + i * mult_rows][curr.second + i * mult_cols].colour != none) return false;
	return tryMove(curr, dest);
}

bool Chess::rookAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (curr.first != dest.first && curr.second != dest.second) return false;
	CELL current = board[curr.first][curr.second], destination = board[dest.first][dest.second];
	if (destination.colour == none || destination.colour == current.colour) return false;
	
	int mult_rows = 0, mult_cols = 0;
	if (curr.first == dest.first)
		mult_cols = (curr.second < dest.second) ? 1 : -1;
	else
		mult_rows = (curr.first < dest.first) ? 1 : -1;
	for (int i = 1; !(curr.first + i * mult_rows == dest.first && curr.second + i * mult_cols == dest.second); ++i)
		if (board[curr.first + i * mult_rows][curr.second + i * mult_cols].colour != none) return false;
	
	if (destination.type == K) return true;
	return tryMove(curr, dest);

}

bool Chess::bishopMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (board[dest.first][dest.second].colour != none) return false;
	if (abs(curr.first - dest.first) != abs(curr.second - dest.second)) return false;

	int mult_rows = (dest.first - curr.first > 0) ? 1 : -1;
	int mult_cols = (dest.second - curr.second > 0) ? 1 : -1;
	//std::cout << "mults: " << mult_rows << " " << mult_cols << "\n";

	for (int i = 1; !(curr.first + i * mult_rows == dest.first && curr.second + i * mult_cols == dest.second); ++i)
		if (board[curr.first + i * mult_rows][curr.second + i * mult_cols].colour != none) return false; 
	return tryMove(curr, dest);
}

bool Chess::bishopAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (abs(curr.first - dest.first) != abs(curr.second - dest.second)) return false; 
	
	CELL current = board[curr.first][curr.second], destination = board[dest.first][dest.second];
	if (destination.colour == none || destination.colour == current.colour) return false; 

	int mult_rows = (dest.first - curr.first > 0) ? 1 : -1;
	int mult_cols = (dest.second - curr.second > 0) ? 1 : -1;
	for (int i = 1; !(curr.first + i * mult_rows == dest.first && curr.second + i * mult_cols == dest.second); ++i)
		if (board[curr.first + i * mult_rows][curr.second + i * mult_cols].colour != none) return false;

	if (destination.type == K) return true;
	return tryMove(curr, dest);

}

bool Chess::queenMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	return (rookMove(curr, dest) || bishopMove(curr, dest));
}

bool Chess::queenAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	return (rookAttack(curr, dest) || bishopAttack(curr, dest));
}

bool Chess::kingMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	std::ofstream fout("some.txt", std::ios_base::trunc);
	if (board[dest.first][dest.second].colour != none) return false;
	if (abs(curr.first - dest.first) > 1 || abs(curr.second - dest.second) > 1) return false;

	if (curr.first == whiteKing.first && curr.second == whiteKing.second) {
		if (abs(dest.first - blackKing.first) < 2 && abs(dest.second - blackKing.second) < 2)  return false; 
	}
	else if (abs(dest.first - whiteKing.first) < 2 && abs(dest.second - whiteKing.second) < 2)  return false; 

	if (curr == whiteKing)
		whiteKing = dest;
	else
		if (curr == blackKing)
			blackKing = dest;
		else  return false; 
	fout << "turn " << turn << "\n";
	if (tryMove(curr, dest)) {
		return true;
	}
	if (dest == whiteKing)
		whiteKing = curr;
	else
		blackKing = curr;
	return false;
	fout.close();
}

bool Chess::kingAttack(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	if (abs(curr.first - dest.first) > 1 || abs(curr.second - dest.second) > 1) return false; 

	CELL current = board[curr.first][curr.second], destination = board[dest.first][dest.second];

	if (destination.colour == none || destination.colour == current.colour) return false;
	if (curr.first == whiteKing.first && curr.second == whiteKing.second) {
		if (abs(dest.first - blackKing.first) < 2 && abs(dest.second - blackKing.second) < 2)  return false;
	}
	else if (abs(dest.first - whiteKing.first) < 2 && abs(dest.second - whiteKing.second) < 2) return false;

	if (tryMove(curr, dest)) {
		if (curr.first == whiteKing.first && curr.second == blackKing.second)
			whiteKing = dest;
		else
			blackKing = dest;
		return true;
	}
	return false;
}

bool Chess::tryMove(const std::pair<int, int>& curr, const std::pair<int, int>& dest) {
	CELL current = board[curr.first][curr.second], destination = board[dest.first][dest.second];

	board[dest.first][dest.second] = current;
	board[curr.first][curr.second] = nothing;

	check();
	if ((turn && CheckWhite) || (!turn && CheckBlack)) {
		board[dest.first][dest.second] = destination;
		board[curr.first][curr.second] = current;
		check();
		return false;
	}
	return true;
}

void Chess::e_pCheck(){
	if (en_passant.first != -1) {
		if ((turn && board[en_passant.first][en_passant.second].colour != white) ||
			(!turn && board[en_passant.first][en_passant.second].colour != black))
			en_passant = { -1, -1 };
	}
}

step_results Chess::make_step(const std::string& str) {
	check();
	int row, col;
	if (str == "-1") {
		if (turn) std::cout << "Black wins\n";
		else std::cout << "White win\n";
		return static_cast<step_results>(2);
	}
	if (str == "file") {
		to_file("output.txt");
		return static_cast<step_results>(3);
	}
	int t = correct_str(str);
	if (t != 0) {
		std::pair<int, int> curr, dest;
		if (t == 1 || t == 3) {
			curr = { int(str[1]) - int('1'), int(str[0]) - int('a') };
			dest = { int(str[4]) - int('1'), int(str[3]) - int('a') };
			if (board[curr.first][curr.second].type != P) return static_cast<step_results>(0);
		}
		else if (t == 2 || t == 4) {
			curr = { int(str[2]) - int('1'), int(str[1]) - int('a') };
			dest = { int(str[5]) - int('1'), int(str[4]) - int('a') };
			if (int(board[curr.first][curr.second].type) != int(str[0])) return static_cast<step_results>(0);
		}
		if (curr.first == dest.first && curr.second == dest.second) return static_cast<step_results>(0);
		if ((turn && board[curr.first][curr.second].colour != white) || (!turn && board[curr.first][curr.second].colour != black)) 
			return static_cast<step_results>(0);

		if (t > 2) {
			if (attack(curr, dest)) {
				e_pCheck();
				turn = !turn;
				return static_cast<step_results>(1);
			}
			else return static_cast < step_results>(0);
		}
		else
			if (move(curr, dest)) {
				e_pCheck();
				turn = !turn;
				return static_cast < step_results>(1);
			}
			else return static_cast < step_results>(0);
	}
	else return static_cast < step_results>(0);
	
	
	/*
	if (str == "-1") {
		return (turn ? 2 : 3);
	}
	else {
		int row_c, col_c, row_d, col_d;
		int t = correct_str(str);
		std::cout << t << " = t\n";
		if (t == 1 || t == 3) {
			row_c = int(str[1]) - int('1'); col_c = int(str[0]) - int('a');
			if (board[row_c][col_c].type != P) return 0;
			row_d = int(str[4]) - int('1'); col_d = int(str[3]) - int('a');
		}
		else if (t == 2 || t == 4) {
			row_c = int(str[2]) - int('1'); col_c = int(str[1]) - int('a');
			std::cout << int(str[0]) << " " << board[row_c][col_c].type << "\n";
			if (int(board[row_c][col_c].type) != int(str[0])) return 0; 
			row_d = int(str[5]) - int('1'); col_d = int(str[4]) - int('a');
		}
		else return 0;
		if ((turn && board[row_c][col_c].colour != white) || (!turn && board[row_c][col_c].colour != black)) return 0;
		if (t == 1 || t == 2) 
			if (move({ row_c, col_c }, { row_d, col_d })) {
				e_pCheck();
				turn = !turn;
				check();
				return 1;
			}
		if (t == 3 || t == 4) 
			if (attack({ row_c, col_c }, { row_d, col_d })) {
				e_pCheck();
				turn = !turn;
				check();
				return 1;
			}
		//std::cout << str << " " << row_c << " " << col_c << " " << row_d << " " << col_d << "\n";
		return 0;
	}*/
	
}

int Chess::correct_str(const std::string& str) {
	//std::cout << str[0] << " " << str[1] << " " << str[2] << " " << str[3] << " " << str[4] << "\n";
	if (str.length() > 6) return 0;
	if (str[0] >= 'a' && str[0] <= 'h') {
		if (str[1] >= '1' && str[1] <= '8' && str[3] >= 'a' && str[3] <= 'h' && str[4] >= '1' && str[4] <= '8')
			if (str[2] == '-') return 1;
			else if (str[2] == 'x') return 3;
	}
	else if (str[0] == 'N' || str[0] == 'R' || str[0] == 'B' || str[0] == 'Q' || str[0] == 'K') {
		if (correct_str(str.substr(1, 5)) == 1) return 2;
		else if (correct_str(str.substr(1, 5)) == 3) return 4;
	} 
	return 0;
}

std::ostream& operator<<(std::ostream& stream, const Chess& game) {
	//stream << head << "\n";
	for (int i = 7; i >= 0; stream << "\n", --i) {
		//stream << left[i];
		for (int j = 0; j < 8; ++j)
			stream << char(game.board[i][j].colour) << char(game.board[i][j].type) << " ";
	}
	return stream;
}

void Chess::to_file(const char* fname) const {
	std::ofstream fout(fname);
	fout << *this;
	fout.close();
}

void Chess::print() const{
	for (int i = 7; i >= 0; --i)
		for (int j = 0; j < 8; ++j)
				ColorPrint(3 * j, 7-i, F_L_WHITE, "%c%c ", char(board[i][j].colour), char(board[i][j].type));

}

/*void Chess::test() {
	std::cout << CheckWhite << " " << CheckBlack << "\n";

	turn = false;
	std::cout << move({ 7, 4 }, { 6, 4 }) << "\n";
	std::cout << *this << "\n";
	
}*/