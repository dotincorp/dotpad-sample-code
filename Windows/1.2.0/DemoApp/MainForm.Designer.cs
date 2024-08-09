namespace demo.app
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBoxKioskSingle = new System.Windows.Forms.GroupBox();
            this.comboKioskSingleLanguage = new System.Windows.Forms.ComboBox();
            this.textBoxKioskSingleBraille = new System.Windows.Forms.TextBox();
            this.comboKioskSinglePort = new System.Windows.Forms.ComboBox();
            this.buttonKioskSigleDisconnect = new System.Windows.Forms.Button();
            this.buttonKioskSingleConnect = new System.Windows.Forms.Button();
            this.buttonKioskSingleInit = new System.Windows.Forms.Button();
            this.buttonKioskSingleBraille = new System.Windows.Forms.Button();
            this.groupBoxKiosk300 = new System.Windows.Forms.GroupBox();
            this.comboBox300Port = new System.Windows.Forms.ComboBox();
            this.buttonKiosk300Disconnect = new System.Windows.Forms.Button();
            this.buttonKiosk300Connect = new System.Windows.Forms.Button();
            this.buttonKiosk300Init = new System.Windows.Forms.Button();
            this.buttonKiosk300Dtm = new System.Windows.Forms.Button();
            this.buttonKiosk300Print = new System.Windows.Forms.Button();
            this.groupBoxDotPad320 = new System.Windows.Forms.GroupBox();
            this.labelDotPadKey = new System.Windows.Forms.Label();
            this.buttonDotPad20Braille = new System.Windows.Forms.Button();
            this.buttonDotPad20Init = new System.Windows.Forms.Button();
            this.comboBox320Port = new System.Windows.Forms.ComboBox();
            this.buttonDotPad320Disconnect = new System.Windows.Forms.Button();
            this.buttonDotPad320Connect = new System.Windows.Forms.Button();
            this.buttonDotPad300Init = new System.Windows.Forms.Button();
            this.buttonDotPad300Dtm = new System.Windows.Forms.Button();
            this.buttonDotPad300Print = new System.Windows.Forms.Button();
            this.labelMessage = new System.Windows.Forms.Label();
            this.timerKeyCode = new System.Windows.Forms.Timer(this.components);
            this.buttonDeviceName = new System.Windows.Forms.Button();
            this.groupBoxKioskSingle.SuspendLayout();
            this.groupBoxKiosk300.SuspendLayout();
            this.groupBoxDotPad320.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxKioskSingle
            // 
            this.groupBoxKioskSingle.Controls.Add(this.comboKioskSingleLanguage);
            this.groupBoxKioskSingle.Controls.Add(this.textBoxKioskSingleBraille);
            this.groupBoxKioskSingle.Controls.Add(this.comboKioskSinglePort);
            this.groupBoxKioskSingle.Controls.Add(this.buttonKioskSigleDisconnect);
            this.groupBoxKioskSingle.Controls.Add(this.buttonKioskSingleConnect);
            this.groupBoxKioskSingle.Controls.Add(this.buttonKioskSingleInit);
            this.groupBoxKioskSingle.Controls.Add(this.buttonKioskSingleBraille);
            this.groupBoxKioskSingle.Location = new System.Drawing.Point(22, 65);
            this.groupBoxKioskSingle.Name = "groupBoxKioskSingle";
            this.groupBoxKioskSingle.Size = new System.Drawing.Size(417, 109);
            this.groupBoxKioskSingle.TabIndex = 8;
            this.groupBoxKioskSingle.TabStop = false;
            this.groupBoxKioskSingle.Text = "Kiosk Single(20,12)";
            // 
            // comboKioskSingleLanguage
            // 
            this.comboKioskSingleLanguage.Enabled = false;
            this.comboKioskSingleLanguage.FormattingEnabled = true;
            this.comboKioskSingleLanguage.Items.AddRange(new object[] {
            "Enlish",
            "Korean",
            "ChineseTraditional",
            "ChineseSimplified",
            "Japanese",
            "Arabic",
            "Italian",
            "Vietnamese",
            "Uzbek",
            "Thai",
            "Greek"});
            this.comboKioskSingleLanguage.Location = new System.Drawing.Point(25, 48);
            this.comboKioskSingleLanguage.Name = "comboKioskSingleLanguage";
            this.comboKioskSingleLanguage.Size = new System.Drawing.Size(109, 20);
            this.comboKioskSingleLanguage.TabIndex = 17;
            this.comboKioskSingleLanguage.Text = "- Language -";
            // 
            // textBoxKioskSingleBraille
            // 
            this.textBoxKioskSingleBraille.Enabled = false;
            this.textBoxKioskSingleBraille.Location = new System.Drawing.Point(25, 78);
            this.textBoxKioskSingleBraille.Name = "textBoxKioskSingleBraille";
            this.textBoxKioskSingleBraille.Size = new System.Drawing.Size(366, 21);
            this.textBoxKioskSingleBraille.TabIndex = 16;
            // 
            // comboKioskSinglePort
            // 
            this.comboKioskSinglePort.FormattingEnabled = true;
            this.comboKioskSinglePort.Location = new System.Drawing.Point(25, 20);
            this.comboKioskSinglePort.Name = "comboKioskSinglePort";
            this.comboKioskSinglePort.Size = new System.Drawing.Size(109, 20);
            this.comboKioskSinglePort.TabIndex = 15;
            this.comboKioskSinglePort.Text = "-Serial Port-";
            // 
            // buttonKioskSigleDisconnect
            // 
            this.buttonKioskSigleDisconnect.Enabled = false;
            this.buttonKioskSigleDisconnect.Location = new System.Drawing.Point(282, 18);
            this.buttonKioskSigleDisconnect.Name = "buttonKioskSigleDisconnect";
            this.buttonKioskSigleDisconnect.Size = new System.Drawing.Size(108, 24);
            this.buttonKioskSigleDisconnect.TabIndex = 14;
            this.buttonKioskSigleDisconnect.Text = "Disconnect";
            this.buttonKioskSigleDisconnect.UseVisualStyleBackColor = true;
            this.buttonKioskSigleDisconnect.Click += new System.EventHandler(this.buttonKioskSingleDisconnect_Click);
            // 
            // buttonKioskSingleConnect
            // 
            this.buttonKioskSingleConnect.Location = new System.Drawing.Point(153, 18);
            this.buttonKioskSingleConnect.Name = "buttonKioskSingleConnect";
            this.buttonKioskSingleConnect.Size = new System.Drawing.Size(108, 24);
            this.buttonKioskSingleConnect.TabIndex = 13;
            this.buttonKioskSingleConnect.Text = "Connect";
            this.buttonKioskSingleConnect.UseVisualStyleBackColor = true;
            this.buttonKioskSingleConnect.Click += new System.EventHandler(this.buttonKioskSingleConnect_Click);
            // 
            // buttonKioskSingleInit
            // 
            this.buttonKioskSingleInit.Enabled = false;
            this.buttonKioskSingleInit.Location = new System.Drawing.Point(282, 46);
            this.buttonKioskSingleInit.Name = "buttonKioskSingleInit";
            this.buttonKioskSingleInit.Size = new System.Drawing.Size(108, 24);
            this.buttonKioskSingleInit.TabIndex = 12;
            this.buttonKioskSingleInit.Text = "Initialize Cells";
            this.buttonKioskSingleInit.UseVisualStyleBackColor = true;
            this.buttonKioskSingleInit.Click += new System.EventHandler(this.buttonKioskSingleInit_Click);
            // 
            // buttonKioskSingleBraille
            // 
            this.buttonKioskSingleBraille.Enabled = false;
            this.buttonKioskSingleBraille.Location = new System.Drawing.Point(153, 47);
            this.buttonKioskSingleBraille.Name = "buttonKioskSingleBraille";
            this.buttonKioskSingleBraille.Size = new System.Drawing.Size(109, 22);
            this.buttonKioskSingleBraille.TabIndex = 10;
            this.buttonKioskSingleBraille.Text = "Braille Data";
            this.buttonKioskSingleBraille.UseVisualStyleBackColor = true;
            this.buttonKioskSingleBraille.Click += new System.EventHandler(this.buttonKioskSingleBraille_Click);
            // 
            // groupBoxKiosk300
            // 
            this.groupBoxKiosk300.Controls.Add(this.comboBox300Port);
            this.groupBoxKiosk300.Controls.Add(this.buttonKiosk300Disconnect);
            this.groupBoxKiosk300.Controls.Add(this.buttonKiosk300Connect);
            this.groupBoxKiosk300.Controls.Add(this.buttonKiosk300Init);
            this.groupBoxKiosk300.Controls.Add(this.buttonKiosk300Dtm);
            this.groupBoxKiosk300.Controls.Add(this.buttonKiosk300Print);
            this.groupBoxKiosk300.Location = new System.Drawing.Point(22, 181);
            this.groupBoxKiosk300.Name = "groupBoxKiosk300";
            this.groupBoxKiosk300.Size = new System.Drawing.Size(417, 83);
            this.groupBoxKiosk300.TabIndex = 10;
            this.groupBoxKiosk300.TabStop = false;
            this.groupBoxKiosk300.Text = "Kiosk300";
            // 
            // comboBox300Port
            // 
            this.comboBox300Port.FormattingEnabled = true;
            this.comboBox300Port.Location = new System.Drawing.Point(26, 24);
            this.comboBox300Port.Name = "comboBox300Port";
            this.comboBox300Port.Size = new System.Drawing.Size(109, 20);
            this.comboBox300Port.TabIndex = 18;
            this.comboBox300Port.Text = "-Serial Port-";
            // 
            // buttonKiosk300Disconnect
            // 
            this.buttonKiosk300Disconnect.Enabled = false;
            this.buttonKiosk300Disconnect.Location = new System.Drawing.Point(282, 20);
            this.buttonKiosk300Disconnect.Name = "buttonKiosk300Disconnect";
            this.buttonKiosk300Disconnect.Size = new System.Drawing.Size(109, 24);
            this.buttonKiosk300Disconnect.TabIndex = 17;
            this.buttonKiosk300Disconnect.Text = "Disconnect";
            this.buttonKiosk300Disconnect.UseVisualStyleBackColor = true;
            this.buttonKiosk300Disconnect.Click += new System.EventHandler(this.buttonKiosk300Disconnect_Click);
            // 
            // buttonKiosk300Connect
            // 
            this.buttonKiosk300Connect.Location = new System.Drawing.Point(153, 20);
            this.buttonKiosk300Connect.Name = "buttonKiosk300Connect";
            this.buttonKiosk300Connect.Size = new System.Drawing.Size(108, 24);
            this.buttonKiosk300Connect.TabIndex = 16;
            this.buttonKiosk300Connect.Text = "Connect";
            this.buttonKiosk300Connect.UseVisualStyleBackColor = true;
            this.buttonKiosk300Connect.Click += new System.EventHandler(this.buttonKiosk300Connect_Click);
            // 
            // buttonKiosk300Init
            // 
            this.buttonKiosk300Init.Enabled = false;
            this.buttonKiosk300Init.Location = new System.Drawing.Point(282, 50);
            this.buttonKiosk300Init.Name = "buttonKiosk300Init";
            this.buttonKiosk300Init.Size = new System.Drawing.Size(109, 25);
            this.buttonKiosk300Init.TabIndex = 9;
            this.buttonKiosk300Init.Text = "Initialize Cells";
            this.buttonKiosk300Init.UseVisualStyleBackColor = true;
            this.buttonKiosk300Init.Click += new System.EventHandler(this.buttonKiosk300Init_Click);
            // 
            // buttonKiosk300Dtm
            // 
            this.buttonKiosk300Dtm.Enabled = false;
            this.buttonKiosk300Dtm.Location = new System.Drawing.Point(153, 50);
            this.buttonKiosk300Dtm.Name = "buttonKiosk300Dtm";
            this.buttonKiosk300Dtm.Size = new System.Drawing.Size(109, 25);
            this.buttonKiosk300Dtm.TabIndex = 8;
            this.buttonKiosk300Dtm.Text = "Print DTM file";
            this.buttonKiosk300Dtm.UseVisualStyleBackColor = true;
            this.buttonKiosk300Dtm.Click += new System.EventHandler(this.buttonKiosk300Dtm_Click);
            // 
            // buttonKiosk300Print
            // 
            this.buttonKiosk300Print.Enabled = false;
            this.buttonKiosk300Print.Location = new System.Drawing.Point(25, 50);
            this.buttonKiosk300Print.Name = "buttonKiosk300Print";
            this.buttonKiosk300Print.Size = new System.Drawing.Size(109, 25);
            this.buttonKiosk300Print.TabIndex = 6;
            this.buttonKiosk300Print.Text = "Print Data";
            this.buttonKiosk300Print.UseVisualStyleBackColor = true;
            this.buttonKiosk300Print.Click += new System.EventHandler(this.buttonKiosk300Print_Click);
            // 
            // groupBoxDotPad320
            // 
            this.groupBoxDotPad320.Controls.Add(this.labelDotPadKey);
            this.groupBoxDotPad320.Controls.Add(this.buttonDotPad20Braille);
            this.groupBoxDotPad320.Controls.Add(this.buttonDotPad20Init);
            this.groupBoxDotPad320.Controls.Add(this.comboBox320Port);
            this.groupBoxDotPad320.Controls.Add(this.buttonDotPad320Disconnect);
            this.groupBoxDotPad320.Controls.Add(this.buttonDotPad320Connect);
            this.groupBoxDotPad320.Controls.Add(this.buttonDotPad300Init);
            this.groupBoxDotPad320.Controls.Add(this.buttonDotPad300Dtm);
            this.groupBoxDotPad320.Controls.Add(this.buttonDotPad300Print);
            this.groupBoxDotPad320.Location = new System.Drawing.Point(22, 272);
            this.groupBoxDotPad320.Name = "groupBoxDotPad320";
            this.groupBoxDotPad320.Size = new System.Drawing.Size(417, 113);
            this.groupBoxDotPad320.TabIndex = 11;
            this.groupBoxDotPad320.TabStop = false;
            this.groupBoxDotPad320.Text = "DotPad320";
            // 
            // labelDotPadKey
            // 
            this.labelDotPadKey.AutoSize = true;
            this.labelDotPadKey.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.labelDotPadKey.Location = new System.Drawing.Point(11, 87);
            this.labelDotPadKey.Name = "labelDotPadKey";
            this.labelDotPadKey.Size = new System.Drawing.Size(132, 12);
            this.labelDotPadKey.TabIndex = 24;
            this.labelDotPadKey.Text = "Press DotPad320 key !";
            // 
            // buttonDotPad20Braille
            // 
            this.buttonDotPad20Braille.Enabled = false;
            this.buttonDotPad20Braille.Location = new System.Drawing.Point(153, 81);
            this.buttonDotPad20Braille.Name = "buttonDotPad20Braille";
            this.buttonDotPad20Braille.Size = new System.Drawing.Size(109, 22);
            this.buttonDotPad20Braille.TabIndex = 23;
            this.buttonDotPad20Braille.Text = "Braille Data";
            this.buttonDotPad20Braille.UseVisualStyleBackColor = true;
            this.buttonDotPad20Braille.Click += new System.EventHandler(this.buttonDotPad20Braille_Click);
            // 
            // buttonDotPad20Init
            // 
            this.buttonDotPad20Init.Enabled = false;
            this.buttonDotPad20Init.Location = new System.Drawing.Point(282, 80);
            this.buttonDotPad20Init.Name = "buttonDotPad20Init";
            this.buttonDotPad20Init.Size = new System.Drawing.Size(108, 24);
            this.buttonDotPad20Init.TabIndex = 22;
            this.buttonDotPad20Init.Text = "Initialize Cells";
            this.buttonDotPad20Init.UseVisualStyleBackColor = true;
            this.buttonDotPad20Init.Click += new System.EventHandler(this.buttonDotPad20Init_Click);
            // 
            // comboBox320Port
            // 
            this.comboBox320Port.FormattingEnabled = true;
            this.comboBox320Port.Location = new System.Drawing.Point(25, 24);
            this.comboBox320Port.Name = "comboBox320Port";
            this.comboBox320Port.Size = new System.Drawing.Size(109, 20);
            this.comboBox320Port.TabIndex = 21;
            this.comboBox320Port.Text = "-Serial Port-";
            // 
            // buttonDotPad320Disconnect
            // 
            this.buttonDotPad320Disconnect.Enabled = false;
            this.buttonDotPad320Disconnect.Location = new System.Drawing.Point(282, 22);
            this.buttonDotPad320Disconnect.Name = "buttonDotPad320Disconnect";
            this.buttonDotPad320Disconnect.Size = new System.Drawing.Size(109, 24);
            this.buttonDotPad320Disconnect.TabIndex = 20;
            this.buttonDotPad320Disconnect.Text = "Disconnect";
            this.buttonDotPad320Disconnect.UseVisualStyleBackColor = true;
            this.buttonDotPad320Disconnect.Click += new System.EventHandler(this.buttonDotPad320Disconnect_Click);
            // 
            // buttonDotPad320Connect
            // 
            this.buttonDotPad320Connect.Location = new System.Drawing.Point(153, 22);
            this.buttonDotPad320Connect.Name = "buttonDotPad320Connect";
            this.buttonDotPad320Connect.Size = new System.Drawing.Size(109, 24);
            this.buttonDotPad320Connect.TabIndex = 19;
            this.buttonDotPad320Connect.Text = "Connect";
            this.buttonDotPad320Connect.UseVisualStyleBackColor = true;
            this.buttonDotPad320Connect.Click += new System.EventHandler(this.buttonDotPad320Connect_Click);
            // 
            // buttonDotPad300Init
            // 
            this.buttonDotPad300Init.Enabled = false;
            this.buttonDotPad300Init.Location = new System.Drawing.Point(282, 51);
            this.buttonDotPad300Init.Name = "buttonDotPad300Init";
            this.buttonDotPad300Init.Size = new System.Drawing.Size(109, 25);
            this.buttonDotPad300Init.TabIndex = 9;
            this.buttonDotPad300Init.Text = "Initicalize Cells";
            this.buttonDotPad300Init.UseVisualStyleBackColor = true;
            this.buttonDotPad300Init.Click += new System.EventHandler(this.buttonDotPad300Init_Click);
            // 
            // buttonDotPad300Dtm
            // 
            this.buttonDotPad300Dtm.Enabled = false;
            this.buttonDotPad300Dtm.Location = new System.Drawing.Point(153, 51);
            this.buttonDotPad300Dtm.Name = "buttonDotPad300Dtm";
            this.buttonDotPad300Dtm.Size = new System.Drawing.Size(109, 25);
            this.buttonDotPad300Dtm.TabIndex = 8;
            this.buttonDotPad300Dtm.Text = "Print DTM file";
            this.buttonDotPad300Dtm.UseVisualStyleBackColor = true;
            this.buttonDotPad300Dtm.Click += new System.EventHandler(this.buttonDotPad300Dtm_Click);
            // 
            // buttonDotPad300Print
            // 
            this.buttonDotPad300Print.Enabled = false;
            this.buttonDotPad300Print.Location = new System.Drawing.Point(25, 51);
            this.buttonDotPad300Print.Name = "buttonDotPad300Print";
            this.buttonDotPad300Print.Size = new System.Drawing.Size(109, 25);
            this.buttonDotPad300Print.TabIndex = 6;
            this.buttonDotPad300Print.Text = "Print Data";
            this.buttonDotPad300Print.UseVisualStyleBackColor = true;
            this.buttonDotPad300Print.Click += new System.EventHandler(this.buttonDotPad300Print_Click);
            // 
            // labelMessage
            // 
            this.labelMessage.BackColor = System.Drawing.Color.Gainsboro;
            this.labelMessage.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.labelMessage.ForeColor = System.Drawing.Color.Blue;
            this.labelMessage.Location = new System.Drawing.Point(22, 36);
            this.labelMessage.Name = "labelMessage";
            this.labelMessage.Size = new System.Drawing.Size(417, 20);
            this.labelMessage.TabIndex = 12;
            this.labelMessage.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // timerKeyCode
            // 
            this.timerKeyCode.Enabled = true;
            this.timerKeyCode.Interval = 1000;
            this.timerKeyCode.Tick += new System.EventHandler(this.timerKeyCode_Tick);
            // 
            // buttonDeviceName
            // 
            this.buttonDeviceName.Enabled = false;
            this.buttonDeviceName.Location = new System.Drawing.Point(350, 11);
            this.buttonDeviceName.Name = "buttonDeviceName";
            this.buttonDeviceName.Size = new System.Drawing.Size(90, 19);
            this.buttonDeviceName.TabIndex = 19;
            this.buttonDeviceName.Text = "Device Name";
            this.buttonDeviceName.UseVisualStyleBackColor = true;
            this.buttonDeviceName.Click += new System.EventHandler(this.buttonDeviceName_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(457, 402);
            this.Controls.Add(this.buttonDeviceName);
            this.Controls.Add(this.labelMessage);
            this.Controls.Add(this.groupBoxDotPad320);
            this.Controls.Add(this.groupBoxKiosk300);
            this.Controls.Add(this.groupBoxKioskSingle);
            this.Name = "MainForm";
            this.Text = "Demo App";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.groupBoxKioskSingle.ResumeLayout(false);
            this.groupBoxKioskSingle.PerformLayout();
            this.groupBoxKiosk300.ResumeLayout(false);
            this.groupBoxDotPad320.ResumeLayout(false);
            this.groupBoxDotPad320.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBoxKioskSingle;
        private System.Windows.Forms.Button buttonKioskSingleBraille;
        private System.Windows.Forms.Button buttonKioskSingleInit;
        private System.Windows.Forms.GroupBox groupBoxKiosk300;
        private System.Windows.Forms.Button buttonKiosk300Init;
        private System.Windows.Forms.Button buttonKiosk300Dtm;
        private System.Windows.Forms.Button buttonKiosk300Print;
        private System.Windows.Forms.GroupBox groupBoxDotPad320;
        private System.Windows.Forms.Button buttonDotPad300Init;
        private System.Windows.Forms.Button buttonDotPad300Dtm;
        private System.Windows.Forms.Button buttonDotPad300Print;
        private System.Windows.Forms.Button buttonKioskSigleDisconnect;
        private System.Windows.Forms.Button buttonKioskSingleConnect;
        private System.Windows.Forms.ComboBox comboKioskSinglePort;
        private System.Windows.Forms.ComboBox comboBox300Port;
        private System.Windows.Forms.Button buttonKiosk300Disconnect;
        private System.Windows.Forms.Button buttonKiosk300Connect;
        private System.Windows.Forms.ComboBox comboBox320Port;
        private System.Windows.Forms.Button buttonDotPad320Disconnect;
        private System.Windows.Forms.Button buttonDotPad320Connect;
        private System.Windows.Forms.Label labelMessage;
        private System.Windows.Forms.ComboBox comboKioskSingleLanguage;
        private System.Windows.Forms.TextBox textBoxKioskSingleBraille;
        private System.Windows.Forms.Button buttonDotPad20Braille;
        private System.Windows.Forms.Button buttonDotPad20Init;
        private System.Windows.Forms.Timer timerKeyCode;
        private System.Windows.Forms.Label labelDotPadKey;
        private System.Windows.Forms.Button buttonDeviceName;
    }
}

