#include "Notify.h"
#include <iostream>

void Notify::NotifyUpdate(float nowfream){

	// 開始フレームを見て通知より前にあるか後ろにあるかで通知更新するか決める
	if (m_IsFirstSimbiso == false) {

		if (nowfream < m_NotifyFream) {
			m_IsNotifyFrontFream = true;
		}
		else {
			m_IsNotifyFrontFream = false;
		}

		m_IsFirstSimbiso = true;
	}
	
	// 引数に入ってくるフレームが通知フレームを超えたら通知フラグをOnにする
	// 1フレームだけ通知をオンにする
	if (m_IsDoOnceNotify == false) {

		if (m_IsNotifyFrontFream == true) {

			if (m_NotifyFream < nowfream) {
				m_IsNotify = true;
				m_IsDoOnceNotify = true;
				
				#ifdef _DEBUG
				DebugString();
				#endif
			}
		}
	}
}

const std::string& Notify::GetNotifyName() const{
	return m_NotifyName;
}

const bool Notify::GetIsNotify() const{
	return m_IsNotify;
}

void Notify::DebugString(){
	std::cout << m_NotifyName << std::endl;
}

Notify::Notify(const std::string& notifyname, float notifyfream):
	m_NotifyName        (notifyname),
	m_NotifyFream       (notifyfream),
	m_IsNotify          (false),
	m_IsNotifyFrontFream(false),
	m_IsFirstSimbiso    (false),
	m_IsDoOnceNotify    (false)
{
}

void NotifyWindow::NotifyWindowUpdate(float nowfream){

	m_BeginNotify.NotifyUpdate(nowfream);
	m_EndNotify.NotifyUpdate(nowfream);
}

const std::string& NotifyWindow::GetBeginNotifyName() const{
	return m_BeginNotify.GetNotifyName();
}

const std::string& NotifyWindow::GetEndNotifyName() const{
	return m_EndNotify.GetNotifyName();
}

const bool NotifyWindow::GetIsBeginNotify() const{
	return m_BeginNotify.GetIsNotify();
}

const bool NotifyWindow::GetIsEndNotify() const{
	return m_EndNotify.GetIsNotify();
}

NotifyWindow::NotifyWindow(const std::string& beginname, float beginfream, const std::string& endname, float endfream):
	m_BeginNotify(beginname,beginfream),
	m_EndNotify  (endname,endfream)
{
}
