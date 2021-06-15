#include "pchLib.h"
#include "TriangleVector.h"

TriangleVector::TriangleVector()
{
}

TriangleVector::TriangleVector(Vector2 left, Vector2 center, Vector2 right)
	:Left(left), Center(center), Right(right)
{
}

TriangleVector::~TriangleVector()
{
}
