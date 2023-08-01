#include "ViewTransform.h"
#include "Transformations/Translation.h"
ViewTransform::ViewTransform(const Point& fromPoint, const Point& toPoint, const Vector& upVector)
	: Matrix(4, 4), from{fromPoint}, to{toPoint}, up{upVector}
{
	Vector forward = (to - from).normalizeVector();
	Vector left = forward.crossProduct(up.normalizeVector());
	Vector trueUp = left.crossProduct(forward);
	Matrix orientation({ {left.getX(), left.getY(), left.getZ(), 0}, {trueUp.getX(), trueUp.getY(), trueUp.getZ(), 0}, {-forward.getX(), -forward.getY(), -forward.getZ(), 0}, {0, 0, 0, 1} });
	this->setMatrix(orientation * Translation(-from.getX(), -from.getY(), -from.getZ()));
}

ViewTransform::ViewTransform(const ViewTransform& copyTransform)
	: Matrix(copyTransform), from{copyTransform.from}, to{copyTransform.to}, up{copyTransform.up}
{
}

ViewTransform::~ViewTransform()
{
}
