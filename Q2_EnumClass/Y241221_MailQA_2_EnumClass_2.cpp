/*
������Q�̂��ԓ��ɑ΂���...
�֐��P�̂ł̎������@�Ƃ������Ɏ��삪���܂��Ă����̂ŁA�֐��̗��p���@�ɂ���ė�O�����̗L�������߂�Ƃ����̂𕷂��ăn�b�Ƃ��܂����B��ϕ׋��ɂȂ�܂��B
#include�����p�����񋓑̂̒�`���@�́A�w�b�_�t�@�C���̑�����#define�̏d�������O�_�ł͂���܂����A���ɋL�q�����舳�|�I�Ɍ��S�ŗL�p�ȃe�N�j�b�N���Ǝv���܂����B���肪�������p�����Ē����܂��I�I
���ۂ�GetName�֐���json�t�@�C���ɑ΂�����o�͂Ƃ��ė��p���Ă��܂����B
�ł��̂ł��̏ꍇ�́A�������������������ނ��Ƃ������ׂɗ�O�������ׂ��Ǝv���܂������A�l�����͍����Ă���ł��傤���H
�܂��A�񋓑̂ƕ�����̑��ݕϊ��v���O�����̃e�N�j�b�N������΋����Ē��������ł��B
```C++
enum class Fruit {
	Apple,
	Banana,
	Orange,
};
constexpr std::size_t FruitCount = 3;
// ���O���ς���Ă��܂����AGetName�֐��ł��B
// ToString�֐��𗘗p����.json�t�@�C���ɏ������݂���B
inline std::string_view ToString(Fruit fruit) {
	switch (fruit) {
	case Fruit::Apple:  return "Apple";
	case Fruit::Banana: return "Banana";
	case Fruit::Orange: return "Orange";
	}
	throw std::runtime_error(std::format("�s����enum�l({})", std::size_t(fruit)));
}
// ToFruit�֐��𗘗p����.json�t�@�C������ǂݎ��B
inline Fruit ToFruit(std::string_view s) {
	for (std::size_t i = 0; i < FruitCount; ++i) {
		const auto fruit = Fruit(i);
		if (s == ToString(fruit)) {
			return fruit;
		}
	}
	throw std::runtime_error(std::format("�s���ȕ�����({})", s));
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
��

�@�u�������������������ނ��Ƃ������ׂɗ�O�������ׂ��H�v
����́c
�u���ׂ��v�ƌ����؂�͓̂���C�����Ă��܂��B
�e���̔��f�i���ӏ󋵂̌����j�����߂���Ƃ��낾�Ǝv���܂��B

�A�u�񋓑̂ƕ�����̑��ݕϊ��v���O�����̃e�N�j�b�N�v
�T���v�������܂����B
�ȉ����������������B
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
		// Fruit �^�𕶎���Ƃ��ďo�͂���B
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
		// �������ǂݍ����Fruit �^�̒l�Ƃ��ĕԂ��B
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
	//Fruit�^�̒l�𕶎��񉻂��ďo�͂���B
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
	//�������ǂݍ����Fruit�^�ɕϊ�����B
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
		throw std::runtime_error("������ŕ\�L���ꂽFruit�^�̒l��ǂݍ������Ƃ��Ď��s�����B");
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
			throw std::runtime_error("������ŕ\�L���ꂽFruit�^�̒l��ǂݍ������Ƃ��Ď��s�����B");
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
	std::cout << "(1) operator<< �̌���\n";
	test1(std::cout);

	std::cout << "(2) operator>> �̌���\n";
	std::cout << test2(std::istringstream{ "Apple Banana Orange Kiwi" }) << '\n';


	static const std::tuple<const char*, std::vector<Fruit>(*)(std::istream&&)> t[]
	{ {"(3) operator >> �̌��؁i��O�̓����ƕߑ��j", test3 }
	, {"(4) operator >> �̌��؁iif���ɂ�锻�f�j"  , test4 }
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
