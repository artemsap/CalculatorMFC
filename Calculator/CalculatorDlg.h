﻿
// CalculatorDlg.h: файл заголовка
//

#pragma once

// Диалоговое окно CCalculatorDlg
class CCalculatorDlg : public CDialogEx
{
// Создание
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV
	
// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonRdev();
	afx_msg void OnBnClickedButtonSeven();
	afx_msg void OnBnClickedButtonFour();
	afx_msg void OnBnClickedButtonOne();
	afx_msg void OnBnClickedButtonChsign();
	afx_msg void OnBnClickedButtonDelelem();
	afx_msg void OnBnClickedButtonSqr();
	afx_msg void OnBnClickedButtonEight();
	afx_msg void OnBnClickedButtonFive();
	afx_msg void OnBnClickedButtonTwo();
	afx_msg void OnBnClickedButtonZero();
	afx_msg void OnBnClickedButtonDelall();
	afx_msg void OnBnClickedButtonSqrt();
	afx_msg void OnBnClickedButtonNine();
	afx_msg void OnBnClickedButtonSix();
	afx_msg void OnBnClickedButtonThree();
	afx_msg void OnBnClickedButtonPoint();
	afx_msg void OnBnClickedButtonDelnum();
	afx_msg void OnBnClickedButtonDevide();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonEqual();
private:
	CString curr_num;
	CString prev_oper;
	
	CString last_oper;

	double lvalue;
	double rvalue;
	double tmp_res;

	double prev_rvalue;
	bool IsEqLast;
	bool IsEqualLast;
	bool IsFastOperation;
	
	void UpdateEditor(CString InputNum);
	void UpdateOperation(CString Oper);
	void DoFastOperation(CString Oper);
	double DoCalculation(double lnum, double rnum, CString last_oper);

	CString GetCorrectNumFromDouble(double num);
};