#include "Shader.h"



Shader::Shader() {
}


Shader::~Shader() {
}

bool Shader::load() {
	GLuint v = compile(GL_VERTEX_SHADER);
	GLuint f = compile(GL_FRAGMENT_SHADER);
	if (v == 0 || f == 0) {
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);
	glLinkProgram(program);

	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (result != 0) {
		return true;
	}

	GLint logLength;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	GLchar* eLog = new GLchar[logLength];

	glGetProgramInfoLog(program, logLength, 0, eLog);

	std::cout << "Shaders failed to link: " << std::endl << eLog << std::endl;  // Debug shaders

	glDeleteProgram(program);

	delete[] eLog;

	return false;
}

bool Shader::compile(GLenum shaderType) {
	std::string filename;

	if (shaderType == GL_VERTEX_SHADER) {
		filename = filenamev;
	}
	if (shaderType == GL_FRAGMENT_SHADER) {
		filename = filenamef;
	}
	
	std::ifstream instream(filename, std::ios::binary);
	if (!instream.is_open()) return nullptr;

	// Get Length
	instream.seekg(0, std::ios::end);    // go to end
	int length = (int)instream.tellg();  // count length
	instream.seekg(0, std::ios::beg);    // go to begin

										 // Read
	char* bytes = new char[length + 1];
	bytes[length] = '\0';
	instream.read(bytes, length);

	// Close
	instream.close();

	GLuint index = glCreateShader(shaderType);  // Creates a shader depending on the shader type
	if (shaderType == GL_VERTEX_SHADER) {  // If the shader is a vertex shader
		vprogram = index;
	}
	if (shaderType == GL_FRAGMENT_SHADER) {  // If the shader is a fragment shader
		fprogram = index;
	}
	glShaderSource(index, 1, &bytes, 0);
	glCompileShader(index);

	delete[] bytes;

	GLint results;

	glGetShaderiv(index, GL_COMPILE_STATUS, &results);  // Will return 0 if the shader failed to compile

	if (results != 0) {
		return true;
	}

	GLint logLength;

	glGetShaderiv(index, GL_INFO_LOG_LENGTH, &logLength);

	GLchar* eLog = new GLchar[logLength];

	glGetShaderInfoLog(index, logLength, 0, eLog);
	std::cout << eLog << std::endl;  // Debug shaders
	glDeleteShader(index);

	delete[] eLog;

	return false;
}

void Shader::use() {
	glUseProgram(program);
}

void Shader::unload() {
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);

	program = 0;
	vprogram = 0;
	fprogram = 0;
}

GLuint Shader::getProgram()
{
	return program;
}
