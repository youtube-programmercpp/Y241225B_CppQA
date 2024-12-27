/*
C++�̃L���X�g�`���́A
�֐��^�L���X�g�A
C-Style�L���X�g�A
�L���X�g���Z�q�ɂ��L���X�g�̂R��ނ�����Ǝv���܂��B

C-Style�L���X�g�͈Ӑ}���Ȃ� dynamic_cast ���s����\��������̂ŗ��p���T����ׂ����Ǝv���܂����A
�֐��^�L���X�g�� static_cast �̎g�������ɂ��Ă��ӌ����f�������ł��B

�֐��^�L���X�g�� static_cast �Ɠ����ł���Ǝv���Ă���̂ł����A
�ł���΁Astatic_cast �𗘗p���鎖���Ӑ}�����L���X�g�͑S�Ċ֐��^�L���X�g�ŗǂ��̂ł͂Ȃ����Ǝv���܂����B
Programmer ����͂ǂ̂悤�Ɏg����������Ă��܂����H
*/

/*
��

�u�֐��^�L���X�g�� static_cast �̎g�������v

�֐��^�L���X�g�͓��ʂł���B
�L�q���ȑf�Ȃ̂������ŁA�������������������i�������鎞�j�Ɏg�p����Ɨǂ��B

�֐��^�L���X�g��C����̎��̃L���X�g�Ɠ����ň�ʓI�ɔ��Ɋ댯�B
����āA���ʂł���Ύg�p�͔��������Ƃ���B

�����A�댯�������ɂȂ�Ȃ��Ƃ�������B
�i�S�ĕ����肫���Ă��āA������͋N���Ȃ��ƒf���ł��鎞�j
�i���ɉ�����肪�N�����Ƃ��Ă��A�y���Ȃ��̂��ƌ����؂�鎞�j
�����������ŁA�Ȃ����^���P��ŒԂ�鎞�A
�֐��^�L���X�g���g���Ɨǂ��B
*/
#include <Windows.h>
#include <iostream>
#include <iomanip>
int main()
{
	const short value = 0x1234;
	std::cout << std::setfill('0')
		<< "[0]" << std::hex << std::setw(2) << WORD(LPCSTR(&value)[0]) << '\n'
		<< "[1]" << std::hex << std::setw(2) << WORD(LPCSTR(&value)[1]) << '\n'
		<< std::setfill(' ')
		<< '\n';
}
