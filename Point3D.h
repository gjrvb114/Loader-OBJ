#pragma once

#include "includes.h"

class Point3D
{
    public:
        Point3D();
        Point3D(const GLdouble& _x, const GLdouble& _y, const GLdouble& _z);
        Point3D(const Point3D& p);
        Point3D(std::ifstream& fichier);
        Point3D minimum(const Point3D& p) const;
        Point3D maximum(const Point3D& p) const;
        GLdouble getx() const{return x;}
        GLdouble gety() const{return y;}
        GLdouble getz() const{return z;}
        void operator-=(const Point3D& p);
        void operator+=(const Point3D& p);
        void operator/=(const GLdouble& f);
        void operator*=(const GLdouble& f);
        GLdouble maxi() const;
        GLdouble mini() const;
        void afficher(std::ostream& stream) const;
    private:
        GLdouble x;
        GLdouble y;
        GLdouble z;
};

Point3D operator-(const Point3D& p1, const Point3D& p2);
Point3D operator+(const Point3D& p1, const Point3D& p2);
Point3D operator/(const Point3D& p, const GLdouble& f);
Point3D operator*(const Point3D& p, const GLdouble& f);

std::ostream& operator<<(std::ostream& stream, const Point3D& p);


