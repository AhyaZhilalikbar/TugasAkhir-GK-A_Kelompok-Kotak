#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	GLuint shaderProgram, VBO, VAO, EBO, texture, VBO2, VAO2, EBO2, texture2;
	GLuint pintuLemariVBO, pintuLemariVAO, pintuLemariEBO, pintuLemariTexture;
	GLuint lantaiVBO, lantaiVAO, lantaiEBO, lantaiTexture;
	GLuint tembokVBO, tembokVAO, tembokEBO, tembokTexture;
	GLuint tidurVBO, tidurVAO, tidurEBO, tidurTexture;
	GLuint kabinetVBO, kabinetVAO, kabinetEBO, kabinetTexture;
	GLuint pintuKabinetVBO, pintuKabinetVAO, pintuKabinetEBO, pintuKabinetTexture;
	GLuint papantidurVBO, papantidurVAO, papantidurEBO, papantidurTexture;
	GLuint papantidur2VBO, papantidur2VAO, papantidur2EBO, papantidur2Texture;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	//Kasur
	void Buildpapantidur();
	void Buildpapantidur2();
	void Buildtidur();
	void Drawpapantidur();
	void Drawpapantidur2();
	void Drawtidur();
	//Kabinet
	void BuildKabinet();
	void BuildPintuKabinet();
	void DrawPintuKabinet();
	void DrawKabinet();
	//tembok
	void Buildtembok();
	void Drawtembok();
	//Lemari
	void BuildLemari();
	void DrawLemari();
	void BuildPintuLemari();
	void DrawPintuLemari();
	void BuildColoredPlane();
	void DrawColoredPlane();
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
};