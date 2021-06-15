#pragma once
#include <string>
#include "../Transform/Transform.h"

class GameObject : public Transform
{
public:
	GameObject();
	GameObject(unsigned int id, Vector2 vec);
	GameObject(unsigned int id, unsigned int layer, Vector2 vec);
	GameObject(std::string name, unsigned int id, unsigned int layer, Vector2 vec);
	virtual ~GameObject();

public:
	Vector2 GetPosition() const { return World_Position; }
	Vector2 GetScale() const { return Scale; }
	float GetRotation() const { return Rotation; }
	std::string GetName() const { return Name; }
	unsigned int GetID() const { return ID; }
	unsigned int GetLayer() const { return Layer; }

	void SetPositionW(Vector2 val) { World_Position = val; }
	void SetPositionW(float x, float y) { World_Position.x = x; World_Position.y = y; }
	void AddPositionW(Vector2 vec) { World_Position.x += vec.x; World_Position.y += vec.y; }
	void SetRotation(float rotation) { Rotation = rotation; }
	void SetScale(Vector2 scale) { Scale = scale; }
	void SetID(unsigned int id) { ID = id; }
	void SetLayer(unsigned int layer) { Layer = layer; }

	virtual void Update();

protected:
	std::string Name;
	unsigned int ID;
	unsigned int Layer;

	// 좌표
	Vector2 World_Position;
	// 크기
	Vector2 Scale;
	// 회전 값
	float Rotation;

};

