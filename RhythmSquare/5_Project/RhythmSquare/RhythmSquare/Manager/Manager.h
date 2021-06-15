#pragma once

enum class eManagerType : unsigned int
{
	NONE = 0,
};

class Manager
{
public:
	Manager();
	virtual ~Manager();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Finalize();

protected:
	unsigned int Seed;
};

