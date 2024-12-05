#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <string>
#include <memory>

template <typename T>
using unique_ptr = std::unique_ptr<T>;

enum PieceType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

enum {
	BLACK,
	WHITE
};

struct Move
{
	short x;
	short y;
};

struct Pos
{
public:
	Pos()
	{
		x = 0;
		y = 0;
		xyToFr();
	};
	Pos(short _x, short _y)
	{
		x = _x;
		y = _y;
		xyToFr();
	};
	short x;
	short y;
	std::string file_rank;


	void setPos(short _x, short _y)
	{
		x = _x;
		y = _y;
		if(!validPos())
			throw (std::invalid_argument("Position not valid"));
		xyToFr();
	};

	void setPos(std::string _fr)
	{
		file_rank = _fr;
		frToXy();
	};

	bool validPos() { return x >= 0 && x <= 7 && y >= 0 && y <= 7; }

	int	reverseY() {
		int rev = 0;
		if(y < 4)
			rev = 7 - y;
		else
			rev = abs(y - 7);
		return rev;
	}

private:
	void frToXy()
	{
		x = file_rank[0] - 97;
		y = file_rank[1] - 49;
	}
	void xyToFr()
	{
		file_rank[0] = x + 97;
		file_rank[1] = y + 49;
	}
};

Move operator-(Pos new_pos, Pos old_pos)
{
	Move move;
	move.x = new_pos.x - old_pos.x;
	move.y = new_pos.y - old_pos.y;
	return move;
}

Pos operator+(Pos pos, Move move)
{
	pos.setPos(pos.x + move.x, pos.y + move.y);
	return pos;
}

std::ostream& operator<<(std::ostream& os, const Pos& pos) {
	os << pos.file_rank << std::endl;
	os << "x: " << pos.x << std::endl;
	os << "y: " << pos.y << std::endl;
	return os;
}

bool operator==(Pos pos1, Pos pos2) {
	return pos1.x == pos2.x && pos1.y == pos2.y;
}

class Pieces
{
protected:
	Pos pos;
	bool color;
	const PieceType type;
public:
	Pieces(short _x, short _y, PieceType _type) : pos(_x, _y), type(_type) {
		color = pos.y <= 1 ?  WHITE : BLACK;
	};
	virtual ~Pieces() {};

	virtual bool	validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) = 0;
	virtual void	makeMove(const Pos& new_pos) {
		pos = new_pos;
	};
	PieceType	getType() const { return type; }
	Pos getPosition() const { return pos; }
	bool getColor() const { return color; }
};

class Pawn : public Pieces {
public:
	bool		firstMove = true;
	const short	dir = color == BLACK ? -1 : 1;
	
	Pawn(short _x, short _y) : Pieces(_x, _y, PAWN) {};
	~Pawn() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		Move move = pos - new_pos;

		// first handle special cases
		if ((move.x == 1 || move.x == -1)
			&& piece != nullptr
			&& (move.y == 1 * dir))
			return true;
		if(firstMove && move.y == 2 * dir)
			return true;

		// then error cases
		if(move.x != 0 || move.y != dir)
			return false;

		// then it should be true
		return true;
	}
	void	makeMove(const Pos& new_pos) override {
		pos = new_pos;
		firstMove = false;
	}
};

class Rook : public Pieces {
public:
	Rook(short _x, short _y) : Pieces(_x, _y, ROOK) {};
	~Rook() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class Knight : public Pieces {
public:
	Knight(short _x, short _y) : Pieces(_x, _y, KNIGHT) {};
	~Knight() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class Bishop : public Pieces {
public:
	Bishop(short _x, short _y) : Pieces(_x, _y, BISHOP) {};
	~Bishop() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class Queen : public Pieces {
public:
	Queen(short _x, short _y) : Pieces(_x, _y, QUEEN) {};
	~Queen() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class King : public Pieces {
public:
	King(short _x, short _y) : Pieces(_x, _y, KING) {};
	~King() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

bool operator==(const std::unique_ptr<Pieces>& piece1, const std::unique_ptr<Pieces>& piece2) {
	if(piece1->getPosition() == piece2->getPosition() && piece1->getType() == piece2->getType()) {
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream&os, const std::unique_ptr<Pieces>& _piece) {
	os << "color: " << _piece->getColor() << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream&os, const Pieces* _piece) {
	os << "color: " << _piece->getColor() << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}

#endif