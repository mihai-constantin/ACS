// CONSTANTIN MIHAI - 336CA

#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include "Camera.h"

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

	Texture2D* CreateMap();


private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	std::unordered_map<std::string, Texture2D*> mapTextures;

	unsigned char* heightPixels;
	int width, height, channels;

	glm::vec3 lightPosition;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;

	// camera
	Mars::Camera* camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;

	bool isOrtographic = false;
	float fov = 60.f;

	bool pressC;

};
