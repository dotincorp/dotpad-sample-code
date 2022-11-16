
// DemoAppDlg.h: 헤더 파일
//

#pragma once

#include <string>

#include "dot_pad_sdk.h"


using namespace DOT_PAD_SDK_API;


class CDemoAppDlg : public CDialogEx {
public:
	CDemoAppDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMOAPP_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

	void LoadDotPadDLL();
	void FreeDotPadDLL();

	HINSTANCE m_hDotPadDLL;

	DOT_PAD_INIT_FUNC dot_pad_init;
	DOT_PAD_DEINIT_FUNC dot_pad_deinit;
	DOT_PAD_DISPLAY_FUNC dot_pad_display;
	DOT_PAD_DISPLAY_DATA_FUNC dot_pad_display_data;
	DOT_PAD_DISPLAY_DATA_PART_FUNC dot_pad_display_data_part;
	DOT_PAD_RESET_DISPLAY_FUNC dot_pad_reset_display;
	DOT_PAD_BRAILLE_DISPLAY_FUNC dot_pad_braille_display;
	DOT_PAD_BRAILLE_ASCII_DISPLAY_FUNC dot_pad_braille_ascii_display;
	DOT_PAD_RESET_BRAILLE_DISPLAY_FUNC dot_pad_reset_braille_display;
	DOT_PAD_SEND_KEY_FUNC dot_pad_send_key;
	DOT_PAD_GET_FW_VERSION_FUNC dot_pad_get_fw_version;
	DOT_PAD_GET_DEVICE_NAME_FUNC dot_pad_get_device_name;
	DOT_PAD_GET_DISPLAY_INFO_FUNC dot_pad_get_display_info;
	DOT_PAD_REGISTER_KEY_CALLBACK_FUNC dot_pad_register_key_callback;
	DOT_PAD_REGISTER_DISPLAY_CALLBACK_FUNC dot_pad_register_display_callback;
public:
	CString strPathName = NULL;
	CString strFileName = NULL;
	std::string displayFilePathName;

	CEdit m_editCOMPORT;
	CEdit m_editDisplayFile;
	CEdit m_editBrailleDisplayData;
	CEdit m_editDisplayDataPartData;
	CEdit m_editDisplayDataPartLength;
	CEdit m_editDisplayDataPartStartIdx;

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
	afx_msg void OnBnClickedButtonDisplayDataPartDisplay();
	afx_msg void OnBnClickedButtonUpRefresh();
	afx_msg void OnBnClickedButtonDownRefresh();
	afx_msg void OnBnClickedButtonDisplayInfo();
	afx_msg void OnBnClickedButtonFirmwareVersion();
	afx_msg void OnBnClickedButtonDeviceName();
};

void CALLBACK DisplayDialogBoxByKeyNoti(const int key);
void CALLBACK DisplayDialogBoxByDisplayComplete(void);
