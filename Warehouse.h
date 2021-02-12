#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "Package.h"

class Warehouse
{
private:
    int maxPackages;
    Package* start;
    static int numofPackages;
    void sorting();

    void expand();
    void reduce();


public:
    Warehouse(int maxPackages);
    void print();
    void packageIn(Package* const p);
    void packageOut(int ID);
};

#endif // WAREHOUSE_H
