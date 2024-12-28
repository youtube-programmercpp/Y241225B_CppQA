/*
■質問２のご返答に対して...
関数単体での実装方法という所に視野が狭まっていたので、関数の利用方法によって例外投入の有無を決めるというのを聞いてハッとしました。大変勉強になります。
#includeを活用した列挙体の定義方法は、ヘッダファイルの増加と#defineの重複が懸念点ではありますが、直に記述するより圧倒的に堅牢で有用なテクニックだと思いました。ありがたく利用させて頂きます！！
実際のGetName関数はjsonファイルに対する入出力として利用していました。
ですのでこの場合は、誤った文字列を書き込むことを避ける為に例外投入すべきと思いましたが、考え方は合っているでしょうか？
また、列挙体と文字列の相互変換プログラムのテクニックがあれば教えて頂きたいです。
```C++
enum class Fruit {
	Apple,
	Banana,
	Orange,
};
constexpr std::size_t FruitCount = 3;
// 名前が変わっていますが、GetName関数です。
// ToString関数を利用して.jsonファイルに書き込みする。
inline std::string_view ToString(Fruit fruit) {
	switch (fruit) {
	case Fruit::Apple:  return "Apple";
	case Fruit::Banana: return "Banana";
	case Fruit::Orange: return "Orange";
	}
	throw std::runtime_error(std::format("不明なenum値({})", std::size_t(fruit)));
}
// ToFruit関数を利用して.jsonファイルから読み取る。
inline Fruit ToFruit(std::string_view s) {
	for (std::size_t i = 0; i < FruitCount; ++i) {
		const auto fruit = Fruit(i);
		if (s == ToString(fruit)) {
			return fruit;
		}
	}
	throw std::runtime_error(std::format("不明な文字列({})", s));
}
```
```json
[
	{
		"fruit_type": "Apple",
		"price": 100
	},
	{
		"fruit_type": "Banana",
		"price": 50
	}
]
```
*/

/*
回答

①「誤った文字列を書き込むことを避ける為に例外投入すべき？」
それは…
「すべき」と言い切るのは難しい気がしています。
各自の判断（周辺状況の検討）が求められるところだと思います。

②「列挙体と文字列の相互変換プログラムのテクニック」
サンプルを作りました。
以下をご覧ください。
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
		// Fruit 型を文字列として出力する。
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
		// 文字列を読み込んでFruit 型の値として返す。
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
void test1(std::ostream& ostm)
{
	//Fruit型の値を文字列化して出力する。
	ostm
		<< Fruit::Apple  << '\n'
		<< Fruit::Banana << '\n'
		<< Fruit::Orange << '\n'
		<< Fruit::Kiwi   << '\n'
		;
}
#include <vector>
std::vector<Fruit> test2(std::istream& istm)
{
	//文字列を読み込んでFruit型に変換する。
	for (std::vector<Fruit> retval;;) {
		Fruit fruit;
		if (istm >> fruit)
			retval.push_back(fruit);
		else
			return retval;
	}
}
std::vector<Fruit> test2(std::istream&& istm)
{
	return test2(istm);
}
std::vector<Fruit> test3(std::istream& istm)
{
	try {
		istm.exceptions(std::ios_base::failbit);
		std::vector<Fruit> retval;
		for (;;) {
			Fruit value;
			if (istm >> value)
				retval.push_back(value);
			else
				return retval;
		}
	}
	catch (const std::ios_base::failure&) {
		throw std::runtime_error("文字列で表記されたFruit型の値を読み込もうとして失敗した。");
	}
}
std::vector<Fruit> test3(std::istream&& istm)
{
	return test3(istm);
}
std::vector<Fruit> test4(std::istream& istm)
{
	for (std::vector<Fruit> retval;;) {
		Fruit value;
		if (istm >> value)
			retval.push_back(value);
		else if (istm.eof())
			return retval;
		else
			throw std::runtime_error("文字列で表記されたFruit型の値を読み込もうとして失敗した。");
	}
}
std::vector<Fruit> test4(std::istream&& istm)
{
	return test4(istm);
}
namespace std {
	ostream& operator<<(ostream& ostm, const vector<Fruit>& values)
	{
		const auto end = values.end();
		auto it = values.begin();
		if (it == end)
			return ostm << "{}";
		else {
			for (ostm << "{ " << *it;;) {
				if (++it == end)
					return ostm << "}";
				else
					ostm << ", " << *it;
			}

		}
	}
}
#include <iostream>
#include <sstream>
#include <tuple>
int main()
{
	std::cout << "(1) operator<< の検証\n";
	test1(std::cout);

	std::cout << "(2) operator>> の検証\n";
	std::cout << test2(std::istringstream{ "Apple Banana Orange Kiwi" }) << '\n';


	static const std::tuple<const char*, std::vector<Fruit>(*)(std::istream&&)> t[]
	{ {"(3) operator >> の検証（例外の投入と捕捉）", test3 }
	, {"(4) operator >> の検証（if文による判断）"  , test4 }
	};
	for (const auto& r : t) {
		std::cout << std::get<0>(r) << '\n';
		try {
			std::cout << (*std::get<1>(r))(std::istringstream{ "Apple Mango Kiwi" }) << '\n';
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
		}
	}
}
