#pragma once

//----------------------------------------
//Singletonテンプレート
//Singletonにしたいクラスを継承させる
//----------------------------------------
template<class T>
class Singleton {
public:
	static T* GetInstance();
	
protected:
	Singleton() {};
	virtual ~Singleton() {};

private:
	//コピー・ムーブ禁止
	void operator=(const Singleton& obj) = delete;
	Singleton(const Singleton& obj)      = delete;
	Singleton(Singleton&&)               = delete;
	Singleton& operator=(Singleton&&)    = delete;
};

template<class T>
inline T* Singleton<T>::GetInstance() {
	static T pInstance;
	return &pInstance;
}
