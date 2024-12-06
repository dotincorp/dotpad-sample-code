using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Timers;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.TaskbarClock;

namespace demo.app
{
    public partial class MainForm : Form
    {
        public delegate void KeyPressCallbackFunc(int value);
        private static KeyPressCallbackFunc keyPresscallbackDelegate;
        private Queue<int> numbersQueue = new Queue<int>();

        public MainForm()
        {
            InitializeComponent();
        }

        // 닷패드 펑션키 콜백함수 리스너
        public void KeyPressCallback(int value)
        {
            Console.WriteLine("function key = " + value);
            numbersQueue.Enqueue(value);

            // C++ 콜백함수와 C#의 Thread가 달라 아래 호출하면 동작안함
            //Thread.Sleep(3000);
            //displayBraille(value);
        }

        private static void displayBraille()
        {
            Random random = new Random();
            StringBuilder input = new StringBuilder();
            input.Append("You should receive your letter tomorrow afternoon.");
            DotPadSDK.DOT_PAD_BRAILLE_DISPLAY(input, 5);
        }


        private void MainForm_Load(object sender, EventArgs e)
        {
            // 시리얼포트 콤보박스 바인딩
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            foreach (string portName in ports) {
                this.comboKioskSinglePort.Items.Add(portName);
                this.comboBox300Port.Items.Add(portName);
                this.comboBox320Port.Items.Add(portName);
            }
        }

        private int GetPortNumber(ComboBox combo)
        {
            if (combo.SelectedItem != null) {
                string portNumber = combo.SelectedItem.ToString();
                portNumber = portNumber.Replace("COM", "");
                return int.Parse(portNumber);
            } else {
                return 0;
            }
        }

        private void showMessage(String message)
        {
            this.labelMessage.ForeColor = Color.White;
            this.labelMessage.BackColor = Color.Blue;
            this.labelMessage.Text = message;
        }

        private void showError(String errorMessage)
        {
            this.labelMessage.ForeColor = Color.White;
            this.labelMessage.BackColor = Color.Red;
            this.labelMessage.Text = errorMessage;
        }

        // ---------------------------------------------------------
        // Device Connect 
        // ---------------------------------------------------------
        private void buttonKioskSingleConnect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            int portNumber = this.GetPortNumber(this.comboKioskSinglePort);
            if (portNumber > 0) {
                DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_INIT(portNumber);
                if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                    this.buttonKioskSingleConnect.Enabled = false;
                    this.buttonKioskSigleDisconnect.Enabled = true;
                    this.buttonKioskSingleBraille.Enabled = true;
                    this.buttonKioskSingleInit.Enabled = true;
                    this.comboKioskSingleLanguage.Enabled = true;
                    this.textBoxKioskSingleBraille.Enabled = true;
                    this.buttonDeviceName.Enabled = true;

                    this.showMessage("Connection was successful in Kiosk single cells.");
                } else {
                    this.showError("Connection failed in Kiosk single cells (error code = " + result + ")");
                }
            } else {
                this.showError("Select the device port to connect");
            }
        }

        private void buttonKiosk300Connect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            int portNumber = this.GetPortNumber(this.comboBox300Port);
            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_INIT_WITH_DEVICE_TYPE(portNumber, 0);
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.buttonKiosk300Connect.Enabled = false;
                this.buttonKiosk300Disconnect.Enabled = true;
                this.buttonKiosk300Dtm.Enabled = true;
                this.buttonKiosk300Print.Enabled = true;
                this.buttonKiosk300Init.Enabled = true;
                this.buttonDeviceName.Enabled = true;
                this.showMessage("Connection was successful in Kiosk 300 cells.");
            } else {
                this.showError("Device connection failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad320Connect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            int portNumber = this.GetPortNumber(this.comboBox320Port);
            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_INIT(portNumber);
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.buttonDotPad320Connect.Enabled = false;
                this.buttonDotPad320Disconnect.Enabled = true;
                this.buttonDotPad300Dtm.Enabled = true;
                this.buttonDotPad300Print.Enabled = true;
                this.buttonDotPad300Init.Enabled = true;
                this.buttonDotPad20Braille.Enabled = true;
                this.buttonDotPad20Init.Enabled = true;
                this.buttonDeviceName.Enabled = true;
                this.showMessage("Connection was successful in DotPad 320 cells.");

                // 닷패드 키코드 콜백 이벤트 등록 (static 변수 선언)
                keyPresscallbackDelegate = new KeyPressCallbackFunc(KeyPressCallback);
                DotPadSDK.DOT_PAD_REGISTER_KEY_CALLBACK(keyPresscallbackDelegate);
            } else {
                this.showError("Connection was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        
        // ---------------------------------------------------------
        // Device Data Print 
        // ---------------------------------------------------------
        private void buttonKioskSingleBraille_Click(object sender, EventArgs e)
        {
            this.showMessage("");
            String brailleText = textBoxKioskSingleBraille.Text;

            StringBuilder input = new StringBuilder(20);
            input.Append(brailleText); // input data

            String language = comboKioskSingleLanguage.Text;
            int languageCode = 0X05;
            if (language == "English") languageCode = 0X05;
            else if (language == "Korean") languageCode = 0x0A;
            else if (language == "Japanese") languageCode = 0x09;
            else if (language == "ChineseTraditional") languageCode = 0x02;
            else if (language == "ChineseSimplified") languageCode = 0x03;
            else if (language == "Arabic") languageCode = 0x01;
            else if (language == "Italian") languageCode = 0x08;
            else if (language == "Vietnamese") languageCode = 0x0D;
            else if (language == "Uzbek") languageCode = 0x19;
            else if (language == "Thai") languageCode = 0x18;
            else if (language == "Greek") languageCode = 0x15;
            this.showMessage("languageCode=" + languageCode);

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_BRAILLE_DISPLAY(input, languageCode); // 0x05(english)
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Braille print was successful in Kiosk single cells.");
            } else {
                this.showError("Braille print was failed in Kiosk single cells  (error code=" + result + ")");
            }
        }

        private void buttonKiosk300Print_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            byte[] input = new byte[] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_DISPLAY_DATA(input, 10);
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Data print was successful in Kiosk 300 cells.");
            } else {
                this.showError("Data print was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad300Print_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            byte[] input = new byte[] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // hexa byte array
            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_DISPLAY_DATA(input, 10);
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Data print was successful in DotPad 320 cells.");
            } else {
                this.showError("Data print was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        // ---------------------------------------------------------
        // Device Dtm file Print 
        // ---------------------------------------------------------
        private void buttonKiosk300Dtm_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            String currentDir = System.IO.Directory.GetCurrentDirectory();
            string filePath = currentDir + "/test-300.dtm";

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_DISPLAY(filePath);
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Dtm file print was successful in Kiosk 300 cells");
            } else {
                this.showError("Dtm file print was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad300Dtm_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            String currentDir = System.IO.Directory.GetCurrentDirectory();
            string filePath = currentDir + "/test-320.dtm";

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_DISPLAY(filePath);
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Dtm file print was successful in DotPad 320 cells");
            } else {
                this.showError("Dtm file print was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        // ---------------------------------------------------------
        // Device Disconnect 
        // ---------------------------------------------------------
        private void buttonKioskSingleDisconnect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_DEINIT();
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.buttonKioskSingleConnect.Enabled = true;
                this.buttonKioskSigleDisconnect.Enabled = false;
                this.buttonKioskSingleBraille.Enabled = false;
                this.buttonKioskSingleInit.Enabled = false;
                this.comboKioskSingleLanguage.Enabled = false;
                this.textBoxKioskSingleBraille.Enabled = false;
                this.buttonDeviceName.Enabled = false;
                this.showMessage("Device disconnection was successful in Kiosk Single Cells.");
            } else {
                this.showError("Device disconnection was failed in Kiosk Single Cells. (error code=" + result + ")");
            }
        }

        private void buttonKiosk300Disconnect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_DEINIT();
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.buttonKiosk300Connect.Enabled = true;
                this.buttonKiosk300Disconnect.Enabled = false;
                this.buttonKiosk300Dtm.Enabled = false;
                this.buttonKiosk300Print.Enabled = false;
                this.buttonKiosk300Init.Enabled = false;
                this.buttonDeviceName.Enabled = false;
                this.showMessage("Device disconnection was successful in Kiosk 300 cells.");
            } else {
                this.showError("Device disconnection was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad320Disconnect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_DEINIT();
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.buttonDotPad320Connect.Enabled = true;
                this.buttonDotPad320Disconnect.Enabled = false;
                this.buttonDotPad300Dtm.Enabled = false;
                this.buttonDotPad300Print.Enabled = false;
                this.buttonDotPad300Init.Enabled = false;
                this.buttonDotPad20Braille.Enabled = false;
                this.buttonDotPad20Init.Enabled = false;
                this.buttonDeviceName.Enabled = false;
                this.showMessage("Device disconnection was successful in DotPad 320 cells.");
            } else {
                this.showError("Device disconnection was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        // ---------------------------------------------------------
        // Device Initialization
        // ---------------------------------------------------------
        private void buttonKioskSingleInit_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_RESET_BRAILLE_DISPLAY();
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Device initialization was successful in Kiosk single cells.");
            } else {
                this.showError("Device initialization was failed in Kiosk single cells. (error code=" + result + ")");
            }
        }

        private void buttonKiosk300Init_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_RESET_DISPLAY();
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Device initialization was successful in Kiosk 300 cells.");
            } else {
                this.showError("Device initialization was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad300Init_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            DOT_PAD_SDK_ERROR result = DotPadSDK.DOT_PAD_RESET_DISPLAY();
            if (result == DOT_PAD_SDK_ERROR.DOT_ERROR_NONE) {
                this.showMessage("Device initialization was successful in DotPad 320 cells.");
            } else {
                this.showError("Device initialization was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad20Init_Click(object sender, EventArgs e)
        {
            resetBraille();
        }

        private void buttonDotPad20Braille_Click(object sender, EventArgs e)
        {
            displayBraille();
        }

        private void timerKeyCode_Tick(object sender, EventArgs e)
        {
            dequeueKeyCodeEvent();
        }

        private void resetBraille()
        {
            DotPadSDK.DOT_PAD_RESET_BRAILLE_DISPLAY();
        }

        private void dequeueKeyCodeEvent()
        {
            if (numbersQueue.Count > 0) {
                int keyCode = numbersQueue.Dequeue();
                DotPadSDK.DOT_PAD_SEND_KEY(keyCode);
            }
        }

        private void buttonDeviceName_Click(object sender, EventArgs e)
        {
            // 기기정보 조회
            DeviceNameCallback callback = new DeviceNameCallback(onDeviceNameReceived);
            DotPadSDK.DOT_PAD_GET_DEVICE_NAME(callback);
        }

        // 디바이스명 콜백함수
        private void onDeviceNameReceived(IntPtr deviceNamePtr)
        {
            string deviceName = Marshal.PtrToStringAnsi(deviceNamePtr);
            MessageBox.Show("Device Name : [" + deviceName + "]");
        }
    }
}
