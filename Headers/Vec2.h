#pragma once
#include <iostream>

template <class T>
class Vec2 {
public:
	T x, y;
	Vec2(T xx, T yy) : x(xx), y(yy) {}
	Vec2() : x(0), y(0) {}

	// equation math operators
	Vec2<T> operator+(const Vec2<T>& other) {
		return Vec2<T>(x + other.x, y + other.y);
	}
	Vec2<T> operator-(const Vec2<T>& other) {
		return Vec2<T>(x - other.x, y - other.y);
	}
	Vec2<T> operator*(const Vec2<T>& other) {
		return Vec2<T>(x*other.x, y*other.y);
	}
	Vec2<T> operator/(const Vec2<T>& other) {
		return Vec2<T>(x / other.x, y / other.y);
	}

	// single math operators
	void operator+=(const Vec2<T>& other) {
		x += other.x;
		y += other.y;
	}
	void operator-=(const Vec2<T>& other) {
		x -= other.x;
	    y -= other.y;
	}
	void operator*=(const Vec2<T>& other) {
		x *= other.x;
		y *= other.y;
	}
	void operator/=(const Vec2<T>& other) {
		x /= other.x;
		y /= other.y;
	}

	//equality operators
	bool operator==(const Vec2<T>& other) {
		return (x == other.x && y == other.y);
	}
	bool operator!=(const Vec2<T>& other) {
		return !(x == other.x && y == other.y);
	}


};

template<class T>
std::ostream& operator<<(std::ostream& os, Vec2<T>& vector) {
	os << "Vec2(" << vector.x << ", " << vector.y << ")";
}
