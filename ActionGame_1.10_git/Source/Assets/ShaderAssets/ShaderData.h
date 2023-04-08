#pragma once
#include "../../System/DirectX/DirectX_Simple.h"

class ShaderData{
public:
	struct vsParts {
		ID3D11VertexShader* m_pVertexShader;
		ID3D11InputLayout* m_pVertexLayout;
	};

	struct psParts {
		ID3D11PixelShader* m_pPixelShader;
	};

	// Getter
	const struct vsParts& GetVertexShader()const;
	const struct psParts& GetPixelShader()const;
	
private:
	void CreateVSshader(const char* vsfile, D3D11_INPUT_ELEMENT_DESC layout[], unsigned int len);
	void CreatePSshader(const char* psfile);

private:
	
	struct ComvsParts {
		ComPtr<ID3D11VertexShader> m_pVertexShader;
		ComPtr<ID3D11InputLayout>  m_pVertexLayout;
	};

	struct CompsParts {
		ComPtr<ID3D11PixelShader>  m_pPixelShader;
	};

	struct vsParts m_vsParts;
	struct psParts m_psParts;

private:
	static std::unordered_map<std::string, struct ComvsParts>m_pVertexShaderList;
	static std::unordered_map<std::string, struct CompsParts>m_pPixelShaderList;
	
public:
	ShaderData(const char* vsfile, 
			   D3D11_INPUT_ELEMENT_DESC layout[], 
			   unsigned int len, 
		       const char* psfile);
	~ShaderData() {};
};

