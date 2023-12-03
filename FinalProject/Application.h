#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Shader.h"
#include "Texture.h"

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader;
	Texture *cubeDiffTex, *cubeSpecTex, *floorDiffTex, * bedDiffTex, * pillowDiffTex, * bed2DiffTex, * steelDiffTex, * steelDiffTex2, * blackDiffTex, * wallDiffTex;
	Cube *wood, *floor, * bed, *pillow, * bed2, * steel, * steel2, * black, * wall1, * wall2, * wall3;
	float angle = 0;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	glm::vec3 viewPos;
	void setupPerspective();
	void setupCamera();
	void setupLighting(); 
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void MoveCameraUp(float speed);
	void MoveCameraDown(float speed);
	void InitCamera();
};

