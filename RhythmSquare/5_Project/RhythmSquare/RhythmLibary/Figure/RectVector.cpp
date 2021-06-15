#include "pchLib.h"
#include "RectVector.h"

RectVector::RectVector()
{
}

RectVector::RectVector(Vector2 lt, Vector2 rt, Vector2 lb, Vector2 rb)
	:LeftTop(lt), RightTop(rt), LeftBottom(lb), RightBottom(rb)
{
}

RectVector::~RectVector()
{
}
