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
	offset_x = 50;
	offset_y = 50;
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

void MatrixMult::CreateComboBox(CComboBox& combobox, int max_num, int x_start, int y_start, int x_size, int y_size, int ID, int curpos)
{
	combobox.Create(WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
		CRect(x_start, y_start, x_start + x_size, y_start + y_size), this, ID);

	CString str;
	for (int i = 1; i != max_num + 1; i++)
	{
		str.Format(_T("%d"), i);
		combobox.AddString(str);
	}
	combobox.SetCurSel(curpos);
}

BOOL MatrixMult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	/*CreateEmtpyMatrix(MatrixLeft, offset_x, offset_y, 3, 3, EditBlockSize);

	CreateComboBox(left_rows_box, 8,
		offset_x + (MatrixLeft[0].size() * EditBlockSize) / 2 - EditBlockSize,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10001, 2);
	CreateComboBox(left_cols_box, 8,
		offset_x + (MatrixLeft[0].size() * EditBlockSize) / 2,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10002, 2);

	int x_start = offset_x + MatrixLeft[0].size() * EditBlockSize + EditBlockSize / 2;
	int y_start = offset_y + MatrixLeft.size() / 2 * EditBlockSize;
	mult_sign.Create(_T("X"), WS_VISIBLE, CRect(x_start, y_start, x_start + EditBlockSize, y_start + EditBlockSize), this);

	int _offset_x = offset_x + (MatrixLeft[0].size() + 1) * EditBlockSize;
	CreateEmtpyMatrix(MatrixRight, _offset_x, offset_y, 3, 3, EditBlockSize);

	CreateComboBox(right_rows_box, 8,
		_offset_x + (MatrixRight[0].size() * EditBlockSize) / 2 - EditBlockSize,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10003, 2);
	CreateComboBox(right_cols_box, 8,
		_offset_x + (MatrixRight[0].size() * EditBlockSize) / 2,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10004, 2);

	x_start = x_start + MatrixRight[0].size() * EditBlockSize + EditBlockSize;
	y_start = offset_y + MatrixRight.size() / 2 * EditBlockSize;
	equal_sign.Create(_T("="), WS_VISIBLE, CRect(x_start, y_start, x_start + EditBlockSize, y_start + EditBlockSize), this);
	*/
	ReDrawAll(true);
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
	if (MatrixLeft[0].size() != MatrixRight.size())
	{
		AfxMessageBox(_T("Неправильный размер матрицы!"));
	}
	else
	{
		DeleteMatrix(ResultMatrix);

		Matrix<double> left_matrix(MatrixLeft.size(), MatrixLeft[0].size());
		Matrix<double> right_matrix(MatrixRight.size(), MatrixRight[0].size());
		Convert(MatrixLeft, left_matrix);
		Convert(MatrixRight, right_matrix);

		CreateEmtpyMatrix(ResultMatrix, offset_x + (MatrixLeft.size() + MatrixRight[0].size() + 2) * EditBlockSize, offset_y, MatrixLeft.size(), MatrixRight[0].size(), EditBlockSize);

		Matrix<double> res = Matrix<double>::multiply(left_matrix, right_matrix);
		ConvertToCEdit(ResultMatrix, res);
	}
}

void MatrixMult::ReDrawAll(bool IsFirst = false)
{
	int cur_pos_left_rows = 1;
	int cur_pos_left_cols = 1;
	int cur_pos_right_rows = 1;
	int cur_pos_right_cols = 1;
	if (!IsFirst)
	{
		DeleteMatrix(MatrixLeft);
		DeleteMatrix(MatrixRight);
		DeleteMatrix(ResultMatrix);
		cur_pos_left_rows = left_rows_box.GetCurSel();
		cur_pos_left_cols = left_cols_box.GetCurSel();
		cur_pos_right_rows = right_rows_box.GetCurSel();
		cur_pos_right_cols = right_cols_box.GetCurSel();
		left_rows_box.DestroyWindow();
		left_cols_box.DestroyWindow();
		right_rows_box.DestroyWindow();
		right_cols_box.DestroyWindow();
	}

	CreateEmtpyMatrix(MatrixLeft, offset_x, offset_y, cur_pos_left_rows + 1, cur_pos_left_cols + 1, EditBlockSize);

	CreateComboBox(left_rows_box, 8,
		offset_x + (MatrixLeft[0].size() * EditBlockSize) / 2 - EditBlockSize,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10001, cur_pos_left_rows);
	
	CreateComboBox(left_cols_box, 8,
		offset_x + (MatrixLeft[0].size() * EditBlockSize) / 2,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10002, cur_pos_left_cols);

	int x_start = offset_x + MatrixLeft[0].size() * EditBlockSize + EditBlockSize / 2;
	int y_start = offset_y + MatrixLeft.size() / 2 * EditBlockSize;
	mult_sign.DestroyWindow();
	mult_sign.Create(_T("X"), WS_VISIBLE, CRect(x_start, y_start, x_start + EditBlockSize, y_start + EditBlockSize), this);

	int _offset_x = offset_x + (MatrixLeft[0].size() + 1) * EditBlockSize;
	CreateEmtpyMatrix(MatrixRight, _offset_x, offset_y, cur_pos_right_rows + 1, cur_pos_right_cols + 1, EditBlockSize);

	CreateComboBox(right_rows_box, 8,
		_offset_x + (MatrixRight[0].size() * EditBlockSize) / 2 - EditBlockSize,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10003, cur_pos_right_rows);

	CreateComboBox(right_cols_box, 8,
		_offset_x + (MatrixRight[0].size() * EditBlockSize) / 2,
		offset_y - EditBlockSize,
		EditBlockSize, 200, 10004, cur_pos_right_cols);

	x_start = x_start + MatrixRight[0].size() * EditBlockSize + EditBlockSize;
	y_start = offset_y + MatrixRight.size() / 2 * EditBlockSize;
	equal_sign.DestroyWindow();
	equal_sign.Create(_T("="), WS_VISIBLE, CRect(x_start, y_start, x_start + EditBlockSize, y_start + EditBlockSize), this);
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
			debug_value += 1;
			CString text;
			text.Format(_T("%g"), debug_value);
			elem->SetWindowText(text);
		}
	}

	debug_value = 0;
	for (auto& row : MatrixRight) {
		for (auto& elem : row) {
			debug_value += 1;
			CString text;
			text.Format(_T("%g"), debug_value);
			elem->SetWindowText(text);
		}
	}
}
