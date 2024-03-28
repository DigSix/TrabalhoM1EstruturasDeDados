#include "commons.cpp";

struct Product{
    string name;
    string size;
    float price = 0.0;
};

struct ProductNode{
    Product product;

    ProductNode* previous = nullptr;
    ProductNode* next = nullptr;
};