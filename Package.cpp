#include "Package.h"
#include <stdlib.h>
#include <iostream>
#include <assert.h>


Package::Package() {
    isEmpty = true;
}

Package::Package(packageSize _size, std::string _description)
{
    Package::size = _size;
    Package::description = _description;
    isEmpty = false;
}

Package::~Package()
{
    //std::cout << "Ware aus dem Lager ausgelagert\n";
}

int Package::getID() const {
    assert(isEmpty == false);

    return packageID;
}

void Package::setID(int ID) {
    assert(isEmpty == false);

    packageID = ID;
    
}

Package::packageSize Package::getSize() const {
    assert(isEmpty == false);

    return size;
    
}

std::string Package::getDescription() const {
    assert(isEmpty == false);

    return description;
    
}

