#include <iostream>

class SudokuBoard
{
	typedef unsigned short us;
	bool fixed[9][9];
	us numbers[9][9];
	bool columns[9][9];
	bool rows[9][9];
	bool boxes[3][3][9];
	void fill();
	bool inRange(us) const;				   // checks if number Є [0,8]
	bool isFree(us y, us x, us num) const; // check if num can be put on position x, y
	bool isFixed(us y, us x) const;		   // check if num can be put on position x, y
	void solveRec(us y, us x);
	void setNumber(us y, us x, us num, bool val);
	void print() const;
	bool solved = false;
	int solutions = 0;

public:
	SudokuBoard(const us[9][9]);
	void solve();
	void init(const us[9][9]);
	/*
	fixed = prefilled boxes, cannot be overriden
	numbers = the numbers on the board
	columns = flags for every column and every number between 1 and 9
	rows = flags for every row and every number between 1 and 9
	boxes = flags for every box and every number between 1 and 9
	 ------------------> x
	|
	|
	|
	|   Board orientation
	|
	|
	V
	y
	*/
};

void SudokuBoard::fill()
{
	for (size_t x = 0, y = 0; y < 9; x++, y += x / 9, x %= 9)
	{
		numbers[x][y] = 0;
		fixed[x][y] = columns[x][y] = rows[x][y] = boxes[x / 3][x % 3][y] = false;
	}
}

SudokuBoard::SudokuBoard(const us board[9][9])
{
	init(board);
}

void SudokuBoard::solve()
{
	if (solved)
	{
		std::cout << "Already solved. Initialise a new sudoku" << std::endl;
		return;
	}
	solveRec(0, 0);
	solved = true;
	if (solutions)
		std::cout << "Found " << solutions << " solution" << (solutions > 1 ? "s" : "") << std::endl;
	else
		std::cout << "No solutions" << std::endl;
}

void SudokuBoard::init(const us board[9][9])
{
	int z;
	fill();
	for (size_t x = 0, y = 0; y < 9; x++, y += x / 9, x %= 9)
	{
		z = board[y][x]; // z Є [1,9]
		if (!z)
			continue;
		z--; // z Є [0,8]
		if (!inRange(z))
		{
			std::cerr << " Invalid board. Invalid value on position x = " << x << " y= " << y << std::endl;
			throw;
		}
		if ((columns[x][z] || rows[y][z] || boxes[y / 3][x / 3][z]))
		{
			std::cerr << " Invalid board. Collision on  position x = " << x << " y= " << y << std::endl;
			throw;
		}
		fixed[y][x] = numbers[y][x] = z + 1;
		columns[x][z] = 1;
		rows[y][z] = 1;
		boxes[y / 3][x / 3][z] = 1;
	}
	solved = false;
	solutions = 0;
}

bool SudokuBoard::inRange(us num) const { return num >= 0 && num <= 8; }

void SudokuBoard::print() const
{
	for (size_t y = 0; y < 9; y++)
	{
		for (size_t x = 0; x < 9; x++)
			std::cout << numbers[y][x] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void SudokuBoard::solveRec(us y, us x)
{
	if (y == 9)
	{
		solutions++;
		return print();
	}
	if (isFixed(y, x)) // if a cell is fixed skip it
		return solveRec(y + ((x + 1) / 9), (x + 1) % 9);

	for (us i = 1; i <= 9; i++)
	{
		if (!isFree(y, x, i))
			continue;			  // check if i can be in the cell
		setNumber(y, x, i, true); // set it in the cell
		solveRec(y + ((x + 1) / 9), (x + 1) % 9);
		setNumber(y, x, i, false); // unset for the backtrack
	}
}

void SudokuBoard::setNumber(us y, us x, us num, bool val)
{
	numbers[y][x] = val ? num : 0;
	num--;
	columns[x][num] = val;
	rows[y][num] = val;
	boxes[y / 3][x / 3][num] = val;
}

bool SudokuBoard::isFree(us y, us x, us num) const
{
	return !(rows[y][num - 1] || columns[x][num - 1] || boxes[y / 3][x / 3][num - 1]);
}

bool SudokuBoard::isFixed(us y, us x) const
{
	return fixed[y][x];
}

int main()
{
	unsigned short example[9][9] = {
		{3, 0, 6, 5, 0, 8, 4, 0, 0},
		{5, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 8, 7, 0, 0, 0, 0, 3, 1},
		{0, 0, 3, 0, 1, 0, 0, 8, 0},
		{9, 0, 0, 8, 6, 3, 0, 0, 5},
		{0, 5, 0, 0, 9, 0, 6, 0, 0},
		{1, 3, 0, 0, 0, 0, 2, 5, 0},
		{0, 0, 0, 0, 0, 0, 0, 7, 4},
		{0, 0, 5, 2, 0, 6, 3, 0, 0}};
		
	unsigned short example2[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 0, 0},
		{6, 0, 0, 1, 9, 5, 0, 0, 0},
		{0, 9, 8, 0, 0, 0, 0, 6, 0},
		{8, 0, 0, 0, 6, 0, 0, 0, 3},
		{4, 0, 0, 8, 0, 3, 0, 0, 1},
		{7, 0, 0, 0, 2, 0, 0, 0, 6},
		{0, 6, 0, 0, 0, 0, 2, 8, 0},
		{0, 0, 0, 4, 1, 9, 0, 0, 5},
		{0, 0, 0, 0, 8, 0, 0, 7, 9}};
	SudokuBoard test(example);
	test.solve();
	test.init(example2);
	test.solve();
}
