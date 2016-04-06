#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glew.h>
#include <glm\glm.hpp>

using namespace std;

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	bool loadObject(const char* path, std::vector<glm::vec3>& out_vertices, std::vector<unsigned int>& out_indices, std::vector<glm::vec3>& out_normals);
};

