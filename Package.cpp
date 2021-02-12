#include "Package.h"
#include <stdlib.h>
#include <iostream>

Package::Package() {}

Package::Package(packageSize _size, std::string _description)
{
    Package::size = _size;
    Package::description = _description;
}

Package::~Package()
{
    //std::cout << "Ware aus dem Lager ausgelagert\n";
}

int Package::getID() const{
    return packageID;
}

void Package::setID(int ID){
    packageID = ID;
}

Package::packageSize Package::getSize() const{
    return size;
}

std::string Package::getDescription() const{
    return description;
}
