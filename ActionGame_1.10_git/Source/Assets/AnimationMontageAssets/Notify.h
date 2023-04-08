#pragma once
#include "../../System/DirectX/DirectX_Simple.h"

//--------------------------------------------------------------------
//	一度だけ送る通知のクラス
//  MontageDatacclassに取り付ける
//--------------------------------------------------------------------
class Notify{
public:
	// 更新
	void NotifyUpdate(float nowfream);

	// Getter
	const std::string& GetNotifyName()const;
	const bool GetIsNotify()const;

private:
	void DebugString();

private:
	// 通知名
	std::string m_NotifyName;

	// 通知するフレーム
	float m_NotifyFream;

	// 通知フラグ
	bool m_IsNotify;

	// 通知より前に通知フレームがいるフラグ
	bool m_IsNotifyFrontFream;
	bool m_IsFirstSimbiso;
	bool m_IsDoOnceNotify;

public:
	Notify(const std::string& notifyname, float notifyfream);
	~Notify() {};
};

//--------------------------------------------------------------------
//	最初と最後に通知を送るクラス
//  MontageDatacclassに取り付ける
//--------------------------------------------------------------------

class NotifyWindow {
public:
	// 更新
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