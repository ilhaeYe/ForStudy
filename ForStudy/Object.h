#pragma once
#include <string>

class Object
{
public:
    Object();
    ~Object();

    void Setname(const std::string& name) { _name = name; }
    const std::string& GetName() const { return _name; }
    void SetX(const int x) { _x = x; }
    int GetX(const int x) const { return _x; }
    void SetY(const int y) { _y = y; }
    int GetY(const int y) const { return _y; }

private:
    std::string _name;
    int _x;
    int _y;

};

