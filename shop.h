#include <iostream>
#include <memory>
#include <map>
#include <vector>

enum food {beans, egg, bread, milk, bananas};

using orderList = std::map<food, double>;

struct Product {
    Product(food value, size_t quantity, double price) : name(value), quantity(quantity), price(price) {}
    food name;
    double quantity;
    double price;
};

using Products = std::vector<std::unique_ptr<Product>>;

class Supplier{
    public:
    Products&& buy(orderList shoppingList);

    private:
    orderList m_priceList = {{food::beans, 0.30}, {food::egg, 0.1}, {food::bread, 0.5}, {food::milk, 0.7}, {bananas, 1}};
    Products m_checkout;

};

class Shop {
    public:
    Products&& buy(orderList shoppingList);
    void supplyList(orderList);
    void buySupplies(Supplier& s);
    void printstock();

    private:
    void markup();
    std::unique_ptr<Supplier> m_supplier;
    orderList m_customerList;
    orderList m_supplyList;
    Products m_stockList;
    Products m_checkout;
    double markupRate = 1.25;
};

class Customer {
    public:
    Products&& doShopping(Shop& s);
    void shoppingList(orderList);
    void putInTrolley(Products&&);

    private:
    orderList m_shoppingList;
    std::shared_ptr<Shop> m_shop;
    Products m_trolley;
};