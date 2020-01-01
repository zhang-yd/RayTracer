
#ifndef _VECTOR_HEAD_ 
#define _VECTOR_HEAD_ 

#include "global.hpp" 

#include <iostream> 
#include <cmath> 



template <typename T>
class Vector2
{
public:
	explicit Vector2():x(0), y(0) {}
	explicit Vector2(const T& t):x(t), y(t) {}
	explicit Vector2(const T& x_, const T& y_): x(x_), y(y_) {}

	Vector2<T>& operator=(const Vector2<T>& t)
	{
		x = t.x; y = t.y; 
		return *this; 
	}

	bool operator==(const Vector2<T>& t)
	{
		return (fabs(x - t.x) < POSITIVE_FLOAT_ZERO && fabs(y - t.y) < POSITIVE_FLOAT_ZERO); 
	}
	bool operator!=(const Vector2<T>& t)
	{
		return !(operator==(t)); 
	}

	Vector2<T> operator+(const Vector2<T>& t)
	{
		Vector2<T> r; 
		r.x = x + t.x;
		r.y = y + t.y; 
		return r; 
	}
	Vector2<T> operator-(const Vector2<T>& t)
	{
		Vector2<T> r; 
		r.x = x - t.x; 
		r.y = y - t.y; 
		return r; 
	}

	Vector2<T>& operator+=(const Vector2<T>& t)
	{
		x += t.x;  y += t.y; 
		return *this; 
	}
	Vector2<T>& operator-=(const Vector2<T>& t)
	{
		x -= t.x; y -= t.y; 
		return *this; 
	}

public:
	T x, y; 
}; 


typedef Vector2<float> vec2f; 






template <typename T>
class Vector3
{
public:
	explicit Vector3():x(0), y(0),z(0) {}
	explicit Vector3(const T& t):x(t), y(t), z(t) {}
	explicit Vector3(const T& x_, const T& y_, const T& z_): x(x_), y(y_), z(z_) {}

	Vector3<T>& operator=(const Vector3<T>& t)
	{
		x = t.x; y = t.y; z = t.z; 
		return *this; 
	}
	bool operator==(const Vector3<T>& t) const 
	{
		return (fabs(x - t.x) < POSITIVE_FLOAT_ZERO && fabs(y - t.y) < POSITIVE_FLOAT_ZERO
			&& fabs(z - t.z) < POSITIVE_FLOAT_ZERO); 
	}
	bool operator!=(const Vector3<T>& t) const 
	{
		return !(operator==(t)); 
	}

	Vector3<T> operator+(const Vector3<T>& t) const 
	{
		Vector3<T> r; 
		r.x = x + t.x; 
		r.y = y + t.y; 
		r.z = z + t.z; 
		return r; 
	}

	Vector3<T>& operator+=(const Vector3<T>& t)
	{
		x += t.x; 
		y += t.y; 
		z += t.z; 
		return *this; 
	}

	Vector3<T> operator-(const Vector3<T>& t) const 
	{
		Vector3<T> r; 
		r.x = x - t.x; 
		r.y = y - t.y; 
		r.z = z - t.z; 
		return r; 
	}
	Vector3<T>& operator-=(const Vector3<T>& t)
	{
		x -= t.x; 
		y -= t.y; 
		z -= t.z; 
		return *this; 
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& t)
	{
		return os << "v3(" << t.x << "," << t.y << "," << t.z << ")"; 
	}

public:
	T x, y, z; 
}; 


typedef Vector3<int> vec3i; 
typedef Vector3<float> vec3f; 


template <typename T, typename U>
Vector3<T> operator*(const Vector3<T>& vt, const U& v)
{
	Vector3<T> r; 
	r.x = static_cast<T>(vt.x * v);
	r.y = static_cast<T>(vt.y * v); 
	r.z = static_cast<T>(vt.z * v); 
	return r;  
}


template <typename T>
Vector3<T> operator-(const Vector3<T>& vt)
{
	return vt * (-1.0f); 
}


template <typename T>
inline Vector3<T>
cross(const Vector3<T>& a, const Vector3<T>& b)
{
	Vector3<T> r; 
	r.x = a.y * b.z - a.z * b.y; 
	r.y = a.z * b.x - a.x * b.z; 
	r.z = a.x * b.y - a.y * b.x; 
	return r; 
}

template <typename T>
inline T 
dot(const Vector3<T>& a, const Vector3<T>& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z; 
}

template <typename T>
inline Vector3<T> 
normal(const Vector3<T>& t)
{
	float tt = sqrt(t.x*t.x + t.y*t.y + t.z*t.z); 
	if(tt < POSITIVE_FLOAT_ZERO)
	{
		return t;
	}
	Vector3<T> r(t.x / tt, t.y / tt, t.z / tt); 
	return r; 
}


template <typename T>
inline float 
norm(const Vector3<T>& t)
{
	float r = sqrt(1.0*t.x*t.x + 1.0*t.y*t.y + 1.0*t.z*t.z); 
	return r; 
}


template <typename T>
inline Vector3<T> 
multi(const Vector3<T>& a, const Vector3<T>& b)
{
	return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z); 
}




#endif  // _VECTOR_HEAD_ 

