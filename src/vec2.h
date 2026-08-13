#pragma once

template <typename A> class vec2 
{
    private:
	A x;
	A y;

    public:
	vec2() : x(0.0), y(0.0) {}
	vec2(A x0, A y0) : x(x0), y(y0) {}
	A X() {return x;}
	A Y() {return y;}

	A dot(const vec2& other)
	{
	    return x*other.x + y*other.y;
	}

	vec2 operator+(const vec2& other)
	{
	    return vec2(x + other.x, y + other.y);
	}

	vec2 operator-(const vec2& other)
	{
	    return vec2(x - other.x, y - other.y);
	}

	vec2 operator/(const A& p)
	{
	    return vec2(x/p, y/p);
	}

	vec2 operator*(const A& p)
	{
	    return vec2(x*p, y*p);
	}

	vec2& operator+=(const vec2& other)
	{
	    x+=other.x;
	    y+=other.y;
	    return *this;
	}

	vec2& operator-=(const vec2& other)
	{
	    x-=other.x;
	    y-=other.y;
	    return *this;
	}

	A mag()
	{
	    return x*x + y*y;
	}

};
