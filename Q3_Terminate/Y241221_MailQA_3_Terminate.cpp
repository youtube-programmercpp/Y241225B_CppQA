/*
�v���I�ȃV�X�e���G���[�����������ꍇ�Aterminate() ���Ăяo�����Ƃ��������̂ł����A
����͍�����@�ł��傤���H

��̓I�ɂ͈ȉ��̂悤�ȃA�v���P�[�V�����I���֐������O�ŗp�ӂ��A�Ăяo���Ă��܂����B
```C++
void Terminate(std::string_view message) {
	MessageBox(nullptr, message.data(), TEXT("ERROR"), MB_ICONERROR);
	std::terminate();
}
```
*/
/*
��

�ǂ̂悤�Ȕw�i������̂��킩��Ȃ��̂ŁA
������@�ɂ��č����E�����Ȃ��A�̔��f�͔��������B

�����A�l�I�� terminate���Ăяo�������Ƃ͖����A
�܂��A�Ăяo�������Ǝv�������Ƃ������B

����������́A���܂��܂̉\��������B
����Aterminate ���g�p�������Ȃ��ʂ������ƌ����؂����̂ł͂Ȃ��B
*/
int main()
{
}
