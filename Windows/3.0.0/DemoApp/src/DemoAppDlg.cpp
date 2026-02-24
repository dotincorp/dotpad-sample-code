
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

#define WM_USER_BLE_FOUND WM_USER + 999
#define DOT_PAD_KEY WM_USER + 888
#define WM_USER_UPDATE_DEVICE_LIST WM_USER + 887

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
	g_hWnd = &this->m_hWnd;
}

CDemoAppDlg::~CDemoAppDlg()
{
	if (dot_pad_ble_scan_stop != NULL) {
		dot_pad_ble_scan_stop();
	}
}


void CDemoAppDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COM_PORT, m_editCOMPORT);
	DDX_Control(pDX, IDC_EDIT_DISPLAY_FILE, m_editDisplayFile);
	DDX_Control(pDX, IDC_EDIT_BRAILLE_DISPLAY_DATA, m_editBrailleDisplayData);
	DDX_Control(pDX, IDC_LIST_CONNECTED_DEVICES, m_listConnectedDevices);
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
	ON_BN_CLICKED(IDC_BUTTON_UP_REFRESH, &CDemoAppDlg::OnBnClickedButtonUpRefresh)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_REFRESH, &CDemoAppDlg::OnBnClickedButtonDownRefresh)
	ON_BN_CLICKED(IDC_BUTTON_DISPLAY_INFO, &CDemoAppDlg::OnBnClickedButtonDisplayInfo)
	ON_BN_CLICKED(IDC_BUTTON_FIRMWARE_VERSION, &CDemoAppDlg::OnBnClickedButtonFirmwareVersion)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_NAME, &CDemoAppDlg::OnBnClickedButtonDeviceName)
	ON_CBN_SELCHANGE(IDC_MODE, &CDemoAppDlg::OnCbnSelchangeComboCommType)
	ON_BN_CLICKED(IDC_SCAN_START, &CDemoAppDlg::OnBnClickedScanStart)
	ON_MESSAGE(WM_USER_BLE_FOUND, &CDemoAppDlg::OnBleDeviceFound)
	ON_MESSAGE(DOT_PAD_KEY, &CDemoAppDlg::OnDotPadSendKey)
	ON_MESSAGE(WM_USER_UPDATE_DEVICE_LIST, &CDemoAppDlg::OnUpdateDeviceList)
	ON_BN_CLICKED(IDC_SCAN_STOP, &CDemoAppDlg::OnBnClickedScanStop)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_DEVICES, &CDemoAppDlg::OnBnClickedButtonRefreshDevices)
END_MESSAGE_MAP()

LRESULT CDemoAppDlg::OnBleDeviceFound(WPARAM wParam, LPARAM lParam)
{
	auto bleDevice = reinterpret_cast<const wchar_t*>(wParam);
	if (bleDevice) {
		AddBleDeviceToList(bleDevice);
	}
	return 0;
}

LRESULT CDemoAppDlg::OnDotPadSendKey(WPARAM wParam, LPARAM lParam) {
	// 키 입력은 새로운 API에서 콜백으로 처리되므로 여기서는 처리하지 않음
	return 0;
}

LRESULT CDemoAppDlg::OnUpdateDeviceList(WPARAM wParam, LPARAM lParam)
{
	UpdateConnectedDeviceList();
	return 0;
}

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

	if (dot_pad_register_key_callback != NULL) {
		dot_pad_register_key_callback(DisplayDialogBoxByKeyNoti);
	}

	if (dot_pad_register_message_callback != NULL) {
		dot_pad_register_message_callback(DisplayDialogBoxByMessageNoti);
	}

	// 연결된 기기 목록 초기화
	UpdateConnectedDeviceList();

	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_MODE);

	if (pComboBox != nullptr) {
		pComboBox->AddString(_T("Serial"));
		pComboBox->AddString(_T("BluetoothLE"));

		pComboBox->SetCurSel(0);
	}
	else {
		AfxMessageBox(_T("콤보박스를 찾을 수 없습니다."));
	}

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
	if (dot_pad_disconnect != NULL) {
		// 모든 기기 연결 해제 (nullptr 전달)
		dot_pad_disconnect(nullptr);
	}

	FreeDotPadDLL();

	CDialog::OnClose();
}


void CDemoAppDlg::LoadDotPadDLL() {
	m_hDotPadDLL = LoadLibrary(_T("DotPadSDK-3.0.0.dll"));

	if (m_hDotPadDLL == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail\nError with (0x%x)"), GetLastError());
		AfxMessageBox(str);

		return;
	}

	// 연결 관리
	dot_pad_connect_ble = (DOT_PAD_CONNECT_BLE_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_CONNECT_BLE");
	dot_pad_connect_serial = (DOT_PAD_CONNECT_SERIAL_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_CONNECT_SERIAL");
	dot_pad_disconnect = (DOT_PAD_DISCONNECT_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_DISCONNECT");
	dot_pad_get_connected_device_count = (DOT_PAD_GET_CONNECTED_DEVICE_COUNT_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_GET_CONNECTED_DEVICE_COUNT");
	dot_pad_get_connected_device_handle = (DOT_PAD_GET_CONNECTED_DEVICE_HANDLE_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_GET_CONNECTED_DEVICE_HANDLE");
	dot_pad_get_device_name = (DOT_PAD_GET_DEVICE_NAME_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_GET_DEVICE_NAME");
	dot_pad_get_fw_version = (DOT_PAD_GET_FW_VERSION_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_GET_FW_VERSION");

	// 스캔
	dot_pad_ble_scan = (DOT_PAD_BLE_SCAN_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_BLE_SCAN");
	dot_pad_ble_scan_stop = (DOT_PAD_BLE_SCAN_STOP_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_BLE_SCAN_STOP");
	dot_pad_usb_scan = (DOT_PAD_USB_SCAN_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_USB_SCAN");

	// Display (Graphic)
	dot_pad_display_file = (DOT_PAD_DISPLAY_FILE_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_DISPLAY_FILE");
	dot_pad_display_data = (DOT_PAD_DISPLAY_DATA_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_DISPLAY_DATA");
	dot_pad_reset_display = (DOT_PAD_RESET_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_RESET_DISPLAY");

	// Display (Braille/Text)
	dot_pad_braille_display = (DOT_PAD_BRAILLE_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_BRAILLE_DISPLAY");
	dot_pad_braille_display_data = (DOT_PAD_BRAILLE_DISPLAY_DATA_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_BRAILLE_DISPLAY_DATA");
	dot_pad_braille_ascii_display = (DOT_PAD_BRAILLE_ASCII_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_BRAILLE_ASCII_DISPLAY");
	dot_pad_reset_braille_display = (DOT_PAD_RESET_BRAILLE_DISPLAY_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_RESET_BRAILLE_DISPLAY");

	// 정보 조회
	dot_pad_get_display_info = (DOT_PAD_GET_DISPLAY_INFO_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_GET_DISPLAY_INFO");

	// 콜백 등록
	dot_pad_register_key_callback = (DOT_PAD_REGISTER_KEY_CALLBACK_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_REGISTER_KEY_CALLBACK");
	dot_pad_register_message_callback = (DOT_PAD_REGISTER_MESSAGE_CALLBACK_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_REGISTER_MESSAGE_CALLBACK");
	dot_pad_register_display_callback = (DOT_PAD_REGISTER_DISPLAY_CALLBACK_FUNC)GetProcAddress(m_hDotPadDLL, "DOT_PAD_REGISTER_DISPLAY_CALLBACK");


	// 함수 포인터 NULL 체크는 선택적으로 수행 (필요시 주석 해제)

	/*
	if (dot_pad_init == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_INIT_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_deinit == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_DEINIT_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_reset_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_RESET_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	
	if (dot_pad_braille_ascii_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_BRAILLE_ASCII_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	if (dot_pad_reset_braille_display == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_RESET_BRAILLE_DISPLAY_FUNC in DotPadSDK.dll!"));
	}
	
	if (dot_pad_get_fw_version == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_GET_FW_VERSION in DotPadSDK.dll!"));
	}
	if (dot_pad_get_device_name == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_GET_DEVICE_NAME in DotPadSDK.dll!"));
	}
	if (dot_pad_get_display_info == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_GET_DISPLAY_INFO_FUNC in DotPadSDK.dll!"));
	}
	
	if (dot_pad_register_display_callback == NULL) {
		AfxMessageBox(_T("Can not find funtion DOT_PAD_REGISTER_DISPLAY_CALLBACK_FUNC in DotPadSDK.dll!"));
	}*/
}


void CDemoAppDlg::FreeDotPadDLL() {
	if (m_hDotPadDLL) {
		FreeLibrary(m_hDotPadDLL);
		m_hDotPadDLL = NULL;
	}

	// 모든 함수 포인터 초기화
	dot_pad_connect_ble = NULL;
	dot_pad_connect_serial = NULL;
	dot_pad_disconnect = NULL;
	dot_pad_get_connected_device_count = NULL;
	dot_pad_get_connected_device_handle = NULL;
	dot_pad_get_device_name = NULL;
	dot_pad_get_fw_version = NULL;
	dot_pad_ble_scan = NULL;
	dot_pad_ble_scan_stop = NULL;
	dot_pad_usb_scan = NULL;
	dot_pad_display_file = NULL;
	dot_pad_display_data = NULL;
	dot_pad_reset_display = NULL;
	dot_pad_braille_display = NULL;
	dot_pad_braille_display_data = NULL;
	dot_pad_braille_ascii_display = NULL;
	dot_pad_reset_braille_display = NULL;
	dot_pad_get_display_info = NULL;
	dot_pad_register_key_callback = NULL;
	dot_pad_register_message_callback = NULL;
	dot_pad_register_display_callback = NULL;
}


void CDemoAppDlg::OnBnClickedButtonInit() {
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_MODE);
	if (pComboBox == nullptr) return;

	int selectedIndex = pComboBox->GetCurSel();
	CString selectedText;
	pComboBox->GetLBText(selectedIndex, selectedText);

	void* deviceHandle = nullptr;
	CString connectionInfo;
	
	if (selectedText == _T("Serial")) {
		if (dot_pad_connect_serial == NULL) {
			CString str;
			str.Format(_T("Loading DLL is fail"));
			AfxMessageBox(str);
			return;
		}

		CString strCOMport;
		((CEdit*)GetDlgItem(IDC_EDIT_COM_PORT))->GetWindowText(strCOMport);
		
		// COM 포트 형식 변환 (예: "3" -> "COM3")
		CString portName;
		portName.Format(_T("COM%s"), strCOMport);

		deviceHandle = dot_pad_connect_serial(portName);
		connectionInfo = portName;  // 연결 정보 저장
	}
	else if (selectedText == _T("BluetoothLE")) {
		if (dot_pad_connect_ble == NULL) {
			CString str;
			str.Format(_T("Loading DLL is fail"));
			AfxMessageBox(str);
			return;
		}

		CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_BLE);
		if (pListBox == nullptr) return;

		int selectedIndex = pListBox->GetCurSel();
		if (selectedIndex == LB_ERR) {
			AfxMessageBox(_T("BLE 기기를 선택해주세요."));
			return;
		}

		DWORD_PTR deviceIndex = pListBox->GetItemData(selectedIndex);

		if (deviceIndex >= bleDevices.size()) return;

		CString selectedDevice = bleDevices[deviceIndex];
		deviceHandle = dot_pad_connect_ble(selectedDevice);
		connectionInfo = selectedDevice;  // 연결 정보 저장
	}

	CString str;
	if (deviceHandle != nullptr) {
		// 연결 정보를 맵에 저장
		m_deviceConnectionInfo[deviceHandle] = connectionInfo;
		
		str.Format(_T("연결 성공"));
		AfxMessageBox(str);
		OnBnClickedScanStop();
	}
	else {
		str.Format(_T("연결 실패"));
		AfxMessageBox(str);
	}
}

void CDemoAppDlg::OnBnClickedButtonDeinit() {
	if (dot_pad_disconnect == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	// 선택한 기기만 해제하거나, 선택이 없으면 모든 기기 해제
	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_disconnect(deviceHandle);

	if (success) {
		// 연결 해제된 기기의 정보를 맵에서 제거
		if (deviceHandle != nullptr) {
			m_deviceConnectionInfo.erase(deviceHandle);
			m_deviceBrailleData.erase(deviceHandle);
			m_deviceBrailleCurrentIndex.erase(deviceHandle);
		}
		else {
			// 모든 기기 해제 시 맵 초기화
			m_deviceConnectionInfo.clear();
			m_deviceBrailleData.clear();
			m_deviceBrailleCurrentIndex.clear();
		}
		
		CString str;
		str.Format(_T("연결 해제 성공"));
		AfxMessageBox(str);
		//UpdateConnectedDeviceList();
	}
	else {
		CString str;
		str.Format(_T("연결 해제 실패"));
		AfxMessageBox(str);
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
	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_display_data(data, 300, deviceHandle);

	if (!success) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonDownData() {
	if (dot_pad_display_data == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	uint8_t data[300] = { 0 };
	memset(data, 0x00, 300);
	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_display_data(data, 300, deviceHandle);

	if (!success) {
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

	if (dot_pad_display_file == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_display_file((char*)displayFilePathName.c_str(), deviceHandle);

	if (!success) {
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


void CALLBACK BrailleTranslatedDataCallback(void* deviceHandle, const uint8_t* translatedData, size_t dataSize) {
	if (g_hWnd == NULL || translatedData == NULL) return;
	CWnd* pWnd = CWnd::FromHandle(*g_hWnd);
	CDemoAppDlg* pDlg = dynamic_cast<CDemoAppDlg*>(pWnd);
	if (pDlg != nullptr) {
		pDlg->OnBrailleTranslatedData(deviceHandle, translatedData, dataSize);
	}
}

void CDemoAppDlg::OnBrailleTranslatedData(void* deviceHandle, const uint8_t* translatedData, size_t dataSize) {
	if (deviceHandle == nullptr || translatedData == NULL) return;

	m_deviceBrailleData[deviceHandle].assign(translatedData, translatedData + dataSize);
	m_deviceBrailleCurrentIndex[deviceHandle] = 0;
}

void CDemoAppDlg::OnBnClickedButtonStringDisplay() {
	CString in_edCtrl = _T("");
	m_editBrailleDisplayData.GetWindowText(in_edCtrl);

	char* in_edCtrlChar = LPSTR(LPCTSTR(in_edCtrl));

	wchar_t* in_edCtrlUTF16 = new wchar_t[in_edCtrl.GetLength() + 1] { 0 };
	Convert1ByteTo2Byte(in_edCtrlUTF16, in_edCtrlChar, in_edCtrl.GetLength());

	if (dot_pad_braille_display == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		delete[] in_edCtrlUTF16;
		return;
	}

	const int defaultLanguageCode = 0x0A;

	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_braille_display(in_edCtrlUTF16, defaultLanguageCode, 2, 2, deviceHandle, BrailleTranslatedDataCallback);

	delete[] in_edCtrlUTF16;

	if (!success) {
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

	char* in_edCtrlChar = new char[in_edCtrl.GetLength() + 1] { 0 };

	Convert2ByteCharTo1BytesChar(in_edCtrlChar, in_edCtrlChar2Byte, (const int)in_edCtrl.GetLength());

	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_braille_ascii_display(in_edCtrlChar, deviceHandle);

	if (!success) {
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

	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_reset_braille_display(deviceHandle);

	if (!success) {
		AfxMessageBox(_T("Braille display reset failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonPrev() {
	if (dot_pad_braille_display_data == NULL || dot_pad_get_display_info == NULL) {
		AfxMessageBox(_T("DLL 함수를 사용할 수 없습니다."), MB_OK);
		return;
	}
	void* deviceHandle = GetSelectedDeviceHandle();
	if (deviceHandle == nullptr) {
		AfxMessageBox(_T("이전/다음은 기기 하나를 선택한 상태에서만 동작합니다."), MB_OK);
		return;
	}
	auto it = m_deviceBrailleData.find(deviceHandle);
	if (it == m_deviceBrailleData.end() || it->second.empty()) {
		AfxMessageBox(_T("저장된 점자 데이터가 없습니다. 먼저 문자열 표시를 실행하세요."), MB_OK);
		return;
	}
	int width = 0, height = 0, braille = 0;
	if (!dot_pad_get_display_info(deviceHandle, &width, &height, &braille)) {
		AfxMessageBox(_T("디스플레이 정보 조회 실패."), MB_OK);
		return;
	}
	size_t step = (size_t)braille;
	if (step == 0) step = 1;
	std::vector<uint8_t>& data = it->second;
	size_t& idx = m_deviceBrailleCurrentIndex[deviceHandle];

	if (idx == 0)
		return;

	if (idx >= step)
		idx -= step;
	else
		idx = 0;
	size_t len = (idx + step <= data.size()) ? step : (data.size() - idx);
	if (len == 0) {
		AfxMessageBox(_T("이전 구간이 없습니다."), MB_OK);
		return;
	}
	
	bool success = dot_pad_braille_display_data(&data[idx], len, deviceHandle);
	if (!success) {
		AfxMessageBox(_T("이전 점자 표시 실패."), MB_OK);
	}

}

void CDemoAppDlg::OnBnClickedButtonNext() {
	if (dot_pad_braille_display_data == NULL || dot_pad_get_display_info == NULL) {
		AfxMessageBox(_T("DLL 함수를 사용할 수 없습니다."), MB_OK);
		return;
	}
	void* deviceHandle = GetSelectedDeviceHandle();
	if (deviceHandle == nullptr) {
		AfxMessageBox(_T("이전/다음은 기기 하나를 선택한 상태에서만 동작합니다."), MB_OK);
		return;
	}
	auto it = m_deviceBrailleData.find(deviceHandle);
	if (it == m_deviceBrailleData.end() || it->second.empty()) {
		AfxMessageBox(_T("저장된 점자 데이터가 없습니다. 먼저 문자열 표시를 실행하세요."), MB_OK);
		return;
	}
	int width = 0, height = 0, braille = 0;
	if (!dot_pad_get_display_info(deviceHandle, &width, &height, &braille)) {
		AfxMessageBox(_T("디스플레이 정보 조회 실패."), MB_OK);
		return;
	}
	size_t step = (size_t)braille;
	if (step == 0) step = 1;
	std::vector<uint8_t>& data = it->second;
	size_t& idx = m_deviceBrailleCurrentIndex[deviceHandle];

	if (idx + step >= data.size()) {
		return;
	}

	if (idx + step < data.size())
		idx += step;
	else if (data.size() > step)
		idx = data.size() - step;
	else
		idx = 0;
	size_t len = (idx + step <= data.size()) ? step : (data.size() - idx);
	if (len == 0) {
		AfxMessageBox(_T("다음 구간이 없습니다."), MB_OK);
		return;
	}

	bool success = dot_pad_braille_display_data(&data[idx], len, deviceHandle);
	if (!success)
		AfxMessageBox(_T("다음 점자 표시 실패."), MB_OK);
}

void CALLBACK DisplayDialogBoxByKeyNoti(void* deviceHandle, DOT_KEY_CODE keyCode, const char* message) {
	CString msg;
	if (message != nullptr) {
		int keyValue = atoi(message);
		msg.Format(_T("Key: %02X"), keyValue);
		AfxMessageBox(msg);
	}
	SendMessage(*g_hWnd, DOT_PAD_KEY, keyCode, 0);
}

void CALLBACK DisplayDialogBoxByMessageNoti(void* deviceHandle, DOT_DATA_CODE dataCode, const char* message){
	if (dataCode == DOT_DATA_CODE::DOT_DATA_CODE_CONNECTED || dataCode == DOT_DATA_CODE_DISCONNECTED) {
		if (g_hWnd != NULL && *g_hWnd != NULL) {
			PostMessage(*g_hWnd, WM_USER_UPDATE_DEVICE_LIST, 0, 0);
		}
	}
	else if (dataCode == DOT_DATA_CODE::DOT_DATA_CODE_DEVICE_FW_VERSION
		|| dataCode == DOT_DATA_CODE::DOT_DATA_CODE_DEVICE_NAME
		) {
		if (message != nullptr) {
			CStringW wmsg(CA2W(message, CP_UTF8));
			AfxMessageBox(wmsg);
		}
	}
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
	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_display_data(data, 300, deviceHandle);

	if (!success) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonDownRefresh() {
	if (dot_pad_display_data == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	uint8_t data[300] = { 0 };
	memset(data, 0x00, 300);
	void* deviceHandle = GetSelectedDeviceHandle();
	bool success = dot_pad_display_data(data, 300, deviceHandle);

	if (!success) {
		AfxMessageBox(_T("Display failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonDisplayInfo() {
	if (dot_pad_get_display_info == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	void* deviceHandle = GetSelectedDeviceHandle();
	int width = 0, height = 0, braille = 0;
	bool success = dot_pad_get_display_info(deviceHandle, &width, &height, &braille);

	if (success) {
		CString msg;
		msg.Format(_T("Width: %d / Height: %d / Braille: %d"), width, height, braille);
		AfxMessageBox(msg);
	}
	else {
		AfxMessageBox(_T("Display info failed!!"), MB_OK);
	}
}


void CDemoAppDlg::OnBnClickedButtonFirmwareVersion() {
	if (dot_pad_get_fw_version == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	void* deviceHandle = GetSelectedDeviceHandle();
	if (deviceHandle == nullptr) {
		AfxMessageBox(_T("기기를 선택해주세요."), MB_OK);
		return;
	}

	bool success = dot_pad_get_fw_version(deviceHandle);

	if (!success) {
		AfxMessageBox(_T("Device name failed!!"), MB_OK);
	}
}

void CDemoAppDlg::OnBnClickedButtonDeviceName() {
	if (dot_pad_get_device_name == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	void* deviceHandle = GetSelectedDeviceHandle();
	if (deviceHandle == nullptr) {
		AfxMessageBox(_T("기기를 선택해주세요."), MB_OK);
		return;
	}

	bool success = dot_pad_get_device_name(deviceHandle);

	if (!success) {
		AfxMessageBox(_T("Device name failed!!"), MB_OK);
	}
}

void CDemoAppDlg::OnCbnSelchangeComboCommType()
{
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_MODE);
	if (pComboBox == nullptr) return;

	int selectedIndex = pComboBox->GetCurSel();
	CString selectedText;
	pComboBox->GetLBText(selectedIndex, selectedText);

	if (selectedText == _T("Serial")) {
		// Serial 관련 UI 보이기
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_COM_PORT)->ShowWindow(SW_SHOW);

		// BLE 관련 UI 숨기기
		GetDlgItem(IDC_LIST_BLE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SCAN_START)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_SCAN_STOP)->ShowWindow(SW_HIDE);
	}
	else if (selectedText == _T("BluetoothLE")) {
		// Serial 관련 UI 숨기기
		GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_COM_PORT)->ShowWindow(SW_HIDE);

		// BLE 관련 UI 보이기
		GetDlgItem(IDC_LIST_BLE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SCAN_START)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_SCAN_STOP)->ShowWindow(SW_SHOW);
	}
}

void CDemoAppDlg::OnBnClickedScanStart()
{
	if (dot_pad_ble_scan == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	dot_pad_ble_scan(DialogBoxByBluetoothScan);
}

void CALLBACK DialogBoxByBluetoothScan(const wchar_t* bleDeviceName)
{
	if (bleDeviceName == nullptr) return;

	// UI 스레드에서 BLE 장치를 추가하기 위해 메시지 전달
	SendMessage(*g_hWnd, WM_USER_BLE_FOUND, reinterpret_cast<WPARAM>(bleDeviceName), 0);
}

void CDemoAppDlg::AddBleDeviceToList(const wchar_t* bleDeviceName)
{
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_BLE);
	if (pListBox == nullptr) return;

	// 디바이스 이름 가져오기
	CString deviceName = bleDeviceName;

	// 리스트 박스에 추가
	int index = pListBox->AddString(deviceName);
	if (index >= 0) {
		bleDevices.push_back(deviceName);
		pListBox->SetItemData(index, static_cast<DWORD_PTR>(bleDevices.size() - 1));
	}
}

void CDemoAppDlg::OnBnClickedScanStop()
{
	if (dot_pad_ble_scan_stop == NULL) {
		CString str;
		str.Format(_T("Loading DLL is fail"));
		AfxMessageBox(str);
		return;
	}

	dot_pad_ble_scan_stop();

	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_BLE);
	pListBox->ResetContent();
	bleDevices.clear();
}

void CDemoAppDlg::UpdateConnectedDeviceList()
{
	if (dot_pad_get_connected_device_count == NULL || 
		dot_pad_get_connected_device_handle == NULL ||
		dot_pad_get_device_name == NULL) {
		return;
	}

	m_listConnectedDevices.ResetContent();
	m_connectedDevices.clear();
	m_connectedDeviceNames.clear();

	int deviceCount = dot_pad_get_connected_device_count();
	
	for (int i = 0; i < deviceCount; i++) {
		void* deviceHandle = nullptr;
		if (dot_pad_get_connected_device_handle(i, &deviceHandle)) {
			if (deviceHandle != nullptr) {
				CString displayName;
				
				// 저장된 연결 정보가 있으면 우선 사용 (포트명 또는 블루투스 기기명)
				auto it = m_deviceConnectionInfo.find(deviceHandle);
				if (it != m_deviceConnectionInfo.end() && !it->second.IsEmpty()) {
					displayName = it->second;
				}
			
				int index = m_listConnectedDevices.AddString(displayName);
				if (index >= 0) {
					m_connectedDevices.push_back(deviceHandle);
					m_connectedDeviceNames.push_back(displayName);
					m_listConnectedDevices.SetItemData(index, static_cast<DWORD_PTR>(m_connectedDevices.size() - 1));
				}
			}
		}
	}
}

void* CDemoAppDlg::GetSelectedDeviceHandle()
{
	int selectedIndex = m_listConnectedDevices.GetCurSel();
	if (selectedIndex == LB_ERR) {
		// 선택된 기기가 없으면 nullptr 반환 (모든 기기에 적용)
		return nullptr;
	}

	DWORD_PTR deviceIndex = m_listConnectedDevices.GetItemData(selectedIndex);
	if (deviceIndex < m_connectedDevices.size()) {
		return m_connectedDevices[deviceIndex];
	}

	return nullptr;
}

void CDemoAppDlg::OnBnClickedButtonRefreshDevices()
{
	UpdateConnectedDeviceList();
}
