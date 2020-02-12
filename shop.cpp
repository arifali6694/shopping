#include "shop.h"

void Customer::shoppingList(orderList shoppingList){
    m_shoppingList = shoppingList;
};

Products&& Customer::doShopping(Shop& shop){
    return shop.buy(m_shoppingList);
};

void Customer::putInTrolley(Products&& products){
    for (auto &p : products){
        m_trolley.push_back(std::move(p));
        std::cout << std::to_string(p->name) << " " << p->price << " " << p->quantity << std::endl;
    }
};

Products&& Shop::buy(orderList shoppingList){
    for (auto& c : shoppingList) {
        size_t count(0); //reset count for each food
        for (auto& s : m_stockList) {//iterate shop's current stock
            if (count < 1){
                if (s != nullptr && c.first == s->name){
                    s->quantity = c.second; //quantity odered by customer
                    s->price = s->price * c.second * markupRate; // price for quantity
                    m_checkout.push_back(std::move(s)); //move product from stock to checkout
                    ++count;
                }
            } else{ break;}
        }
    }
    return std::move(m_checkout);
};

void Shop::supplyList(orderList supplyList){
    m_supplyList = supplyList;
};

void Shop::buySupplies(Supplier& sup){
    m_stockList = sup.buy(m_supplyList);
};

void Shop::printstock(){
    std::cout << "\nCurrent stock:" << std::endl;
    for (auto &p : m_stockList){
        if(p != nullptr){
            std::cout << "item: " << p->name  << std::endl;}
        }
};

void Shop::markup(){
    for (auto& p : m_checkout){
        double price = p->price;
        p->price = price * markupRate;
    }
};

Products&& Supplier::buy(orderList shoppingList){
    for (auto& c : shoppingList){
            m_checkout.push_back(std::unique_ptr<Product>(new Product(c.first, 1, m_priceList[c.first])));
    }
    return std::move(m_checkout);
};