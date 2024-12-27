/*
enum class を条件として switch 文を利用する場合、
どの要素にも当てはまらないケースを考えた例外処理を実装すべきでしょうか？
```C++
enum class Fruit {
    Apple,
    Banana,
    Orange,
};

std::string_view GetName(Fruit fruit) {
    switch (fruit) {
    case Fruit::Apple:  return "Apple";
    case Fruit::Banana: return "Banana";
    case Fruit::Orange: return "Orange";
    }
    // この例外投入を実装すべきか分かりません。
    // また、この例外投入時に投げるオブジェクトは runtime_error 型で良いのでしょうか？
    // out_of_range や domain_error の方が適切でしょうか？
    throw std::runtime_error(std::format("不明なenum値({})", std::size_t(fruit)));
}
```
*/
/*
回答

<例外の考え方>
必要であれば例外を投入する。
必要のない例外は投入しない。

処理の続行が困難になったとき、
処理を続行させるのが適切でないとき、
エラー値を返すか例外を投入するか、どちらかが望まれる。

GetName で名前を取得し、そしてそれをどうするのか…
そこが問われている。

予期しない値に遭遇した際、そのことが分かるように文字列化した数値を提示することで困るかどうか。
困る場合は例外を投入すべきである。
困らない場合は例外を投入すべきではない。

GetName で得た文字列をサーバーに送信する。
サーバーに意味不明の文字列を送信することは避けたい。
異常があれば、サーバーからの応答ではなく、送信前の時点で把握したい。
というような何らかの特殊事情があれば例外を投入すべきだと言える。

特にそういうわけではない場合、例外を投入するのは避けたい。
*/
enum class Fruit
{
#define DefineFruit(name)   name,
#include "DefineFruit.h"
#undef  DefineFruit
};
#include <string>
#include <ostream>
#include <istream>
namespace std {
    ostream& operator<<(ostream& ostm, Fruit fruit)
    {
        switch (fruit) {
#define DefineFruit(name) case Fruit::name: return ostm << #name;
#include "DefineFruit.h"
#undef  DefineFruit
        default:
            return ostm.setstate(std::ios_base::failbit), ostm;
        }
    }
    istream& operator>>(istream& istm, Fruit& fruit)
    {
        string s;
        if (istm >> s) {
#define DefineFruit(name) if (s == #name) {fruit = Fruit::name; return istm;}
#include "DefineFruit.h"
#undef  DefineFruit
            return istm.setstate(std::ios_base::failbit), istm;
        }
        else
            return istm;
    }
}
#include <iostream>
#include <sstream>
#include <tuple>
int main()
{
    std::cout << "(1) operator<< の検証\n";
    const auto s = (std::ostringstream()
        << Fruit::Apple  << '\n'
        << Fruit::Banana << '\n'
        << Fruit::Orange << '\n'
        << Fruit::Kiwi   << '\n'
        << Fruit(12345 ) << '\n'
        ).str();
    std::cout << s;
    std::cout << "(2) operator>> の検証\n";
    for (std::istringstream istm{s};;) {
        Fruit fruit;
        if (istm >> fruit)
            std::cout << fruit << '\n';
        else
            break;
    }
}
