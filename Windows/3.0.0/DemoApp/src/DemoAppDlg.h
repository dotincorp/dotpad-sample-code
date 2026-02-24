
// DemoAppDlg.h: 헤더 파일
//

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <map>

#include "DotSDKAPI.h"


using namespace DOT_PAD_SDK_API;


class CDemoAppDlg : public CDialogEx {
public:
	CDemoAppDlg(CWnd* pParent = nullptr);
	~CDemoAppDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMOAPP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	std::vector<CString> bleDevices;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void AddBleDeviceToList(const wchar_t* bleDevice);

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

	void LoadDotPadDLL();
	void FreeDotPadDLL();

	HINSTANCE m_hDotPadDLL;

	// 연결 관리
	DOT_PAD_CONNECT_BLE_FUNC dot_pad_connect_ble;
	DOT_PAD_CONNECT_SERIAL_FUNC dot_pad_connect_serial;
	DOT_PAD_DISCONNECT_FUNC dot_pad_disconnect;
	DOT_PAD_GET_CONNECTED_DEVICE_COUNT_FUNC dot_pad_get_connected_device_count;
	DOT_PAD_GET_CONNECTED_DEVICE_HANDLE_FUNC dot_pad_get_connected_device_handle;
	DOT_PAD_GET_DEVICE_NAME_FUNC dot_pad_get_device_name;
	DOT_PAD_GET_FW_VERSION_FUNC dot_pad_get_fw_version;
	DOT_PAD_GET_HW_VERSION_FUNC dot_pad_get_hw_version;

	// 스캔
	DOT_PAD_BLE_SCAN_FUNC dot_pad_ble_scan;
	DOT_PAD_BLE_SCAN_STOP_FUNC dot_pad_ble_scan_stop;
	DOT_PAD_USB_SCAN_FUNC dot_pad_usb_scan;

	// Display (Graphic)
	DOT_PAD_DISPLAY_FILE_FUNC dot_pad_display_file;
	DOT_PAD_DISPLAY_DATA_FUNC dot_pad_display_data;
	DOT_PAD_RESET_DISPLAY_FUNC dot_pad_reset_display;

	// Display (Braille/Text)
	DOT_PAD_BRAILLE_DISPLAY_FUNC dot_pad_braille_display;
	DOT_PAD_BRAILLE_DISPLAY_DATA_FUNC dot_pad_braille_display_data;
	DOT_PAD_BRAILLE_ASCII_DISPLAY_FUNC dot_pad_braille_ascii_display;
	DOT_PAD_RESET_BRAILLE_DISPLAY_FUNC dot_pad_reset_braille_display;

	// 정보 조회
	DOT_PAD_GET_DISPLAY_INFO_FUNC dot_pad_get_display_info;

	// 콜백 등록
	DOT_PAD_REGISTER_KEY_CALLBACK_FUNC dot_pad_register_key_callback;
	DOT_PAD_REGISTER_MESSAGE_CALLBACK_FUNC dot_pad_register_message_callback;
	DOT_PAD_REGISTER_DISPLAY_CALLBACK_FUNC dot_pad_register_display_callback;

	// 연결된 기기 관리
	std::vector<void*> m_connectedDevices;
	std::vector<CString> m_connectedDeviceNames;
	// deviceHandle과 연결 시 사용한 포트명/블루투스 기기명 매핑
	std::map<void*, CString> m_deviceConnectionInfo;

	// 디바이스별 점역된 점자 데이터 (DOT_PAD_BRAILLE_DISPLAY 콜백으로 수신)
	std::map<void*, std::vector<uint8_t>> m_deviceBrailleData;
	// 디바이스별 Prev/Next 현재 표시 위치(바이트 오프셋)
	std::map<void*, size_t> m_deviceBrailleCurrentIndex;
public:
	CString strPathName = NULL;
	CString strFileName = NULL;
	std::string displayFilePathName;

	CEdit m_editCOMPORT;
	CEdit m_editDisplayFile;
	CEdit m_editBrailleDisplayData;
	CListBox m_listConnectedDevices;

	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonDeinit();
	afx_msg void OnBnClickedButtonUpData();
	afx_msg void OnBnClickedButtonDownData();
	afx_msg void OnBnClickedButtonDisplayFileOpen();
	afx_msg void OnBnClickedButtonDisplay();
	afx_msg void OnBnClickedButtonStringDisplay();
	afx_msg void OnBnClickedButtonAsciiDisplay();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonUpRefresh();
	afx_msg void OnBnClickedButtonDownRefresh();
	afx_msg void OnBnClickedButtonDisplayInfo();
	afx_msg void OnBnClickedButtonFirmwareVersion();
	afx_msg void OnBnClickedButtonDeviceName();
	afx_msg void OnCbnSelchangeComboCommType();
	afx_msg void OnBnClickedScanStart();
	afx_msg void OnBnClickedButtonRefreshDevices();

	LRESULT OnBleDeviceFound(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedScanStop();
	LRESULT OnDotPadSendKey(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateDeviceList(WPARAM wParam, LPARAM lParam);

	// 연결된 기기 목록 업데이트
	void UpdateConnectedDeviceList();
	// 선택한 기기의 handle 가져오기 (nullptr이면 모든 기기)
	void* GetSelectedDeviceHandle();

	// DOT_PAD_BRAILLE_DISPLAY 콜백에서 호출: 점역된 데이터 저장
	void OnBrailleTranslatedData(void* deviceHandle, const uint8_t* translatedData, size_t dataSize);
};

void CALLBACK DisplayDialogBoxByKeyNoti(void* deviceHandle, DOT_KEY_CODE keyCode, const char* message);
void CALLBACK DisplayDialogBoxByMessageNoti(void* deviceHandle, DOT_DATA_CODE dataCode, const char* message);
void CALLBACK DisplayDialogBoxByDisplayComplete(void);
void CALLBACK DialogBoxByBluetoothScan(const wchar_t* bleDeviceName);
void CALLBACK BrailleTranslatedDataCallback(void* deviceHandle, const uint8_t* translatedData, size_t dataSize);

static HWND* g_hWnd = NULL;