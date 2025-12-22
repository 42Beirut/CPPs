#include <iostream>
#include "Point.hpp"

int main(void) {
    // Define a triangle
    Point a(0.0f, 0.0f);
    Point b(10.0f, 0.0f);
    Point c(5.0f, 10.0f);
    
    // Test points
    Point inside(5.0f, 5.0f);
    Point outside(15.0f, 5.0f);
    Point onVertex(0.0f, 0.0f);
    Point onEdge(5.0f, 0.0f);
    Point justInside(5.0f, 1.0f);
    
    std::cout << "Testing BSP (Binary Space Partitioning)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Triangle vertices:" << std::endl;
    std::cout << "  A: (" << a.getX() << ", " << a.getY() << ")" << std::endl;
    std::cout << "  B: (" << b.getX() << ", " << b.getY() << ")" << std::endl;
    std::cout << "  C: (" << c.getX() << ", " << c.getY() << ")" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Point (5, 5) is inside: " << (bsp(a, b, c, inside) ? "true" : "false") << std::endl;
    std::cout << "Point (15, 5) is inside: " << (bsp(a, b, c, outside) ? "true" : "false") << std::endl;
    std::cout << "Point (0, 0) [vertex] is inside: " << (bsp(a, b, c, onVertex) ? "true" : "false") << std::endl;
    std::cout << "Point (5, 0) [on edge] is inside: " << (bsp(a, b, c, onEdge) ? "true" : "false") << std::endl;
    std::cout << "Point (5, 1) [just inside] is inside: " << (bsp(a, b, c, justInside) ? "true" : "false") << std::endl;
    
    return 0;
}
