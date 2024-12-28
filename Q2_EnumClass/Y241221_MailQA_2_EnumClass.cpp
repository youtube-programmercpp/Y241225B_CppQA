/*
enum class �������Ƃ��� switch ���𗘗p����ꍇ�A
�ǂ̗v�f�ɂ����Ă͂܂�Ȃ��P�[�X���l������O�������������ׂ��ł��傤���H
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
    // ���̗�O�������������ׂ���������܂���B
    // �܂��A���̗�O�������ɓ�����I�u�W�F�N�g�� runtime_error �^�ŗǂ��̂ł��傤���H
    // out_of_range �� domain_error �̕����K�؂ł��傤���H
    throw std::runtime_error(std::format("�s����enum�l({})", std::size_t(fruit)));
}
```
*/
/*
��

<��O�̍l����>
�K�v�ł���Η�O�𓊓�����B
�K�v�̂Ȃ���O�͓������Ȃ��B

�����̑��s������ɂȂ����Ƃ��A
�����𑱍s������̂��K�؂łȂ��Ƃ��A
�G���[�l��Ԃ�����O�𓊓����邩�A�ǂ��炩���]�܂��B

GetName �Ŗ��O���擾���A�����Ă�����ǂ�����̂��c
����������Ă���B

�\�����Ȃ��l�ɑ��������ہA���̂��Ƃ�������悤�ɕ����񉻂������l��񎦂��邱�Ƃō��邩�ǂ����B
����ꍇ�͗�O�𓊓����ׂ��ł���B
����Ȃ��ꍇ�͗�O�𓊓����ׂ��ł͂Ȃ��B

GetName �œ�����������T�[�o�[�ɑ��M����B
�T�[�o�[�ɈӖ��s���̕�����𑗐M���邱�Ƃ͔��������B
�ُ킪����΁A�T�[�o�[����̉����ł͂Ȃ��A���M�O�̎��_�Ŕc���������B
�Ƃ����悤�ȉ��炩�̓��ꎖ�����Η�O�𓊓����ׂ����ƌ�����B

���ɂ��������킯�ł͂Ȃ��ꍇ�A��O�𓊓�����͔̂��������B
*/
