#include "TextureManager.h"
#define ALADDIN_IMAGE "Image/Genesis 32X SCD - Aladdin - Aladdin.png"
#define FINISH_IMAGE "Image/Finish.png"
#define THEEND_IMAGE "Image/TheEnd.png"

TextureManager* TextureManager::instance = 0;

//contructor of Texture manager class
TextureManager::TextureManager()
{
	aladdin_image = 0;

}

//get texture manager current instance (get texture manager pointer)
TextureManager* TextureManager::GetInstance()
{
	if (instance == 0)
	{
		instance = new TextureManager();
	}
	return instance;
}


//Tạo các Texture
void TextureManager::CreateTexture(LPDIRECT3DDEVICE9 d3ddev)
{
	srand((unsigned)time(NULL));
	HRESULT res = D3DXCreateSprite(d3ddev, &sprite_handler);

	if (aladdin_image == NULL)
		aladdin_image = LoadTexture(d3ddev, ALADDIN_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
}

void TextureManager::CreateSurface(LPDIRECT3DDEVICE9 d3ddev)
{
	if (finish_image == NULL)
		finish_image = LoadSurface(d3ddev, FINISH_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	if (theend_image == NULL)
		theend_image = LoadSurface(d3ddev, THEEND_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
}

LPD3DXSPRITE TextureManager::GetSprite_Handler()
{
	return sprite_handler;
}

//Lấy Texture tương ứng với mỗi đối tượng
LPDIRECT3DTEXTURE9 TextureManager::GetAladdinTexture()
{
	return aladdin_image;
}

LPDIRECT3DSURFACE9 TextureManager::GetFinishTexture()
{
	return finish_image;
}

LPDIRECT3DSURFACE9 TextureManager::GetTheEndTexture()
{
	return theend_image;
}

LPDIRECT3DTEXTURE9 TextureManager::LoadTexture(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 image;
	D3DXIMAGE_INFO info;
	HRESULT result;

	//get Texture image from file
	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(0, "Fail To Load Image", "Hello DirectX", MB_OK);
		return NULL;
	}

	//create texture (image) from file image
	result = D3DXCreateTextureFromFileEx(
		d3ddev,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transcolor,
		&info,
		NULL,
		&image);

	//check create texture
	if (result != D3D_OK)
	{
		MessageBox(0, "Fail To Create Texture!", "Hello DirectX", MB_OK);
		return NULL;
	}
	return image;
}

LPDIRECT3DSURFACE9 TextureManager::LoadSurface(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;
	//get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
		return NULL;
	//create surface
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width, //width of the surface
		info.Height, //height of the surface
		D3DFMT_X8R8G8B8, //surface format
		D3DPOOL_DEFAULT, //memory pool to use
		&image, //pointer to the surface
		NULL); //reserved (always NULL)
	if (result != D3D_OK)
		return NULL;

	//load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(
		image, //destination surface
		NULL, //destination palette
		NULL, //destination rectangle
		filePath, //source filename
		NULL, //source rectangle
		D3DX_DEFAULT, //controls how image is filtered
		transcolor, //for transparency (0 for none)
		NULL); //source image info (usually NULL)
			   //make sure file was loaded okay
	if (result != D3D_OK)
		return NULL;
	return image;
}

//destructor of Texture manager class
TextureManager::~TextureManager()
{
	if (instance != NULL) { delete instance; instance = nullptr; }
	if (sprite_handler != NULL) { delete sprite_handler; sprite_handler = nullptr; }
	if (aladdin_image != NULL)
		aladdin_image->Release();
	if (finish_image != NULL)
		finish_image->Release();
	if (theend_image != NULL)
		theend_image->Release();
}
