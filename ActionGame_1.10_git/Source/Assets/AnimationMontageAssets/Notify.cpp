#include "Notify.h"
#include <iostream>

void Notify::NotifyUpdate(float nowfream){

	// �J�n�t���[�������Ēʒm���O�ɂ��邩���ɂ��邩�Œʒm�X�V���邩���߂�
	if (m_IsFirstSimbiso == false) {

		if (nowfream < m_NotifyFream) {
			m_IsNotifyFrontFream = true;
		}
		else {
			m_IsNotifyFrontFream = false;
		}

		m_IsFirstSimbiso = true;
	}
	
	// �����ɓ����Ă���t���[�����ʒm�t���[���𒴂�����ʒm�t���O��On�ɂ���
	// 1�t���[�������ʒm���I���ɂ���
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
