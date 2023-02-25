
// CalculatorDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CCalculatorDlg



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, curr_num(_T("0")), IsEqLast(false), prev_oper(_T("")), last_oper(_T(""))
	, IsEqualLast(false), prev_rvalue(0), IsFastOperation(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CALC_TMP, curr_num);
	DDX_Text(pDX, IDC_CALC_OPER, prev_oper);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Mod, &CCalculatorDlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_RDEV, &CCalculatorDlg::OnBnClickedButtonRdev)
	ON_BN_CLICKED(IDC_BUTTON_SEVEN, &CCalculatorDlg::OnBnClickedButtonSeven)
	ON_BN_CLICKED(IDC_BUTTON_FOUR, &CCalculatorDlg::OnBnClickedButtonFour)
	ON_BN_CLICKED(IDC_BUTTON_ONE, &CCalculatorDlg::OnBnClickedButtonOne)
	ON_BN_CLICKED(IDC_BUTTON_CHSIGN, &CCalculatorDlg::OnBnClickedButtonChsign)
	ON_BN_CLICKED(IDC_BUTTON_DELELEM, &CCalculatorDlg::OnBnClickedButtonDelelem)
	ON_BN_CLICKED(IDC_BUTTON_SQR, &CCalculatorDlg::OnBnClickedButtonSqr)
	ON_BN_CLICKED(IDC_BUTTON_EIGHT, &CCalculatorDlg::OnBnClickedButtonEight)
	ON_BN_CLICKED(IDC_BUTTON_FIVE, &CCalculatorDlg::OnBnClickedButtonFive)
	ON_BN_CLICKED(IDC_BUTTON_TWO, &CCalculatorDlg::OnBnClickedButtonTwo)
	ON_BN_CLICKED(IDC_BUTTON_ZERO, &CCalculatorDlg::OnBnClickedButtonZero)
	ON_BN_CLICKED(IDC_BUTTON_DELALL, &CCalculatorDlg::OnBnClickedButtonDelall)
	ON_BN_CLICKED(IDC_BUTTON_SQRT, &CCalculatorDlg::OnBnClickedButtonSqrt)
	ON_BN_CLICKED(IDC_BUTTON_NINE, &CCalculatorDlg::OnBnClickedButtonNine)
	ON_BN_CLICKED(IDC_BUTTON_SIX, &CCalculatorDlg::OnBnClickedButtonSix)
	ON_BN_CLICKED(IDC_BUTTON_THREE, &CCalculatorDlg::OnBnClickedButtonThree)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CCalculatorDlg::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_DELNUM, &CCalculatorDlg::OnBnClickedButtonDelnum)
	ON_BN_CLICKED(IDC_BUTTON_DEVIDE, &CCalculatorDlg::OnBnClickedButtonDevide)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCalculatorDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCalculatorDlg::OnBnClickedButtonEqual)
END_MESSAGE_MAP()


// Обработчики сообщений CCalculatorDlg

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_NUMPAD0 || pMsg->wParam == 0x30)
			OnBnClickedButtonZero();
		else if (pMsg->wParam == VK_NUMPAD1 || pMsg->wParam == 0x31)
			OnBnClickedButtonOne();
		else if (pMsg->wParam == VK_NUMPAD2 || pMsg->wParam == 0x32)
			OnBnClickedButtonTwo();
		else if (pMsg->wParam == VK_NUMPAD3 || pMsg->wParam == 0x33)
			OnBnClickedButtonThree();
		else if (pMsg->wParam == VK_NUMPAD4 || pMsg->wParam == 0x34)
			OnBnClickedButtonFour();
		else if (pMsg->wParam == VK_NUMPAD5 || pMsg->wParam == 0x35)
			OnBnClickedButtonFive();
		else if (pMsg->wParam == VK_NUMPAD6 || pMsg->wParam == 0x36)
			OnBnClickedButtonSix();
		else if (pMsg->wParam == VK_NUMPAD7 || pMsg->wParam == 0x37)
			OnBnClickedButtonSeven();
		else if (pMsg->wParam == VK_NUMPAD8 || pMsg->wParam == 0x38)
			OnBnClickedButtonEight();
		else if (pMsg->wParam == VK_NUMPAD9 || pMsg->wParam == 0x39)
			OnBnClickedButtonNine();
		else if (pMsg->wParam == VK_MULTIPLY)
			OnBnClickedButtonMultiply();
		else if (pMsg->wParam == VK_ADD || pMsg->wParam == VK_OEM_PLUS)
			OnBnClickedButtonPlus();
		else if (pMsg->wParam == VK_SUBTRACT || pMsg->wParam == VK_OEM_MINUS)
			OnBnClickedButtonMinus();
		else if (pMsg->wParam == VK_DIVIDE)
			OnBnClickedButtonDevide();
		else if (pMsg->wParam == VK_SEPARATOR)
			OnBnClickedButtonPoint();
		else if (pMsg->wParam == VK_DELETE)
			OnBnClickedButtonDelelem();
		else if (pMsg->wParam == VK_BACK)
			OnBnClickedButtonDelnum();
		//else if (pMsg->wParam == VK_RETURN)
		//	OnBnClickedButtonEqual();
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CCalculatorDlg::OnBnClickedButtonOne()
{
	UpdateEditor(CString("1"));
}

void CCalculatorDlg::OnBnClickedButtonTwo()
{
	UpdateEditor(CString("2"));
}

void CCalculatorDlg::OnBnClickedButtonThree()
{
	UpdateEditor(CString("3"));
}

void CCalculatorDlg::OnBnClickedButtonFour()
{
	UpdateEditor(CString("4"));
}

void CCalculatorDlg::OnBnClickedButtonFive()
{
	UpdateEditor(CString("5"));
}

void CCalculatorDlg::OnBnClickedButtonSix()
{
	UpdateEditor(CString("6"));
}

void CCalculatorDlg::OnBnClickedButtonSeven()
{
	UpdateEditor(CString("7"));
}

void CCalculatorDlg::OnBnClickedButtonEight()
{
	UpdateEditor(CString("8"));
}

void CCalculatorDlg::OnBnClickedButtonNine()
{
	UpdateEditor(CString("9"));
}

void CCalculatorDlg::OnBnClickedButtonZero()
{
	UpdateEditor(CString("0"));
}

void CCalculatorDlg::OnBnClickedButtonPoint()
{
	UpdateEditor(CString("."));
}

void CCalculatorDlg::OnBnClickedButtonDelelem()
{
	curr_num = CString("0");
	UpdateData(false);
}

void CCalculatorDlg::OnBnClickedButtonDelall()
{
	curr_num = CString("0");
	prev_oper = CString("");
	last_oper = CString("");
	UpdateData(false);
}

void CCalculatorDlg::OnBnClickedButtonDelnum()
{
	curr_num.Delete(curr_num.GetLength() - 1);
	if (curr_num == "")
		curr_num = CString("0");
	UpdateData(false);
}

void CCalculatorDlg::OnBnClickedButtonRdev()
{
	DoFastOperation(CString("revdevide"));
}

void CCalculatorDlg::OnBnClickedButtonChsign()
{
	DoFastOperation(CString("chsign"));
}

void CCalculatorDlg::OnBnClickedButtonSqr()
{
	DoFastOperation(CString("sqr"));
}

void CCalculatorDlg::OnBnClickedButtonSqrt()
{
	DoFastOperation(CString("sqrt"));
}

void CCalculatorDlg::OnBnClickedButtonMod()
{
	DoFastOperation(CString("%"));
}

void CCalculatorDlg::OnBnClickedButtonDevide()
{
	UpdateOperation(CString("/"));
}

void CCalculatorDlg::OnBnClickedButtonMultiply()
{
	UpdateOperation(CString("*"));
}

void CCalculatorDlg::OnBnClickedButtonMinus()
{
	UpdateOperation(CString("-"));
}

void CCalculatorDlg::OnBnClickedButtonPlus()
{
	UpdateOperation(CString("+"));
}

void CCalculatorDlg::OnBnClickedButtonEqual()
{
	if (IsEqualLast && last_oper != "")
	{
		tmp_res = DoCalculation(lvalue, prev_rvalue, last_oper);
		CString tmp_str;
		tmp_str.Format(_T("%g"), prev_rvalue);
		prev_oper = curr_num + last_oper + tmp_str + CString("=");
	}
	else if (IsEqualLast && last_oper == "")
	{
		tmp_res = _ttof(curr_num);
		prev_oper = curr_num + CString("=");
	}
	else if (IsFastOperation)
	{
		tmp_res = _ttof(curr_num);
		prev_oper += CString("=");
	}
	else
	{
		rvalue = _ttof(curr_num);
		prev_rvalue = rvalue;
		tmp_res = DoCalculation(lvalue, rvalue, last_oper);
		prev_oper += curr_num + CString("=");
	}
		
	lvalue = tmp_res;
	curr_num.Format(_T("%g"), tmp_res);
	IsEqLast = true;
	IsEqualLast = true;

	UpdateData(false);
}

void CCalculatorDlg::UpdateEditor(CString InputNum)
{
	if (!IsEqLast)
	{
		if (InputNum != ".")
		{
			if (curr_num != "0")
				curr_num += InputNum;
			else
				curr_num = InputNum;
		}
		else
		{
			if (curr_num.Find('.') == -1)
				curr_num += InputNum;
		}
	}
	else
	{
		if (InputNum != ".")
		{
			curr_num = InputNum;
		}
		else
		{
			curr_num = CString("0.");
		}

		if (IsEqualLast)
		{
			lvalue = 0;
			prev_oper = "";
			last_oper = "";
		}

	}
	IsEqLast = false;
	IsEqualLast = false;
	IsFastOperation = false;
	UpdateData(false);
}

void CCalculatorDlg::UpdateOperation(CString Oper)
{
	IsEqLast = true;
	lvalue = _ttof(curr_num);
	rvalue = lvalue;
	prev_oper = curr_num + Oper;
	last_oper = Oper;
	UpdateData(false);
}

void CCalculatorDlg::DoFastOperation(CString Oper)
{
	IsFastOperation = true;
	auto tmp = _ttof(curr_num);

	if (Oper == CString("sqr"))
	{
		tmp *= tmp;
		prev_oper = Oper + '(' + curr_num + ')';
	}
	else if (Oper == CString("sqrt"))
	{
		tmp = sqrt(tmp);
		prev_oper = Oper + '(' + curr_num + ')';
	}
	else if (Oper == CString("chsign"))
	{
		tmp = -tmp;
	}
	else if (Oper == CString("revdevide"))
	{
		tmp = 1 / tmp;
		prev_oper = CString("1/") + curr_num;
	}
	else if (Oper == CString("%"))
	{
		tmp = tmp / 100;
	}

	curr_num.Format(_T("%g"), tmp);
	UpdateData(false);
}

double CCalculatorDlg::DoCalculation(double lnum, double rnum, CString last_oper)
{
	double res = 0;

	if (last_oper == CString("+"))
	{
		res = lnum + rnum;
	}
	else if (last_oper == CString("-"))
	{
		res = lnum - rnum;
	}
	else if (last_oper == CString("/"))
	{
		res = lnum / rnum;
	}
	else if (last_oper == CString("*"))
	{
		res = lnum * rnum;
	}
	else
	{
		res = rnum;
	}

	return res;
}

CString CCalculatorDlg::GetCorrectNumFromDouble(double num)
{
	CString res;
	res;

	int len_to_del = 0;
	for (int i = res.GetLength() - 1; i != 0; --i) {
		if (res[i] == '0')
			len_to_del++;
		else
			break;
	}
	res.Delete(res.GetLength() - len_to_del - 1, len_to_del);

	return res;
}
