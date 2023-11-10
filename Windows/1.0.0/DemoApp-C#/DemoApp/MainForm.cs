using System;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace demo.app
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }


        private void MainForm_Load(object sender, EventArgs e)
        {
            // 시리얼포트 콤보박스 바인딩
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            foreach (string portName in ports)
            {
                this.comboBox20Port.Items.Add(portName);
                this.comboBox300Port.Items.Add(portName);
                this.comboBox320Port.Items.Add(portName);
            }
        }

        private int GetPortNumber(ComboBox combo)
        {
            if (combo.SelectedItem != null)
            {
                string portNumber = combo.SelectedItem.ToString();
                portNumber = portNumber.Replace("COM", "");
                return int.Parse(portNumber);
            }
            else
            {
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
        private void buttonKiosk20Connect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            int portNumber = this.GetPortNumber(this.comboBox20Port);
            if (portNumber > 0)
            {
                ERROR_CODE result = DotPadSDK.DOT_PAD_INIT(portNumber);
                if (result == ERROR_CODE.DOT_ERROR_NONE)
                {
                    this.buttonKiosk20Connect.Enabled = false;
                    this.buttonKiosk20Disconnect.Enabled = true;
                    this.buttonKiosk20Braille.Enabled = true;
                    this.buttonKiosk20Init.Enabled = true;
                    this.comboBox_language.Enabled = true;
                    this.textBox_braille.Enabled = true;
                    this.showMessage("Connection was successful in Kiosk 20 cells.");
                }
                else
                {
                    this.showError("Connection failed in Kiosk 20 cells (error code = " + result + ")");
                }
            }
            else
            {
                this.showError("Select the device port to connect");
            }
        }

        private void buttonKiosk300Connect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            int portNumber = this.GetPortNumber(this.comboBox300Port);
            ERROR_CODE result = DotPadSDK.DOT_PAD_INIT_WITH_DEVICE_TYPE(portNumber, 0);
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.buttonKiosk300Connect.Enabled = false;
                this.buttonKiosk300Disconnect.Enabled = true;
                this.buttonKiosk300Dtm.Enabled = true;
                this.buttonKiosk300Print.Enabled = true;
                this.buttonKiosk300Init.Enabled = true;
                this.showMessage("Connection was successful in Kiosk 300 cells.");
            }
            else
            {
                this.showError("Device connection failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad320Connect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            int portNumber = this.GetPortNumber(this.comboBox320Port);
            ERROR_CODE result = DotPadSDK.DOT_PAD_INIT(portNumber);
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.buttonDotPad320Connect.Enabled = false;
                this.buttonDotPad320Disconnect.Enabled = true;
                this.buttonDotPad320Dtm.Enabled = true;
                this.buttonDotPad320Print.Enabled = true;
                this.buttonDotPad320Init.Enabled = true;
                this.showMessage("Connection was successful in DotPad 320 cells.");
            }
            else
            {
                this.showError("Connection was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        // ---------------------------------------------------------
        // Device Data Print 
        // ---------------------------------------------------------
        private void buttonKiosk20Braille_Click(object sender, EventArgs e)
        {
            this.showMessage("");
            String brailleText = textBox_braille.Text;

            StringBuilder input = new StringBuilder(20);
            input.Append(brailleText); // input data

            String language = comboBox_language.Text;
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

            ERROR_CODE result = DotPadSDK.DOT_PAD_BRAILLE_DISPLAY(input, languageCode, 1); // 0x05(english)
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Braille print was successful in Kiosk 20 cells.");
            }
            else
            {
                this.showError("Braille print was failed in Kiosk 20 cells  (error code=" + result + ")");
            }
        }

        private void buttonKiosk300Print_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            byte[] input = new byte[] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
            ERROR_CODE result = DotPadSDK.DOT_PAD_DISPLAY_DATA(input, 10);
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Data print was successful in Kiosk 300 cells.");
            }
            else
            {
                this.showError("Data print was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad320Print_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            byte[] input = new byte[] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // hexa byte array
            ERROR_CODE result = DotPadSDK.DOT_PAD_DISPLAY_DATA(input, 10);
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Data print was successful in DotPad 320 cells.");
            }
            else
            {
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

            ERROR_CODE result = DotPadSDK.DOT_PAD_DISPLAY(filePath);
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Dtm file print was successful in Kiosk 300 cells");
            }
            else
            {
                this.showError("Dtm file print was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad320Dtm_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            String currentDir = System.IO.Directory.GetCurrentDirectory();
            string filePath = currentDir + "/test-320.dtm";

            ERROR_CODE result = DotPadSDK.DOT_PAD_DISPLAY(filePath);
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Dtm file print was successful in DotPad 320 cells");
            }
            else
            {
                this.showError("Dtm file print was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        // ---------------------------------------------------------
        // Device Disconnect 
        // ---------------------------------------------------------
        private void buttonKiosk20Disconnect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            ERROR_CODE result = DotPadSDK.DOT_PAD_DEINIT();
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.buttonKiosk20Connect.Enabled = true;
                this.buttonKiosk20Disconnect.Enabled = false;
                this.buttonKiosk20Braille.Enabled = false;
                this.buttonKiosk20Init.Enabled = false;
                this.comboBox_language.Enabled = false;
                this.textBox_braille.Enabled = false;
                this.showMessage("Device disconnection was successful in Kiosk 20 cells.");
            }
            else
            {
                this.showError("Device disconnection was failed in Kiosk 20 cells. (error code=" + result + ")");
            }
        }

        private void buttonKiosk300Disconnect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            ERROR_CODE result = DotPadSDK.DOT_PAD_DEINIT();
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.buttonKiosk300Connect.Enabled = true;
                this.buttonKiosk300Disconnect.Enabled = false;
                this.buttonKiosk300Dtm.Enabled = false;
                this.buttonKiosk300Print.Enabled = false;
                this.buttonKiosk300Init.Enabled = false;
                this.showMessage("Device disconnection was successful in Kiosk 300 cells.");
            }
            else
            {
                this.showError("Device disconnection was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad320Disconnect_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            ERROR_CODE result = DotPadSDK.DOT_PAD_DEINIT();
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.buttonDotPad320Connect.Enabled = true;
                this.buttonDotPad320Disconnect.Enabled = false;
                this.buttonDotPad320Dtm.Enabled = false;
                this.buttonDotPad320Print.Enabled = false;
                this.buttonDotPad320Init.Enabled = false;
                this.showMessage("Device disconnection was successful in DotPad 320 cells.");
            }
            else
            {
                this.showError("Device disconnection was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        // ---------------------------------------------------------
        // Device Initialization
        // ---------------------------------------------------------
        private void buttonKiosk20Init_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            ERROR_CODE result = DotPadSDK.DOT_PAD_RESET_BRAILLE_DISPLAY();
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Device initialization was successful in Kiosk 20 cells.");
            }
            else
            {
                this.showError("Device initialization was failed in Kiosk 20 cells. (error code=" + result + ")");
            }
        }

        private void buttonKiosk300Init_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            ERROR_CODE result = DotPadSDK.DOT_PAD_RESET_DISPLAY();
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Device initialization was successful in Kiosk 300 cells.");
            }
            else
            {
                this.showError("Device initialization was failed in Kiosk 300 cells. (error code=" + result + ")");
            }
        }

        private void buttonDotPad320Init_Click(object sender, EventArgs e)
        {
            this.showMessage("");

            ERROR_CODE result = DotPadSDK.DOT_PAD_RESET_DISPLAY();
            if (result == ERROR_CODE.DOT_ERROR_NONE)
            {
                this.showMessage("Device initialization was successful in DotPad 320 cells.");
            }
            else
            {
                this.showError("Device initialization was failed in DotPad 320 cells. (error code=" + result + ")");
            }
        }

        private void comboBox_language_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
