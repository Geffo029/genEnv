#include "RawData.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>



using namespace gen;


std::vector<std::string> split(std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}


obj::data obj::readFile(const char *ObjFile) {
	std::vector<float> verticesVector;
	std::vector<float> vTextureVector;
	std::vector<float> vNormalsVector;
	std::vector<unsigned short> facesVector;

	std::ifstream fileReader(ObjFile);
	std::string line;
	while (getline(fileReader, line)) {
		char lineHeader[3];

		if (line.at(0) == 'v') {
			float values[3];
			int reads = sscanf(line.c_str(), "%s %f %f %f", lineHeader, &values[0], &values[1], &values[2]);
			std::vector<float> *currentVector = nullptr;
			
			std::string header = std::string(lineHeader);
			if (header.compare("v") == 0) currentVector = &verticesVector;
			else if (header.compare("vt") == 0) currentVector = &vTextureVector;
			else if (header.compare("vn") == 0) currentVector = &vNormalsVector;

			for (int i = 0; i < reads-1; i++) {
				currentVector->push_back(values[i]);
			}
		} else if (line.at(0) == 'f') {
			int values[3][3];
			int reads = sscanf(line.c_str(), "%s %d/%d/%d %d/%d/%d %d/%d/%d", lineHeader, 
			                   &values[0][0], &values[0][1], &values[0][2], &values[1][0], &values[1][1], &values[1][2],
			                   &values[2][0], &values[2][1], &values[2][2]);
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++) 
					{ facesVector.push_back(values[i][j]); }
		}
	}

	obj::data data;
	data.vCount = verticesVector.size();
	data.vDimension = 3;
	data.v = new float[data.vCount];
	data.vtCount = vTextureVector.size();
	data.vtDimension = 2;
	data.vt = new float[data.vtCount];
	data.vnCount = vNormalsVector.size();
	data.vnDimension = 3;
	data.vn = new float[data.vnCount];
	data.fCount = facesVector.size();
	data.fDimension = 3;
	data.f = new unsigned short[data.fCount];

	for (int i = 0; i < verticesVector.size(); i++) data.v[i] = verticesVector.at(i);
	for (int i = 0; i < vTextureVector.size(); i++) data.vt[i] = vTextureVector.at(i);
	for (int i = 0; i < vNormalsVector.size(); i++) data.vn[i] = vNormalsVector.at(i);
	for (int i = 0; i < facesVector.size(); i++) data.f[i] = facesVector.at(i);

	return data;
}

obj::data::~data()
{
	vCount = 0;
	vDimension = 0;
	delete v;
	vtCount = 0;
	vtDimension = 0;
	delete vt;
	vnCount = 0;
	vnDimension = 0;
	delete vn;
	fCount = 0;
	fDimension = 0;
	delete f;
	f = nullptr;
}

void obj::cleanup(obj::data data)
{
	data.vCount = 0;
	data.vDimension = 0;
	delete data.v;
	data.vtCount = 0;
	data.vtDimension = 0;
	delete data.vt;
	data.vnCount = 0;
	data.vnDimension = 0;
	delete data.vn;
	data.fCount = 0;
	data.fDimension = 0;
	delete data.f;
	data.f = nullptr;
}


image::data image::readFile(const char *imageFile)
{
	image::data data;
	stbi_set_flip_vertically_on_load(true);  
	data.pixels = stbi_load(imageFile, &data.width, &data.height, &data.channelsCount, 0); 
	return data;
}

image::data::~data()
{
	width = 0;
	height = 0;
	channelsCount = 0;
	delete pixels;
	pixels = nullptr;
}


void image::cleanup(image::data data)
{
	data.width = 0;
	data.height = 0;
	data.channelsCount = 0;
	delete data.pixels;
	data.pixels = nullptr;
}
