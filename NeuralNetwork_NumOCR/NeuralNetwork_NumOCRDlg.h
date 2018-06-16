
// NeuralNetwork_NumOCRDlg.h : ヘッダー ファイル
//

#pragma once


#include "FFNN.h"

// CNeuralNetworkNumOCRDlg ダイアログ
class CNeuralNetworkNumOCRDlg : public CDialog
{
// コンストラクション
public:
	CNeuralNetworkNumOCRDlg(CWnd* pParent = NULL);	// 標準コンストラクター
	~CNeuralNetworkNumOCRDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEURALNETWORK_NUMOCR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	BOOL m_bLButton;

	HDC m_hdcInput;
	HBITMAP m_hbmpInput;
	COLORREF *m_lpInputPxl;
	CRect m_rcInput;
	FF_Neural m_NumOcr;
	CFont m_stResFont;

	void GetInputPixel(doubleVec &vecInput);

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnExec();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnTrain();
	CStatic m_numInput;
	CButton m_btnRecog;
	CButton m_btnClear;
	CStatic m_stRes;
};
