#include "commons.cpp";

struct Product{
    string name;
    string size;
    float price = 0.0;
};

struct ProductNode{
    Product product;

    Product* previous = nullptr;
    Product* next = nullptr;
};