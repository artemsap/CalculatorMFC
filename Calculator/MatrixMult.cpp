// MatrixMult.cpp: файл реализации
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "MatrixMult.h"

// Диалоговое окно MatrixMult

IMPLEMENT_DYNAMIC(MatrixMult, CDialogEx)

MatrixMult::MatrixMult(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MATRIX, pParent)
{
	EditBlockSize = 40;
	offset_x = 100;
	offset_y = 100;
}

MatrixMult::~MatrixMult()
{
}

void MatrixMult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MatrixMult, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MULT, &MatrixMult::OnBnClickedButtonMult)
	ON_CBN_SELCHANGE(10001, &MatrixMult::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(10002, &MatrixMult::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(10003, &MatrixMult::OnCbnSelchangeCombo)
	ON_CBN_SELCHANGE(10004, &MatrixMult::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDC_BUTTON_DEBUG, &MatrixMult::OnBnClickedButtonDebug)
END_MESSAGE_MAP()

void MatrixMult::CreateEmtpyMatrix(std::vector<std::vector<CEdit*>>& Matrix, size_t offset_x, size_t offset_y, size_t Rows, size_t Cols, size_t EditBlockSize)
{
	for (int i = 0; i != Rows; ++i)
	{
		std::vector<CEdit*> tmp_vector;
		for (int j = 0; j != Cols; ++j)
		{
			CEdit* tmp_Edit = new CEdit;
			tmp_Edit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_NUMBER,
				CRect(offset_x + EditBlockSize * j,
					offset_y + EditBlockSize * i,
					offset_x + EditBlockSize * (j + 1),
					offset_y + EditBlockSize * (i + 1)), this, i + j);
			tmp_Edit->SetWindowText(_T("0"));
			tmp_vector.push_back(tmp_Edit);
		}
		Matrix.push_back(tmp_vector);
	}
}

void MatrixMult::DeleteMatrix(std::vector<std::vector<CEdit*>>& Matrix)
{
	for (auto rows : Matrix)
		for (auto elem : rows)
			elem->DestroyWindow();

	for (auto rows : Matrix)
	{
		std::for_each(rows.begin(), rows.end(), std::default_delete<CEdit>());
		rows.clear();
	}
	Matrix.clear();
}

void MatrixMult::CreateComboBox(CComboBox& combobox, int max_num, int x_start, int y_start, int x_size, int y_size, int ID)
{
	combobox.Create(WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
		CRect(x_start, y_start, x_start + x_size, y_start + y_size), this, ID);

	CString str;
	for (int i = 1; i != max_num + 1; i++)
	{
		str.Format(_T("%d"), i);
		combobox.AddString(str);
	}
	combobox.SetCurSel(2);
}

BOOL MatrixMult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CreateEmtpyMatrix(MatrixLeft, offset_x, offset_y, 3, 3, EditBlockSize);

	CreateComboBox(left_rows_box, 8,
		offset_x + (MatrixLeft[0].size() / 2 - 1) * EditBlockSize,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10001);
	CreateComboBox(left_cols_box, 8, 
		offset_x + (MatrixLeft[0].size()/2) * EditBlockSize, 
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10002);

	/*mult_sign.Create(_T("X"), WS_VISIBLE,
		CRect(offset_x + MatrixLeft[0].size() * EditBlockSize + EditBlockSize/2,
			offset_y + MatrixLeft.size() / 2 * EditBlockSize,
			offset_x + MatrixLeft[0].size() * EditBlockSize + EditBlockSize,
			offset_y + MatrixLeft.size() / 2 * EditBlockSize + EditBlockSize/2 + EditBlockSize), this);*/

	int _offset_x = offset_x + (MatrixLeft[0].size() + 1) * EditBlockSize;
	CreateEmtpyMatrix(MatrixRight, _offset_x, offset_y, 3, 3, EditBlockSize);

	CreateComboBox(right_rows_box, 8,
		_offset_x + (MatrixRight[0].size() / 2 - 1) * EditBlockSize,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10003);
	CreateComboBox(right_cols_box, 8,
		_offset_x + (MatrixRight[0].size() / 2) * EditBlockSize,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10004);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


BOOL MatrixMult::DestroyWindow()
{
	DeleteMatrix(MatrixLeft);
	DeleteMatrix(MatrixRight);
	DeleteMatrix(ResultMatrix);

	return CDialogEx::DestroyWindow();
}

void MatrixMult::OnBnClickedButtonMult()
{
	DeleteMatrix(ResultMatrix);

	Matrix<double> left_matrix(MatrixLeft);
	Matrix<double> right_matrix(MatrixRight);

	CreateEmtpyMatrix(ResultMatrix, offset_x + (MatrixLeft.size() + MatrixRight.size() + 2) * EditBlockSize, offset_y, MatrixLeft.size(), MatrixRight[0].size(), EditBlockSize);
	
	Matrix<double> res = Matrix<double>::multiply(left_matrix, right_matrix);
	res.ConvertToCEdit(ResultMatrix);
}

void MatrixMult::ReDrawAll()
{
	DeleteMatrix(MatrixLeft);
	DeleteMatrix(MatrixRight);
	DeleteMatrix(ResultMatrix);

	CreateEmtpyMatrix(MatrixLeft, offset_x, offset_y, left_rows_box.GetCurSel() + 1, left_cols_box.GetCurSel() + 1, EditBlockSize);

	/*mult_sign.Create(_T("X"), WS_VISIBLE,
		CRect(offset_x + MatrixLeft[0].size() * EditBlockSize + EditBlockSize/2,
			offset_y + MatrixLeft.size() / 2 * EditBlockSize,
			offset_x + MatrixLeft[0].size() * EditBlockSize + EditBlockSize,
			offset_y + MatrixLeft.size() / 2 * EditBlockSize + EditBlockSize/2 + EditBlockSize), this);*/

	int _offset_x = offset_x + (MatrixLeft[0].size() + 1) * EditBlockSize;
	CreateEmtpyMatrix(MatrixRight, _offset_x, offset_y, right_rows_box.GetCurSel() + 1, right_cols_box.GetCurSel() + 1, EditBlockSize);
}

void MatrixMult::OnCbnSelchangeCombo()
{
	ReDrawAll();
}

void MatrixMult::OnBnClickedButtonDebug()
{
	double debug_value = 0;
	for (auto& row : MatrixLeft) {
		for (auto& elem : row) {
			debug_value += 1.1;
			CString text;
			text.Format(_T("%g"), debug_value);
			elem->SetWindowText(text);
		}
	}

	debug_value = 0;
	for (auto& row : MatrixRight) {
		for (auto& elem : row) {
			debug_value += 1.1;
			CString text;
			text.Format(_T("%g"), debug_value);
			elem->SetWindowText(text);
		}
	}
}
