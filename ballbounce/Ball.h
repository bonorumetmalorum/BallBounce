#pragma once
#include "Entity.h"
#include "tiny_obj_loader.h"

class Ball :
	public Entity
{
public:
	Ball();
	~Ball();

	void draw();

private:
	float radius;
	tinyobj::attrib_t atributes;

};

