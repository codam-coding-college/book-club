#pragma once

#include "Model.h"
#include <iostream>

//	This class is responsible for simply displaying the data of the model
class View : public Updateable
{
	public:
		//View();
		//~View();

		void	update(Model* model) override;

		void	displayModel(Model* model) const;
		void	displaySection(Model* model, uint x, uint y, uint w, uint h) const;

	private:
		struct ViewSettings
		{
			uint	width;
			uint	height;
			uint	x;
			uint	y;
		}	m_settings;

};
