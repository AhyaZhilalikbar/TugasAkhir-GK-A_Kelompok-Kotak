#include "Demo.h"

Demo::Demo() {

}
Demo::~Demo() {
}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);
	BuildLemari();
	BuildPintuLemari();
	Buildtidur();
	Buildpapantidur();
	Buildpapantidur2();
	Buildtembok();
	BuildColoredPlane();
	BuildKabinet();
	BuildPintuKabinet();
	InitCamera();
}
void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &tembokVAO);
	glDeleteBuffers(1, &tembokVBO);
	glDeleteBuffers(1, &tembokEBO);
}

void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.001f;
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

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth/2;
	double midY = screenHeight/2;
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
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);


	

}
void Demo::Update(double deltaTime) {
	
}
void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// set lighting attributes ON
	GLint lightPosLoc = glGetUniformLocation(this->shaderProgram, "lightPos");
	glUniform3f(lightPosLoc, 0, 5, 0);
	GLint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, 0, 3, 0);
	GLint lightColorLoc = glGetUniformLocation(this->shaderProgram, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	DrawLemari();
	DrawPintuLemari();
	Drawtembok();
	Drawtidur();
	Drawpapantidur();
	Drawpapantidur2();
	DrawColoredPlane();
	DrawKabinet();
	DrawPintuKabinet();
	glDisable(GL_DEPTH_TEST);
}

void Demo::Buildpapantidur()
{
	glGenTextures(1, &papantidurTexture);
	glBindTexture(GL_TEXTURE_2D, papantidurTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("papankayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	float vertices[] = {
		//front
		 1.9,   0.0,  -3.7, 0, 0,  // 0
		 3.9,   0.0,  -3.7, 1, 0,  // 1
		 3.9,   1.0,  -3.7, 1, 1,  // 2
		 1.9,   1.0,  -3.7, 0, 1,  // 3

		// right
		 3.9,   0.0, -3.7, 0, 0,  // 4
		 3.9,   0.0, -3.9, 1, 0,  // 5
		 3.9,   1.0, -3.9, 1, 1,  // 6
		 3.9,   1.0, -3.7, 0, 1,  // 7

		// back
		 1.9,   0.0, -3.9, 0, 0, // 8 
		 3.9,   0.0, -3.9, 1, 0, // 9
		 3.9,   1.0, -3.9, 1, 1, // 10
		 1.9,   1.0, -3.9, 0, 1, // 11

		// left   4
		 1.9,   0.0, -3.9, 0, 0, // 12
		 1.9,   0.0, -3.7, 1, 0, // 13
		 1.9,   1.0, -3.7, 1, 1, // 14
		 1.9,   1.0, -3.9, 0, 1, // 15

		// upper4
		 1.9,   1.0, -3.7, 0, 0,   // 16
		 3.9,   1.0, -3.7, 1, 0,  // 17
		 3.9,   1.0, -3.9, 1, 1,  // 18
		 1.9,   1.0, -3.9, 0, 1,   // 19

		// bottom
		 1.9,   0.1, -3.7, 0, 0, // 20
		 3.9,   0.1, -3.7, 1, 0,  // 21
		 3.9,   0.1, -3.9, 1, 1,  // 22
		 1.9,   0.1, -3.9, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6, 7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &papantidurVAO);
	glGenBuffers(1, &papantidurVBO);
	glGenBuffers(1, &papantidurEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(papantidurVAO);

	glBindBuffer(GL_ARRAY_BUFFER, papantidurVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, papantidurEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::Buildpapantidur2() {
	glGenTextures(1, &papantidur2Texture);
	glBindTexture(GL_TEXTURE_2D, papantidur2Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("papankayu.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	float vertices[] = {
		// format position, tex coords
		// front
		 1.9,   0.0,  0.3, 0, 0,  // 0
		 3.9,   0.0,  0.3, 1, 0,  // 1
		 3.9,   0.7,  0.3, 1, 1,  // 2
		 1.9,   0.7,  0.3, 0, 1,  // 3

		// right
		 3.9,   0.0,  0.3, 0, 0,  // 4
		 3.9,   0.0,  0, 1, 0,  // 5
		 3.9,   0.7,  0, 1, 1,  // 6
		 3.9,   0.7,  0.3, 0, 1,  // 7

		// back
		 1.9,   0.0,  0, 0, 0, // 8 
		 3.9,   0.0,  0, 1, 0, // 9
		 3.9,   0.7,  0, 1, 1, // 10
		 1.9,   0.7,  0, 0, 1, // 11

		// left   4
		 1.9,   0.0,  0, 0, 0, // 12
		 1.9,   0.0,  0.3, 1, 0, // 13
		 1.9,   0.7,  0.3, 1, 1, // 14
		 1.9,   0.7,  0, 0, 1, // 15

		// upper4
		 1.9,   0.7,  0.3, 0, 0,   // 16
		 3.9,   0.7,  0.3, 1, 0,  // 17
		 3.9,   0.7,  0, 1, 1,  // 18
		 1.9,   0.7,  0, 0, 1,   // 19

		// bottom
		 1.9,   0.1,  0.3, 0, 0, // 20
		 3.9,   0.1,  0.3, 1, 0,  // 21
		 3.9,   0.1,  0, 1, 1,  // 22
		 1.9,   0.1,  0, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6, 7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &papantidur2VAO);
	glGenBuffers(1, &papantidur2VBO);
	glGenBuffers(1, &papantidur2EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(papantidur2VAO);

	glBindBuffer(GL_ARRAY_BUFFER, papantidur2VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, papantidur2EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::Buildtidur()
{
	glGenTextures(1, &tidurTexture);
	glBindTexture(GL_TEXTURE_2D, tidurTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kasur.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	float vertices[] = {
		// format position, tex coords
		// front
		 2.0,   0.0, -0, 0, 0,  // 0
		 3.8,   0.0, -0, 1, 0,  // 1
		 3.8,   0.6, -0, 1, 1,  // 2
		 2.0,   0.6, -0, 0, 1,  // 3

		// right
		 3.8,   0.0, -0, 0, 0,  // 4
		 3.8,   0.0, -3.7, 1, 0,  // 5
		 3.8,   0.6, -3.7, 1, 1,  // 6
		 3.8,   0.6, -0, 0, 1,  // 7

		// back
		 2.0,   0.0, -3.7, 0, 0, // 8 
		 3.8,   0.0, -3.7, 1, 0, // 9
		 3.8,   0.6, -3.7, 1, 1, // 10
		 2.0,   0.6, -3.7, 0, 1, // 11

		// left   4
		 2.0,   0.0, -3.7, 0, 0, // 12
		 2.0,   0.0, -0, 1, 0, // 13
		 2.0,   0.6, -0, 1, 1, // 14
		 2.0,   0.6, -3.7, 0, 1, // 15

		// upper4
		 2.0,   0.6, -0, 0, 0,   // 16
		 3.8,   0.6, -0, 1, 0,  // 17
		 3.8,   0.6, -3.7, 1, 1,  // 18
		 2.0,   0.6, -3.7, 0, 1,   // 19

		// bottom
		 2.0,   0.1, -1.5, 0, 0, // 20
		 3.8,   0.1, -1.5, 1, 0,  // 21
		 3.8,   0.1, -3.7, 1, 1,  // 22
		 2.0,   0.1, -3.7, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6, 7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &tidurVAO);
	glGenBuffers(1, &tidurVBO);
	glGenBuffers(1, &tidurEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tidurVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tidurVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tidurEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::Buildtembok()
{
	glGenTextures(1, &tembokTexture);
	glBindTexture(GL_TEXTURE_2D, tembokTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("tembok001.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	float vertices[] = {
		// format position, tex coords, normal
		  //front
		   4.0, -0.1, 4.0  ,0, 0,  // 0
		   4.0, -0.1, -4.0 ,1, 0,  // 1
		   4.0, 4.0, -4.0 ,1, 1,  // 2          
		   4.0, 4.0, 4.0  ,0, 1,    // 3
		   //right
		   4.0, -0.1,  -4.0, 0, 0,  // 4
		  -4.0, -0.1,  -4.0,1, 0,     // 5            
		  -4.0, 4.0,  -4.0,1, 1, // 6
		   4.0, 4.0,  -4.0,0, 1, // 7
		   //back
		  -4.0, -0.1,  4.0,0, 0,  // 8 
		  -4.0, -0.1, -4.0,1, 0,  // 9 
		  -4.0, 4.0, -4.0,1, 1,  // 10 
		  -4.0, 4.0,  4.0,0, 1,  // 11 
		  //left
		  -4.0, -0.1,  4.0,0, 0,     // 12
		   4.0, -0.1,  4.0,1, 0,    // 13
		   4.0, 4.0,  4.0,1, 1,    // 14             
		  -4.0, 4.0,  4.0,0, 1,     // 15
		  //up
		   4.0, 4.0,  4.0, 0, 0,   // 16
		   4.0, 4.0, -4.0, 1, 0,  // 17
		  -4.0, 4.0, -4.0, 1, 1,   // 18
		  -4.0, 4.0,  4.0, 0, 1,   // 19
		   //bottom
		   4.0, -0.1,  4.0,0, 0,    // 20           
		   4.0, -0.1, -4.0,1, 0,   // 21
		  -4.0, -0.1, -4.0,1, 1,   // 22
		  -4.0, -0.1,  4.0,0, 1,  // 23
	};
	unsigned int indices[] = {
	 0,  1,  2,  0,  2,  3,   // front
	 4,  5,  6,  4,  6, 7,   // right
	 8,  9,  10, 8,  10, 11,  // back
	 //12, 14, 13, 12, 15, 14,  // left
	 16, 18, 17, 16, 19, 18,  // upper
	 20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &tembokVAO);
	glGenBuffers(1, &tembokVBO);
	glGenBuffers(1, &tembokEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tembokVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tembokVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tembokEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::BuildLemari() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("lemari.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	float vertices[] = {
		// format position, tex coords
		// front
		-3.0,   0.0, -3.9, 0, 0,  // 0
		-3.0,   0.0, -2.0, 1, 0,  // 1
		-3.0,   3.0, -2.0, 1, 1,  // 2
		-3.0,   3.0, -3.9, 0, 1,  // 3

		// right
		-3.0,   0.0, -2.0, 0, 0,  // 4
		-3.9,   0.0, -2.0, 1, 0,  // 5
		-3.9,   3.0, -2.0, 1, 1,  // 6
		-3.0,   3.0, -2.0, 0, 1,  // 7

		// back
		-3.9,   0.0, -3.9, 0, 0, // 8 
		-3.9,   0.0, -2.0, 1, 0, // 9
		-3.9,   3.0, -2.0, 1, 1, // 10
		-3.9,   3.0, -3.9, 0, 1, // 11

		// left
		-3.9,   0.0, -3.9, 0, 0, // 12
		-3.0,   0.0, -3.9, 1, 0, // 13
		-3.0,   3.0, -3.9, 1, 1, // 14
		-3.9,   3.0, -3.9, 0, 1, // 15

		// upper
		-3.0,   3.0, -3.9, 0, 0,   // 16
		-3.0,   3.0, -2.0, 1, 0,  // 17
		-3.9,   3.0, -2.9, 1, 1,  // 18
		-3.9,   3.0, -3.9, 0, 1,   // 19

		// bottom
		-3.0,   0.1, -3.9, 0, 0, // 20
		-3.0,   0.1, -2.0, 1, 0,  // 21
		-3.9,   0.1, -2.9, 1, 1,  // 22
		-3.9,   0.1, -3.9, 0, 1, // 23
	};		   
	unsigned int indices[] = {
		4,  5,  6,  4,  6, 7,   // right
		0,  1,  2,  0,  2,  3,   // front
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::BuildPintuLemari() {
	glGenTextures(1, &pintuLemariTexture);
	glBindTexture(GL_TEXTURE_2D, pintuLemariTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pintuLemari.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	float vertices[] = {
		// format position, tex coords
		// front
		-2.95,   0.0, -3.9, 0, 0,  // 0
		-2.95,   0.0, -2.0, 1, 0,  // 1
		-2.95,   3.0, -2.0, 1, 1,  // 2
		-2.95,   3.0, -3.9, 0, 1,  // 3

		// right
		-2.99,   0.0, -2.0, 0, 0,  // 4
		-2.95,   0.0, -2.0, 1, 0,  // 5
		-2.95,   3.0, -2.0, 1, 1,  // 6
		-2.99,   3.0, -2.0, 0, 1,  // 7

		// back
		-2.95,   0.0, -3.9, 0, 0, // 8 
		-2.95,   0.0, -2.0, 1, 0, // 9
		-2.95,   3.0, -2.0, 1, 1, // 10
		-2.95,   3.0, -3.9, 0, 1, // 11

		// left
		-2.95,   0.0, -3.9, 0, 0, // 12
		-2.99,   0.0, -3.9, 1, 0, // 13
		-2.99,   3.0, -3.9, 1, 1, // 14
		-2.95,   3.0, -3.9, 0, 1, // 15

		// upper
		-2.99,   3.0, -3.9, 0, 0,   // 16
		-2.99,   3.0, -2.0, 1, 0,  // 17
		-2.95,   3.0, -2.9, 1, 1,  // 18
		-2.95,   3.0, -3.9, 0, 1,   // 19

		// bottom
		-2.95,   0.1, -3.9, 0, 0, // 20
		-2.95,   0.1, -2.0, 1, 0,  // 21
		-2.99,   0.1, -2.9, 1, 1,  // 22
		-2.99,   0.1, -3.9, 0, 1, // 23
	};
	unsigned int indices[] = {
		4,  5,  6,  4,  6, 7,   // right
		0,  1,  2,  0,  2,  3,   // front
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};
	glGenVertexArrays(1, &pintuLemariVAO);
	glGenBuffers(1, &pintuLemariVBO);
	glGenBuffers(1, &pintuLemariEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(pintuLemariVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pintuLemariVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pintuLemariEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::BuildKabinet() {
	glGenTextures(1, &kabinetTexture);
	glBindTexture(GL_TEXTURE_2D, kabinetTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("kabinet.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords
		// front
		 0.0,   0.0, -3.0, 0, 0,  // 0
		 1.8,   0.0, -3.0, 1, 0,  // 1
		 1.8,   1.0, -3.0, 1, 1,  // 2
		 0.0,   1.0, -3.0, 0, 1,  // 3

		// right
		 1.8,   0.0, -3.0, 0, 0,  // 4
		 1.8,   0.0, -3.9, 1, 0,  // 5
		 1.8,   1.0, -3.9, 1, 1,  // 6
		 1.8,   1.0, -3.0, 0, 1,  // 7

		// back
		 1.8,   0.0, -3.9, 0, 0, // 8 
		 0.0,   0.0, -3.9, 1, 0, // 9
		 0.0,   1.0, -3.9, 1, 1, // 10
		 1.8,   1.0, -3.9, 0, 1, // 11

		// left
		 0.0,   0.0, -3.9, 0, 0, // 12
		 0.0,   0.0, -3.0, 1, 0, // 13
		 0.0,   1.0, -3.0, 1, 1, // 14
		 0.0,   1.0, -3.9, 0, 1, // 15

		// upper
		 1.8,   1.0, -3.0, 0, 0,   // 16
		 0.0,   1.0, -3.0, 1, 0,  // 17
		 0.0,   1.0, -3.9, 1, 1,  // 18
		 1.8,   1.0, -3.9, 0, 1,   // 19

		// bottom
		 1.8,   0.1, -3.0, 0, 0, // 20
		 0.0,   0.1, -3.0, 1, 0,  // 21
		 1.8,   0.1, -3.9, 1, 1,  // 22
		 0.0,   0.1, -3.9, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6, 7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

	};

	glGenVertexArrays(1, &kabinetVAO);
	glGenBuffers(1, &kabinetVBO);
	glGenBuffers(1, &kabinetEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(kabinetVAO);

	glBindBuffer(GL_ARRAY_BUFFER, kabinetVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kabinetEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::BuildPintuKabinet() {
	glGenTextures(1, &pintuKabinetTexture);
	glBindTexture(GL_TEXTURE_2D, pintuKabinetTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("pintuKabinet.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] = {
		// format position, tex coords
		// front
		 0.0,   0.0, -2.95, 0, 0,  // 0
		 1.8,   0.0, -2.95, 1, 0,  // 1
		 1.8,   1.0, -2.95, 1, 1,  // 2
		 0.0,   1.0, -2.95, 0, 1,  // 3

		// right
		 1.8,   0.0, -2.95, 0, 0,  // 4
		 1.8,   0.0, -2.99, 1, 0,  // 5
		 1.8,   1.0, -2.99, 1, 1,  // 6
		 1.8,   1.0, -2.95, 0, 1,  // 7

		// back
		 1.8,   0.0, -2.99, 0, 0, // 8 
		 0.0,   0.0, -2.99, 1, 0, // 9
		 0.0,   1.0, -2.99, 1, 1, // 10
		 1.8,   1.0, -2.99, 0, 1, // 11

		// left
		 0.0,   0.0, -2.99, 0, 0, // 12
		 0.0,   0.0, -2.95, 1, 0, // 13
		 0.0,   1.0, -2.95, 1, 1, // 14
		 0.0,   1.0, -2.99, 0, 1, // 15

		// upper
		 1.8,   1.0, -2.95, 0, 0,   // 16
		 0.0,   1.0, -2.95, 1, 0,  // 17
		 0.0,   1.0, -2.99, 1, 1,  // 18
		 1.8,   1.0, -2.99, 0, 1,   // 19

		// bottom
		 1.8,   0.1, -2.95, 0, 0, // 20
		 0.0,   0.1, -2.95, 1, 0,  // 21
		 1.8,   0.1, -2.99, 1, 1,  // 22
		 0.0,   0.1, -2.99, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6, 7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22,   // bottom

	};

	glGenVertexArrays(1, &pintuKabinetVAO);
	glGenBuffers(1, &pintuKabinetVBO);
	glGenBuffers(1, &pintuKabinetEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(pintuKabinetVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pintuKabinetVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pintuKabinetEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawPintuKabinet() {
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pintuKabinetTexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);
	glBindVertexArray(pintuKabinetVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::DrawKabinet() {
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, kabinetTexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);
	glBindVertexArray(kabinetVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::DrawLemari()
{
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::DrawPintuLemari() {
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pintuLemariTexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);
	glBindVertexArray(pintuLemariVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::Drawpapantidur()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, papantidurTexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(papantidurVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::Drawpapantidur2()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, papantidur2Texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(papantidur2VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::Drawtidur()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tidurTexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glBindVertexArray(tidurVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("marble.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, 0.0, -50.0,  0,  0,
		 50.0, 0.0, -50.0, 50,  0,
		 50.0, 0.0,  50.0, 50, 50,
		-50.0, 0.0,  50.0,  0, 50,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}
void Demo::Drawtembok()
{
	glUseProgram(shaderProgram);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tembokTexture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);
	glBindVertexArray(tembokVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::InitCamera()
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
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float y = viewCamY - posCamY;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	posCamY = posCamY + y * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
	viewCamY = viewCamY + y * speed;
}
void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float y = viewCamY - posCamY;
	float orthoX = -z;
	float orthoY = y;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	posCamY = posCamY + orthoY * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
	viewCamY = viewCamY + orthoY * speed;
}
void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float y = viewCamY - posCamY;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
	viewCamY = (float)(posCamY + glm::cos(speed) * y - glm::sin(speed) * y);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Camera: Free Camera Implementation", 800, 600, false, false);
}