#include <scxx/scxx.hh>
#include <iostream>

int main (){
    // alph a("Hello world 2024");
    // alph b("Replaced!");
    // b.append(a.substr(a.find("Hello")+5));
    // std::cout << b.value()<<"\n";
    // std::cout << b.at(b.length-1)<<"\n";
    str a = "a a b a ca";
    // std::cout << a.value() <<'\n';
    // std::cout << a.at(a.size()) <<'\n';
    std::cout << a.replaceAll("a", "Buffeloo") <<'\n';
}