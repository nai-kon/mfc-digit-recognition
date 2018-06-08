
// NeuralNetwork_NumOCRDlg.h : ヘッダー ファイル
//

#pragma once


// CNeuralNetworkNumOCRDlg ダイアログ
class CNeuralNetworkNumOCRDlg : public CDialog
{
// コンストラクション
public:
	CNeuralNetworkNumOCRDlg(CWnd* pParent = NULL);	// 標準コンストラクター

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
	CPoint m_ptMouse;
	CArray<CPoint> arMouse;
	HDC m_hdcInput;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnExec();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnStnClickedOleEditChangeIcon();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedNuminput();
	CStatic m_numInput;
};
