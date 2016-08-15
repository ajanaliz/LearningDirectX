#include "pch.h"
#include "Game.h"
#include <fstream>


// loading a file into an Array^
Array<byte>^ LoadShaderFile(std::string File)
{
	Array<byte>^ FileData = nullptr;

	//open the file
	std::ifstream VertexFile(File, std::ios::in | std::ios::binary | std::ios::ate);

	if (VertexFile.is_open())
	{
		int length = (int)VertexFile.tellg();

		// collect the data
		FileData = ref new Array<byte>(length);
		VertexFile.seekg(0, std::ios::beg);
		VertexFile.read(reinterpret_cast<char*>(FileData->Data), length);
		VertexFile.close();
	}

	return FileData;
}



// initializes and prepares Direct3D
void CGame::Initialize()
{
	// define temp pointer variables to a device and a device context
	ComPtr<ID3D11Device> tempDevice;
	ComPtr<ID3D11DeviceContext> tempDeviceContext;


	// creating the device and the device context objects
	D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
		&tempDevice, nullptr, &tempDeviceContext);

	// convert the pointers from the DX 11 version to the DX 11.2 version
	tempDevice.As(&device);
	tempDeviceContext.As(&deviceContext);
	
	// 1. convert our D3D11Device1 interface to an IDXGIDEVICE1
	ComPtr<IDXGIDevice1> dxgiDevice;
	device.As(&dxgiDevice);

	// 2. utilize the IDXGIDevice1 interface to get access to the adapter
	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// 3. use the IDXGIAdapter interface to get access to the parent.
	ComPtr<IDXGIFactory2> dxgiFactory;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

	// set up the swap chain description struct
	DXGI_SWAP_CHAIN_DESC1 swapChainDescription = { 0 };

	
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // how the swap chain should be utilized
	swapChainDescription.BufferCount = 2;								// a front buffer and a back buffer
	swapChainDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;			// a common swap chain format  // UNORM = unsigned normalized integer
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // the recommended flip mode
	swapChainDescription.SampleDesc.Count = 1;							// disables anti-aliasing

	CoreWindow^ Window = CoreWindow::GetForCurrentThread();

	dxgiFactory->CreateSwapChainForCoreWindow(
		device.Get(),							// address of the device
		reinterpret_cast<IUnknown*>(Window),	// address of the window
		&swapChainDescription,					// address of the swap chain description
		nullptr,
		&swapChain								//address of the swap chain
	);

	// get a direct pointer to the back buffer
	ComPtr<ID3D11Texture2D> backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);

	// create a render target that points to our back buffer
	device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget);

	// set the viewport
	D3D11_VIEWPORT viewport = { 0 };

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Window->Bounds.Width;
	viewport.Height = Window->Bounds.Height;

	deviceContext->RSSetViewports(1, &viewport);

	InitGraphics();
	InitPipeline();
}



// performs updates to the game state
void CGame::Update()
{

}


// renders a single frame of 3D graphics
void CGame::Render()
{
	// set the new render target as the active render target
	deviceContext->OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

	// clear the back buffer to some colour
	float colour[4] = { 0.0f,0.1f,0.3f,1.0f };
	deviceContext->ClearRenderTargetView(renderTarget.Get(), colour);

	// setting up the vertex buffer
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->Draw(3, 0);

	// setting up the primitive topology
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// swap the back buffer and the front buffer
	swapChain->Present(1, 0);
}

void CGame::InitGraphics()
{
	VERTEX Vertices[] = 
	{
		{0.0f, 0.5f, 0.0f},
		{0.45f, -0.5f, 0.0f},
		{-0.45f, -0.5f, 0.0f}
	};

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(Vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	
	D3D11_SUBRESOURCE_DATA subResourceData = { Vertices, 0, 0 };

	device->CreateBuffer(&bufferDesc, &subResourceData, &vertexBuffer);
}


// initializes the GPU settings and prepares it for rendering
void CGame::InitPipeline()
{
	// load the shader files
	Array<byte>^ VSFile = LoadShaderFile("VertexShader.cso");
	Array<byte>^ PSFile = LoadShaderFile("PixelShader.cso");


	// create the shader objects
	device->CreateVertexShader(VSFile->Data, VSFile->Length, nullptr, &vertexShader);
	device->CreatePixelShader(PSFile->Data, PSFile->Length, nullptr, &pixelShader);

	// set the shaders as active shaders.
	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

	// initialize input layout
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	// creating the input layout
	device->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc), VSFile->Data, VSFile->Length, &inputLayout);
	deviceContext->IASetInputLayout(inputLayout.Get());

}