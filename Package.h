#ifndef PACKAGE_H
#define PACKAGE_H
#include <iostream>

class Package
{
public:
    enum packageSize { small, medium, big };

private:
    bool isEmpty;
    int packageID;
    packageSize size;
    std::string description;

public:
    Package();
    Package(packageSize _size, std::string _description);
    ~Package();
    int getID() const;
    void setID(int ID);
    packageSize getSize() const;
    std::string getDescription() const;
};

#endif // PACKAGE_H