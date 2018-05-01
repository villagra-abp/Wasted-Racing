#pragma once

//=========================================================================
//                               INCLUDES                                //
//=========================================================================
#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>
#include <chrono>

#include <RedPanda.h>

//=========================================================================
//                        RED PANDA STUDIO CLASS                         //
//=========================================================================

namespace rps {

class RedPandaStudio{

public:

    RedPandaStudio() {}
    ~RedPandaStudio() {}

    //////////////////////////////
    //  DEVICE CONSTRUCTORS
    static RedPandaStudio& createDevice(int width, int height, int depth, int framerate, bool vsync, bool fullscreen);
    void updateDevice();
    void dropDevice();

    //////////////////////////////
    //  NODE CONSTRUCTORS

    //Creates an object and returns a TMesh
    TNode* createObjectNode(TNode* parent, glm::vec3 position, const char* mesh); 
    //Creates a camera and returns a TCamera
    TNode* createCamera(TNode* parent, glm::vec3 position, glm::vec3 target);
    //Creates a light and returns a TLight
    TNode* createLight(TNode* parent, glm::vec3 position, glm::vec3 intensity);
    //Creates an emitter and return a TEmitter
    TNode* createEmitter(TNode* parent, const char* shape, glm::vec3 nPosition, float nRadius, 
            int nBirthrate, float nParticleLife, glm::vec3 nBirthDirection, float nBirthSize, glm::vec4 nBirthColor);

    TNode* createEmitter(TNode* parent, const char* shape, glm::vec3 nPosition, float nRadius, int nBirthrate, float nParticleLife,
            glm::vec3 nBirthDirection, glm::vec3 nDeathDirection, float nVariationDirection, float nBirthSize, float nDeathSize, 
            float nVariationSize, glm::vec4 nBirthColor, glm::vec4 nDeathColor, float nVariationColor);
    //Deletes a mesh, camera or light, given a TMesh, TCamera or TLight
    void deleteObject(TNode* leaf);

    void updateCamera(glm::vec3 position, glm::vec3 target);

    void setGUIDrawFunction(void (*)());

    //////////////////////////////
    //  GETTERS
    SDL_Window* getWindow()               { return window;           }
    TNode* getSceneRoot()                 { return scene;            }
    ResourceManager* getResourceManager() { return resourceManager;  }
    SDL_GLContext* getContext()           { return context;          }  

    //////////////////////////////
    //  SETTERS
    void setWindow(SDL_Window* rw )   {   window = rw;    }   

private: 

    //////////////////////////////
    //  FUNCTIONS
    void initSDLWindow(int width, int height, int depth, int framerate, bool vsync, bool fullscreen);
    void initOpenGL();
    void initScene();
    void renderLights();
    void renderCamera();
    void renderParticles();
    void updateParticles();
    void calculateNodeTransform(TNode* node, glm::mat4& mat);  //Given a node, returns its accumulated transform. Should receive an identity as input
    TNode* addRotScaPos(TNode* parent, glm::vec3 position); //Returns the Position Node
    void deleteNode(TNode* node); //Deletes a node and all his children
    

    //////////////////////////////
    //  VARIABLES
    SDL_Window* window;
    SDL_GLContext* context;
    TNode *scene;
    ResourceManager *resourceManager;
    //Lights and camera and particles
    TNode *camera;
    std::vector<TNode*> lights;
    std::vector<TNode*> emitters;

    //Skybox
    TResourceSkybox*  skybox;
    //Skybox shader
    GLuint skyboxID;
    //SKybox vertex array
    GLuint skyVertexArray;

    //Particles
    GLuint particlesID;
    GLuint paticlesVertexArray;


    //Chrono
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    double fps = 0;
    bool firstUpdate = true;

    //Chrono flag
    bool showFPS = false;
    

};

//Transformation facade
//Input node has to be of type Mesh/Light/Camera
void translateNode(TNode* node, glm::vec3 position);
void rotateNode(TNode* node, glm::vec3 rotation);
void scaleNode(TNode* node, glm::vec3 scale);


}
