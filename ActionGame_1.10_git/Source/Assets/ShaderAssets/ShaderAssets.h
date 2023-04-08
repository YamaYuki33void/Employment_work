#pragma once
#include "../../System/DirectX/DirectX_Simple.h"
#include "../InterfaceAssets.h"
#include "ShaderData.h"

class ShaderAssets :
	public InterfaceAssets, public Singleton<ShaderAssets>
{
public:
	friend Singleton<ShaderAssets>;

public:
	// ���񃍁[�h
	void LoadInitalize()override;

	// Getter
	const class ShaderData* GetShaderData(const std::string& dataname);

private:
	// �V�F�[�_���X�g
	std::unordered_map<std::string, class ShaderData> m_pShaderDataList;

private:
	ShaderAssets() {};
	~ShaderAssets() {};
};

