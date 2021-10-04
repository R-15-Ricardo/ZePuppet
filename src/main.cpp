#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Model/Model.hpp"
#include "Prim/Ellipsoid.hpp"
#include "Prim/Camera.hpp"

#include "GLAux/Renderer.hpp"
#include "GLAux/Vertex.hpp"
#include "GLAux/Shader.hpp"

#include "CharacterController/Controller.hpp"

const char* glsl_version = "#version 130";

int main ()
{
	GLFWwindow* window;

	//Initializes GLFW
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, "Ze puppet", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//Context for the current window (Valid OpenGL rendering context)
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//Initializes GLEW
	if (glewInit() != GLEW_OK) std::cout<<"Error"<<std::endl;
	else std::cout<<"[GLEW] OK!"<<std::endl;

	float* positions;
	unsigned int* indices;
	std::pair<int,int> nVertices = genS2Mesh(1.f,100, positions, indices);


	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_LINE_SMOOTH);

	//- - - - - Vertex Array setup for object - - - - -
	VertexArray va;

    VertexBuffer vb(positions, nVertices.first * 3 * sizeof(float));
	VertexBufferLayout layout;
	layout.AddFloat(3);
    IndexBuffer ib(indices, nVertices.second);
    va.AddBuffer(vb, layout);

	Model model = ZePuppet();

	//Viewport camera
	Camera camera(0.f, -90.f, glm::vec3(0.0f,0.0f,25.0f));

	Shader shader("res/shaders/sphere.shader");
	//Shader camera uniforms
	glm::mat4 View = camera.getCamera();
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f); //I'll toy with this later
	shader.SetUniformMat4f("f_View", View);
	shader.SetUniformMat4f("f_Projection", Projection);

	//Lighting unifroms
	glm::vec4 lightColor(1.f, 1.0f, 1.0f, 1.f);
	glm::vec3 lightPosition(-7.f, 7.f,30.f);
	shader.SetUniform4f("u_LightColor", lightColor); 
	shader.SetUniform3f("lightPos", lightPosition);
	//- - - - - View attributes - - - - -
	
	
	//More openGL shananigans
	va.Unbind();
	vb.Unbind();
	ib.Unbind();

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER ,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Renderer renderer(0.f, 0.f, 0.f);
	Renderer renderer(0.96f, 0.92f, 0.88f);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;

	ImGui::StyleColorsDark();
	ImGui::GetStyle().WindowRounding = 0.0f;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//Main window loop
	while(!glfwWindowShouldClose(window))
	{
		
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		ShowCharacterController(model);
   
		ImGui::Render();
		//Render solid
		renderer.Clear();
		model.draw(renderer,va,ib,shader);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//Whatever "front and back buffers" mean
		glfwSwapBuffers(window);
		glfwPollEvents();

		
	}
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

	glfwTerminate();

	return 0;
}

