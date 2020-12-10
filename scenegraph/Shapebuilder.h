#ifndef SHAPEBUILDER_H
#define SHAPEBUILDER_H

#include <lib/CS123SceneData.h>
#include <map>
#include <memory>

// Singlenton implementation
// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289

class Shape;

class ShapeBuilder {
public:
    static ShapeBuilder& getInstance()
    {
        static ShapeBuilder instance;
        return instance;
    };

private:
    ShapeBuilder() { }
    std::map<std::string, Shape*> m_shapes;

public:
    ShapeBuilder(ShapeBuilder const&) = delete;
    void operator=(ShapeBuilder const&) = delete;
    ~ShapeBuilder();
    Shape* LoadShape(PrimitiveType type, int param1, int param2);
    void setMeshLoadedShape(std::string& filename, Shape*);
    Shape* getMeshLoadedShape(std::string& filename);
};

#endif // SHAPEBUILDER_H
