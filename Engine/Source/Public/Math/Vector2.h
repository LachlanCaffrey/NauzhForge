#pragma once

struct Vector2 {
	// Simple constructor
	Vector2() : x(0.0f), y(0.0f) {}

	// Assigned constructor
	Vector2(float x, float y) : x(x), y(y) {}

	// Uniform constructor
	Vector2(float uniform) : x(uniform), y(uniform) {}

	~Vector2() = default;

	// OPERATORS

	// Vector2 assignment operator
	Vector2& operator=(const Vector2& Other) {
		x = Other.x;
		y = Other.y;

		return *this;
	}

	// Boolean operators
	// if 2 Vector2s are euqual
	bool operator==(const Vector2& Other) const {
		return x == Other.x && y == Other.y;
	}

	// if 2 Vector2s are not equal
	bool operator!=(const Vector2& Other) const {
		return x != Other.x || y != Other.y;
	}
	
	// Arithmetic operators
	// Addition Vector2
	Vector2 operator+(const Vector2& Other) const {
		return Vector2(Other.x + x, Other.y + y);
	}

	// Addition equals
	// "*this" is essentially "Vector2(x,y)"
	Vector2& operator+=(const Vector2& Other) {
		return *this = *this + Other;
	}

	// Subtrtact Vector2
	Vector2 operator-(const Vector2& Other) const {
		return Vector2(x - Other.x, y - Other.y);
	}

	// Subtract equals
	Vector2& operator-= (const Vector2 & Other){
		return *this = *this - Other;
	}

	// Multiplication
	// Multiply Vector2 by Vector2
	Vector2 operator*(const Vector2& Other) const {
		return Vector2(x * Other.x, y * Other.y);
	}

	// Multiply equals Vector2 by Vector2
	Vector2& operator*=(const Vector2& Other) {
		return *this = *this * Other;
	}

	// Multiply Vector2 by float
	Vector2 operator*(const float& Scalar) const {
		return Vector2(x * Scalar, y * Scalar);
	}

	// Multiply equals Vector2 by float
	Vector2& operator*=(const float& Scalar) {
		return *this = *this * Scalar;
	}

	// Division Vector2
	Vector2 operator/(const Vector2& Other) const;

	// Division equals
	Vector2 operator/=(const Vector2& Other);

	// Division float
	Vector2 operator/(const float& Scalar) const;

	// Division equals float
	Vector2 operator/=(const float& Scalar);

	// Return an infinite negative vector
	// otherwise known as an invalid vector
	static Vector2 NaN();

	// Get the squared length/magnitude/size of the Vector2
	// this is inaccurate by double the size but cheaper
	float LengthSqd() const {
		return x * x + y * y;
	}

	// Get the legnth/magnitude/size of the Vector2
	float Length() const;

	// Get the distance between 2 Vector2s
	// this in inaccurate by double the size but cheaper
	static float DistSqd(Vector2& V1, Vector2& V2) {
		Vector2 DistanceVectror(V1 - V2);

		// x2 + y2
		return DistanceVectror.x * DistanceVectror.x + DistanceVectror.y * DistanceVectror.y;
	}

	// Get the distance between 2 Vector2s
	static float Distance(Vector2& V1, Vector2& V2);

	// Change the vector2 to a normalised value
	Vector2& Normalise();

	// Return a normalised vector based on another vector
	static Vector2 Normalised(const Vector2& Other);

	// Log the Vector2 to the console
	void Log();

	// Log the length of the Vector2 to the console
	void LogLength();

	float x, y;
};