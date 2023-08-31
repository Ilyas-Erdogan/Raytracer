#pragma once
#include "Object.h"
#include <string>

class Group :
    public Object, public std::enable_shared_from_this<Group>
{
public:
    // Constructors
    Group(const std::string name = "");
    ~Group();

    virtual const std::vector<class Intersection> localIntersect(const class Ray& localRay);
    virtual const Vector localNormalAt(const class Point& localPoint, const Intersection& hit) const;
    virtual std::shared_ptr<class Group> toGroup() override;
    // Utility
    const bool isEmpty() const;
    const std::vector<std::shared_ptr<Object>>& getChildren() const;
    void addChild(const std::shared_ptr<Object>& shape);

    //Getters
    const std::string getName() const;
private:
    std::vector<std::shared_ptr<Object>> children;
    std::string name;
};

