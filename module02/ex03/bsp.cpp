#include "Point.hpp"

// Calculate the sign of the area of a triangle formed by three points
// This uses the cross product formula
static Fixed sign(Point const p1, Point const p2, Point const p3) {
    return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) - 
           (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
}

// Check if a point is inside a triangle using barycentric coordinates
// A point is inside a triangle if it has the same sign for all three sub-triangles
bool bsp(Point const a, Point const b, Point const c, Point const point) {
    Fixed d1, d2, d3;
    bool hasNeg, hasPos;
    
    d1 = sign(point, a, b);
    d2 = sign(point, b, c);
    d3 = sign(point, c, a);
    
    // If any of the distances is zero, the point is on an edge or vertex
    if (d1 == Fixed(0) || d2 == Fixed(0) || d3 == Fixed(0)) {
        return false;
    }
    
    hasNeg = (d1 < Fixed(0)) || (d2 < Fixed(0)) || (d3 < Fixed(0));
    hasPos = (d1 > Fixed(0)) || (d2 > Fixed(0)) || (d3 > Fixed(0));
    
    // Point is inside if all signs are the same (all positive or all negative)
    return !(hasNeg && hasPos);
}
