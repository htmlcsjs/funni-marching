#include "RenderingFunctions.hpp"

namespace helpers2D
{
    namespace RenderingFunctions
    {
        float circle(float x, float y, float size) 
        {
            float size_divisor = size*size;
            return (x*x) / size_divisor + (y*y) / size_divisor;
        }
    } // namespace RenderingFunctions
} // namespace helpers2D