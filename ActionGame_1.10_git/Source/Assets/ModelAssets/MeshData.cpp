#include "MeshData.h"

void OneMesh::MeshDraw(){

	auto* devcon = SimepleD3D::DX11GetDeviceContext();

	// SRV���Z�b�g
	if (m_Texture.Sre.Get() != nullptr) {
		devcon->PSSetShaderResources(0, 1, m_Texture.Sre.GetAddressOf());
	}

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	// ���_�o�b�t�@���Z�b�g
	devcon->IASetVertexBuffers(0, 1, m_VertexBuffer.GetVertexBuffer().GetAddressOf(), &stride, &offset);

	// �C���f�b�N�X�o�b�t�@���Z�b�g
	devcon->IASetIndexBuffer(m_IndexBuffer.GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	// �g�|���W�[���Z�b�g
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �C���f�b�N�X�o�b�t�@�𗘗p���ĕ`��
	devcon->DrawIndexed(static_cast<unsigned int>(m_Indices.size()), 0, 0);
}

void OneMesh::RemakeVertexBuffer(){
	m_VertexBuffer.TVertexBufferRemake(m_pVertices);
}

void OneMesh::SetMeshScale(const DirectX::SimpleMath::Vector3& scale){

	for (auto&& vector : m_pVertices) {
		vector.Pos *= scale;
		vector.Normal *= scale;
	}

	RemakeVertexBuffer();
}

void OneMesh::SetPibotOffset(const DirectX::SimpleMath::Vector3& offset){

	for (auto&& vector : m_pVertices) {
		vector.Pos += offset;
		vector.Normal += offset;
	}

	RemakeVertexBuffer();
}

OneMesh::OneMesh(std::vector<Vertex>& vertices, 
				 std::vector<unsigned int>& indices, 
				 Texture& texture):
	m_pVertices(vertices),
	m_Indices  (indices),
	m_Texture  (texture)
{
	// ���_�o�b�t�@�쐬
	m_VertexBuffer.TCreateVertexBuffer(m_pVertices);

	// �C���f�b�N�X�o�b�t�@�쐬
	m_IndexBuffer.TCreateIndexBuffer(m_Indices);
}

void MeshData::SetModelScale(const DirectX::SimpleMath::Vector3& scale){

	for (auto&& mesh : m_MeshList) {
		mesh.second.SetMeshScale(scale);
	}
}

void MeshData::SetModelPibotOffset(const DirectX::SimpleMath::Vector3& offset){

	for (auto&& mesh : m_MeshList) {
		mesh.second.SetPibotOffset(offset);
	}
}

void MeshData::SetOwnerComponent(Component* comp){
	m_pOwnerComponent = comp;
}

std::unordered_map<std::string, class OneMesh>& MeshData::GetMeshList(){
	return m_MeshList;
}

Model::FbxMyFormatManager& MeshData::GetFbxManager() const{
	return *m_pFbxManager;
}

Component& MeshData::GetComponent() const{
	return *m_pOwnerComponent;
}

MeshData::MeshData(const char* myformatfile, const char* texdirectory, const ShaderData* shaderdata):
	m_pFbxManager(std::make_unique<Model::FbxMyFormatManager>()),
	m_TexDirectory(texdirectory),
	m_pShaderData(shaderdata)
{
	// �o�C�i���t�@�C���̓ǂݍ���
	m_pFbxManager->MeshLoad(myformatfile);
}
