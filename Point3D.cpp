#include "Point3D.h"

Point3D::Point3D(): x(0), y(0), z(0)
{
}

Point3D::Point3D(const GLdouble& _x, const GLdouble& _y, const GLdouble& _z):
    x(_x), y(_y), z(_z)
{
}

Point3D::Point3D(std::ifstream* fichier)
{
    *fichier >> x >> y >> z;
}

Point3D::Point3D(const Point3D& p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

Point3D Point3D::minimum(const Point3D& p) const
{
    Point3D out(p);
    if(x<p.x)
    {
        out.x = x;
    }
    if(y<p.y)
    {
        out.y = y;
    }
    if(z<p.z)
    {
        out.z = z;
    }
    return out;
}

Point3D Point3D::maximum(const Point3D& p) const
{
    Point3D out(p);
    if(x>p.x)
    {
        out.x = x;
    }
    if(y>p.y)
    {
        out.y = y;
    }
    if(z>p.z)
    {
        out.z = z;
    }
    return out;
}

 GLdouble Point3D::maxi() const
 {
     GLdouble out;
     if(x>=y && x>=z)
     {
         out = x;
     }
     else if(y>=x && y>=z)
     {
         out = y;
     }
     else
     {
         out = z;
     }
     return out;
 }

 GLdouble Point3D::mini() const
 {
     GLdouble out;
     if(x<=y && x<=z)
     {
         out = x;
     }
     else if(y<=x && y<=z)
     {
         out = y;
     }
     else
     {
         out = z;
     }
     return out;
 }

void Point3D::operator-=(const Point3D& p)
{
    x-=p.x;
    y-=p.y;
    z-=p.z;
}
void Point3D::operator+=(const Point3D& p)
{
    x+=p.x;
    y+=p.y;
    z+=p.z;
}

void Point3D::operator/=(const GLdouble& f)
{
    x/=f;
    y/=f;
    z/=f;
}

void Point3D::operator*=(const GLdouble& f)
{
    x*=f;
    y*=f;
    z*=f;
}

Point3D operator-(const Point3D& p1, const Point3D& p2)
{
    Point3D out(p1);
    out-=p2;
    return out;
}

Point3D operator+(const Point3D& p1, const Point3D& p2)
{
    Point3D out(p1);
    out+=p2;
    return out;
}

Point3D operator/(const Point3D& p, const GLdouble& f)
{
    Point3D out(p);
    out /= f;
    return out;
}

Point3D operator*(const Point3D& p, const GLdouble& f)
{
    Point3D out(p);
    out *= f;
    return out;
}

void Point3D::afficher(std::ostream& stream) const
{
    stream << x << ";" << y << ";" << z << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Point3D& p)
{
    p.afficher(stream);
    return stream;
}
