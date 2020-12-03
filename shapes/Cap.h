#ifndef CAP_H
#define CAP_H

#include "Surface.h"

class Cap:public Surface
{
public:
    Cap();
   void buildSurface(int param1,int param2, int param3, std::vector<Vertex>&, std::vector<Normal>&, std::vector<TextureCoord>&);
};

#endif // CAP_H
