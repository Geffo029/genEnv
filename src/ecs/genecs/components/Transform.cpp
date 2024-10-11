#include "Transform.h"
#include <iostream>



using namespace gen;


Transform::Transform(bool empty, float loc_x, float loc_y, float loc_z, float rot_x, float rot_y, float rot_z, float rot_w, float sc_x, float sc_y, float sc_z)
{
	// std::cout << "Transform CONSTRUCTOR called" << std::endl;
	this->empty = empty;
	location[0] = loc_x;
	location[1] = loc_y;
	location[2] = loc_z;
	rotation[0] = rot_x;
	rotation[1] = rot_y;
	rotation[2] = rot_z;
	rotation[3] = rot_w;
	scale[0] = sc_x;
	scale[1] = sc_y;
	scale[2] = sc_z;
}

// Transform::Transform(Transform &&other) {
// 	location[0] = other.location[0]; location[1] = other.location[1]; location[2] = other.location[2];
// 	rotation[0] = other.rotation[0]; rotation[1] = other.rotation[1]; rotation[2] = other.rotation[2]; rotation[3] = other.rotation[3];
// 	scale[0] = other.scale[0]; scale[1] = other.scale[1]; scale[2] = other.scale[2];
// }
void Transform::newFrom(Transform&& other)
{
	location[0] = other.location[0]; location[1] = other.location[1]; location[2] = other.location[2];
	rotation[0] = other.rotation[0]; rotation[1] = other.rotation[1]; rotation[2] = other.rotation[2]; rotation[3] = other.rotation[3];
	scale[0] = other.scale[0]; scale[1] = other.scale[1]; scale[2] = other.scale[2];
}

void Transform::copyFrom(std::unique_ptr<Transform> other)
{
	// location[0] = other->location[0]; location[1] = other->location[1]; location[2] = other->location[2];
	// rotation[0] = other.rotation[0]; rotation[1] = other.rotation[1]; rotation[2] = otherrotation[2]; rotation[3] = other.rotation[3];
	// scale[0] = other.scale[0]; scale[1] = other.scale[1]; scale[2] = other.scale[2];
	empty = other->empty;
	std::copy(other->location, (other->location)+3, location);
	std::copy(other->rotation, (other->rotation)+4, rotation);
	std::copy(other->scale, (other->scale)+3, scale);
}

void Transform::setLocation(float loc_x, float loc_y, float loc_z)
{
	location[0] = loc_x; location[1] = loc_y; location[2] = loc_z;
}

void Transform::setRotation(float rot_x, float rot_y, float rot_z, float rot_w)
{
	rotation[0] = rot_x; rotation[1] = rot_y; rotation[2] = rot_z; rotation[3] = rot_w;
}

void Transform::setScale(float sc_x, float sc_y, float sc_z)
{
	scale[0] = sc_x; scale[1] = sc_y; scale[2] = sc_z;
}

float* Transform::getLocation() { return location; }

float* Transform::getRotation() { return rotation; }

float* Transform::getScale() { return scale; }

bool Transform::isEmpty() { return empty; }


Transform::~Transform()
{
	// std::cout << "Transform DESTRUCTOR called" << std::endl;	
}
	
std::unique_ptr<Transform> Transform::newTransform()
{
	return std::make_unique<Transform>(false, 0,0,0, 0,0,0,1, 1,1,1);
}

std::unique_ptr<Transform> Transform::newTransform(float loc_x, float loc_y, float loc_z, float rot_x, float rot_y, float rot_z, float rot_w, float sc_x, float sc_y, float sc_z)
{
	return std::make_unique<Transform>(false, loc_x, loc_y, loc_z, rot_x, rot_y, rot_z, rot_w, sc_x, sc_y, sc_z);
}

Transform Transform::emptyTransform()
{
	Transform transform = Transform(true, 0,0,0, 0,0,0,0, 0,0,0);
	return transform;
}

