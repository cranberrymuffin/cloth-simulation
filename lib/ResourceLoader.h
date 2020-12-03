#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <exception>
#include <string>
#include <vector>
#include "GL/glew.h"

class SceneObject;
namespace CS123 {

class IOException : public std::exception {
public:
    IOException(const std::string &what) : message(what) {}
    virtual ~IOException() throw() {}
    virtual const char* what() const throw() override { return message.c_str(); }

private:
    std::string message;
};

}

class ResourceLoader
{
public:
    static std::string loadResourceFileToString(const std::string &resourcePath);

    static void readObjFile(std::vector<SceneObject*>&, const std::string& filename);
};

#endif // RESOURCELOADER_H
