#include "Model.h"
#include "View.h"
#include <functional>

int	main(void)
{
	//	Create a view
	View	view;

	//	Create a model with the instance to be updated on update
	Model	model(10, 10, &view);

	//	Initial draw of grid
	view.displayModel(&model);

	//	Set pos (9, 9) to 'A' which triggers an update callback
	model.setAt(9, 9, 'A');

	return (0);
}
