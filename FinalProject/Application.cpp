#include "Application.h"

Application::Application()
{

}

Application::~Application()
{
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
}

void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	viewPos = glm::vec3(0, 2, 7);
	glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3( 0, 1, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);
}

void Application::Init()
{
	// Build a lighting map shader
	shader = new Shader("texturedCube.vert", "texturedCube.frag");
	shader->Init();

	// Create cube diffuse texture and specular texture
	cubeDiffTex = new Texture("Wood030_1K-PNG_Color.png");
	cubeDiffTex->Init();
	cubeSpecTex = new Texture("");
	cubeSpecTex->Init();
	// Create instance of cube
	wood = new Cube(shader, cubeDiffTex, cubeSpecTex);
	wood->Init();
	wood->SetScale(0.2f, 0.2f, 0.2f);

	// Create floor diffuse texture and specular texture
	floorDiffTex = new Texture("Tiles040.png");
	floorDiffTex->Init();
	// Create instance of floor
	floor = new Cube(shader, floorDiffTex, cubeSpecTex);
	floor->Init();
	floor->SetScale(2.0f, 0.2f, 2.0f);

	// Create bed diffuse texture and specular texture
	bedDiffTex = new Texture("Fabric040_1K-PNG_Color.png");
	bedDiffTex->Init();
	// Create instance of bed
	bed = new Cube(shader, bedDiffTex, cubeSpecTex);
	bed->Init();
	bed->SetScale(0.2f, 0.2f, 0.2f);

	// Create bed2 diffuse texture and specular texture
	bed2DiffTex = new Texture("blue.png");
	bed2DiffTex->Init();
	// Create instance of bed
	bed2 = new Cube(shader, bed2DiffTex, cubeSpecTex);
	bed2->Init();
	bed2->SetScale(0.2f, 0.2f, 0.2f);

	// Create steel diffuse texture and specular texture
	steelDiffTex = new Texture("steel.png");
	steelDiffTex->Init();
	// Create instance of bed
	steel = new Cube(shader, steelDiffTex, cubeSpecTex);
	steel->Init();
	steel->SetScale(0.2f, 0.2f, 0.2f);

	// Create steel2 diffuse texture and specular texture
	steelDiffTex2 = new Texture("steel2.png");
	steelDiffTex2->Init();
	// Create instance of bed
	steel2 = new Cube(shader, steelDiffTex2, cubeSpecTex);
	steel2->Init();
	steel2->SetScale(0.2f, 0.2f, 0.2f);

	// Create pillow diffuse texture and specular texture
	pillowDiffTex = new Texture("bantal.png");
	pillowDiffTex->Init();
	// Create instance of pillow
	pillow = new Cube(shader, pillowDiffTex, cubeSpecTex);
	pillow->Init();
	pillow->SetScale(0.2f, 0.2f, 0.2f);

	// Create black diffuse texture and specular texture
	blackDiffTex = new Texture("black.png");
	blackDiffTex->Init();
	// Create instance of black
	black = new Cube(shader, blackDiffTex, cubeSpecTex);
	black->Init();
	black->SetScale(0.2f, 0.2f, 0.2f);

	// Create wall diffuse texture and specular texture
	wallDiffTex = new Texture("wall.png");
	wallDiffTex->Init();
	// Create instance of black
	wall1 = new Cube(shader, wallDiffTex, cubeSpecTex);
	wall1->Init();
	wall1->SetScale(0.2f, 2.0f, 2.0f);

	wall2 = new Cube(shader, wallDiffTex, cubeSpecTex);
	wall2->Init();
	wall2->SetScale(2.0f, 2.0f, 0.2f);

	wall3 = new Cube(shader, wallDiffTex, cubeSpecTex);
	wall3->Init();
	wall3->SetScale(2.0f, 0.2f, 2.0f);

	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	// setup lighting
	setupLighting();

	InitCamera();
}

void Application::DeInit()
{
	delete wood;
	delete floor;
	delete bed;
	delete pillow;
}

void Application::Update(double deltaTime)
{
	angle += (float)((deltaTime * 0) / 1000);
	wood->SetRotation(angle, 0, 1, 0);
	floor->SetRotation(angle, 0, 1, 0);
	bed->SetRotation(angle, 0, 1, 0);
	pillow->SetRotation(angle, 0, 1, 0);
	bed2->SetRotation(angle, 0, 1, 0);
	steel->SetRotation(angle, 0, 1, 0);
	steel2->SetRotation(angle, 0, 1, 0);
	black->SetRotation(angle, 0, 1, 0);
	wall1->SetRotation(angle, 0, 1, 0);
	wall2->SetRotation(angle, 0, 1, 0);
	wall3->SetRotation(angle, 0, 1, 0);
}

void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	shader->setMat4("view", view);


	//lantai
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 16; j++) {
			floor->SetPosition(-6 + i, -10, -7 + j);
			floor->Draw();
		}
	}
	//tembok
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			wall1->SetPosition(55, -0.5 + i, -7 + j);
			wall1->Draw();
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			wall1->SetPosition(-65, -0.5 + i, -7 + j);
			wall1->Draw();
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			wall2->SetPosition(-6 + j, -0.5 + i, 85);
			wall2->Draw();
		}
	}
	//plafon
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 16; j++) {
			wall3->SetPosition(-6 + i, 90, -7 + j);
			wall3->Draw();
		}
	}
	//lemari
	for (int i = -14; i < 30; i++) {
		for (int j = 0; j < 25; j++) {
			wood->SetPosition(47, 5 + i, -53 + j);
			wood->Draw();
		}
	}
	for (int i = -14; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			wood->SetPosition(28 + j, 5 + i, -28);
			wood->Draw();
		}
	}
	for (int i = -14; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			wood->SetPosition(28 + j, 5 + i, -53);
			wood->Draw();
		}
	}
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 26; j++) {
			wood->SetPosition(28 + i, 34, -53 + j);
			wood->Draw();
		}
	}
	for (int i = -14; i < 30; i++) {
		for (int j = 0; j < 25; j++) {
			wood->SetPosition(27, 5 + i, -53 + j);
			wood->Draw();
		}
	}
	//engsel lemari
	for (int i = -1; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			steel2->SetPosition(27, 28 + i, -28 + j);
			steel2->Draw();
		}
	}
	for (int i = -1; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			steel2->SetPosition(27, 12 + i, -28 + j);
			steel2->Draw();
		}
	}
	for (int i = -1; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			steel2->SetPosition(27, -7 + i, -28 + j);
			steel2->Draw();
		}
	}
	//gagang lemari
	for (int i = -1; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			steel->SetPosition(26, 15 + i, -51 + j);
			steel->Draw();
		}
	}

	//alas kursi
	for(int i = 0; i < 16; i++) {
		for (int j = 0; j < 15; j++) {
			steel2->SetPosition(20 + i, 5, 1 + j);
			steel2->Draw();
		}
	}

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			bed2->SetPosition(22 + i, 6, 2 + j);
			bed2->Draw();
		}
	}

	//kaki kursi
	for (int i = 0; i < 15; i++) {
		steel2->SetPosition(20, 5 - i, 1);
		steel2->Draw();
	}

	for (int i = 0; i < 15; i++) {
		steel2->SetPosition(35, 5 - i, 1);
		steel2->Draw();
	}

	for (int i = 0; i < 15; i++) {
		steel2->SetPosition(20, 5 - i, 15);
		steel2->Draw();
	}

	for (int i = 0; i < 15; i++) {
		steel2->SetPosition(35, 5 - i, 15);
		steel2->Draw();
	}

	//sandaran kursi
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 15; j++) {
			steel2->SetPosition(20, 5 + i, 1 + j);
			steel2->Draw();
		}
	}
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			bed2->SetPosition(21, 7 + i, 2 + j);
			bed2->Draw();
		}
	}

	//daun meja besar
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 36; j++) {
			wood->SetPosition(25 + i, 15, -10 + j);
			wood->Draw();
			wood->SetPosition(25 + i, 14, -10 + j);
			wood->Draw();
		}
	}

	//kaki meja besar
	for (int i = 0; i < 25; i++) {
		steel->SetPosition(26, 15 - i, -9);
		steel->Draw();
		steel->SetPosition(27, 15 - i, -9);
		steel->Draw();
		steel->SetPosition(27, 15 - i, -8);
		steel->Draw();
		steel->SetPosition(26, 15 - i, -8);
		steel->Draw();
	}
	for (int i = 0; i < 25; i++) {
		steel->SetPosition(26, 15 - i, 24);
		steel->Draw();
		steel->SetPosition(27, 15 - i, 24);
		steel->Draw();
		steel->SetPosition(27, 15 - i, 23);
		steel->Draw();
		steel->SetPosition(26, 15 - i, 23);
		steel->Draw();
	}
	for (int i = 0; i < 25; i++) {
		steel->SetPosition(45, 15 - i, 24);
		steel->Draw();
		steel->SetPosition(44, 15 - i, 24);
		steel->Draw();
		steel->SetPosition(44, 15 - i, 23);
		steel->Draw();
		steel->SetPosition(45, 15 - i, 23);
		steel->Draw();
	}
	for (int i = 0; i < 25; i++) {
		steel->SetPosition(45, 15 - i, -9);
		steel->Draw();
		steel->SetPosition(44, 15 - i, -9);
		steel->Draw();
		steel->SetPosition(44, 15 - i, -8);
		steel->Draw();
		steel->SetPosition(45, 15 - i, -8);
		steel->Draw();
	}

	//Kasur

	//Kepala
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 40; j++) {
			wood->SetPosition(46, 15 - i, 33 + j);
			wood->Draw();
		}
	}

	//tengah
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 73; j++) {
			wood->SetPosition(46 - j, 1, 33 + i);
			wood->Draw();
			wood->SetPosition(46 - j, 0, 33 + i);
			wood->Draw();
			wood->SetPosition(46 - j, -1, 33 + i);
			wood->Draw();
			wood->SetPosition(46 - j, -2, 33 + i);
			wood->Draw();
			wood->SetPosition(46 - j, -3, 33 + i);
			wood->Draw();
		}
	}

	//Springbed
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 70; j++) {
			bed->SetPosition(45 - j, 5, 35 + i);
			bed->Draw();
			bed->SetPosition(45 - j, 4, 35 + i);
			bed->Draw();
			bed->SetPosition(45 - j, 3, 35 + i);
			bed->Draw();
			bed->SetPosition(45 - j, 2, 35 + i);
			bed->Draw();
		}
	}

	//Bantal
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 10; j++) {
			pillow->SetPosition(45 - j, 9, 45 + i);
			pillow->Draw();
			pillow->SetPosition(45 - j, 8, 45 + i);
			pillow->Draw();
			pillow->SetPosition(45 - j, 7, 45 + i);
			pillow->Draw();
			pillow->SetPosition(45 - j, 6, 45 + i);
			pillow->Draw();
		}
	}

	//guling
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 25; j++) {
			pillow->SetPosition(25 - j, 9, 60 + i);
			pillow->Draw();
			pillow->SetPosition(25 - j, 8, 60 + i);
			pillow->Draw();
			pillow->SetPosition(25 - j, 7, 60 + i);
			pillow->Draw();
			pillow->SetPosition(25 - j, 6, 60 + i);
			pillow->Draw();
		}
	}

	//selimut
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			bed2->SetPosition(-22 + i, 6, 37 + j);
			bed2->Draw();
		}
	}

	//kaki
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 6; j++) {
			for(int k = 0; k < 6; k++)
				//Kiri Bawah
				wood->SetPosition(-26, 0 - i, 33 + j);
				wood->Draw();
				wood->SetPosition(-26 + j, 0 - i, 33);
				wood->Draw();
				wood->SetPosition(-20, 0 - i, 33 + j);
				wood->Draw();
				wood->SetPosition(-26 + j, 0 - i, 38);
				wood->Draw();
				//Kanan Bawah
				wood->SetPosition(-26, 0 - i, 67 + j);
				wood->Draw();
				wood->SetPosition(-26 + j, 0 - i, 67);
				wood->Draw();
				wood->SetPosition(-20, 0 - i, 67 + j);
				wood->Draw();
				wood->SetPosition(-26 + j, 0 - i, 72);
				wood->Draw();
				//Kiri Atas
				wood->SetPosition(40, 0 - i, 33 + j);
				wood->Draw();
				wood->SetPosition(40 + j, 0 - i, 33);
				wood->Draw();
				wood->SetPosition(46, 0 - i, 33 + j);
				wood->Draw();
				wood->SetPosition(40 + j, 0 - i, 38);
				wood->Draw();
				//Kanan Atas
				wood->SetPosition(40, 0 - i, 67 + j);
				wood->Draw();
				wood->SetPosition(40 + j, 0 - i, 67);
				wood->Draw();
				wood->SetPosition(46, 0 - i, 67 + j);
				wood->Draw();
				wood->SetPosition(40 + j, 0 - i, 72);
				wood->Draw();
		}
	}
	//bantal lantai
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			bed->SetPosition(-55 + i, -9, 18 + j);
			bed->Draw();
		}
	}
	//monitor
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 25; j++) {
			black->SetPosition(40, 20 + i, -4 + j);
			black->Draw();
		}
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 20; j++) {
			steel2->SetPosition(41, 23 + i, -2 + j);
			steel2->Draw();
		}
	}
	//stand monitor
	for (int i = 0; i < 15; i++) {
			steel2->SetPosition(42, 17 + i, -8 + i);
			steel2->Draw();
	}
	//bracket stand monitor
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			steel2->SetPosition(42 + i, 13, -11 + j);
			steel2->Draw();
			steel2->SetPosition(42 + i, 16, -11 + j);
			steel2->Draw();
		}
	}
	for (int i = 0; i < 4; i++) {
		steel2->SetPosition(42, 13 + i, -11);
		steel2->Draw();
		steel2->SetPosition(43, 13 + i, -11);
		steel2->Draw();
	}

	//keyboard
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 15; j++) {
			steel->SetPosition(29 + i, 16, -1 + j);
			steel->Draw();
		}
	}
	//mouse
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			steel2->SetPosition(30 + i, 16, 16 + j);
			steel2->Draw();
			black->SetPosition(33, 16, 16);
			black->Draw();
			black->SetPosition(33, 16, 17);
			black->Draw();
			steel->SetPosition(33, 16, 18);
			steel->Draw();
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			steel2->SetPosition(30 + i, 17, 16 + j);
			steel2->Draw();
		}
	}
	//CPU
	for (int i = -14; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			steel2->SetPosition(45, 5 + i, -23 + j);
			steel2->Draw();
		}
	}
	for (int i = -14; i < 8; i++) {
		for (int j = 0; j < 17; j++) {
			steel2->SetPosition(28 + j, 5 + i, -14);
			steel2->Draw();
		}
	}
	for (int i = -14; i < 8; i++) {
		for (int j = 0; j < 17; j++) {
			steel2->SetPosition(28 + j, 5 + i, -23);
			steel2->Draw();
		}
	}
	for (int i = -14; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			steel2->SetPosition(28, 5 + i, -23 + j);
			steel2->Draw();
		}
	}
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 10; j++) {
			steel2->SetPosition(28 + i, 13, -23 + j);
			steel2->Draw();
		}
	}
	for (int i = -10; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			black->SetPosition(27, 3 + i, -20 + j);
			black->Draw();
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			black->SetPosition(27, 8 + i, -21 + j);
			black->Draw();
		}
	}
	//daun meja kecil
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 22; j++) {
			wood->SetPosition(-58 + i, 4, 42 + j);
			wood->Draw();
			wood->SetPosition(-58 + i, 3, 42 + j);
			wood->Draw();
		}
	}

	//kaki meja kecil
	for (int i = 0; i < 12; i++) {
		steel->SetPosition(-57, 2 - i, 62);
		steel->Draw();
		steel->SetPosition(-56, 2 - i, 62);
		steel->Draw();
		steel->SetPosition(-57, 2 - i, 61);
		steel->Draw();
		steel->SetPosition(-56, 2 - i, 61);
		steel->Draw();
	}
	for (int i = 0; i < 12; i++) {
		steel->SetPosition(-39, 2 - i, 62);
		steel->Draw();
		steel->SetPosition(-38, 2 - i, 62);
		steel->Draw();
		steel->SetPosition(-39, 2 - i, 61);
		steel->Draw();
		steel->SetPosition(-38, 2 - i, 61);
		steel->Draw();
	}
	for (int i = 0; i < 12; i++) {
		steel->SetPosition(-57, 2 - i, 44);
		steel->Draw();
		steel->SetPosition(-56, 2 - i, 44);
		steel->Draw();
		steel->SetPosition(-57, 2 - i, 43);
		steel->Draw();
		steel->SetPosition(-56, 2 - i, 43);
		steel->Draw();
	}
	for (int i = 0; i < 12; i++) {
		steel->SetPosition(-39, 2 - i, 44);
		steel->Draw();
		steel->SetPosition(-38, 2 - i, 44);
		steel->Draw();
		steel->SetPosition(-39, 2 - i, 43);
		steel->Draw();
		steel->SetPosition(-38, 2 - i, 43);
		steel->Draw();
	}

	glDisable(GL_DEPTH_TEST);

}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		MoveCameraUp(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		MoveCameraDown(CAMERA_SPEED);
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 5;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Application::InitCamera()
{
	posCamX = 0.0f;
	posCamY = 1.0f;
	posCamZ = 8.0f;
	viewCamX = 0.0f;
	viewCamY = 1.0f;
	viewCamZ = 0.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.100f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Application::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}

void Application::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}

void Application::MoveCameraUp(float speed)
{
	posCamY += speed + 0.05;
	viewCamY += speed + 0.05;
}

void Application::MoveCameraDown(float speed)
{
	posCamY -= speed + 0.05;
	viewCamY -= speed + 0.05;
}

void Application::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}


int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Cube Example", 
		800, 600, 
		true, 
		false);
}