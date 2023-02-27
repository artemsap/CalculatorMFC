#pragma once
#include "afxdialogex.h"
#include <vector>
#include <algorithm>
#include <memory>
#include "Matrix.h"

// Диалоговое окно MatrixMult

class MatrixMult : public CDialogEx
{
	DECLARE_DYNAMIC(MatrixMult)

public:
	MatrixMult(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~MatrixMult();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATRIX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	std::vector<std::vector<CEdit*>> MatrixLeft;
	std::vector<std::vector<CEdit*>> MatrixRight;
	std::vector<std::vector<CEdit*>> ResultMatrix;

	CComboBox left_rows_box;
	CComboBox left_cols_box;
	
	CComboBox right_rows_box;
	CComboBox right_cols_box;

	CStatic mult_sign;
	CStatic equal_sign;

	size_t EditBlockSize;

	int offset_x;
	int offset_y;

	void CreateEmtpyMatrix(std::vector<std::vector<CEdit*>>& Matrix, size_t offset_x, size_t offset_y, size_t Rows, size_t Cols, size_t EditBlockSize);
	void DeleteMatrix(std::vector<std::vector<CEdit*>>& Matrix);

	void CreateComboBox(CComboBox& combobox, int max_num, int x_start, int y_start, int x_end, int y_end, int ID);

	void ReDrawAll();

public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonMult();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnBnClickedButtonDebug();
};
