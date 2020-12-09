#ifndef PLANE_H
#define PLANE_H

#include "GL/glew.h"

#include "../common/common.h"
#include <memory>
#include <vector>

class Plane {
public:
    Plane();
    void buildSurface(int param1, int param2, int param3,
        std::vector<Vertex>&, std::vector<Normal>&, std::vector<TextureCoord>&);
};

#endif // PLANE_H
