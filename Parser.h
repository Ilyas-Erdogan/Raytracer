#include <string>
#include <vector>
#include "Types/Point.h"
#include "VectorB1.h"
#include "VectorB2.h"
#include "Primitives/Group.h"
#include "Primitives/Triangle.h"

class Parser
{
public:
	// Concstructor
	Parser(const std::string fileToOpen);
	~Parser();

	// Utility
	const int parseOBJFile();
	const std::vector<double> parseVertexCommand(std::string substr) const;
	const std::vector<int> parseFaceCommand(std::string substr) const;
	const std::vector<double> parseNormals(std::string substr) const;
	const std::vector<std::pair<int, int>> parseFaceWithNormals(std::string substr) const;
	const std::vector<std::shared_ptr<Triangle>> fanTriangulation(const std::vector<int>& indices) const;
	const std::shared_ptr<Group> objToGroup();
	bool hasSlashes(std::string substr) const;

	// Getters
	const VectorB1& getVertices() const;
	const VectorB2& getNormals() const;
	const std::shared_ptr<Group>& getDefaultGroup() const;
	const std::shared_ptr<Group>& getMostRecentGroup() const;
private:
	const std::string file;
	VectorB1 vertices;
	VectorB2 normals;
	std::shared_ptr<Group> defaultGroup = std::make_shared<Group>();
	std::shared_ptr<Group> mostRecentGroup = nullptr;
};