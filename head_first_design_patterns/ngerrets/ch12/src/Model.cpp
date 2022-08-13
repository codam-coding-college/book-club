#include "Model.h"

Model::Model(uint width, uint height, Updateable* updateable)
: m_width(width), m_height(height), m_updateable(updateable)
{
	constructGrid();
}

Model::~Model()
{
	destroyGrid();
}

void	Model::constructGrid()
{
	m_grid = new char[m_height * m_width];
	//	Init to printable 0's
	for (uint i = 0; i < m_height * m_width; i++)
		m_grid[i] = '0';
}

void	Model::destroyGrid()
{
	delete m_grid;
}

char	Model::getAt(uint x, uint y) const
{
	if (x >= m_width || y >= m_height)
		return (0);
	return m_grid[y * m_width + x];
}

void	Model::setAt(uint x, uint y, char c)
{
	if (x >= m_width || y >= m_height)
		return ;
	m_grid[y * m_width + x] = c;
	if (m_updateable)
		m_updateable->update(this);
}
