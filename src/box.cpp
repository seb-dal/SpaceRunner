#include <runner/include/box.hpp>

Box::Box() {
	pmin = Origin();
	pmax = Origin();
	T = Identity();
}



Box::Box(const Point& i_pmin, const Point& i_pmax) {
	pmin = i_pmin;
	pmax = i_pmax;
	T = Identity();
}



bool static collidesBox(const Box& A, const Box& B, const int i) {
	Vector v = B.T.inverse()(A.T(Vector(
		(i == 0) ? 1 : (i == 1) ? -1 : 0, // 0 = vector(1,0,0) | 1 = vector(-1,0,0) 
		(i == 2) ? 1 : (i == 3) ? -1 : 0,
		(i == 4) ? 1 : (i == 5) ? -1 : 0
	)));

	Point corner = A.T.inverse()(B.T(Point(
		((v.x <= 0) ? B.pmax.x : B.pmin.x),
		((v.y <= 0) ? B.pmax.y : B.pmin.y),
		((v.z <= 0) ? B.pmax.z : B.pmin.z)
	)));

	int id2 = i / 2;
	if (i % 2 == 0)
		return A.pmax(id2) <= corner(id2);
	else
		return A.pmin(id2) >= corner(id2);
}



bool Box::collides(const Box& rhs) {
	int i;
	for (i = 0; i < 6; i++)
		if (collidesBox(*this, rhs, i) || collidesBox(rhs, *this, i))
			return false;
	return true;
}


