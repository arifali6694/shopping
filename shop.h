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
    // Supplier();
    // ~Supplier();
    //void recv(orderList& shoppingList);
    Products&& buy(orderList shoppingList);
    //void register_shop(Shop& s);

    private:
    orderList m_priceList = {{food::beans, 0.30}, {food::egg, 0.1}, {food::bread, 0.5}, {food::milk, 0.7}, {bananas, 1}};
    Products m_checkout;
    //std::shared_ptr<Shop> m_shop;

};

class Shop {
    public:
    // Shop();
    // ~Shop();
    Products&& buy(orderList shoppingList);
    void supplyList(orderList);
    void buySupplies(Supplier& s);
    void printstock();
    //void putInCheckout (Products &&);
    //void Shop::register_customer(Customer& c);

    private:
    void markup();
    std::unique_ptr<Supplier> m_supplier;
    orderList m_customerList;
    orderList m_supplyList;
    Products m_stockList;
    Products m_checkout;
    //std::unique_ptr<Customer> m_customer;

    double markupRate = 1.25;
};

class Customer {
    public:
    // Customer();
    // ~Customer();
    Products&& doShopping(Shop& s);
    void shoppingList(orderList);
    void putInTrolley(Products&&);
    //Customer(std::map<food,int>);

    private:
    orderList m_shoppingList;
    std::shared_ptr<Shop> m_shop;
    Products m_trolley;
};