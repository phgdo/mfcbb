
// finalDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "final.h"
#include "finalDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static int fWidth;
static int fHeight;
const double PI = 3.141592653589793;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CfinalDlg dialog



CfinalDlg::CfinalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfinalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BALLS, m_edt_balls);
	DDX_Control(pDX, IDC_LIST_BALLS, m_list_balls);
	DDX_Control(pDX, IDC_BTN_CREATE, m_btn_create);
	DDX_Control(pDX, IDC_BTN_DELETE, m_btn_delete);
}

BEGIN_MESSAGE_MAP(CfinalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
//	ON_EN_CHANGE(IDC_EDIT1, &CfinalDlg::OnEnChangeEdit1)
ON_BN_CLICKED(IDC_BTN_CREATE, &CfinalDlg::OnBnClickedBtnCreate)
ON_WM_ERASEBKGND()
ON_BN_CLICKED(IDC_BTN_DELETE, &CfinalDlg::OnBnClickedBtnDelete)
ON_EN_UPDATE(IDC_EDIT_BALLS, &CfinalDlg::OnEnUpdateEditBalls)
END_MESSAGE_MAP()


// CfinalDlg message handlers

BOOL CfinalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetTimer(1, 1000 / 100, NULL);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CfinalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CfinalDlg::OnPaint()
{
	CPaintDC dc(this);
	// Tạo CDC tạm thời và bitmap tạm thời

	/*
	CRect rectDialog;
	GetClientRect(rectDialog);

	CDC m_dcDoubleBuffer;
	CBitmap m_bmpDoubleBuffer;

	// Tính toán kích thước double buffer
	int doubleBufferWidth = rectDialog.Width() - 200;
	int doubleBufferHeight = rectDialog.Height();

	// Kiểm tra nếu kích thước double buffer đã thay đổi
	if (m_bmpDoubleBuffer.GetSafeHandle() == nullptr || m_bmpDoubleBuffer.GetBitmapDimension() != CSize(doubleBufferWidth, doubleBufferHeight))
	{
		m_dcDoubleBuffer.DeleteDC();
		m_bmpDoubleBuffer.DeleteObject();

		// Tạo bitmap double buffer mới
		m_dcDoubleBuffer.CreateCompatibleDC(&dc);
		m_bmpDoubleBuffer.CreateCompatibleBitmap(&dc, doubleBufferWidth, doubleBufferHeight);
		m_dcDoubleBuffer.SelectObject(&m_bmpDoubleBuffer);
	}

	// Vẽ nội dung lên double buffer
	m_dcDoubleBuffer.FillSolidRect(0, 0, doubleBufferWidth, doubleBufferHeight, RGB(255, 255, 255));
	for (const auto& ball : m_balls) {
		ball.Draw(&m_dcDoubleBuffer);
	}
	// Vẽ các yếu tố giao diện lên double buffer

	// Vẽ double buffer lên dialog
	dc.BitBlt(0, 0, doubleBufferWidth, doubleBufferHeight, &m_dcDoubleBuffer, 0, 0, SRCCOPY);

	// Tải lại 2/3 độ rộng của dialog
	int invalidateLeft = 0;
	int invalidateRight = rectDialog.Width() * 2 / 3;
//	InvalidateRect(CRect(invalidateLeft, 0, invalidateRight, rectDialog.Height()));
	*/
	
	CDC memDC;
	CBitmap memBitmap;
	CRect rect;
	GetClientRect(&rect);
	rect.left -= 200;
	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	// Tô màu nền cho CDC tạm thời
	memDC.FillSolidRect(rect, RGB(255, 255, 255));
	// Vẽ các đối tượng Ball lên CDC tạm thời
	for (const auto& ball : m_balls) {
		ball.Draw(&memDC);
	}

	// Vẽ lại các control lên CDC tạm thời
	//m_edt_balls.SendMessage(WM_PRINTCLIENT, (WPARAM)memDC.GetSafeHdc(), PRF_CLIENT);
	//m_list_balls.SendMessage(WM_PRINTCLIENT, (WPARAM)memDC.GetSafeHdc(), PRF_CLIENT);
	//m_btn_create.SendMessage(WM_PRINTCLIENT, (WPARAM)memDC.GetSafeHdc(), PRF_CLIENT);
	//m_btn_delete.SendMessage(WM_PRINTCLIENT, (WPARAM)memDC.GetSafeHdc(), PRF_CLIENT);


	// Sao chép CDC tạm thời lên CDC chính của dialog
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// Giải phóng các đối tượng đã sử dụng
	memDC.SelectObject(pOldBitmap);
	memBitmap.DeleteObject();
	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CfinalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int random1(int max, int min) {
	srand(time(NULL));
	return rand() % (max - min + 1);
}

void CfinalDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*
	// TODO: Add your message handler code here and/or call default
	int random = rand() % (8 - 1 + 1);
	switch (random)
	{
	case 1:
		m_balls.push_back(Ball(point.x, point.y, 20, RGB(255, 0, 0), 1, 1));
		break;
	case 2:
		m_balls.push_back(Ball(point.x, point.y, 20, RGB(0, 255, 0), 1, -1));
		break;
	case 3:
		m_balls.push_back(Ball(point.x, point.y, 20, RGB(0, 0, 255), -1, -1));
		break;
	case 4:
		m_balls.push_back(Ball(point.x, point.y, 25, RGB(255, 0, 0), -1, 1));
		break;
	case 5:
		m_balls.push_back(Ball(point.x, point.y, 25, RGB(0, 255, 0), 1, 0));
		break;
	case 6:
		m_balls.push_back(Ball(point.x, point.y, 25, RGB(0, 0, 255), 0, 1));
		break;
	case 7:
		m_balls.push_back(Ball(point.x, point.y, 25, RGB(255, 0, 0), -1, 0));
		break;
	case 8:
		m_balls.push_back(Ball(point.x, point.y, 25, RGB(0, 255, 0), 0, -1));
		break;
	}
	// Vẽ lại dialog để hiển thị bóng mới
	*/
	//Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
	
}

int Collision(int x, int y, int r, int vx, int vy, int width, int height){ 
	if ((x + r) >= width && vx > 0) {
		return 1;
	}
	else if ((x - r) <= 200 && vx < 0) {
		return 1;
	}
	if ((y + r) >= height && vy > 0) {
		return 2;
	}
	else if (y - r <= 0 && vy < 0) {
		return 2;
	}
}
double CaculateAngle(double radian) {
	return round((radian * 180) / PI);
}
void CfinalDlg::OnTimer(UINT_PTR nIDEvent)
{
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();
	fWidth = width;
	fHeight = height;
	// TODO: Add your message handler code here and/or call default
	m_list_balls.ResetContent();
	int a1 = 0;
	int a2 = 0;
	for (int i = 0; i < m_balls.size(); i++) {
		//Va chạm với nhau:
		/*
		for (int j = 0; j < m_balls.size(); j++) {
			if (i != j) {
				float dx = m_balls.at(j).x - m_balls.at(i).x;
				float dy = m_balls.at(j).y - m_balls.at(i).y;
				float d = sqrt(dx * dx + dy * dy);

				if (d <= m_balls.at(i).r + m_balls.at(j).r) {
					float dx = (m_balls.at(j).x + m_balls.at(j).vx) - (m_balls.at(i).x + m_balls.at(i).vx);
					float dy = (m_balls.at(j).y + m_balls.at(j).vy) - (m_balls.at(i).y + m_balls.at(i).vy);
					float d2 = sqrt((dx * dx + dy * dy));

					double angle1 = abs(atan2(m_balls.at(i).vy, m_balls.at(i).vx));
					a1 = angle1;
					double angle2 = abs(atan2(m_balls.at(j).vy, m_balls.at(j).vx));
					a2 = angle2;
					double angle = CaculateAngle(angle1) + CaculateAngle(angle2);
					if (angle == 180 && ((m_balls.at(i).CheckAngle() == m_balls.at(j).CheckAngle() + 2)) || (m_balls.at(j).CheckAngle() == m_balls.at(i).CheckAngle() + 2)) {
						m_balls.at(i).vy = -1 * m_balls.at(i).vy;
						m_balls.at(j).vy = -1 * m_balls.at(j).vy;
						
						m_balls.at(i).vx = -1 * m_balls.at(i).vx;
						m_balls.at(j).vx = -1 * m_balls.at(j).vx;

						m_balls.at(i).color = RGB(86, 145, 153); // xanh nước
					}
					else if (angle == 90 && ((m_balls.at(i).vx == 0 || m_balls.at(i).vy == 0) && (m_balls.at(j).vx == 0 || m_balls.at(j).vy == 0))) {
						m_balls.at(i).vy = -1 * m_balls.at(i).vy;
						m_balls.at(j).vy = -1 * m_balls.at(j).vy;
						m_balls.at(i).vx = -1 * m_balls.at(i).vx;
						m_balls.at(j).vx = -1 * m_balls.at(j).vx;
						m_balls.at(i).color = RGB(143, 153, 86); //Vàng
					}
					else if (m_balls.at(i).CheckAngle() == m_balls.at(j).CheckAngle()) {
						m_balls.at(j).vx = -1 * m_balls.at(j).vx;
						m_balls.at(j).vy = -1 * m_balls.at(j).vy;
						m_balls.at(i).color = RGB(148, 35, 148); //tím
					}
					else {
						int vx1 = m_balls.at(i).vx;
						int vx2 = m_balls.at(j).vx;
						int vy1 = m_balls.at(i).vy;
						int vy2 = m_balls.at(j).vy;
						m_balls.at(i).vx = vx2;
						m_balls.at(i).vy = vy2;
						m_balls.at(j).vx = vx1;
						m_balls.at(j).vy = vy1;
						m_balls.at(i).color = RGB(148, 112, 35); //Cam
					}
				}
			}
			
		}
		*/
		//Va chạm cạnh
		if (Collision(m_balls.at(i).x, m_balls.at(i).y, m_balls.at(i).r, m_balls.at(i).vx, m_balls.at(i).vy, width, height) == 1) {
			m_balls.at(i).vx = -1 * m_balls.at(i).vx;
		}
		else if (Collision(m_balls.at(i).x, m_balls.at(i).y, m_balls.at(i).r, m_balls.at(i).vx, m_balls.at(i).vy, width, height) == 2) {
			m_balls.at(i).vy = -1 * m_balls.at(i).vy;
		}
		m_balls.at(i).move();
		CString xPos;
		xPos.Format(_T("%d"), m_balls.at(i).x);
		CString yPos;
		yPos.Format(_T("%d"), m_balls.at(i).y);
		CString index;
		index.Format(_T("%d"), i);
		CString aaaa;
		aaaa.Format(_T("%d"), a1);
		CString aaaa2;
		aaaa2.Format(_T("%d"), a2);
		CString bPos = _T("Ball ") + index + "(" + xPos + " - " + yPos + ") " + aaaa + " - " + aaaa2;
		m_list_balls.AddString(bPos);
	}
	//Invalidate();
	InvalidateRect(CRect(200, 0, fWidth, fHeight));
	UpdateWindow();
	CDialogEx::OnTimer(nIDEvent);
}

/*
void CfinalDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
*/

void CfinalDlg::OnBnClickedBtnCreate()
{
	
	CString str;
	m_edt_balls.GetWindowText(str);

	int numBalls = _tstoi(str);
	if (numBalls > 0 && numBalls <= 200) {
		int temp = 0;
		std::vector<int> xPos;
		for (int i = 0; i < numBalls; i++) {
			xPos.push_back(rand() % ((fWidth-50) - 250 + 1) + 250);
		}
		std::vector<int> yPos;
		for (int i = 0; i < numBalls; i++) {
			yPos.push_back(rand() % ((fHeight-50) - 100 + 1) + 100);
		}
		for (int i = 0; i < numBalls; i++) {
			temp++;
			int random = temp;
			int x = xPos.at(i);
			int y = yPos.at(i);
			switch (random)
			{
			case 1:
				m_balls.push_back(Ball(x, y, 20, RGB(255, 0, 0), 1, 1));
				break;
			case 2:
				m_balls.push_back(Ball(x, y, 20, RGB(0, 255, 0), 1, -1));
				break;
			case 3:
				m_balls.push_back(Ball(x, y, 20, RGB(0, 0, 255), -1, -1));
				break;
			case 4:
				m_balls.push_back(Ball(x, y, 25, RGB(255, 0, 0), -1, 1));
				break;
			case 5:
				m_balls.push_back(Ball(x, y, 25, RGB(0, 255, 0), 1, 0));
				break;
			case 6:
				m_balls.push_back(Ball(x, y, 25, RGB(0, 0, 255), 0, 1));
				break;
			case 7:
				m_balls.push_back(Ball(x, y, 25, RGB(255, 0, 0), -1, 0));
				break;
			case 8:
				m_balls.push_back(Ball(x, y, 25, RGB(0, 255, 0), 0, -1));
				break;
			}
			if (temp == 8) {
				temp = 0;
			}
		}
		
	}
	else {
		MessageBox(_T("Vui lòng nhập số từ 1-200"), _T("Thông báo"), MB_OK | MB_ICONWARNING);
	}
	
	// TODO: Add your control notification handler code here
}


BOOL CfinalDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CfinalDlg::OnBnClickedBtnDelete()
{
	m_balls.clear();
	m_edt_balls.SetWindowTextW(_T(""));
	// TODO: Add your control notification handler code here
}


void CfinalDlg::OnEnUpdateEditBalls()
{
	m_balls.clear();
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}
