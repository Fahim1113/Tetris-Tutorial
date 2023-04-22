#include "Board.h"
#include <assert.h>

Board::Cell::Cell()
	:bExists(false),
	c(WHITE)
{
}

void Board::Cell::SetColor(Color c_in)
{
	c = c_in;
	bExists = true;
}

void Board::Cell::Remove()
{
	bExists = false;
}

Color Board::Cell::GetColor() const
{
	return c;
}

Board::Board(Vec2<int> screenPos, Vec2<int> widthHeight, int cellSize_in, int padding)
	:
	screenPos(screenPos),
	width(widthHeight.GetX()),
	height(widthHeight.GetY()),
	cellSize(cellSize_in),
	padding(padding)
{
	assert(width > 0 && height > 0);
	assert(cellSize > 0);
	cells.resize(width * height);
}

void Board::SetCell(Vec2<int> pos, Color c)
{
	assert(pos.GetX() >= 0 && pos.GetY() >= 0 && pos.GetX() < width && pos.GetY() < height);
	cells[pos.GetY() * width + pos.GetX()].SetColor(c);
}

void Board::DrawCell(Vec2<int> pos) const
{
	assert(pos.GetX() >= 0 && y >= 0 && pos.GetX() < width && y < height);
	Color c = cells[pos.GetY() * width + pos.GetX()].GetColor();
	Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
	raycpp::DrawRectangle(topLeft, Vec2{cellSize, cellSize} - padding, c);
}

void Board::DrawBorder() const
{
	raycpp::DrawRectangleLinesEx(screenPos - (cellSize / 2),
								 Vec2{ width * cellSize, height * cellSize } + cellSize,
								 cellSize/2,
								 WHITE);
}

void Board::Draw() const
{
	for (int iY = 0; iY < height; ++iY)
	{
		for (int iX = 0; iX < width; ++iX)
		{
			DrawCell({ iX, iY });
		}

	}
	DrawBorder();
}
