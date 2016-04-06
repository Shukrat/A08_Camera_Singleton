#include "ModelLoader.h"
#pragma warning (disable : 4996)

ModelLoader::ModelLoader(){

}


ModelLoader::~ModelLoader(){

}

bool ModelLoader::loadObject(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<unsigned int>& out_indices, std::vector<glm::vec3>& out_normals) {
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	ifstream inFileBin(path, ios::in);
	if (!inFileBin.is_open()) return false;
	
	string line;
	while (getline(inFileBin, line)) {
		istringstream myISS = istringstream(line);

		string subString;
		myISS >> subString;

		if (subString == "v") {
			float subFloat1;
			float subFloat2;
			float subFloat3;
			myISS >> subFloat1;
			myISS >> subFloat2;
			myISS >> subFloat3;
			glm::vec3 vertex = glm::vec3(subFloat1, subFloat2, subFloat3);
			temp_vertices.push_back(vertex);
		}
		else if (subString == "vt") {
			float subFloat1;
			float subFloat2;
			myISS >> subFloat1;
			myISS >> subFloat2;
			glm::vec2 uv = glm::vec2(subFloat1, subFloat2);
			temp_uvs.push_back(uv);
		}
		else if (subString == "vn") {
			float subFloat1;
			float subFloat2;
			float subFloat3;
			myISS >> subFloat1;
			myISS >> subFloat2;
			myISS >> subFloat3;
			glm::vec3 normal = glm::vec3(subFloat1, subFloat2, subFloat3);
			temp_normals.push_back(normal);
		}
		else if (subString == "f") {
			int subVert1, subUV1, subNormal1, subVert2, subUV2, subNormal2, subVert3, subUV3, subNormal3;
			char slash;
			myISS >> subVert1;
				myISS >> slash;
			myISS >> subUV1;
				myISS >> slash;
			myISS >> subNormal1;

			myISS >> subVert2;
				myISS >> slash;
			myISS >> subUV2;
				myISS >> slash;
			myISS >> subNormal2;

			myISS >> subVert3;
				myISS >> slash;
			myISS >> subUV3;
				myISS >> slash;
			myISS >> subNormal3;
			vertexIndices.push_back(subVert1);
			vertexIndices.push_back(subVert2);
			vertexIndices.push_back(subVert3);
			uvIndices.push_back(subUV1);
			uvIndices.push_back(subUV2);
			uvIndices.push_back(subUV3);
			normalIndices.push_back(subNormal1);
			normalIndices.push_back(subNormal2);
			normalIndices.push_back(subNormal3);
		}
	}

	for (unsigned int i = 0; i < temp_vertices.size(); i++) {
		glm::vec3 vertex = temp_vertices[i];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int indices = vertexIndices[i] - 1;
		out_indices.push_back(indices);
	}
	for (unsigned int i = 0; i < temp_normals.size(); i++) {
		glm::vec3 normal = temp_normals[i];
		out_normals.push_back(normal);
	}

	return true;
}