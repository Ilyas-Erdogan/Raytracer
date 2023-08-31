#include "Parser.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include "Primitives/Triangle.h"
#include "Primitives/SmoothTriangle.h"

Parser::Parser(const std::string fileToOpen)
	: file{fileToOpen}
{
}

Parser::~Parser()
{
}

const int Parser::parseOBJFile()
{
	// Get current file directory
	std::string dir = std::filesystem::current_path().string();
	// Create file stream for object file
	std::ifstream OBJFile(this->file);
	// Ignored line bount to return
	int ignoredLines = 0;
	// Variable to hold line information fed from OBJ file
	std::string line;

	// Check if file was found
	if (OBJFile.is_open())
	{
		// Iterate through each line of the file
		while (std::getline(OBJFile, line))
		{
			// Found vertex
			if (line[0] == 'v')
			{
				// Found normals
				if (line[1] == 'n')
				{
					// Add normal
					std::vector<double> normalCoords = this->parseNormals(line.substr(3));
					this->normals.push_back(Vector(normalCoords[0], normalCoords[1], normalCoords[2]));
				}
				else
				{
					// Get coordinates
					std::vector<double> coordinates = this->parseVertexCommand(line.substr(2));
					// Create and add point to list
					Point pointToAdd(coordinates[0], coordinates[1], coordinates[2]);
					this->vertices.push_back(pointToAdd);
				}
			}

			// Found face
			else if (line[0] == 'f')
			{
				if (this->hasSlashes(line.substr(2)))
				{
					std::vector<std::pair<int, int>> indices = this->parseFaceWithNormals(line.substr(2));
					std::shared_ptr<SmoothTriangle> st = std::make_shared<SmoothTriangle>(this->vertices[indices[0].first], this->vertices[indices[1].first], this->vertices[indices[2].first], this->normals[indices[0].second], this->normals[indices[1].second], this->normals[indices[2].second]);
					this->getMostRecentGroup()->addChild(st);
				}
				else
				{
					// Get 1 based indices
					std::vector<int> indices = this->parseFaceCommand(line.substr(2));
					// Singular triangle detected
					if (indices.size() == 3)
					{
						// Create triangle and add as child
						std::shared_ptr<Triangle> t = std::make_shared<Triangle>(this->vertices[indices[0]], this->vertices[indices[1]], this->vertices[indices[2]]);
						this->getMostRecentGroup()->addChild(t);
					}
					// Convex polygon detected
					else if (indices.size() > 3)
					{
						// Triangulate and add as children
						for (const std::shared_ptr<Triangle>& triangle : this->fanTriangulation(indices))
						{
							this->getMostRecentGroup()->addChild(triangle);
						}
					}
				}
			}
			// Found group
			else if (line[0] == 'g')
			{
				// Constructs new group with given name
				std::shared_ptr<Group> newGroup = std::make_shared<Group>(line.substr(2));
				this->mostRecentGroup = newGroup;
				this->defaultGroup->addChild(newGroup);
			}
			else
			{
				// No command found, ignore line
				ignoredLines++;
			}
		}
	}

	return ignoredLines;
}

/**
* Takes a string of values on turns it in a vector of doubles
* 
* @param std::string susbtr String to parse.
* 
* @return An immutable vector containing the three values of the vertex
*/
const std::vector<double> Parser::parseVertexCommand(std::string substr) const
{
	std::stringstream ss(substr);
	std::vector<double> v;

	// Add each coordinate value to the vector
	while (std::getline(ss, substr, ' '))
	{
		v.push_back(std::stod(substr));
	}

	return v;
}

const std::vector<int> Parser::parseFaceCommand(std::string substr) const
{
	std::stringstream ss(substr);
	std::vector<int> v;

	// Add each verted index to the vector
	while (std::getline(ss, substr, ' '))
	{
		v.push_back(std::stoi(substr));
	}

	return v;
}


const std::vector<double> Parser::parseNormals(std::string substr) const
{
	std::stringstream ss(substr);
	std::vector<double> v;

	// Add each coordinate value to the vector
	while (std::getline(ss, substr, ' '))
	{
		v.push_back(std::stod(substr));
	}

	return v;
}

const std::vector<std::pair<int, int>> Parser::parseFaceWithNormals(std::string substr) const
{
	std::vector<std::string> splitted;
	std::stringstream ss(substr);

	while (std::getline(ss, substr, ' '))
	{
		splitted.push_back(std::string(substr));
	}

	std::vector<std::pair<int, int>> indices;

	for (const std::string& s : splitted)
	{
		indices.push_back(std::make_pair<int, int>(std::stoi(s.substr(0,1)), std::stoi(s.substr(s.length() - 1, 1))));
	}

	return indices;
}

/**
* Triangulates polygons based on the provided indices from the vertex list of the calling class.
* 
* @param std::vector<int> Immutable reference to the indices of the face.
* 
* @return A list of all the triangles produced from the triangulation.
*/
const std::vector<std::shared_ptr<Triangle>> Parser::fanTriangulation(const std::vector<int>& indices) const
{
	std::vector<std::shared_ptr<Triangle>> triangles = {};

	for (int i = 2; i < this->vertices.size(); i++)
	{
		triangles.push_back(std::make_shared<Triangle>(this->vertices[indices[0]], this->vertices[indices[i-1]], this->vertices[indices[i]]));
	}

	return triangles;
}

/**
* @return A shared pointer of an OBJ file converted to a group.
*/
const std::shared_ptr<Group> Parser::objToGroup()
{
	this->parseOBJFile();
	return this->defaultGroup;
}

bool Parser::hasSlashes(std::string substr) const
{
	for (const char& c : substr)
	{
		if (c == '/')
		{
			return true;
		}
	}

	return false;
}

/**
* @return An immutable reference to the list of vertices that the parser has collected.
*/
const VectorB1& Parser::getVertices() const
{
	return this->vertices;
}

/**
* @return An immutable reference to the list of normals that the parser has collected.
*/
const VectorB2& Parser::getNormals() const
{
	return this->normals;
}

/**
* @return An immutable reference to the group.
*/
const std::shared_ptr<Group>& Parser::getDefaultGroup() const
{
	return this->defaultGroup;
}

/**
* @return An immutable reference to the most recently added group.
*/
const std::shared_ptr<Group>& Parser::getMostRecentGroup() const
{
	if (this->mostRecentGroup == nullptr)
	{
		return this->defaultGroup;
	}
	return this->defaultGroup->getChildren().back()->toGroup();
}
