#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <iostream>

enum food {beans, egg, bread, milk};

using orderList = std::map<food, double>;

struct Product {
    Product(food value, size_t quantity, double price) : name(value), quantity(quantity), price(price) {}
    food name;
    size_t quantity;
    double price;
};

class Customer {
    public:
    Customer();
    void push(orderList&);
    void putInTrolley(std::vector<std::unique_ptr<Product>> &&);
    //Customer(std::map<food,int>);

    private:
    ~Customer();
    orderList m_shoppingList;
    std::shared_ptr<Shop> m_shop;
    std::vector<std::unique_ptr<Product>> m_trolley;
};

class Shop {
    public:
    Shop();
    std::vector<std::unique_ptr<Product>> recv(orderList shoppingList);
    void putInCheckout (std::vector<std::unique_ptr<Product>> &&);
    void Shop::register_customer(Customer& c);

    private:
    ~Shop();
    void markup();
    std::unique_ptr<Supplier> m_supplier;
    orderList m_customerList;
    std::vector<std::unique_ptr<Product>> m_stockList;
    std::vector<std::unique_ptr<Product>> m_checkout;
    std::shared_ptr<Customer> m_customer;

    double markupRate = 1.25;
};

class Supplier{
    public:
    void recv(orderList& shoppingList);
    void register_shop(Shop&);

    private:
    Supplier();
    ~Supplier();
    orderList m_priceList = {{food::beans, 0.30}, {food::egg, 0.4}, {food::bread, 0.5}, {food::milk, 0.7}};
    std::vector<std::unique_ptr<Product>> m_checkout;
    std::shared_ptr<Shop> m_shop;

};