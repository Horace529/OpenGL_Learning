#include <glad/glad.h> 
#include <GLFW\glfw3.h>
#include <iostream>
#include "ShaderReader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //just for MacOS
#ifdef __APPLE__ 
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	//to read vertex shader file and compile it
    std::string vertexShaderSourceStr = readShaderFile("Shaders/vertex.glsl");
	const char* vertexShaderSource = vertexShaderSourceStr.c_str();
#ifdef _DEBUG//will not be included in release build, only for debugging purposes
    std::cout << "Vertex shader source length: " << vertexShaderSourceStr.size() << std::endl;
    std::cout << "First 50 chars of Vertex shader: " << vertexShaderSourceStr.substr(0, 50) << std::endl;
    std::cout << "Vertex Pointer address: " << (void*)vertexShaderSource << std::endl;
#endif
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
    // check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

	//to read fragment shader file and compile it
    std::string fragmentShaderSourceStr = readShaderFile("Shaders/fragment.glsl");
    const char* fragmentShaderSource = fragmentShaderSourceStr.c_str();
#ifdef _DEBUG//will not be included in release build, only for debugging purposes
    std::cout << "Fragment shader source length: " << fragmentShaderSourceStr.size() << std::endl;
    std::cout << "First 50 chars of Fragment shader: " << fragmentShaderSourceStr.substr(0, 50) << std::endl;
    std::cout << "Fragment Pointer address: " << (void*)fragmentShaderSource << std::endl;
#endif
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    //to link shaders into a shader program
    unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
	
    //delete the shader objects after linking
    glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//set up vertex data and buffers and configure vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
    float Vertices[] = {
        -0.5f, -0.5f, -0.3f, // left  
         0.5f, -0.5f, 0.2f, // right 
         -0.6f,  0.5f, 0.0f,  // top   left
         0.6f,  0.5f, 0.0f  // top   right
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,  // first triangle
        0, 1, 3   // second triangle
	};


	//just an ID for the vertex buffer object and vertex array object
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//main loop
    while (!glfwWindowShouldClose(window))
    {   

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}