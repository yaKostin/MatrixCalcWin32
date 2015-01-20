#include "afxwin.h" // MFC �������� � ����������� ����������
#include "afxext.h"     // MFC ����������
#include "resource.h"
#include <cstdlib>

#define MAX_ROW 5
#define MAX_COL 5

#define IDC_MYBUTTON 100	// ������������� ������
#define IDC_MYEDIT 102	// ������������� ���� ��������������
#define IDC_ROWCOUNTCMBBX 103 
#define IDC_COLCOUNTCMBBX 104
#define IDC_LISTBOX 105
#define IDC_MATRIXA 200
#define IDC_MATRIXB 300
#define IDC_ZEROMATRIXARADIOBTN 400
#define IDC_ONEMATRIXARADIOBTN 401
#define IDC_USERMATRIXARADIOBTN 402
#define IDC_ZEROMATRIXBRADIOBTN 403
#define IDC_ONEMATRIXBRADIOBTN 404
#define IDC_USERMATRIXBRADIOBTN 405

static UINT indicators[] =
{
	IDS_STRING2,		// ������������� ������ ������ � ��������
	IDS_STRING1		// ������������� ������ ������ � ��������
};

class CMainWnd : public CFrameWnd
{
public:
	CMainWnd();	// ����������� �� ���������
	afx_msg void OnLButtonDblClk(UINT, CPoint);	// ����������� ��������� ������ �� ����� ������
	afx_msg void OnRButtonDblClk(UINT, CPoint);	// ����������� ��������� ������ �� ������ ������
	afx_msg void OnMouseMove(UINT, CPoint cp);		// ��� ������� ����� ���������� ��� �������� ����
	afx_msg void OnKeyDown(UINT, UINT, UINT);	// ����������� ��������� ������ �� �������
	afx_msg void OnRadioBtnChangedA();
	afx_msg void OnRadioBtnChangedB();
	afx_msg void OnSelchangeComboArray();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);	// ��� ������� ���������� ��� �������� ����
	void MenuExit();	// ��������� ������� �� ����� ������ ���� 
	~CMainWnd(); 	// ����������
private:
	CStatic *MyStatic;	// ��������� �� ������ �������
	CButton* MyButton;	// ��������� �� ������ ������
	CButton* typeZeroMatrixARadioBtn;
	CButton* typeOneMatrixARadioBtn;
	CButton* typeUserMatrixARadioBtn;
	//B
	CButton* typeZeroMatrixBRadioBtn;
	CButton* typeOneMatrixBRadioBtn;
	CButton* typeUserMatrixBRadioBtn;
	//
	CComboBox* rowCountCmbBx;
	CComboBox* colCountCmbBx;
	CEdit ***matrixACEdit;
	CEdit ***matrixBCEdit;
	CEdit* MyEdit;	// ��������� �� ������ ���� ��������������
	CListBox* listBox;
	CStatusBar m_wndStatusBar;	// ����� ������ ���������
	CMenu m_wndMenu;	// ��� ��� ����� ����
	CToolBar my_ToolBar;		// ��� ��� ����� ������ ������������ 
	CEdit*** CreateCEditMatrix(CEdit*** matrixCEdit, int x, int y, int width, int height, int xPadding, int yPadding, int id);
	void InitCComboBox(CComboBox* comboBox, int minNum, int maxNum);
	void InitCEditMatrix(CEdit*** matrixCEdit, char* str);
	void LimitRows(CEdit ***matrix, int rowCount);
	void LimitCols(CEdit ***matrix, int colCount);
	DECLARE_MESSAGE_MAP(); // ������� �������� 
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)	// ������� �������� �� ���������
	ON_WM_LBUTTONDBLCLK()		// ������� �� ������� ����� ������ ����
	ON_WM_RBUTTONDBLCLK()		// ������� �� ������� ������ ������ �����
	ON_WM_MOUSEMOVE()					   // ���� ���������
	ON_WM_KEYDOWN()			// ������� �� ������� �������
	ON_WM_CREATE()			// ������� �������� ����
	ON_COMMAND(ID_FILE_EXIT, MenuExit)	// ��� ��� , ��������� ������� �� ����� ����
	ON_BN_CLICKED(IDC_ZEROMATRIXARADIOBTN, OnRadioBtnChangedA)
	ON_BN_CLICKED(IDC_ONEMATRIXARADIOBTN, OnRadioBtnChangedA)
	ON_BN_CLICKED(IDC_USERMATRIXARADIOBTN, OnRadioBtnChangedA)
	//
	ON_BN_CLICKED(IDC_ZEROMATRIXBRADIOBTN, OnRadioBtnChangedB)
	ON_BN_CLICKED(IDC_ONEMATRIXBRADIOBTN, OnRadioBtnChangedB)
	ON_BN_CLICKED(IDC_USERMATRIXBRADIOBTN, OnRadioBtnChangedB)
	//
	//ON_CONTROL_RANGE(CBN_SELCHANGE, IDC_ZEROMATRIXARADIOBTN, IDC_USERMATRIXARADIOBTN, OnSelchangeComboArray)
	ON_CBN_SELCHANGE(IDC_ROWCOUNTCMBBX, OnSelchangeComboArray)
END_MESSAGE_MAP()

void CMainWnd::MenuExit()
{
	DestroyWindow(); // ���������� ���� 
}

void CMainWnd::OnKeyDown(UINT, UINT, UINT)
{
	AfxMessageBox(" Key Button Down ");
}

void CMainWnd::OnMouseMove(UINT, CPoint cp)
{
	char chX[10];				// ����� ��� ���������
	char chY[10];				// ����� ��� ���������
	itoa(cp.x, chX,10);			// ����� ��������� � ������
	itoa(cp.y, chY,10);			// ����� ��������� � ������
	CString csStatusX(chX);		// ��������� ������
	CString csStatusY(chY);		// ��������� ������
	m_wndStatusBar.SetPaneText(0, csStatusX);		// �������  ������ ������
	m_wndStatusBar.SetPaneText(1, csStatusY);		// �������   ������ ������ 
}

void CMainWnd::OnRadioBtnChangedA()
{
	switch(GetCheckedRadioButton(IDC_ZEROMATRIXARADIOBTN, IDC_USERMATRIXBRADIOBTN))
	{
	case IDC_ZEROMATRIXARADIOBTN:
			this->InitCEditMatrix(matrixACEdit, "0");
		break;
	case IDC_ONEMATRIXARADIOBTN:
			this->InitCEditMatrix(matrixACEdit, "1");
		break;
	case IDC_USERMATRIXARADIOBTN:
			this->InitCEditMatrix(matrixACEdit, "");
		break;
	default:
		break;
	}

}

void CMainWnd::OnRadioBtnChangedB()
{
	switch(GetCheckedRadioButton(IDC_ZEROMATRIXBRADIOBTN, IDC_USERMATRIXBRADIOBTN))
	{
	case IDC_ZEROMATRIXBRADIOBTN:
			this->InitCEditMatrix(matrixBCEdit, "0");
		break;
	case IDC_ONEMATRIXBRADIOBTN:
			this->InitCEditMatrix(matrixBCEdit, "1");
		break;
	case IDC_USERMATRIXBRADIOBTN:
			this->InitCEditMatrix(matrixBCEdit, "");
		break;
	default:
		break;
	}

}

void CMainWnd::OnSelchangeComboArray()
{
	//CComboBox* combo = (CComboBox*)GetDlgItem(IDC_ROWCOUNTCMBBX);
	char rowCountStr[3];
	int selected = this->rowCountCmbBx->GetCurSel();
	this->rowCountCmbBx->GetLBText(selected, rowCountStr);
	int rowCount = atoi(rowCountStr);
	//AfxMessageBox(rowCountStr);
	this->LimitRows(this->matrixACEdit, rowCount);
}

void CMainWnd::OnRButtonDblClk(UINT, CPoint)
{
	AfxMessageBox(" Rigth Button Click ");
}
void CMainWnd::OnLButtonDblClk(UINT, CPoint)
{
	AfxMessageBox(" Left Button Click ");
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)  return -1;
	my_ToolBar.Create(this);						    // ������� ������ �������������
	my_ToolBar.LoadToolBar(IDR_TOOLBAR1);					    // ����� �� �� ��������
	my_ToolBar.SetBarStyle(my_ToolBar.GetBarStyle()  | CBRS_SIZE_DYNAMIC);    // ��������� �����
	my_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndStatusBar.Create(this);						    // ������� ������ ���������
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)); // ���������� � ������ ��������������
	m_wndMenu.LoadMenu(IDR_MENU);                 			    // ��������� ���� �� ����� �������
	SetMenu(&m_wndMenu);							    // ���������� ����
	return 0;
}

CMainWnd::CMainWnd()
{
	Create(NULL, "MatrixCalculator", WS_OVERLAPPEDWINDOW, rectDefault, NULL, NULL);						// ������� ���� ���������
	// �������� new �� ��������� � ������ ������ ������ NULL
	// �������� ��������� �� NULL ���� ����������� ���������� �� ���������� ������
	MyStatic = new CStatic();				
	if (MyStatic!=NULL)
		MyStatic->Create("MyStatic",WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(10,50,100,100),this);				// ������� 
	MyButton = new CButton();       				// ������ ����� �� ������ �������� ��������� ������
	if (MyButton!=NULL)
		MyButton->Create("MyButton",WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(120,50,220,100), this, IDC_MYBUTTON); 
	//����� - ���������� ����� �������
	rowCountCmbBx = new CComboBox();
	if (rowCountCmbBx != NULL) 
	{
		rowCountCmbBx->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, CRect(10, 50, 100, 150), this, IDC_ROWCOUNTCMBBX);
		InitCComboBox(rowCountCmbBx, 2, MAX_ROW);
	}
	//����� - ���������� �������� �������
	colCountCmbBx = new CComboBox();
	if (colCountCmbBx != NULL) 
	{
		colCountCmbBx->Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWN, CRect(400, 100, 500, 120), this, IDC_COLCOUNTCMBBX);
		InitCComboBox(colCountCmbBx, 2, MAX_COL);
	}

	/*listBox = new CListBox();
	if (listBox != NULL)
	{
		listBox->Create(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES, CRect(100, 150, 200, 250), this, IDC_LISTBOX);
	}*/

	typeZeroMatrixARadioBtn = new CButton();
	typeZeroMatrixARadioBtn->Create("�������", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP|WS_TABSTOP, CRect(200, 300, 300, 320), this, IDC_ZEROMATRIXARADIOBTN);

	typeOneMatrixARadioBtn = new CButton();
	typeOneMatrixARadioBtn->Create("���������", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, CRect(200, 330, 300, 350), this, IDC_ONEMATRIXARADIOBTN);

	typeUserMatrixARadioBtn = new CButton();
	typeUserMatrixARadioBtn->Create("����������", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, CRect(200, 360, 300, 380), this, IDC_USERMATRIXARADIOBTN);
	//B types
	typeZeroMatrixBRadioBtn = new CButton();
	typeZeroMatrixBRadioBtn->Create("�������", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP|WS_TABSTOP, CRect(400, 300, 500, 320), this, IDC_ZEROMATRIXBRADIOBTN);

	typeOneMatrixBRadioBtn = new CButton();
	typeOneMatrixBRadioBtn->Create("���������", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, CRect(400, 330, 500, 350), this, IDC_ONEMATRIXBRADIOBTN);

	typeUserMatrixBRadioBtn = new CButton();
	typeUserMatrixBRadioBtn->Create("����������", WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, CRect(400, 360, 500, 380), this, IDC_USERMATRIXBRADIOBTN);

	MyEdit = new CEdit();
	if (MyEdit!=NULL)
		MyEdit->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(50, 50, 100, 80), this, IDC_MYEDIT);
	
	int matrixX = 150;
	int matrixY = 150;
	int matrixWidth = 300;
	int matrixHeight = 300;
	int ceilWidth = 40;
	int ceilHeight = 20;
	int ceilPaddingX = 10;
	int ceilPaddingY = 10;

	/*matrixACEdit = new CEdit**[MAX_ROW];
	for (int i = 0; i < MAX_ROW; i++)
	{
		matrixACEdit[i] = new CEdit*[MAX_COL];
		for (int j = 0; j < MAX_COL; j++)
			matrixACEdit[i][j] = new CEdit();
	}*/
	matrixACEdit = this->CreateCEditMatrix(matrixACEdit, matrixX, matrixY, ceilWidth, ceilHeight, ceilPaddingX, ceilPaddingY, IDC_MATRIXA);
	this->InitCEditMatrix(matrixACEdit, 0);
	matrixBCEdit = this->CreateCEditMatrix(matrixBCEdit, matrixX + matrixWidth, matrixY, ceilWidth, ceilHeight, ceilPaddingX, ceilPaddingY, IDC_MATRIXB);
	this->InitCEditMatrix(matrixBCEdit, 0);
}

CMainWnd::~CMainWnd()
{
	//if (MyStatic!=NULL) 
		delete MyStatic;	// ������� ������������ ������
	if (MyButton!=NULL) delete MyButton;	// ������� ������������ ������
	if (MyEdit!=NULL) delete MyEdit;	// ������� ������������ ������
	if (rowCountCmbBx != NULL) delete rowCountCmbBx;
	//if (matrixACEdit != NULL) �������� �������� ***
}

class CMyApp : public CWinApp
{
public:
	CMyApp();			//����������� �� ���������
	virtual BOOL InitInstance();//����������� �������������
};

CMyApp::CMyApp() // ����������� �������� ������ ����������
{}

void CMainWnd::LimitRows(CEdit ***matrix, int rowCount)
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			matrix[i][j]->ShowWindow(SW_SHOW);
		}
	}

	for (int i = rowCount; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			matrix[i][j]->ShowWindow(SW_HIDE);
		}
	}
}

//�������� � comboBox ������ - �� minNum �� maxNum
void CMainWnd::InitCComboBox(CComboBox* comboBox, int minNum, int maxNum)
{
	char indexStr[3];
	for (int i = minNum; i <= maxNum; i++)
	{
		itoa(i, indexStr, 10);
		comboBox->AddString(indexStr);
	}
	comboBox->SetCurSel(0);
}

void CMainWnd::InitCEditMatrix(CEdit*** matrixCEdit, char* str)
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			matrixCEdit[i][j]->SetWindowTextA(str);
		}
	}
}

//������������� CEdit*** � ���������� � ����
CEdit*** CMainWnd::CreateCEditMatrix(CEdit*** matrixCEdit, int x, int y, int width, int height, int xPadding, int yPadding, int id)
{
	matrixCEdit = new CEdit**[MAX_ROW];

	int index = 0;
	for (int i = 0; i < MAX_ROW; i++)
	{
		matrixCEdit[i] = new CEdit*[MAX_COL];
		for (int j = 0; j < MAX_COL; j++)
		{
			matrixCEdit[i][j] = new CEdit();
			int x1 = x + (xPadding + width) * j;
			int x2 = x1 + width;
			int y1 = y + (yPadding + height)* i;
			int y2 = y1 + height;
			matrixCEdit[i][j]->Create(WS_CHILD|WS_VISIBLE|WS_BORDER, CRect(x1, y1, x2, y2), this, id + index++);
			//matrixCEdit[i][j]->SetWindowTextA("a");
		}
	}
	return matrixCEdit;
}

BOOL CMyApp::InitInstance() // ����������� �������������
{
	m_pMainWnd=new CMainWnd();	// ������� ����� ����
	ASSERT(m_pMainWnd);	// ��������� ��� ������������
	m_pMainWnd->ShowWindow(SW_SHOW);// �������� ����
	m_pMainWnd->UpdateWindow();	// �������� ����
	return TRUE;		// ������� ��� ��� ���������
};

CMyApp theApp;	// ������ ����������