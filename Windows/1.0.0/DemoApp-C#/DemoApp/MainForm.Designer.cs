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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.comboBox_language = new System.Windows.Forms.ComboBox();
            this.textBox_braille = new System.Windows.Forms.TextBox();
            this.comboBox20Port = new System.Windows.Forms.ComboBox();
            this.buttonKiosk20Disconnect = new System.Windows.Forms.Button();
            this.buttonKiosk20Connect = new System.Windows.Forms.Button();
            this.buttonKiosk20Init = new System.Windows.Forms.Button();
            this.buttonKiosk20Braille = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.comboBox300Port = new System.Windows.Forms.ComboBox();
            this.buttonKiosk300Disconnect = new System.Windows.Forms.Button();
            this.buttonKiosk300Connect = new System.Windows.Forms.Button();
            this.buttonKiosk300Init = new System.Windows.Forms.Button();
            this.buttonKiosk300Dtm = new System.Windows.Forms.Button();
            this.buttonKiosk300Print = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.comboBox320Port = new System.Windows.Forms.ComboBox();
            this.buttonDotPad320Disconnect = new System.Windows.Forms.Button();
            this.buttonDotPad320Connect = new System.Windows.Forms.Button();
            this.buttonDotPad320Init = new System.Windows.Forms.Button();
            this.buttonDotPad320Dtm = new System.Windows.Forms.Button();
            this.buttonDotPad320Print = new System.Windows.Forms.Button();
            this.labelMessage = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBox_language);
            this.groupBox1.Controls.Add(this.textBox_braille);
            this.groupBox1.Controls.Add(this.comboBox20Port);
            this.groupBox1.Controls.Add(this.buttonKiosk20Disconnect);
            this.groupBox1.Controls.Add(this.buttonKiosk20Connect);
            this.groupBox1.Controls.Add(this.buttonKiosk20Init);
            this.groupBox1.Controls.Add(this.buttonKiosk20Braille);
            this.groupBox1.Location = new System.Drawing.Point(22, 73);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(417, 144);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Kiosk 20 cells";
            // 
            // comboBox_language
            // 
            this.comboBox_language.Enabled = false;
            this.comboBox_language.FormattingEnabled = true;
            this.comboBox_language.Items.AddRange(new object[] {
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
            this.comboBox_language.Location = new System.Drawing.Point(25, 70);
            this.comboBox_language.Name = "comboBox_language";
            this.comboBox_language.Size = new System.Drawing.Size(109, 20);
            this.comboBox_language.TabIndex = 17;
            this.comboBox_language.Text = "- Language -";
            this.comboBox_language.SelectedIndexChanged += new System.EventHandler(this.comboBox_language_SelectedIndexChanged);
            // 
            // textBox_braille
            // 
            this.textBox_braille.Enabled = false;
            this.textBox_braille.Location = new System.Drawing.Point(25, 96);
            this.textBox_braille.Name = "textBox_braille";
            this.textBox_braille.Size = new System.Drawing.Size(366, 21);
            this.textBox_braille.TabIndex = 16;
            // 
            // comboBox20Port
            // 
            this.comboBox20Port.FormattingEnabled = true;
            this.comboBox20Port.Location = new System.Drawing.Point(25, 24);
            this.comboBox20Port.Name = "comboBox20Port";
            this.comboBox20Port.Size = new System.Drawing.Size(109, 20);
            this.comboBox20Port.TabIndex = 15;
            this.comboBox20Port.Text = "-Serial Port-";
            // 
            // buttonKiosk20Disconnect
            // 
            this.buttonKiosk20Disconnect.Enabled = false;
            this.buttonKiosk20Disconnect.Location = new System.Drawing.Point(282, 23);
            this.buttonKiosk20Disconnect.Name = "buttonKiosk20Disconnect";
            this.buttonKiosk20Disconnect.Size = new System.Drawing.Size(108, 24);
            this.buttonKiosk20Disconnect.TabIndex = 14;
            this.buttonKiosk20Disconnect.Text = "Disconnect";
            this.buttonKiosk20Disconnect.UseVisualStyleBackColor = true;
            this.buttonKiosk20Disconnect.Click += new System.EventHandler(this.buttonKiosk20Disconnect_Click);
            // 
            // buttonKiosk20Connect
            // 
            this.buttonKiosk20Connect.Location = new System.Drawing.Point(154, 22);
            this.buttonKiosk20Connect.Name = "buttonKiosk20Connect";
            this.buttonKiosk20Connect.Size = new System.Drawing.Size(108, 24);
            this.buttonKiosk20Connect.TabIndex = 13;
            this.buttonKiosk20Connect.Text = "Connect";
            this.buttonKiosk20Connect.UseVisualStyleBackColor = true;
            this.buttonKiosk20Connect.Click += new System.EventHandler(this.buttonKiosk20Connect_Click);
            // 
            // buttonKiosk20Init
            // 
            this.buttonKiosk20Init.Enabled = false;
            this.buttonKiosk20Init.Location = new System.Drawing.Point(282, 66);
            this.buttonKiosk20Init.Name = "buttonKiosk20Init";
            this.buttonKiosk20Init.Size = new System.Drawing.Size(108, 24);
            this.buttonKiosk20Init.TabIndex = 12;
            this.buttonKiosk20Init.Text = "Initialize Cells";
            this.buttonKiosk20Init.UseVisualStyleBackColor = true;
            this.buttonKiosk20Init.Click += new System.EventHandler(this.buttonKiosk20Init_Click);
            // 
            // buttonKiosk20Braille
            // 
            this.buttonKiosk20Braille.Enabled = false;
            this.buttonKiosk20Braille.Location = new System.Drawing.Point(153, 68);
            this.buttonKiosk20Braille.Name = "buttonKiosk20Braille";
            this.buttonKiosk20Braille.Size = new System.Drawing.Size(109, 22);
            this.buttonKiosk20Braille.TabIndex = 10;
            this.buttonKiosk20Braille.Text = "Braille Data";
            this.buttonKiosk20Braille.UseVisualStyleBackColor = true;
            this.buttonKiosk20Braille.Click += new System.EventHandler(this.buttonKiosk20Braille_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.comboBox300Port);
            this.groupBox3.Controls.Add(this.buttonKiosk300Disconnect);
            this.groupBox3.Controls.Add(this.buttonKiosk300Connect);
            this.groupBox3.Controls.Add(this.buttonKiosk300Init);
            this.groupBox3.Controls.Add(this.buttonKiosk300Dtm);
            this.groupBox3.Controls.Add(this.buttonKiosk300Print);
            this.groupBox3.Location = new System.Drawing.Point(22, 226);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(417, 103);
            this.groupBox3.TabIndex = 10;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Kiosk 300 cells";
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
            this.buttonKiosk300Connect.Location = new System.Drawing.Point(154, 20);
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
            this.buttonKiosk300Init.Location = new System.Drawing.Point(282, 58);
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
            this.buttonKiosk300Dtm.Location = new System.Drawing.Point(153, 58);
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
            this.buttonKiosk300Print.Location = new System.Drawing.Point(25, 58);
            this.buttonKiosk300Print.Name = "buttonKiosk300Print";
            this.buttonKiosk300Print.Size = new System.Drawing.Size(109, 25);
            this.buttonKiosk300Print.TabIndex = 6;
            this.buttonKiosk300Print.Text = "Print Data";
            this.buttonKiosk300Print.UseVisualStyleBackColor = true;
            this.buttonKiosk300Print.Click += new System.EventHandler(this.buttonKiosk300Print_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.comboBox320Port);
            this.groupBox4.Controls.Add(this.buttonDotPad320Disconnect);
            this.groupBox4.Controls.Add(this.buttonDotPad320Connect);
            this.groupBox4.Controls.Add(this.buttonDotPad320Init);
            this.groupBox4.Controls.Add(this.buttonDotPad320Dtm);
            this.groupBox4.Controls.Add(this.buttonDotPad320Print);
            this.groupBox4.Location = new System.Drawing.Point(22, 340);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(417, 107);
            this.groupBox4.TabIndex = 11;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "DotPad 320 cells";
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
            this.buttonDotPad320Disconnect.Location = new System.Drawing.Point(282, 20);
            this.buttonDotPad320Disconnect.Name = "buttonDotPad320Disconnect";
            this.buttonDotPad320Disconnect.Size = new System.Drawing.Size(109, 24);
            this.buttonDotPad320Disconnect.TabIndex = 20;
            this.buttonDotPad320Disconnect.Text = "Disconnect";
            this.buttonDotPad320Disconnect.UseVisualStyleBackColor = true;
            this.buttonDotPad320Disconnect.Click += new System.EventHandler(this.buttonDotPad320Disconnect_Click);
            // 
            // buttonDotPad320Connect
            // 
            this.buttonDotPad320Connect.Location = new System.Drawing.Point(153, 20);
            this.buttonDotPad320Connect.Name = "buttonDotPad320Connect";
            this.buttonDotPad320Connect.Size = new System.Drawing.Size(109, 24);
            this.buttonDotPad320Connect.TabIndex = 19;
            this.buttonDotPad320Connect.Text = "Connect";
            this.buttonDotPad320Connect.UseVisualStyleBackColor = true;
            this.buttonDotPad320Connect.Click += new System.EventHandler(this.buttonDotPad320Connect_Click);
            // 
            // buttonDotPad320Init
            // 
            this.buttonDotPad320Init.Enabled = false;
            this.buttonDotPad320Init.Location = new System.Drawing.Point(282, 62);
            this.buttonDotPad320Init.Name = "buttonDotPad320Init";
            this.buttonDotPad320Init.Size = new System.Drawing.Size(109, 25);
            this.buttonDotPad320Init.TabIndex = 9;
            this.buttonDotPad320Init.Text = "Initicalize Cells";
            this.buttonDotPad320Init.UseVisualStyleBackColor = true;
            this.buttonDotPad320Init.Click += new System.EventHandler(this.buttonDotPad320Init_Click);
            // 
            // buttonDotPad320Dtm
            // 
            this.buttonDotPad320Dtm.Enabled = false;
            this.buttonDotPad320Dtm.Location = new System.Drawing.Point(153, 62);
            this.buttonDotPad320Dtm.Name = "buttonDotPad320Dtm";
            this.buttonDotPad320Dtm.Size = new System.Drawing.Size(109, 25);
            this.buttonDotPad320Dtm.TabIndex = 8;
            this.buttonDotPad320Dtm.Text = "Print DTM file";
            this.buttonDotPad320Dtm.UseVisualStyleBackColor = true;
            this.buttonDotPad320Dtm.Click += new System.EventHandler(this.buttonDotPad320Dtm_Click);
            // 
            // buttonDotPad320Print
            // 
            this.buttonDotPad320Print.Enabled = false;
            this.buttonDotPad320Print.Location = new System.Drawing.Point(25, 62);
            this.buttonDotPad320Print.Name = "buttonDotPad320Print";
            this.buttonDotPad320Print.Size = new System.Drawing.Size(109, 25);
            this.buttonDotPad320Print.TabIndex = 6;
            this.buttonDotPad320Print.Text = "Print Data";
            this.buttonDotPad320Print.UseVisualStyleBackColor = true;
            this.buttonDotPad320Print.Click += new System.EventHandler(this.buttonDotPad320Print_Click);
            // 
            // labelMessage
            // 
            this.labelMessage.BackColor = System.Drawing.Color.Gainsboro;
            this.labelMessage.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.labelMessage.ForeColor = System.Drawing.Color.Blue;
            this.labelMessage.Location = new System.Drawing.Point(22, 26);
            this.labelMessage.Name = "labelMessage";
            this.labelMessage.Size = new System.Drawing.Size(417, 20);
            this.labelMessage.TabIndex = 12;
            this.labelMessage.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(464, 468);
            this.Controls.Add(this.labelMessage);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Name = "MainForm";
            this.Text = "Demo App";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonKiosk20Braille;
        private System.Windows.Forms.Button buttonKiosk20Init;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button buttonKiosk300Init;
        private System.Windows.Forms.Button buttonKiosk300Dtm;
        private System.Windows.Forms.Button buttonKiosk300Print;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button buttonDotPad320Init;
        private System.Windows.Forms.Button buttonDotPad320Dtm;
        private System.Windows.Forms.Button buttonDotPad320Print;
        private System.Windows.Forms.Button buttonKiosk20Disconnect;
        private System.Windows.Forms.Button buttonKiosk20Connect;
        private System.Windows.Forms.ComboBox comboBox20Port;
        private System.Windows.Forms.ComboBox comboBox300Port;
        private System.Windows.Forms.Button buttonKiosk300Disconnect;
        private System.Windows.Forms.Button buttonKiosk300Connect;
        private System.Windows.Forms.ComboBox comboBox320Port;
        private System.Windows.Forms.Button buttonDotPad320Disconnect;
        private System.Windows.Forms.Button buttonDotPad320Connect;
        private System.Windows.Forms.Label labelMessage;
        private System.Windows.Forms.ComboBox comboBox_language;
        private System.Windows.Forms.TextBox textBox_braille;
    }
}

