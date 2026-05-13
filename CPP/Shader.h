#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	unsigned int ID; // the program ID
	Shader(const char* vertexPath, const char* fragmentPath);

	//to use/activate the shader
	void use();

	//let's write a Template function to set uniform variables in the shader
	template<typename T>
	void setUniform(const std::string& name, T value) const;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
	
};

// ===================================================
// All specializations of the setUniform function in merely one function
// ===================================================
template<typename T>
void Shader::setUniform(const std::string& name, T value) const
    {   
        int loc = glGetUniformLocation(ID, name.c_str());
#ifdef _DEBUG
        if (loc == -1) {
            std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
        }
#endif 
        if constexpr (std::is_same_v<T, int> || std::is_same_v<T, bool>) {
            glUniform1i(loc, static_cast<int>(value));
        }
        else if constexpr (std::is_same_v<T, float>) {
            glUniform1f(loc, value);
        }
        else if constexpr (std::is_same_v<T, glm::vec2>) {
            glUniform2fv(loc, 1, glm::value_ptr(value));
        }
        else if constexpr (std::is_same_v<T, glm::vec3>) {
            glUniform3fv(loc, 1, glm::value_ptr(value));
        }
        else if constexpr (std::is_same_v<T, glm::vec4>) {
            glUniform4fv(loc, 1, glm::value_ptr(value));
        }
        else if constexpr (std::is_same_v<T, glm::mat2>) {
            glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        }
        else if constexpr (std::is_same_v<T, glm::mat3>) {
            glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        }
        else if constexpr (std::is_same_v<T, glm::mat4>) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        }
        else {
            static_assert(sizeof(T) == 0, "Unsupported uniform type");
        }
}


#endif // !SHADER_H

