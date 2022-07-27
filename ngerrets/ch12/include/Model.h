#pragma once

using uint = unsigned int;

class Model;

//	For anything that can be updated by the Model
class Updateable
{
	public:
		virtual void	update(Model* model) = 0;
};

//	In this case the model is a simple "2d" grid of characters
class Model
{
	public:
		Model(uint width, uint height, Updateable* updateable);
		~Model();

		inline uint	getWidth() const { return m_width; }
		inline uint	getHeight() const { return m_height; }

		char	getAt(uint x, uint y) const;
		void	setAt(uint x, uint y, char c);
		//	void	setUpdateCallbackFunction(UpdateCallbackF func);

	private:
		uint			m_width;
		uint			m_height;
		char*			m_grid;
		Updateable*		m_updateable;
	
	private:
		void	constructGrid();
		void	destroyGrid();

};
