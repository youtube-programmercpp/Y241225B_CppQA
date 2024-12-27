/*
for ���ɂ����ă��[�v�J�E���^�ƈقȂ�^�������A
���[�v���ɏ���������Ȃ��ϐ��𗘗p�������ꍇ�A
�ȉ��̃e�N�j�b�N�͕��ՓI�ɗ��p���ėǂ����̂Ȃ̂ł��傤���H
```C++
for (auto [ i, x ] = std::make_tuple(std::size_t(0), .0); i < 10; ++i) {
    x += double(i) / double(i + 1);
    std::cout << x << std::endl;
}
// for ���̊O�ł� x �𗘗p���Ȃ��B
```
*/
/*
��
���ՓI�Ɏg�p���ėǂ��ƍl����B
�������͖����̂ŁB
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
