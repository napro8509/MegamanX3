#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <iostream>
#include "Directx.h"
#include "trace.h"

using namespace std;

class TextureManager
{
private:
	static TextureManager* instance;

	LPD3DXSPRITE sprite_handler;

	LPDIRECT3DTEXTURE9 aladdin_image;

	LPDIRECT3DSURFACE9 finish_image;
	LPDIRECT3DSURFACE9 theend_image;


public:
	//contructor of Texture manager class
	TextureManager();

	static TextureManager* GetInstance();

	//create texture
	void CreateTexture(LPDIRECT3DDEVICE9 d3ddev);
	void CreateSurface(LPDIRECT3DDEVICE9 d3ddev);

	LPD3DXSPRITE GetSprite_Handler();

	//Lấy Texture tương ứng với mỗi đối tượng
	LPDIRECT3DTEXTURE9 GetAladdinTexture();

	LPDIRECT3DSURFACE9 GetFinishTexture();
	LPDIRECT3DSURFACE9 GetTheEndTexture();


	//LoadTexture
	LPDIRECT3DTEXTURE9 LoadTexture(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor);
	LPDIRECT3DSURFACE9 LoadSurface(LPDIRECT3DDEVICE9 d3ddev, LPCSTR filePath, D3DCOLOR transcolor);

	//destructor of Texture manager class
	~TextureManager();
};

#endif