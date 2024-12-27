/*
for 文においてループカウンタと異なる型を持ち、
ループ毎に初期化されない変数を利用したい場合、
以下のテクニックは普遍的に利用して良いものなのでしょうか？
```C++
for (auto [ i, x ] = std::make_tuple(std::size_t(0), .0); i < 10; ++i) {
    x += double(i) / double(i + 1);
    std::cout << x << std::endl;
}
// for 文の外では x を利用しない。
```
*/
/*
回答
普遍的に使用して良いと考える。
何も問題は無いので。
*/
#include <tuple>
#include <iostream>
int main()
{
    for (auto [i, x] = std::tuple<size_t, double>{}; i < 10; ++i) {
        x += double(i) / double(i + 1);
        std::cout << x << std::endl;
    }
}
