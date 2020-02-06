#include "shop.h"

int main(){
    Supplier sup;
    Shop Tesco(sup);
    sup.register_shop(Tesco);
    Customer arif(Tesco);
    Tesco.register_customer(arif);

    orderList ariforder = {{beans, 1}, {egg, 1}};
    arif.push(ariforder);
    return 0;
}



