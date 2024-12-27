/*
致命的なシステムエラーが発生した場合、terminate() を呼び出すこともあったのですが、
これは酷い手法でしょうか？

具体的には以下のようなアプリケーション終了関数を自前で用意し、呼び出していました。
```C++
void Terminate(std::string_view message) {
	MessageBox(nullptr, message.data(), TEXT("ERROR"), MB_ICONERROR);
	std::terminate();
}
```
*/
/*
回答

どのような背景があるのかわからないので、
処理手法について酷い・酷くない、の判断は避けたい。

ただ、個人的に terminateを呼び出したことは無く、
また、呼び出したいと思ったことも無い。

しかしこれは、たまたまの可能性もある。
今後、terminate を使用したくなる場面が無いと言い切れるものではない。
*/
int main()
{
}
