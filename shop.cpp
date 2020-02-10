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
                    //double price = s->price;
                    s->price = s->price * c.second * markupRate; // price for quantity
                    m_checkout.push_back(std::move(s)); //move product from stock to checkout
                    ++count;
                    //continue;
                }
            } else{ break;}
        }//if (count < 1){//if product not in shop stock, send order to supplier
        
        //    orderList m ={{c.first,(c.second-count)}};
        //    m_supplier->recv(m);
        //}
    }
    //markup();
    //m_customer->putInTrolley(std::move(m_checkout));//move checkout products into customer's trolley
    return std::move(m_checkout);
};

void Shop::supplyList(orderList supplyList){
    m_supplyList = supplyList;
};

void Shop::buySupplies(Supplier& sup){
    m_stockList = sup.buy(m_supplyList);
}
void Shop::printstock(){
    std::cout << "\ncurrent stock:" << std::endl;
    for (auto &p : m_stockList){
        if(p != nullptr){
            std::cout << "item: " << p->name  << std::endl;}
        }
};

// void Shop::putInCheckout(Products&& products){
//     for (auto& p : products){
//         m_checkout.push_back(std::move(p));
//     }
// };

void Shop::markup(){
    for (auto& p : m_checkout){
        double price = p->price;
        p->price = price * markupRate;
    }
};

// void Shop::register_customer(Customer& c){
//     m_customer = std::make_unique<Customer>(&c);
// };

// void Supplier::register_shop(Shop& s){
//     m_shop = std::make_shared<Shop>(&s);
// };

Products&& Supplier::buy(orderList shoppingList){
    for (auto& c : shoppingList){
        //for ( int i = 0; i < c.second; ++i){
            m_checkout.push_back(std::unique_ptr<Product>(new Product(c.first, 1, m_priceList[c.first])));
        //}
        //m_shop->putInCheckout(std::move(m_checkout));//put new products into shop checkout
    }
    return std::move(m_checkout);
};