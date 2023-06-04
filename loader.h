#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#define L_OFFSET -1
struct Vertex {
	glm::vec3 position;
	glm::vec2 UV;
	glm::vec3 normal;
};
namespace mdload {
	inline void splitString(std::string inputString, char splitter, std::vector<std::string>* outSource) {
		std::string currentElement = "";
		for (size_t i = 0; i < inputString.size(); i++) {
			if (inputString[i] == splitter) {
				if (currentElement.size() > 0) {
					outSource->push_back(currentElement);
					currentElement = "";
				}
				continue;
			}
			currentElement += inputString[i];
		}
		if (currentElement.size() > 0) {
			outSource->push_back(currentElement);
		}
	}
	inline void loadModel(std::string fileSource, std::vector<Vertex>* vertexDst) {
		std::vector<Vertex> rawVertexData;
		std::vector<glm::vec3> loadedModelVertexPositions;
		std::vector<glm::vec3> loadedModelVertexNormals;
		std::vector<glm::vec2> loadedModelVertexUVs;
		std::vector<std::string> fElements;
		std::vector<std::string> lines;
		splitString(fileSource, '\n', &lines);
		std::vector<std::string> lineElements;
		glm::vec3 centerLoc;
		unsigned int verticeCount = 0;
		for (size_t i = 0; i < lines.size(); i++) {
			if (lines[i].size() == 0)
				continue;
			if (lines[i][0] == '#')
				continue;
			lineElements.clear();
			splitString(lines[i], ' ', &lineElements);
			if (lineElements[0] == "v") {
				glm::vec3 vert(std::atof(lineElements[1].c_str()), std::atof(lineElements[2].c_str()), std::atof(lineElements[3].c_str()));
				loadedModelVertexPositions.push_back(vert);
				verticeCount++;
				centerLoc += vert;
				continue;
			}
			if (lineElements[0] == "vn") {
				loadedModelVertexNormals.push_back(glm::vec3(std::atof(lineElements[1].c_str()), std::atof(lineElements[2].c_str()), std::atof(lineElements[3].c_str())));
				continue;
			}
			if (lineElements[0] == "vt") {
				loadedModelVertexUVs.push_back(glm::vec2(std::atof(lineElements[1].c_str()), std::atof(lineElements[2].c_str())));
			}
			if (lineElements[0] == "f") {
				unsigned int vLoc1, uvLoc1, nLoc1;
				unsigned int vLoc2, uvLoc2, nLoc2;
				unsigned int vLoc3, uvLoc3, nLoc3;
				unsigned int vLoc4, uvLoc4, nLoc4;
				if (lineElements.size() == 4) {
					//triangle
					fElements.clear();
					splitString(lineElements[1], '/', &fElements);
					vLoc1 = atol(fElements[0].c_str()) + L_OFFSET;
					uvLoc1 = atol(fElements[1].c_str()) + L_OFFSET;
					nLoc1 = atol(fElements[2].c_str()) + L_OFFSET;
					fElements.clear();
					splitString(lineElements[2], '/', &fElements);
					vLoc2 = atol(fElements[0].c_str()) + L_OFFSET;
					uvLoc2 = atol(fElements[1].c_str()) + L_OFFSET;
					nLoc2 = atol(fElements[2].c_str()) + L_OFFSET;
					fElements.clear();
					splitString(lineElements[3], '/', &fElements);
					vLoc3 = atol(fElements[0].c_str()) + L_OFFSET;
					uvLoc3 = atol(fElements[1].c_str()) + L_OFFSET;
					nLoc3 = atol(fElements[2].c_str()) + L_OFFSET;
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc1],loadedModelVertexUVs[uvLoc1],loadedModelVertexNormals[nLoc1] });
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc2],loadedModelVertexUVs[uvLoc2],loadedModelVertexNormals[nLoc2] });
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc3],loadedModelVertexUVs[uvLoc3],loadedModelVertexNormals[nLoc3] });
				}
				else if (lineElements.size() == 5) {
					//quad
					fElements.clear();
					splitString(lineElements[1], '/', &fElements);
					vLoc1 = atol(fElements[0].c_str()) + L_OFFSET;
					uvLoc1 = atol(fElements[1].c_str()) + L_OFFSET;
					nLoc1 = atol(fElements[2].c_str()) + L_OFFSET;
					fElements.clear();
					splitString(lineElements[2], '/', &fElements);
					vLoc2 = atol(fElements[0].c_str()) + L_OFFSET;
					uvLoc2 = atol(fElements[1].c_str()) + L_OFFSET;
					nLoc2 = atol(fElements[2].c_str()) + L_OFFSET;
					fElements.clear();
					splitString(lineElements[3], '/', &fElements);
					vLoc3 = atol(fElements[0].c_str()) + L_OFFSET;
					uvLoc3 = atol(fElements[1].c_str()) + L_OFFSET;
					nLoc3 = atol(fElements[2].c_str()) + L_OFFSET;
					fElements.clear();
					splitString(lineElements[4], '/', &fElements);
					vLoc4 = atol(fElements[0].c_str()) + L_OFFSET;
					uvLoc4 = atol(fElements[1].c_str()) + L_OFFSET;
					nLoc4 = atol(fElements[2].c_str()) + L_OFFSET;
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc1],loadedModelVertexUVs[uvLoc1],loadedModelVertexNormals[nLoc1] });
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc2],loadedModelVertexUVs[uvLoc2],loadedModelVertexNormals[nLoc2] });
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc3],loadedModelVertexUVs[uvLoc3],loadedModelVertexNormals[nLoc3] });
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc1],loadedModelVertexUVs[uvLoc1],loadedModelVertexNormals[nLoc1] });
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc3],loadedModelVertexUVs[uvLoc3],loadedModelVertexNormals[nLoc3] });
					rawVertexData.push_back(Vertex{ loadedModelVertexPositions[vLoc4],loadedModelVertexUVs[uvLoc4],loadedModelVertexNormals[nLoc4] });
				}
			}
		}
		if (verticeCount > 0) {
			centerLoc /= verticeCount;
			for (unsigned int i = 0; i < rawVertexData.size(); i++) {
				vertexDst->push_back(Vertex{ rawVertexData[i].position - centerLoc,rawVertexData[i].UV,rawVertexData[i].normal });
			}
		}
	}
}
