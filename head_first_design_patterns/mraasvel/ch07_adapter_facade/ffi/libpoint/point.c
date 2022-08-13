typedef struct Point Point;

struct Point {
	int x;
	int y;
};

Point add_point(Point a, Point b) {
	return (Point) {
		x: a.x + b.x,
		y: a.y + b.y,
	};
}
