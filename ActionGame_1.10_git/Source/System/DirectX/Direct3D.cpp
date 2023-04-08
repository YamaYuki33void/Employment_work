#include "Direct3D.h"

bool Direct3D::Initialize(const HWND hWnd, const int width, const int height) {

	//-----------------------------------------------------------------------------------
	// ファクトリー作成(ビデオ グラフィックの設定の列挙や指定に使用されるオブジェクト)
	//-----------------------------------------------------------------------------------
	ComPtr<IDXGIFactory> factory;
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory)))) {
		return false;
	}

	//--------------------------------------------------------
	//デバイス生成(主にリソース作成時に使用するオブジェクト)
	//--------------------------------------------------------
	UINT creationFlags = 0;

#ifdef _DEBUG
	// DEBUGビルド時はDirect3Dのデバッグを有効にする
	// (すごく重いが細かいエラーがわかる)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,	// Direct3D 11.1  ShaderModel 5
		D3D_FEATURE_LEVEL_11_0,	// Direct3D 11    ShaderModel 5
		D3D_FEATURE_LEVEL_10_1,	// Direct3D 10.1  ShaderModel 4
		D3D_FEATURE_LEVEL_10_0,	// Direct3D 10.0  ShaderModel 4
		D3D_FEATURE_LEVEL_9_3,	// Direct3D 9.3   ShaderModel 3
		D3D_FEATURE_LEVEL_9_2,	// Direct3D 9.2   ShaderModel 3
		D3D_FEATURE_LEVEL_9_1,	// Direct3D 9.1   ShaderModel 3
	};

	// デバイスとでデバイスコンテキストを作成
	D3D_FEATURE_LEVEL futureLevel;
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&m_pDevice,
		&futureLevel,
		&m_pDeviceContext)))
	{
		return false;
	}

	//------------------------------------------------------------------------------
	// スワップチェイン作成(フロントバッファに表示可能なバックバッファを持つもの)
	//------------------------------------------------------------------------------

	DXGI_SWAP_CHAIN_DESC scDesc = {};		                // スワップチェーンの設定データ
	scDesc.BufferDesc.Width = width;						// 画面の幅
	scDesc.BufferDesc.Height = height;						// 画面の高さ
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バッファの形式
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.BufferDesc.RefreshRate.Numerator = 0;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.SampleDesc.Count = 1;							// MSAAは使用しない
	scDesc.SampleDesc.Quality = 0;							// MSAAは使用しない
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// バッファの使用方法
	scDesc.BufferCount = 2;									// バッファの数
	scDesc.OutputWindow = hWnd;
	scDesc.Windowed = TRUE;									// ウィンドウモード
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(factory->CreateSwapChain(m_pDevice.Get(), &scDesc, &m_pSwapChain))) {
		return false;
	}

	// スワップチェインからバックバッファリソース取得
	ComPtr<ID3D11Texture2D> pBackBuffer;
	if (FAILED(m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer)))) {
		return false;
	}

	// バックバッファリソース用のRTVを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = scDesc.BufferDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	if (FAILED(m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), &rtvDesc, &m_pRenderTargetView))) {
		return false;
	}

	//=====================================================
	// デバイスコンテキストに描画に関する設定を行っておく
	//=====================================================

	// バックバッファをRTとしてセット
	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), nullptr);

	// ビューポートの設定
	D3D11_VIEWPORT vp = { 0.0f, 0.0f, (float)width , (float)height, 0.0f, 1.0f };
	m_pDeviceContext->RSSetViewports(1, &vp);

	//zバッファ作成
	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width              = width;
	txDesc.Height             = height;
	txDesc.MipLevels          = 1;
	txDesc.ArraySize          = 1;
	txDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count   = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage              = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags     = 0;
	txDesc.MiscFlags          = 0;

	if (FAILED(m_pDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilBuffer))) {
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format             = txDesc.Format;
	dsDesc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;

	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), &dsDesc, &m_pDepthStencilView))) {
		return false;
	}

	// ステンシルステート作成
	// 深度テストを行う深度ステンシルステートの作成
	D3D11_DEPTH_STENCIL_DESC desc = {};
	desc.DepthEnable    = true;
	desc.DepthFunc      = D3D11_COMPARISON_LESS_EQUAL;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.StencilEnable  = false;

	desc.StencilEnable    = true;
	desc.StencilReadMask  = 0xFF;
	desc.StencilWriteMask = 0xFF;

	desc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	desc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;

	desc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
	desc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;

	if (FAILED(m_pDevice->CreateDepthStencilState(&desc, &m_pDepthStencilState))) {
		return false;
	}

	// デバイスコンテキストへセット
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState.Get(), 1);
	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
	
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	//rasterDesc.CullMode            = D3D11_CULL_NONE;
	rasterDesc.CullMode              = D3D11_CULL_BACK;
	rasterDesc.DepthBias             = 0;
	rasterDesc.DepthBiasClamp        = 0.0f;
	rasterDesc.DepthClipEnable       = true;
	//rasterDesc.FillMode            = D3D11_FILL_WIREFRAME;
	rasterDesc.FillMode              = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable     = false;
	rasterDesc.ScissorEnable         = false;
	rasterDesc.SlopeScaledDepthBias  = 0.0f;
	
	if (FAILED(m_pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState))) {
		return false;
	}

	//AlphaBlendの作成
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.AlphaToCoverageEnable       = false;
		blendDesc.IndependentBlendEnable      = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		blendDesc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
		if (FAILED(m_pDevice->CreateBlendState(&blendDesc, m_pAlphablendingState.GetAddressOf()))) {
			return false;
		}
	}

	//何もしないBlendを作成
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.AlphaToCoverageEnable		  = false;
		blendDesc.IndependentBlendEnable	  = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend				= D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend				= D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].BlendOpAlpha		    = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		blendDesc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_INV_SRC_ALPHA;
		if (FAILED(m_pDevice->CreateBlendState(&blendDesc, m_pInvalidblendingState.GetAddressOf()))) {
			return false;
		}
	}

	// サンプラーステート設定
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	
	if (FAILED(m_pDevice->CreateSamplerState(&smpDesc, &m_pSamplerstate))){
		return false;
	}

	// サンプラーステートを転送
	m_pDeviceContext->PSSetSamplers(0, 1, m_pSamplerstate.GetAddressOf());

	return true;
}

ComPtr<ID3D11Device> Direct3D::GetDevice()const{
    return m_pDevice;
}

ComPtr<ID3D11DeviceContext> Direct3D::GetDeviceContext()const{
    return m_pDeviceContext;
}

ComPtr<IDXGISwapChain> Direct3D::GetSwapChain()const{
    return m_pSwapChain;
}

ComPtr<ID3D11RenderTargetView> Direct3D::GetBackBufferView()const{
    return m_pRenderTargetView;
}

ComPtr<ID3D11DepthStencilView> Direct3D::GetDepthStencilView() const{
	return m_pDepthStencilView;
}

void Direct3D::SetRenderTargetView(){

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());
}

void Direct3D::SetOnAlphaBlending() {

	float blendFactor[4] = { 0,0,0,0 };
	m_pDeviceContext->OMSetBlendState(m_pAlphablendingState.Get(), blendFactor, 0xffffffff);
}
void Direct3D::SetInvalidBlending() {

	float blendFactor[4] = { 0,0,0,0 };
	m_pDeviceContext->OMSetBlendState(m_pInvalidblendingState.Get(), blendFactor, 0xffffffff);
}

void Direct3D::SetOffZbuffer(){
	ID3D11RenderTargetView* rtvtable[1];

	rtvtable[0] = m_pRenderTargetView.Get();

	m_pDeviceContext->OMSetRenderTargets(
		1,									
		rtvtable,								
		nullptr								
	);
}

void Direct3D::SetOnZbuffer(){
	ID3D11RenderTargetView* rtvtable[1];

	rtvtable[0] = m_pRenderTargetView.Get();

	m_pDeviceContext->OMSetRenderTargets(
		1,										
		rtvtable,								
		m_pDepthStencilView.Get()				
	);
}



Direct3D::~Direct3D(){

	if (m_pDeviceContext) {
		m_pDeviceContext->ClearState();
	}
	if (m_pSwapChain) {
		m_pSwapChain->SetFullscreenState(false, nullptr);
	}
}
