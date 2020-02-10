#include "shop.h"


namespace{
    void print(Products list){
        std::cout << "\nItems bought:\n";
        for (auto &p : list){
            std::cout << "item: " << p->name <<" price: "<< p->price << " quantity: " << p->quantity << std::endl;
        }
    }
}

int main(){
    Supplier sup;
    Shop tesco;
    //sup.register_shop(Tesco);
    Customer arif;
    //Tesco.register_customer(arif);

    tesco.printstock();
    orderList ariforder1 = {{beans, 1}, {egg, 10}};
    arif.shoppingList(ariforder1);
    Products trolley; 
    trolley = arif.doShopping(tesco);
    print(std::move(trolley));

    orderList shopSupplies = {{beans, 1}, {egg, 1}, {milk, 1}, {bananas, 1}};
    tesco.supplyList(shopSupplies);
    tesco.buySupplies(sup);
    tesco.printstock();

    Products trolley2 ;
    trolley2 = arif.doShopping(tesco);
    print(std::move(trolley2));
    tesco.printstock();

    Products trolley3;
    orderList ariforder2 = {{milk, 1}, {bananas, 3.5}};
    arif.shoppingList(ariforder2);
    trolley3 = arif.doShopping(tesco);
    print(std::move(trolley3));
    tesco.printstock();


    return 0;
}
