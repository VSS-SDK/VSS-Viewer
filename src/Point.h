/*
 * The MIT License
 *
 * Copyright (c) 2010 Paul Solt, PaulSolt@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef POINT_H
#define POINT_H

#include <string>
#include <math.h>
#include <stdio.h>

namespace glutFramework {

	template <class T>
	class Point {

public:

		T x;
		T y;
		T z;
		T w;

public:

		Point();
		Point( T x, T y, T z );
		Point( T x, T y, T z, T w );
		Point( const Point &other );
		Point& operator=( const Point &rhs );
		bool operator==( const Point<T> &other ) const;
		bool operator!=( const Point<T> &other ) const;
		T distance( const Point &other ) const;
		void transform( T matrix[4][4] );
		void setPoint( T x, T y, T z, T w );
		friend std::ostream & operator<<( std::ostream &os, const Point &point ) {
			return os << "Point: (" << point.x << ", " << point.y << ", " << point.z << ", " << point.w << ")";
		}
	};

	template <class T> Point<T>::Point() {
		setPoint( 0.0, 0.0, 0.0, 1.0 );
	}

	template <class T> Point<T>::Point( T x, T y, T z ) {
		setPoint( x, y, z, 1.0 );
	}

	template <class T> Point<T>::Point( T x, T y, T z, T w ) {
		setPoint( x, y, z, w );
	}

	template <class T> Point<T>::Point( const Point &other ) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	template <class T> Point<T>& Point<T>::operator=( const Point &rhs ) {
		// Check for self-assignment
		if (this == &rhs)
			return *this;  // skip and return this

		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;

		return *this;
	}

	template <class T> bool Point<T>::operator==( const Point<T> &other ) const {
		if( x == other.x && y == other.y && z == other.z && w == other.w ) {
			return true;
		}
		return false;
	}

	template <class T> bool Point<T>::operator!=( const Point<T> &other ) const {
		return !(*this == other);
	}

	/* Calculate the distance between this point and a given point */
	template <class T> T Point<T>::distance( const Point &other ) const {
		return sqrt( (other.x - x) * (other.x - x) +
		             (other.y - y) * (other.y - y) +
		             (other.z - z) * (other.z - z) );
	}

	/* Transform the point by a given amount (x,y,z). */
	template <class T> void Point<T>::transform( T matrix[4][4] ) {
		// Matrix multiplication
		T value[] = { 0, 0, 0, 1 };
		value[0] = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3] * w;
		value[1] = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3] * w;
		value[2] = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3] * w;

		x = value[0];
		y = value[1];
		z = value[2];
		w = 1.0;
	}

	/* Set the point to a new position */
	template <class T> void Point<T>::setPoint( T x, T y, T z, T w ) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

} // namespace

#endif
