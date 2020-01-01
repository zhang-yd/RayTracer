

#ifndef _OBJECT_HEAD_ 
#define _OBJECT_HEAD_ 

#include "vector.hpp"
#include "intersect.hpp" 
#include "material.hpp" 


class Object
{
public:
	enum class ObjectType
	{
		NONE = -1, 
		Sphere = 1, 
		Cube, 
	}; 

	Object(ObjectType obty): m_material(Material()), m_type(ObjectType::NONE) {}
	Object(const Material& m, const ObjectType obty): m_material(m), m_type(obty) {} 
	virtual ~Object() {} 

	virtual void intersect(Intersect& ites, const Ray& r) const = 0; 

protected:
	Material m_material; 
	ObjectType m_type; 
}; 


class Sphere: public Object
{	
public:
	Sphere(): Object(ObjectType::Sphere), m_pos(vec3f(0, 0,0)), m_radius(0) {}
	Sphere(const vec3f& p, const float& r, const Material& m): Object(m, ObjectType::Sphere), m_pos(p), m_radius(r) {}

	void intersect(Intersect& ites, const Ray& r) const override;

private:
	vec3f m_pos; 
	float m_radius; 
}; 




class Cube: public Object
{
public:
	Cube(): Object(ObjectType::Cube), m_min(vec3f(0, 0,0)), m_max(vec3f(0,0,0)) {}
	Cube(const vec3f& mi, const vec3f& mx, const Material& m): Object(m, ObjectType::Cube), m_min(mi), m_max(mx) {}

	void intersect(Intersect& ites, const Ray& r) const override;

private:
	vec3f m_min; 
	vec3f m_max;  
}; 



#endif // _OBJECT_HEAD_ 
