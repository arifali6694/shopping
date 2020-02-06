#include "shop.h"

Customer::Customer(Shop& s) {m_shop = std::make_shared<Shop>(&s);}

void Customer::push(orderList& shoppingList){
    m_shoppingList = shoppingList;
    m_shop->recv(m_shoppingList);
};

void Customer::putInTrolley(std::vector<std::unique_ptr<Product>> && products){
    for (auto &p : products){
        m_trolley.push_back(std::move(p));
        std::cout << std::to_string(p->name) << " " << p->price << " " << p->quantity << std::endl;
    }
};

Shop::Shop(Supplier& s) {*m_supplier = s;} //std::make_unique<Shop>(&s)

void Shop::recv(orderList shoppingList){
    m_customerList = shoppingList;
    for (auto& c : m_customerList) {
        size_t count(0); //reset count for each food
        for (auto& s : m_stockList) {//iterate shop's current stock
            if (count < c.second){
                if (c.first == s->name){
                    m_checkout.push_back(std::move(s)); //move product from stock to checkout
                    ++count;
                    //continue;
                }
            } else{ break;}

        }if (count < c.second){ //if product not in shop stock, send order to supplier
            orderList m ={{c.first,(c.second-count)}};
            m_supplier->recv(m);
        }
    }
    markup();
    m_customer->putInTrolley(std::move(m_checkout));//move checkout products into customer's trolley
};

void Shop::putInCheckout(std::vector<std::unique_ptr<Product>>&& products){
    for (auto& p : products){
        m_checkout.push_back(std::move(p));
    }
};

void Shop::markup(){
    for (auto& p : m_checkout){
        double price = p->price;
        p->price = price * markupRate;
    }
};

void Shop::register_customer(Customer& c){
    m_customer = std::make_unique<Customer>(&c);
};

void Supplier::register_shop(Shop& s){
    m_shop = std::make_shared<Shop>(&s);
};

void Supplier::recv(orderList& shoppingList){
    for (auto& c : shoppingList) {
        for ( int i = 0; i < c.second; ++i){
            m_checkout.push_back(std::unique_ptr<Product>(new Product(c.first, 1, m_priceList[c.first])));
        }
        m_shop->putInCheckout(std::move(m_checkout));//put new products into shop checkout
    }
};