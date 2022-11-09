
// DemoAppDlg.cpp: 구현 파일
//

#include <vector>
#include <sstream>

#include "framework.h"
#include "DemoApp.h"
#include "DemoAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx {
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CDemoAppDlg::CDemoAppDlg(CWnd* pParent)
	: CDialogEx(IDD_DEMOAPP_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CDemoAppDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COM_PORT, m_editCOMPORT);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_FILE, m_editDisplayFile);
	DDX_Control(pDX, IDC_EDIT_BRAILLE_DISPLAY_DATA, m_editBrailleDisplayData);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_DATA_PART_DATA, m_editDisplayDataPartData);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_DATA_PART_LENGTH, m_editDisplayDataPartLength);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_DATA_PART_START_IDX, m_editDisplayDataPartStartIdx);
}


BEGIN_MESSAGE_MAP(CDemoAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CDemoAppDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_DEINIT, &CDemoAppDlg::OnBnClickedButtonDeinit)
	ON_BN_CLICKED(IDC_BUTTON_UP_DATA, &CDemoAppDlg::OnBnClickedButtonUpData)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_DATA, &CDemoAppDlg::OnBnClickedButtonDownData)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY_FILE_OPEN, &CDemoAppDlg::OnBnClickedButtonDisplayFileOpen)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY, &CDemoAppDlg::OnBnClickedButtonDisplay)
	ON_BN_CLICKED(IDC_BUTTON_STRING_DISPLAY, &CDemoAppDlg::OnBnClickedButtonStringDisplay)
	ON_BN_CLICKED(IDC_BUTTON_ASCII_DISPLAY, &CDemoAppDlg::OnBnClickedButtonAsciiDisplay)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDemoAppDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CDemoAppDlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CDemoAppDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY_DATA_PART_DISPLAY, &CDemoAppDlg::OnBnClickedButtonDisplayDataPartDisplay)
	ON_BN_CLICKED(IDC_BUTTON_UP_REFRESH, &CDemoAppDlg::OnBnClickedButtonUpRefresh)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_REFRESH, &CDemoAppDlg::OnBnClickedButtonDownRefresh)
END_MESSAGE_MAP()


BOOL CDemoAppDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	LoadDotPadDLL();

	dot_pad_register_key_callback(DisplayDialogBoxByKeyNoti);

	dot_pad_register_display_callback(DisplayDialogBoxByDisplayComplete);

	return TRUE;
}


BOOL CDemoAppDlg::PreTranslateMessage(MSG* pMsg) {
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN) {
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDemoAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CDemoAppDlg::OnPaint() {
	if (IsIconic()) {
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}


HCURSOR CDemoAppDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}


void CDemoAppDlg::OnClose() {
	if (dot_pad_init != NULL) {
		DOT_PAD_SDK_ERROR error = dot_pad_deinit();

		if ((error != DOT_ERROR_NONE) && (error != DOT_ERROR_DOT_PAD_COULD_NOT_INIT)) {
			CString str;
			str.Format(_T("Deinitialization is fail\nError with (0x%x)"), error);
			AfxMessageBox(str);

			return;
		}
	}

	FreeDotPadDLL();

	CDialog::OnClose();
}


void CDemoAppDlg::LoadDotPadDLL() {
	m_hDotPadDLL = LoadLibrary(_T("DotPadSDK.dll"));

	if (m_hDotPadDLL == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail\nError with (0x%x)"), GetLastError());
		AfxMessageBox(str);

		return;
	}

	dot_pad_init = (DOT_PAD_INIT_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_INIT");
	dot_pad_deinit = (DOT_PAD_DEINIT_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_DEINIT");
	dot_pad_display = (DOT_PAD_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_DISPLAY");
	dot_pad_display_data = (DOT_PAD_DISPLAY_DATA_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_DISPLAY_DATA");
	dot_pad_display_data_part = (DOT_PAD_DISPLAY_DATA_PART_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_DISPLAY_DATA_PART");
	dot_pad_reset_display = (DOT_PAD_RESET_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_RESET_DISPLAY");
	dot_pad_braille_display = (DOT_PAD_BRAILLE_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_BRAILLE_DISPLAY");
	dot_pad_braille_ascii_display = (DOT_PAD_BRAILLE_ASCII_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_BRAILLE_ASCII_DISPLAY");
	dot_pad_reset_braille_display = (DOT_PAD_RESET_BRAILLE_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_RESET_BRAILLE_DISPLAY");
	dot_pad_send_key = (DOT_PAD_SEND_KEY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_SEND_KEY");
	dot_pad_register_key_callback = (DOT_PAD_REGISTER_KEY_CALLBACK_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_REGISTER_KEY_CALLBACK");
	dot_pad_register_display_callback = (DOT_PAD_REGISTER_DISPLAY_CALLBACK_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_REGISTER_DISPLAY_CALLBACK");

	if (dot_pad_init == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_INIT_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_deinit == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_DEINIT_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_display_data == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_DISPLAY_DATA_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_display_data_part == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_DISPLAY_DATA_PART_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_reset_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_RESET_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_braille_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_BRAILLE_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_braille_ascii_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_BRAILLE_ASCII_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_reset_braille_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_RESET_BRAILLE_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_send_key == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_SEND_KEY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_register_key_callback == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_REGISTER_KEY_CALLBACK_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_register_display_callback == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_REGISTER_DISPLAY_CALLBACK_FUNC in DotPadSDK.dll!"));
	}
}


void CDemoAppDlg::FreeDotPadDLL() {
	if (m_hDotPadDLL) {
		FreeLibrary(m_hDotPadDLL);
		m_hDotPadDLL = NULL;
	}

	dot_pad_init = NULL;
	dot_pad_deinit = NULL;
	dot_pad_display = NULL;
	dot_pad_display_data = NULL;
	dot_pad_display_data_part = NULL;
	dot_pad_reset_display = NULL;
	dot_pad_braille_display = NULL;
	dot_pad_braille_ascii_display = NULL;
	dot_pad_reset_braille_display = NULL;
	dot_pad_send_key = NULL;
	dot_pad_register_key_callback = NULL;
	dot_pad_register_display_callback = NULL;
}


void CDemoAppDlg::OnBnClickedButtonInit() {
	if (dot_pad_init == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	CString strCOMport;
	((CEdit*)GetDlgItem(IDC_EDIT_COM_PORT))->GetWindowText(strCOMport);

	DOT_PAD_SDK_ERROR error = dot_pad_init(_ttoi(strCOMport));

	CString str;
	if (error == DOT_ERROR_NONE) {
		str.Format(_T("Initialization is success"));
		AfxMessageBox(str);

		return;
	}
	else {
		str.Format(_T("Initialization is fail\nError with (0x%x)"), error);
		AfxMessageBox(str);

		return;
	}
}


void CDemoAppDlg::OnBnClickedButtonDeinit() {
	if (dot_pad_deinit == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	DOT_PAD_SDK_ERROR error = dot_pad_deinit();

	if ((error != DOT_ERROR_NONE) && (error != DOT_ERROR_DOT_PAD_COULD_NOT_INIT))
	{
		CString str;
		str.Format(_T("Deinitialization is fail\nError with (0x%x)"), error);
		AfxMessageBox(str);

		return;
	}
	else {
		CString str;
		str.Format(_T("Deinitialization is success"));
		AfxMessageBox(str);

		return;
	}
}


void CDemoAppDlg::OnBnClickedButtonUpData() {
	if (dot_pad_display_data == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	uint8_t data[300] = { 0 };
	memset(data, 0xff, 300);
	DOT_PAD_SDK_ERROR error = dot_pad_display_data(data, 300, false);

	if (error == DOT_ERROR_DISPLAY_DATA_UNCHAGNED) {
		AfxMessageBox(_T("Display data is same!!"), MB_OK);
	}
	else if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonDownData() {
	if (dot_pad_display == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	uint8_t data[300] = { 0 };
	DOT_PAD_SDK_ERROR error = dot_pad_display_data(data, 300, false);

	if (error == DOT_ERROR_DISPLAY_DATA_UNCHAGNED) {
		AfxMessageBox(_T("Display data is same!!"), MB_OK);
	}
	else if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonDisplayFileOpen() {
	TCHAR szFilter[] = _T("DTM(*.dtm)|*.dtm|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal()) {
		strPathName = dlg.GetPathName();
		strFileName = dlg.GetFileName();

		displayFilePathName = std::string(CT2CA(strPathName));

		m_editDisplayFile.SetWindowTextW(strFileName);
	}
}


void CDemoAppDlg::OnBnClickedButtonDisplay() {
	if (displayFilePathName.empty()) {
		AfxMessageBox(_T("Check display file!!"), MB_OK);
		return;
	}

	DOT_PAD_SDK_ERROR error = dot_pad_display((char*)displayFilePathName.c_str());

	if (error == DOT_ERROR_DISPLAY_DATA_UNCHAGNED) {
		AfxMessageBox(_T("Display data is same!!"), MB_OK);
	}
	else if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}


static void Convert1ByteTo2Byte(wchar_t* dest, char* src, int len)
{
	dest[0] = ((wchar_t)(*(src)) & 0xFF) | (wchar_t)(*(src + 1) << 8);
	for (int i = 1; i < len; i++) {
		dest[i] = ((wchar_t)(*(src + i * 2)) & 0xFF) | (wchar_t)(*(src + i * 2 + 1) << 8);
	}
}


void CDemoAppDlg::OnBnClickedButtonStringDisplay() {
	CString in_edCtrl = _T("");
	m_editBrailleDisplayData.GetWindowText(in_edCtrl);

	char* in_edCtrlChar = LPSTR(LPCTSTR(in_edCtrl));

	wchar_t* in_edCtrlUTF16 = new wchar_t[in_edCtrl.GetLength() + 1]{ 0 };
	Convert1ByteTo2Byte(in_edCtrlUTF16, in_edCtrlChar, in_edCtrl.GetLength());

	if (dot_pad_braille_display == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	const int defaultLanguageCode = 0x0A;

	DOT_PAD_SDK_ERROR error = dot_pad_braille_display(in_edCtrlUTF16, defaultLanguageCode);

	delete[] in_edCtrlUTF16;

	if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Braille display failed!!"), MB_OK);
	}
}


static void Convert2ByteCharTo1BytesChar(char* dst, const char* src, const int len) {
	int dstIdx = 0;
	for (int i = 0; i < len * 2; i += 2) {
		dst[dstIdx++] = (char)src[i] & 0xFF;
	}
}

void CDemoAppDlg::OnBnClickedButtonAsciiDisplay() {
	CString in_edCtrl = _T("");
	m_editBrailleDisplayData.GetWindowText(in_edCtrl);

	char* in_edCtrlChar2Byte = LPSTR(LPCTSTR(in_edCtrl));

	if (dot_pad_braille_ascii_display == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	char* in_edCtrlChar = new char[in_edCtrl.GetLength() + 1]{ 0 };

	Convert2ByteCharTo1BytesChar(in_edCtrlChar, in_edCtrlChar2Byte, (const int)in_edCtrl.GetLength());

	DOT_PAD_SDK_ERROR error = dot_pad_braille_ascii_display(in_edCtrlChar);

	if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Braille ASCII display failed!!"), MB_OK);
	}

	delete[] in_edCtrlChar;
}


void CDemoAppDlg::OnBnClickedButtonReset() {
	if (dot_pad_reset_braille_display == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	DOT_PAD_SDK_ERROR error = dot_pad_reset_braille_display();

	if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Braille ASCII display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonPrev() {
	if (dot_pad_send_key == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	DOT_PAD_SDK_ERROR error = dot_pad_send_key(1);

	if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Braille ASCII display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonNext() {
	if (dot_pad_send_key == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	DOT_PAD_SDK_ERROR error = dot_pad_send_key(2);

	if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Braille ASCII display failed!!"), MB_OK);
	}
}


void CALLBACK DisplayDialogBoxByKeyNoti(const int key) {
	CString msg;
	msg.Format(_T("Key: %X"), key);
	AfxMessageBox(msg);
}


static std::vector<std::string> Split(std::string input, char delimiter) {
	std::vector<std::string> splited;
	std::stringstream ss(input);
	std::string temp;

	while (getline(ss, temp, delimiter)) {
		splited.push_back(temp);
	}

	return splited;
}


void CDemoAppDlg::OnBnClickedButtonDisplayDataPartDisplay() {
	if (dot_pad_display_data_part == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	CString in_edCtrlData = _T("");
	m_editDisplayDataPartData.GetWindowText(in_edCtrlData);

	std::string data_str = std::string(CT2CA(in_edCtrlData));

	std::vector<std::string> data_vec_str = Split(data_str, ' ');

	std::vector<int> data_vec_int;

	int temp = 0;
	for (std::string data : data_vec_str) {
		temp = 0;
		std::istringstream iss(data);
		iss >> std::hex >> temp;

		if (!(temp >= 0x00 && temp <= 0xFF)) {
			CString str;
			str.Format(_T("Invalid Value"));
			AfxMessageBox(str);
			return;
		}
		data_vec_int.push_back(temp);
	}

	uint8_t* displayData = new uint8_t[data_vec_int.size() + 1]{ 0 };

	for (int i = 0; i < data_vec_int.size(); i++) {
		displayData[i] = data_vec_int[i];
	}

	CString in_edCtrlLength = _T(""), in_edCtrlStartIdx = _T("");
	m_editDisplayDataPartLength.GetWindowText(in_edCtrlLength);
	m_editDisplayDataPartStartIdx.GetWindowText(in_edCtrlStartIdx);
	DOT_PAD_SDK_ERROR error = dot_pad_display_data_part(displayData, _ttoi(in_edCtrlLength), _ttoi(in_edCtrlStartIdx));

	if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}

	delete[] displayData;
}


void CALLBACK DisplayDialogBoxByDisplayComplete(void) {
	CString msg;
	msg.Format(_T("Complete!!"));
	AfxMessageBox(msg);
}


void CDemoAppDlg::OnBnClickedButtonUpRefresh() {
	if (dot_pad_display_data == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	uint8_t data[300] = { 0 };
	memset(data, 0xff, 300);
	DOT_PAD_SDK_ERROR error = dot_pad_display_data(data, 300, true);

	if (error == DOT_ERROR_DISPLAY_DATA_UNCHAGNED) {
		AfxMessageBox(_T("Display data is same!!"), MB_OK);
	}
	else if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonDownRefresh() {
	if (dot_pad_display == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);

		return;
	}

	uint8_t data[300] = { 0 };
	DOT_PAD_SDK_ERROR error = dot_pad_display_data(data, 300, true);

	if (error == DOT_ERROR_DISPLAY_DATA_UNCHAGNED) {
		AfxMessageBox(_T("Display data is same!!"), MB_OK);
	}
	else if (error != DOT_ERROR_NONE) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}
