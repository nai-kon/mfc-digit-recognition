
// NeuralNetwork_NumOCR.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CNeuralNetworkNumOCRApp:
// このクラスの実装については、NeuralNetwork_NumOCR.cpp を参照してください
//

class CNeuralNetworkNumOCRApp : public CWinApp
{
public:
	CNeuralNetworkNumOCRApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CNeuralNetworkNumOCRApp theApp;
