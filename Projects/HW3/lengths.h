#pragma once

#include <iostream>

// Alex Chapman ECE 309 HW3

class Centimeter;  // forward declaration

/* Complete the following implementation to work with the test cases */

class Inch {
public:
    // Construct object from double
    explicit Inch(double v = 0.0);

    // Conversion constructor from Centimeter
    explicit Inch(const Centimeter& cm);

    // return value in inches
    double in() const;

    // Add support for operators (used non-member application)

private:
    double value;  // inches
};

class Centimeter {
public:
    // Construct object from double
    explicit Centimeter(double v = 0.0);

    // Conversion constructor from Inch
    explicit Centimeter(const Inch& in);

    // return value in centimeters
    double cm() const;

    // Add support for operators (used non-member application)

private:
    double value;  // centimeters
};

// ******************** Member function definitions ********************

// Inch Members
inline Inch::Inch(double v)
{
    value = v;
}
inline Inch::Inch(const Centimeter& cm)
{
    value = cm.cm() / 2.54;
}
inline double Inch::in() const
{
    return value;
}

// Centimeter Members
inline Centimeter::Centimeter(double v)
{
    value = v;
}
inline Centimeter::Centimeter(const Inch& in)
{
    value = in.in() * 2.54;
}
inline double Centimeter::cm() const
{
    return value;
}

// ******************** Non-member operators ********************


// ***** Addition & Subtraction *****

// Same unit Operators
inline Inch operator+(const Inch& a, const Inch& b)
{
    return Inch(a.in() + b.in());
}

inline Inch operator-(const Inch& a, const Inch& b)
{
    return Inch(a.in() - b.in());
}



inline Centimeter operator+(const Centimeter& a, const Centimeter& b)
{
    return Centimeter(a.cm() + b.cm());
}

inline Centimeter operator-(const Centimeter& a, const Centimeter& b)
{
    return Centimeter(a.cm() - b.cm());
}



// Mixed unit operators
inline Inch operator+(const Inch& a, const Centimeter& b)
{
    return Inch(a.in() + Inch(b).in());
}

inline Inch operator-(const Inch& a, const Centimeter& b)
{
    return Inch(a.in() - Inch(b).in());
}



inline Centimeter operator+(const Centimeter& a, const Inch& b)
{
    return Centimeter(a.cm() + Centimeter(b).cm());
}
inline Centimeter operator-(const Centimeter& a, const Inch& b)
{
    return Centimeter(a.cm() - Centimeter(b).cm());
}



// ***** Scalar Multiplication *****
// Inch
inline Inch operator*(const Inch& a, double s)
{
    return Inch(a.in() * s);
}

inline Inch operator*(double s, const Inch& a)
{
    return Inch(a.in() * s);
}



// Centimeter
inline Centimeter operator*(const Centimeter& a, double s)
{
    return Centimeter(a.cm() * s);
}

inline Centimeter operator*(double s, const Centimeter& a)
{
    return Centimeter(a.cm() * s);
}

// ***** Scalar Division *****
// Inch
inline Inch operator/(const Inch& a, double s)
{
    return Inch(a.in() / s);
}

// Centimeter
inline Centimeter operator/(const Centimeter& a, double s)
{
    return Centimeter(a.cm() / s);
}
