
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
	arMouse.SetSize(1024);
}

void CNeuralNetworkNumOCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_NUMINPUT, m_numInput);
}

BEGIN_MESSAGE_MAP(CNeuralNetworkNumOCRDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXEC, &CNeuralNetworkNumOCRDlg::OnBnClickedBtnExec)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CNeuralNetworkNumOCRDlg::OnBnClickedBtnClear)
	ON_STN_CLICKED(ID_OLE_EDIT_CHANGE_ICON, &CNeuralNetworkNumOCRDlg::OnStnClickedOleEditChangeIcon)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_STN_CLICKED(ID_NUMINPUT, &CNeuralNetworkNumOCRDlg::OnStnClickedNuminput)
END_MESSAGE_MAP()


// CNeuralNetworkNumOCRDlg メッセージ ハンドラー

BOOL CNeuralNetworkNumOCRDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	

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
		//CPaintDC    cdc(GetDlgItem(ID_NUMINPUT));
		//CPaintDC    cdcApp(this);
		CDC* pDC = m_numInput.GetDC();




		ReleaseDC(pDC);
		//CDC			memDC;
		//CBitmap		memBmp;
		//memDC.CreateCompatibleDC(pDC);

		////CRect rcBack;
		////GetDlgItem(ID_NUMINPUT)->GetClientRect(rcBack);
		////cdc.FillSolidRect(0, 0, rcBack.Width(), rcBack.Height(), RGB(0, 0, 0)); 
		//CRect		rc;
		//this->GetClientRect(rc);
		//memBmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
		//memDC.SelectObject(&memBmp);
		//

		//CPen Pen(PS_SOLID, 10, RGB(0, 0, 0));
		//CPen* pOldPen = memDC.SelectObject(&Pen);
		//int iSize = arMouse.GetSize();
		//for (int i = 0; i < iSize; i++) {
		//	memDC.Ellipse(arMouse[i].x - 2, arMouse[i].y - 2, arMouse[i].x + 2, arMouse[i].y + 2);
		//}
		//memDC.SelectObject(pOldPen);

		//::BitBlt(pDC->GetSafeHdc(), 0, 0, rc.Width(), rc.Height(), memDC.GetSafeHdc(), 0, 0, SRCCOPY);
		//
		//::DeleteObject(memDC);
		//::DeleteObject(memBmp);

		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CNeuralNetworkNumOCRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNeuralNetworkNumOCRDlg::OnBnClickedBtnExec()
{

}


void CNeuralNetworkNumOCRDlg::OnBnClickedBtnClear()
{
	arMouse.RemoveAll();
	arMouse.SetSize(1024);
	InvalidateRect(NULL);
}


void CNeuralNetworkNumOCRDlg::OnStnClickedOleEditChangeIcon()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CNeuralNetworkNumOCRDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bLButton) {


		arMouse.Add(point);
		CRect rc;
		InvalidateRect(NULL);
		//TRACE("point.x:%d y:%d", m_ptMouse.x, m_ptMouse.y);
	}

	CDialog::OnMouseMove(nFlags, point);
}


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


void CNeuralNetworkNumOCRDlg::OnStnClickedNuminput()
{


}
