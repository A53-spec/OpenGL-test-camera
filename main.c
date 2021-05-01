#include "include/glew.h"
#include "include/glfw3.h"
#include "include/linmath.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//homemade
#include "utils.h"
#include "camera.h"
#include "VertBuffer.h"

GLFWwindow *gWindow;

float points[] = {
	 -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
	
float colours[] = {
 0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

const int Width = 1280;
const int Height = 720;

float x=0,y=0,z=0;

vec3 cameraPos, cameraFront, cameraUp;
vec3 Add_pos_front; 
float lastX=1280/2, lastY=720/2;
float yaw=-90.0f,pitch;
int firstMouse=1;
float camSpeed = 5.0f;
float fov=45;

double deltaTime,currentframe,lastframe;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void Mouse_callback(GLFWwindow* window, int state, int xpos,int ypos);
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void Init_GLFW_GLEW(int Width, int Height, const char* WindowName);
//WinMain(){
int main(){
	//Initalisation
	
	GLint link_ok=0;
	GLint compile_ok=0;

	Init_GLFW_GLEW(Width,Height,"Cubes !");
	glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//set key callback function
	glfwSetKeyCallback(gWindow,Key_Callback);
	glfwSetCursorPosCallback(gWindow, Mouse_callback);  
	glfwSetScrollCallback(gWindow, scroll_callback); 

	 // tell GL to only draw onto a pixel if the shape is closer to the viewer
  	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glEnable(GL_CULL_FACE);
  	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	
	GLuint Texture = loadBMP("test.bmp");
	GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	GLuint colours_vbo = 0;
	glGenBuffers(1, &colours_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	GLint vs= create_shader("test_vs.glsl",GL_VERTEX_SHADER);
	GLint fs= create_shader("test_fs.glsl",GL_FRAGMENT_SHADER);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram(shader_programme);
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &link_ok);
	if(!link_ok){
		printf("[ERROR] Error in glinkProgram\n");
		abort();
	}

	GLint mov = glGetUniformLocation(shader_programme, "m_transform");
	if(mov!=-1){
		printf("[INFO] link mov\n");
	}else{
		printf("[INFO] mov not found\n");
	}
	mat4x4 Model;
	mat4x4 Projection;
	mat4x4 view;
	mat4x4 result;
	mat4x4 temp;
	mat4x4 te;
	mat4x4 t;
	mat4x4_identity(result);
	mat4x4_identity(view);
	mat4x4_identity(Projection);
	mat4x4_identity(Model);

	double mousex,mousey;
	int i,j;
	vec3 center;
	vec3 up={0.0f,1.0f,0.0f};
	printf("[INFO] Diplaying !\n");
	cameraPos[0] = cameraPos[2] = cameraPos[1] = 3.0f;
	cameraFront[0] = cameraFront[1]=cameraFront[2] = 0.0f;
	cameraUp[0] = cameraUp[2] = 0.0f; cameraUp[1] = 1.0f;
	

	while(!glfwWindowShouldClose(gWindow)){
		currentframe = glfwGetTime();
		deltaTime = currentframe - lastframe;
		lastframe = currentframe;
		// wipe the drawing surface clear
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

	
		vec3_add(Add_pos_front,cameraPos,cameraFront);	
		mat4x4_perspective(Projection,fov*0.01745329251,Width/Height,0.1f,100.0f);										
		mat4x4_look_at(view,cameraPos,Add_pos_front,cameraUp);
		mat4x4_mul(temp,Projection,view);
		mat4x4_mul(result,temp,Model);
		glfwPollEvents();

		glUseProgram(shader_programme);
		//625 draw calls !!
		for(i=0;i<50;i+=2){
			for(j=0;j<50;j+=2){
				mat4x4_translate_in_place(result,j,0.0f,i);
				glBindVertexArray(vao);
				glUniformMatrix4fv(mov,1,GL_FALSE,&result);
				glDrawArrays(GL_TRIANGLES, 0, 36);//dessiner les carées
				mat4x4_translate_in_place(result,-j,0.0f,-i);
			}
		}


		glfwSwapBuffers(gWindow);
		//printf("%f\n", 1/deltaTime); //printf fps
	}

    // De-Initialization
	printf("[INFO] De-Initialization...\n");
	glDeleteProgram(shader_programme);
	glDeleteBuffers(1,&points_vbo);
	glDeleteVertexArrays(1,&vao);
	glfwDestroyWindow(gWindow);
	glfwTerminate();
	return(0);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camSpeed -= (float)yoffset;
	fov -= (float)yoffset;
}

static void Mouse_callback(GLFWwindow* window, int state, int xpos,int ypos){
	double posx,posy;
	glfwGetCursorPos(gWindow,&posx,&posy);
	int i;
	if (firstMouse)
    {
        lastX = posx;
        lastY = posy;
        firstMouse = 0;
    }
  
    float xoffset = posx - lastX;
    float yoffset = lastY - posy; 
    lastX = posx;
    lastY = posy;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    vec3 direction;
    direction[0] = cos((yaw)*0.01745329251) * cos((pitch)*0.01745329251);
    direction[1] = sin((pitch)*0.01745329251);
    direction[2] = sin((yaw)*0.01745329251) * cos((pitch)*0.01745329251);
	for(i=0;i<3;i++){
		cameraFront[i] = direction[i];
		//printf("%d: %d", i,cameraFront[i]);
	}
	//printf("\n");
}
static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if(key == GLFW_KEY_W && (action == GLFW_REPEAT)){
		int i;
		for(i=0;i<3;i++){
			cameraPos[i] +=camSpeed*deltaTime*cameraFront[i];
		}
	}
	if(key == GLFW_KEY_S &&  (action == GLFW_REPEAT)){
		int i;
		for(i=0;i<3;i++){
			cameraPos[i] -=camSpeed*deltaTime*cameraFront[i];
		}
	}
	if(key == GLFW_KEY_A &&  (action == GLFW_PRESS || action == GLFW_REPEAT)){
		vec3 temp;
		int i;
		//vec3_norm(cameraFront,cameraUp);
		vec3_mul_cross(temp,cameraFront,cameraUp);
		for(i=0;i<3;i++){
			cameraPos[i] -=camSpeed*deltaTime*temp[i];
		}
	}
	if(key == GLFW_KEY_D &&  (action == GLFW_PRESS || action == GLFW_REPEAT)){
		vec3 temp;
		int i;
		//vec3_norm(cameraFront,cameraUp);
		vec3_mul_cross(temp,cameraFront,cameraUp);
		for(i=0;i<3;i++){
			cameraPos[i] +=camSpeed*deltaTime*temp[i];
		}	
	}
	if(key == GLFW_KEY_Q &&  (action == GLFW_PRESS || action == GLFW_REPEAT)){
		camSpeed++;
	}
	if(key == GLFW_KEY_E &&  (action == GLFW_PRESS || action == GLFW_REPEAT)){
		camSpeed--;
	}
}
//refaire vect3 add et vec3 scale !
void Init_GLFW_GLEW(int Width, int Height, const char* WindowName){
//Initialize the librairy
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	
	printf("[INFO] Initalising GLFW...\n");
	if(!glfwInit()){
		printf("[ERROR] Error initalising glfw\n");
		abort();
	}
	printf("[INFO] Compiled against GLFW %i.%i.%i\n",
       GLFW_VERSION_MAJOR,
       GLFW_VERSION_MINOR,
       GLFW_VERSION_REVISION);
	printf("[INFO] Running against GLFW %i.%i.%i\n", major, minor, revision);	

	   
	printf("[INFO] Creating window: %d by %d\n", Width, Height);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	gWindow = glfwCreateWindow(Width, Height, WindowName, NULL, NULL);
	if(!gWindow){//test gwindow; if null then terminate program
		glfwTerminate();
		printf("[ERROR] Error creating the window\n");
		abort();
	}
	// Make the window's context current 
	printf("[INFO] Making glfw context...\n");
	glfwMakeContextCurrent(gWindow);
	printf("[INFO] Initalising GLEW...\n");
	GLenum err = glewInit();
	if(GLEW_OK != err){
		printf("%s\n", glewGetErrorString(err));
		abort();
	}
	if(!GLEW_VERSION_2_0){
		printf("[ERROR] Error, your graphic card does not support OpenGl 2.0\n");
		abort();
	}
	printf("[INFO] Using GLEW version :%s\n", glewGetString(GLEW_VERSION));
}
