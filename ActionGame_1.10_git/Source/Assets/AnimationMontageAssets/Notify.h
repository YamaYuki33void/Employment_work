#pragma once
#include "../../System/DirectX/DirectX_Simple.h"

//--------------------------------------------------------------------
//	��x��������ʒm�̃N���X
//  MontageDatacclass�Ɏ��t����
//--------------------------------------------------------------------
class Notify{
public:
	// �X�V
	void NotifyUpdate(float nowfream);

	// Getter
	const std::string& GetNotifyName()const;
	const bool GetIsNotify()const;

private:
	void DebugString();

private:
	// �ʒm��
	std::string m_NotifyName;

	// �ʒm����t���[��
	float m_NotifyFream;

	// �ʒm�t���O
	bool m_IsNotify;

	// �ʒm���O�ɒʒm�t���[��������t���O
	bool m_IsNotifyFrontFream;
	bool m_IsFirstSimbiso;
	bool m_IsDoOnceNotify;

public:
	Notify(const std::string& notifyname, float notifyfream);
	~Notify() {};
};

//--------------------------------------------------------------------
//	�ŏ��ƍŌ�ɒʒm�𑗂�N���X
//  MontageDatacclass�Ɏ��t����
//--------------------------------------------------------------------

class NotifyWindow {
public:
	// �X�V
	void NotifyWindowUpdate(float nowfream);

	// Getter
	const std::string& GetBeginNotifyName()const;
	const std::string& GetEndNotifyName()const;
	const bool GetIsBeginNotify()const;
	const bool GetIsEndNotify()const;

private:
	class Notify m_BeginNotify;
	class Notify m_EndNotify;

public:
	NotifyWindow(const std::string& beginname,float beginfream, const std::string& endname, float endfream);
	~NotifyWindow() {};
};