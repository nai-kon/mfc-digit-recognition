
// NeuralNetwork_NumOCRDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "NeuralNetwork_NumOCR.h"
#include "NeuralNetwork_NumOCRDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNeuralNetworkNumOCRDlg ダイアログ



CNeuralNetworkNumOCRDlg::CNeuralNetworkNumOCRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_NEURALNETWORK_NUMOCR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bLButton = FALSE;
	m_hdcInput = NULL;
	m_hbmpInput = NULL;
	m_lpInputPxl = NULL;
}

CNeuralNetworkNumOCRDlg::~CNeuralNetworkNumOCRDlg()
{
	if (m_hbmpInput) DeleteObject(m_hbmpInput);
	if (m_hdcInput) DeleteDC(m_hdcInput);
}

void CNeuralNetworkNumOCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_NUMINPUT, m_numInput);
	DDX_Control(pDX, IDC_BTN_EXEC, m_btnRecog);
}

BEGIN_MESSAGE_MAP(CNeuralNetworkNumOCRDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_EXEC, &CNeuralNetworkNumOCRDlg::OnBnClickedBtnExec)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CNeuralNetworkNumOCRDlg::OnBnClickedBtnClear)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CNeuralNetworkNumOCRDlg メッセージ ハンドラー

BOOL CNeuralNetworkNumOCRDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	m_numInput.GetWindowRect(&m_rcInput);
	ScreenToClient(&m_rcInput);

	//DIB情報の設定
	static BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = m_rcInput.Width();
	bmpInfo.bmiHeader.biHeight = m_rcInput.Height();
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	CDC	*pDC = m_numInput.GetDC();

	m_hdcInput = CreateCompatibleDC(pDC->GetSafeHdc());
	m_hbmpInput = CreateDIBSection(m_hdcInput, &bmpInfo, DIB_RGB_COLORS, (void**)&m_lpInputPxl, NULL, 0);

	ReleaseDC(pDC);

	SelectObject(m_hdcInput, m_hbmpInput);
	PatBlt(m_hdcInput, 0, 0, m_rcInput.Width(), m_rcInput.Height(), WHITENESS);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CNeuralNetworkNumOCRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		// バッファを表画面へ転送
		BitBlt(dc.GetSafeHdc(), m_rcInput.left, m_rcInput.top, m_rcInput.Width(), m_rcInput.Height(), m_hdcInput, 0, 0, SRCCOPY);

		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
//HCURSOR CNeuralNetworkNumOCRDlg::OnQueryDragIcon()
//{
//	return static_cast<HCURSOR>(m_hIcon);
//}

void CNeuralNetworkNumOCRDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLButton = TRUE;

	CDialog::OnLButtonDown(nFlags, point);
}


void CNeuralNetworkNumOCRDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bLButton = FALSE;

	CDialog::OnLButtonUp(nFlags, point);
}


// 手書き文字の描画
void CNeuralNetworkNumOCRDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	static CPoint prePoint(point);

	if (m_bLButton) {
		CPen lPen(PS_SOLID, 7, RGB(0, 0, 0));
		HGDIOBJ hOld = SelectObject(m_hdcInput, lPen);
		MoveToEx(m_hdcInput, prePoint.x - m_rcInput.left, prePoint.y - m_rcInput.top, NULL);
		LineTo(m_hdcInput, point.x - m_rcInput.left, point.y - m_rcInput.top);
		InvalidateRect(m_rcInput);
		SelectObject(m_hdcInput, hOld);
	}

	prePoint = point; // 前回のマウス位置を記憶

	CDialog::OnMouseMove(nFlags, point);
}

// 入力画面をクリア
void CNeuralNetworkNumOCRDlg::OnBnClickedBtnClear()
{
	m_btnRecog.EnableWindow(TRUE);
	m_bLButton = FALSE;
	PatBlt(m_hdcInput, 0, 0, m_rcInput.Width(), m_rcInput.Height(), WHITENESS);
	InvalidateRect(m_rcInput);
}


// 文字認識処理
void CNeuralNetworkNumOCRDlg::OnBnClickedBtnExec()
{
	// Recognitionボタンを無効化
	m_btnRecog.EnableWindow(FALSE);

	// 数値
	InputPixToVec();

}



// 手書き入力文字をベクトル化
void CNeuralNetworkNumOCRDlg::InputPixToVec()
{
	if (m_lpInputPxl == NULL) return;

	// 文字を囲う枠および文字のセンタリング
	RECT rcNumFrame = {LONG_MAX, LONG_MAX, LONG_MIN, LONG_MIN};
	int iWidth = m_rcInput.Width();
	int iHeight = m_rcInput.Height();

	for(int iY = 0; iY < iHeight; iY++){
		int iYOffset = (iHeight - iY - 1) * iWidth; // 上下反転している事に注意
		for (int iX = 0; iX < iWidth; iX++) {
			BYTE bRedPix = GetRValue(m_lpInputPxl[iYOffset + iX]); // モノクロなので赤の画素のみ取得でOK
			if (bRedPix == 0) { // 文字の描画位置取得
				if (iY < rcNumFrame.top) rcNumFrame.top = iY;
				if (iY > rcNumFrame.bottom) rcNumFrame.bottom = iY;
				if (iX < rcNumFrame.left) rcNumFrame.left = iX;
				if (iX > rcNumFrame.right) rcNumFrame.right = iX;
			}
		}
	}

	// 中心位置からの文字のズレを算出
	int dX = (rcNumFrame.left + (rcNumFrame.right - rcNumFrame.left) / 2) - iWidth / 2;
	int dY = (rcNumFrame.top + (rcNumFrame.bottom - rcNumFrame.top) / 2) - iHeight / 2;

	// 文字のセンタリングとベクトル化
	for (int iY = 0; iY < iHeight; iY+=6) {
		for (int iX = 0; iX < iWidth; iX+=6) {

			UINT uiAvgPix = 0;
			for (int iInY = iY; iInY < iY + 6; iInY++) {
				int iOffsetY = (iHeight - iInY - 1 - dY);
				for (int iInX = iX; iInX < iX + 6; iInX++) {

					BYTE bRedPix = 255;
					if (iOffsetY >= 0 && iOffsetY < iHeight && iInX + dX >= 0 && iInX + dX < iWidth) {
						bRedPix = GetRValue(m_lpInputPxl[(iOffsetY * iWidth) + iInX + dX]);
					}

					//TRACE("y:%d x:%d\n", iInY, iInX);
					uiAvgPix += bRedPix;
				}
			}
			uiAvgPix /= 36;


			//for (int iInY = iY; iInY < iY + 6; iInY++) {
			//	int iYOffset = (iHeight - iInY - 1) * iWidth;
			//	for (int iInX = iX; iInX < iX + 6; iInX++) {
			//		m_lpInputPxl[iYOffset + iInX] = RGB(uiAvgPix, uiAvgPix, uiAvgPix);
			//	}
			//}

		}
	}


	// 文字を囲う枠を描画
	CPen lPen(PS_SOLID, 1, RGB(255, 50, 50));
	HGDIOBJ hOld = SelectObject(m_hdcInput, lPen);
	SelectObject(m_hdcInput, GetStockObject(NULL_BRUSH));
	Rectangle(m_hdcInput, rcNumFrame.left - 5, rcNumFrame.top - 5, rcNumFrame.right + 5, rcNumFrame.bottom + 5);
	InvalidateRect(m_rcInput);

}
