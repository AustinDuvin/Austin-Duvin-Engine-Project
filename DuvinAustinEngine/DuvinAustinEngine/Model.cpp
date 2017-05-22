#include "Model.h"
#include "Model.h"



Model::Model() {
	vertArr = 0;
	vertCount = 0;
	maxXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	maxX = 0.0f;
	maxY = 0.0f;
	maxZ = 0.0f;
}


Model::~Model() {
}

bool Model::buffer(std::string objFile) {
	std::vector<glm::vec3> locations;  // Holds the locations of the vertices
	std::vector<glm::vec2> uvs;  // Holds the uvs of the vertices
	std::vector<glm::vec3> normals;  // Holds the normals of the vertices
	std::vector<VertInd> indices;

	std::ifstream instream;
	std::string line;
	instream.open(objFile);  // Gives object file to the input stream
	if (!instream.is_open()) return nullptr;

	while (getline(instream, line)) {
		std::istringstream lineStream(line);
		std::string label;

		lineStream >> label;  // Gets the label before each line to check what the data is

		if (label == "v") {  // If the data is location data
			float x;
			float y;
			float z;

			lineStream >> x >> y >> z;
			glm::vec3 loc(x, y, z);
			locations.insert(locations.end(), loc);

			if (loc.x > maxX) {
				maxX = loc.x;
			}

			if (loc.y > maxY) {
				maxY = loc.y;
			}

			if (loc.z > maxZ) {
				maxZ = loc.z;
			}
		}
		else if (label == "vt") {  // If the data is uv data
			float x;
			float y;

			lineStream >> x >> y;
			glm::vec2 uv(x, y);
			uvs.insert(uvs.end(), uv);
		}
		else if (label == "vn") {  // If the data is normal data
			float x;
			float y;
			float z;

			lineStream >> x >> y >> z;
			glm::vec3 norm(x, y, z);
			normals.insert(normals.end(), norm);
		}
		else if (label == "f") {  // If the data is a vertex
			for (int i = 0; i < 3; i++) {
				glm::uint loc;
				glm::uint uv;
				glm::uint norm;
				char slash;

				lineStream >> loc >> slash >> uv >> slash >> norm;
				loc--;
				uv--;
				norm--;
				VertInd index(loc, uv, norm);
				indices.insert(indices.end(), index);
			}
		}
	}

	maxXYZ = glm::vec3(maxX, maxY, maxZ);

	instream.close();

	// Define model vertex locations
	vertCount = indices.size();

	// Duplicate vertices into a single buffer
	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
		vertBufData[i] = { locations[indices[i].locInd], uvs[indices[i].uvInd], normals[indices[i].normInd] };  // Gives the vertex buffer the data from the .obj file

	GLuint vertBuf;

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertCount, &vertBufData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);  // Set vertex position

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));  // Set vertex uv
	
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(float)));  // Set fragment normal

	glBindVertexArray(0);  // Unbind VAO

	return true;
}

void Model::render() {
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
}
