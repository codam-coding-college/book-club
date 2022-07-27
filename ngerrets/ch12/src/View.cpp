#include "View.h"

void	View::displayModel(Model* model) const
{
	for (uint y = 0; y < model->getHeight(); y++)
	{
		for (uint x = 0; x < model->getWidth(); x++)
		{
			std::cout << "  " << model->getAt(x, y) << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void	View::update(Model* model)
{
	displayModel(model);
}
