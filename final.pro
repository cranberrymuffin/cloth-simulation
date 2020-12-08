# -------------------------------------------------
# Project created by QtCreator 2010-08-22T14:12:19
# -------------------------------------------------
QT += opengl xml
TARGET = final
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += ui/mainwindow.cpp \
    camera/CamtransCamera.cpp \
    camera/OrbitingCamera.cpp \
    camera/QuaternionCamera.cpp \
    cloth/solver.cpp \
    cloth/state.cpp \
    gl/GLDebug.cpp \
    gl/datatype/FBO.cpp \
    gl/datatype/IBO.cpp \
    gl/datatype/VAO.cpp \
    gl/datatype/VBO.cpp \
    gl/datatype/VBOAttribMarker.cpp \
    gl/shaders/CS123Shader.cpp \
    gl/shaders/Shader.cpp \
    gl/textures/DepthBuffer.cpp \
    gl/textures/RenderBuffer.cpp \
    gl/textures/Texture.cpp \
    gl/textures/Texture2D.cpp \
    gl/textures/TextureParameters.cpp \
    gl/textures/TextureParametersBuilder.cpp \
    gl/util/FullScreenQuad.cpp \
    lib/CS123XmlSceneParser.cpp \
    lib/RGBA.cpp \
    lib/ResourceLoader.cpp \
    main.cpp \
    glew-1.10.0/src/glew.c \
    models/cube.cpp \
    particle/Particle.cpp \
    particle/particle.cpp \
    scenegraph/DynamicSceneObject.cpp \
    scenegraph/OpenGLScene.cpp \
    scenegraph/Scene.cpp \
    scenegraph/SceneObject.cpp \
    scenegraph/SceneObjectMaterial.cpp \
    scenegraph/SceneviewScene.cpp \
    scenegraph/Shapebuilder.cpp \
    shapes/Cap.cpp \
    shapes/Cloth.cpp \
    shapes/ClothParticle.cpp \
    shapes/Cone.cpp \
    shapes/Cylinder.cpp \
    shapes/LoadedShape.cpp \
    shapes/Plane.cpp \
    shapes/PlaneShape.cpp \
    shapes/Shape.cpp \
    shapes/Sphere.cpp \
    shapes/Surface.cpp \
    shapes/cubeshape.cpp \
    ui/Databinding.cpp \
    ui/Settings.cpp \
    ui/SupportCanvas3D.cpp \
    ui/view.cpp \
    ui/viewformat.cpp

HEADERS += ui/mainwindow.h \
    camera/Camera.h \
    camera/CamtransCamera.h \
    camera/OrbitingCamera.h \
    camera/QuaternionCamera.h \
    cloth/solver.h \
    cloth/state.h \
    common/common.h \
    gl/GLDebug.h \
    gl/datatype/FBO.h \
    gl/datatype/IBO.h \
    gl/datatype/VAO.h \
    gl/datatype/VBO.h \
    gl/datatype/VBOAttribMarker.h \
    gl/shaders/CS123Shader.h \
    gl/shaders/Shader.h \
    gl/shaders/ShaderAttribLocations.h \
    gl/textures/DepthBuffer.h \
    gl/textures/RenderBuffer.h \
    gl/textures/Texture.h \
    gl/textures/Texture2D.h \
    gl/textures/TextureParameters.h \
    gl/textures/TextureParametersBuilder.h \
    gl/util/FullScreenQuad.h \
    lib/CS123ISceneParser.h \
    lib/CS123SceneData.h \
    lib/CS123XmlSceneParser.h \
    lib/RGBA.h \
    lib/ResourceLoader.h \
    models/cube.h \
    particle/Particle.h \
    particle/particle.h \
    scenegraph/DynamicSceneObject.h \
    scenegraph/OpenGLScene.h \
    scenegraph/Scene.h \
    scenegraph/SceneObject.h \
    scenegraph/SceneObjectMaterial.h \
    scenegraph/SceneviewScene.h \
    scenegraph/Shapebuilder.h \
    shapes/Cap.h \
    shapes/Cloth.h \
    shapes/ClothParticle.h \
    shapes/Cone.h \
    shapes/Cylinder.h \
    shapes/LoadedShape.h \
    shapes/Plane.h \
    shapes/PlaneShape.h \
    shapes/Shape.h \
    shapes/Sphere.h \
    shapes/Surface.h \
    shapes/cubeshape.h \
    tinyobjloader/tiny_obj_loader.h \
    ui/Databinding.h \
    ui/Settings.h \
    ui/SupportCanvas3D.h \
    ui_mainwindow.h \
    glew-1.10.0/include/GL/glew.h \
    ui/view.h \
    ui/viewformat.h

FORMS += ui/mainwindow.ui
INCLUDEPATH += glm ui glew-1.10.0/include
DEPENDPATH += glm ui glew-1.10.0/include

DEFINES += _USE_MATH_DEFINES
DEFINES += TIXML_USE_STL
DEFINES += GLM_SWIZZLE GLM_FORCE_RADIANS
OTHER_FILES += shaders/shader.frag \
    shaders/shader.vert

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g
QMAKE_LFLAGS += -no-pie
QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

# QMAKE_CXX_FLAGS_WARN_ON += -Wunknown-pragmas -Wunused-function -Wmain

macx {
    QMAKE_CXXFLAGS_WARN_ON -= -Warray-bounds -Wc++0x-compat
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    resources/models/cornell_box.mtl \
    resources/models/cube.mtl \
    shaders/depth.frag \
    shaders/depth.vert \
    shaders/fullscreenquad/fullscreenquad.frag \
    shaders/fullscreenquad/fullscreenquad.vert \
    shaders/normals/normals.frag \
    shaders/normals/normals.gsh \
    shaders/normals/normals.vert \
    shaders/normals/normals.vert \
    shaders/normals/normals.frag \
    shaders/normals/normals.gsh \
    shaders/normals/normalsArrow.frag \
    shaders/normals/normalsArrow.gsh \
    shaders/normals/normalsArrow.gsh \
    shaders/normals/normalsArrow.frag \
    shaders/normals/normalsArrow.vert \
    shaders/normals/normalsArrow.vert \
    shaders/quad.frag \
    shaders/quad.vert \
    shaders/wireframe/wireframe.frag \
    shaders/wireframe/wireframe.vert
