#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <iostream>

enum food {beans, egg, bread, milk, beans_6pk, egg_12pk};

using orderList = std::map<food, double>;

class Supplier{
    public:
    Supplier();
    ~Supplier();
    void recv(orderList& shoppingList);
    void register_shop(Shop& s);

    private:
    orderList m_priceList = {{food::beans, 0.30}, {food::egg, 0.1}, {food::bread, 0.5}, {food::milk, 0.7}, {food::beans_6pk, 1.5}, {food::egg_12pk, 1.2}};
    std::vector<std::unique_ptr<Product>> m_checkout;
    std::shared_ptr<Shop> m_shop;

};
struct Product {
    Product(food value, size_t quantity, double price) : name(value), quantity(quantity), price(price) {}
    food name;
    size_t quantity;
    double price;
};

class Shop {
    public:
    Shop(Supplier& sup);
    ~Shop();
    void recv(orderList shoppingList);
    void putInCheckout (std::vector<std::unique_ptr<Product>> &&);
    void Shop::register_customer(Customer& c);

    private:
    void markup();
    std::unique_ptr<Supplier> m_supplier;
    orderList m_customerList;
    std::vector<std::unique_ptr<Product>> m_stockList;
    std::vector<std::unique_ptr<Product>> m_checkout;
    std::unique_ptr<Customer> m_customer;

    double markupRate = 1.25;
};

class Customer {
    public:
    Customer(Shop& s);
    ~Customer();
    void push(orderList&);
    void putInTrolley(std::vector<std::unique_ptr<Product>> &&);
    //Customer(std::map<food,int>);

    private:
    orderList m_shoppingList;
    std::shared_ptr<Shop> m_shop;
    std::vector<std::unique_ptr<Product>> m_trolley;
};