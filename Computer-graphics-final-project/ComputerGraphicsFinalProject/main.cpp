// #define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Resources/LIBS/IMGUI/imgui.h"
#include "Resources/LIBS/IMGUI/imgui_impl_glfw_gl3.h"
#include "imfilebrowser.h"

#include <fstream>
#include <string>
#include <sstream>


#include "ErrorHandler.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Camera.h"

const int testcode[25][25] = {
0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0,
0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0,
0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0,
0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0,
0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0,
1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1,
1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0,
0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0,
0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1,
0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0,
0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1,
0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1,
0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1,
0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1,
0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0
};

const GLfloat BufferWidth = 1366.0f;
const GLfloat BufferHeight = 720.0f;
const float toRadians = 3.1415926535897f / 180; // degree to gradient facter
Window win;
Camera camera;

int main(void)
{
	
	win = Window(BufferWidth, BufferHeight);
	
	win.Initialise();


	if (glewInit() != GLEW_OK) {
		std::cout << "Error!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		
		
		float positions[] = {
			-12, -12, 12, 0.0f, 0.0f,   // col0&1&2 : indices coordinates 
			 12, -12, 12, 1.0f, 0.0f,   // col3&4 : texture coordinates 
			 12, 12, 12, 1.0f, 1.0f,
		    -12, 12, 12, 0.0f, 1.0f,
			-12, -12, -12, 0.0f, 0.0f,  
			 12, -12, -12, 1.0f, 0.0f,   
			 12, 12, -12, 1.0f, 1.0f,
			-12, 12, -12, 0.0f, 1.0f
		};
		
		unsigned int indices[] = {
			0, 1, 2, 
			2, 3, 0, // front
			5, 4, 7,
			7, 6, 5, // tail
			4, 0, 3,
			3, 7, 4, // left
			1, 5, 6,
			6, 2, 1, // right
			4, 5, 1,
			1, 4, 0, // bottom
			3, 2, 6,
			6, 7, 3  // top
		};

		Renderer renderer;
		renderer.EnableBlending();

		VertexArray vao;
		VertexBuffer vbo(positions, sizeof(positions));

		VertexBufferLayout vbl;
		vbl.Push<float>(3);  // indices coordinate
		vbl.Push<float>(2);  // texture coordinate
		
		vao.AddBuffer(vbo, vbl);
		
		IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
		
		// default: use 2d
		glm::mat4 proj = glm::ortho(0.0f, BufferWidth, 0.0f, BufferHeight, -100.0f, 100.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// model transformation same for 2,3D
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		// rotate angle in degree along z,y,x axis
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));  // z
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));  // y
		model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));  // x
		// scale the cube
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		Shader shader("Basic.shader");
		shader.Bind();
		// shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		Texture myTexture("Resources/Textures/test/test.png");
		Texture myTexture1("Resources/Textures/jellyfish/jellyfish.png");
		myTexture.Bind();  // use default 0
		shader.SetUniform1i("u_Texture", 0);

		// Initailize GUI
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(win.getWindowPointer(), true);
		ImGui::StyleColorsDark();
		bool show_demo_window = true;
		bool show_another_window = true;
		ImVec4 clear_color = ImVec4(44.0/255, 51.0/255, 48.0/255, 1.00f);
		// Enable file browsering
		// create a file browser instance
		ImGui::FileBrowser fileDialog;
		// (optional) set browser properties
		fileDialog.SetTitle("Texture Picker");
		fileDialog.SetTypeFilters({ ".png", ".jpg", ".jpeg", "bmp" });

		// End Initialize GUI

		glm::vec3 scaleA(1.0f, 1.0f, 1.0f);
		glm::vec3 rotationA(0, 0, 0);
		glm::vec3 translationA(0, 0, 0);  // FOR OBJECT 
		glm::vec3 translationB(0, 0, 0);  // FOR CAMERA
		glm::vec3 translationC(0, 0, 0);  // FOR CAMERA
		
		std::string texture_location = "Resources/Textures/test/test.png";
		bool draw_qr_code_flag = false;
		bool enable3dflag = false;
		bool is_camera_fixed = true;
		bool update_texture_flag = false;

		char textInput[300] = "http://idiospace.com";  // for QR raw info input
	
		while (!win.getShouldClose())
		{
			
			GLCall(glfwPollEvents());

			renderer.Clear();

			ImGui_ImplGlfwGL3_NewFrame();

			// Dark blue background
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

			
			

			// set camera
			if (enable3dflag)
			{
				proj = glm::perspective(glm::radians(90.0f), BufferWidth / BufferHeight, 0.1f, 2000.0f);
				view = glm::lookAt(
					glm::vec3(640+ translationB.x, 360+ translationB.y, 200+ translationB.z), // Camera is at, in World Space
					glm::vec3(640+ translationC.x, 360+ translationC.y, -201+ translationC.z), // and looks at the origin
					glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
				);
			}
			else {
				// 2d version
				proj = glm::ortho(0.0f, 1366.0f, 0.0f, 720.0f, -1500.0f, 1500.0f);
				view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
			}

			// draw the baseline image
			/*
			{
				// rotate alone z axis
				model = glm::translate(glm::mat4(1.0f), translationA);
				model = glm::rotate(model, rotationA.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::rotate(model, rotationA.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, rotationA.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
				model = glm::scale(model, scaleA);

				glm::mat4 mvp = proj * view * model;
				shader.Bind();
				shader.SetUniform4f("u_Color", 0.5f, 0.3f, 0.8f, 1.0f);
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(vao, ib, shader);
			}
			*/
			
			if (draw_qr_code_flag) {
				// mvp transformation and re - draw
				for (int i = 0; i < 25; ++i) {
					for (int j = 0; j < 25; ++j) {
						{
							if (testcode[i][j] == 1) {
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(24 * (i + 1), 24 * (j + 1), 0));
								// rotate alone z axis
								model = glm::translate(model, translationA);
								model = glm::rotate(model, rotationA.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
								model = glm::rotate(model, rotationA.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
								model = glm::rotate(model, rotationA.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
								model = glm::scale(model, scaleA);

								glm::mat4 mvp = proj * view * model;
								shader.Bind();
								shader.SetUniformMat4f("u_MVP", mvp);
								renderer.Draw(vao, ib, shader);
							}
						}
					}
				}
			}

			// IMGUI window
			{
				static float f = 0.0f;
				static int counter = 0;
				ImGui::Text("QR Pro: Powerful & Elegant");                           // Display some text (you can use a format string too)
				ImGui::SliderFloat("TranslationA.x", &translationA.x, 0.0f, 1280.0f);            
				ImGui::SliderFloat("TranslationA.y", &translationA.y, 0.0f, 720.0f);            
				ImGui::SliderFloat("TranslationA.z", &translationA.z, -1000.0f, 500.0f);
				ImGui::SliderFloat("RotationA.x", &rotationA.x, 0.0f, 360.0f);
				ImGui::SliderFloat("RotationA.y", &rotationA.y, 0.0f, 360.0f);
				ImGui::SliderFloat("RotationA.z", &rotationA.z, 0.0f, 360.0f);
				ImGui::SliderFloat("ScaleA.x", &scaleA.x, 0.5f, 5.0f);           
				ImGui::SliderFloat("ScaleA.y", &scaleA.y, 0.5f, 5.0f);           
				ImGui::SliderFloat("ScaleA.z", &scaleA.z, 0.5f, 5.0f);
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				ImGui::Checkbox("Input Window", &show_another_window);
				ImGui::SameLine();
				
				ImGui::Checkbox("3D View", &enable3dflag);
				ImGui::SameLine();
				if (ImGui::Button("Camera Status")) 
				{
					is_camera_fixed = !is_camera_fixed;
				}
				
				if (is_camera_fixed) {
					ImGui::SameLine();
					ImGui::Text("Fixed");
				}
				else
				{
					ImGui::SameLine();
					ImGui::Text("Free");
				}

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				if (show_another_window)
				{
					ImGui::Begin("Input Window", &show_another_window);
					// open file dialog when user clicks this button
					if (ImGui::Button("Texture Picker"))
						fileDialog.Open();
					ImGui::Text("Type Raw Message Here");
					ImGui::InputText("##text1", textInput, sizeof(textInput));
					ImGui::SameLine(); 
					if (ImGui::Button("Generate"))
					{
						draw_qr_code_flag = true;
					}
					ImGui::End();
				}

				fileDialog.Display();

				if (fileDialog.HasSelected())
				{
					std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
					texture_location = fileDialog.GetSelected().string();
					fileDialog.ClearSelected();
					update_texture_flag = true;
				}

				// camera control
				if (!is_camera_fixed)
				{
					// ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
					ImGui::Begin("Camera controller", &show_another_window);

					ImGui::SliderFloat("Viewsrc.x", &translationB.x, -683.0f, 683.0f);
					ImGui::SliderFloat("Viewsrc.y", &translationB.y, -360.0f, 360.0f);
					ImGui::SliderFloat("Viewsrc.z", &translationB.z, -800.0f, 800.0f);
					ImGui::SliderFloat("Viewdst.x", &translationC.x, -180.0f, +180.0f);
					ImGui::SliderFloat("Viewdst.y", &translationC.y, -180.0f, +180.0f);
					ImGui::SliderFloat("Viewdst.z", &translationC.z, -180.0f, +180.0f);
					ImGui::Text("Set Cam Back to Origin (Screen Center)");
					ImGui::SameLine();
					if (ImGui::Button("Reset"))
					{
						translationB = glm::vec3(0, 0, 0);
						translationC = glm::vec3(0, 0, 0);
					}
					ImGui::End();
				}

				// rerendering the image
				if (update_texture_flag) 
				{
					myTexture.Unbind();
					myTexture1.Bind();
					shader.SetUniform1i("u_Texture", 0);
					update_texture_flag = false;
				}
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			win.swapBuffers();
			
		}

	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}



