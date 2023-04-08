#pragma once
#include "../../../../System/DirectX/DirectX_Simple.h"
#include "AnimationPlayer/AnimationPlayer.h"

class State{
public:
	// �X�e�[�g�ŗL�̓���
	virtual void Update() = 0;
	virtual void OnEnter() {};
	virtual void OnExit() {};

	// �X�e�[�g�ύX
	void ChangeState(const std::string& statename);

	// �A�j���[�V�����̒ǉ�
	void AddAnimationPlayer(class AnimationPlayer* data);

	// Getter
	const std::string& GetStateName()const;
	class AnimationStateComponent* GetAnimState()const;

	// Setter
	void SetAnimation(class AnimationPlayer* animadata);
	
private:
	// �X�e�[�g��
	std::string m_StateName;

	// �A�j���[�V�����̍Đ��Ǘ�
	std::vector<std::unique_ptr<class AnimationPlayer>> m_pAnimationPlayerList;

	// �I�[�i�[
	class AnimationStateComponent* m_pOwnerAnimState;

public:
	State(class AnimationStateComponent* comp, const std::string& statename);
	virtual~State() {};
};

