#pragma once


class BoxObject
{
public:
	BoxObject();
	BoxObject(float left, float top, float right, float bottom);
	~BoxObject();

	void Draw();
	void CollisionCheck(BoxObject other);


private:
	Vector2 m_Position;
	Vector2 m_V1, m_V2, m_V3, m_V4;

	BoxCollision m_BoxCol;

	bool m_Collision;
};

