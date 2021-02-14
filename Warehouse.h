#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "Package.h"

class Warehouse
{
private:
    int maxPackages;
    Package* start;
    int numofPackages;
    void sorting();

    void expand();
    void reduce();


public:
    Warehouse(int _maxPackages);
    void print(bool sorted = false);
    void packageIn(Package* const p);
    Package packageOut(int ID, bool& found);
};

#endif // WAREHOUSE_H