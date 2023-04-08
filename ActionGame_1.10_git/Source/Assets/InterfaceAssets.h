#pragma once
#include "../../Source/System/Designpattern/Singleton.h"

//--------------------------------------
// Assetsデータ管理のインターフェース
//--------------------------------------

class InterfaceAssets
{
public:
	// 初回読み込み
	virtual void LoadInitalize() = 0;
};

