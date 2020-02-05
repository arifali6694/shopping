#include <iostream>
#include <map>

struct Product {
std::string name;
size_t quantity;
};

class Shop {
    public:
    Shop();
    
    private:
    ~Shop();
    
    //recv();
};
enum class food {beans, egg, bread, milk};

class Customer {
    Customer();
    Customer(std::map<food,int>);
    ~Customer();

    void push();//push: shop_ptr->recv(m_shoplist)
    private:
    std::map<food, int> m_shoplist;
    

};