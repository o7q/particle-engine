namespace ParticleEngine
{
    partial class ParticleMenu
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.RenderPictureBox = new System.Windows.Forms.PictureBox();
            this.StepButton = new System.Windows.Forms.Button();
            this.RunButton = new System.Windows.Forms.Button();
            this.IterationsTextBox = new System.Windows.Forms.TextBox();
            this.DelayTextBox = new System.Windows.Forms.TextBox();
            this.InfoLabel = new System.Windows.Forms.Label();
            this.GenerateWorldButton = new System.Windows.Forms.Button();
            this.PauseButton = new System.Windows.Forms.Button();
            this.ClearWorldButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.PerformanceModeCheckBox = new System.Windows.Forms.CheckBox();
            this.SaveWorldButton = new System.Windows.Forms.Button();
            this.WorldsComboBox = new System.Windows.Forms.ComboBox();
            this.LoadWorldButton = new System.Windows.Forms.Button();
            this.TitlebarPanel = new System.Windows.Forms.Panel();
            this.CloseButton = new System.Windows.Forms.Button();
            this.TitlebarPictureBox = new System.Windows.Forms.PictureBox();
            this.StopButton = new System.Windows.Forms.Button();
            this.StoneButtonLabel = new System.Windows.Forms.Label();
            this.SandButtonLabel = new System.Windows.Forms.Label();
            this.DirtButtonLabel = new System.Windows.Forms.Label();
            this.GrassButtonLabel = new System.Windows.Forms.Label();
            this.WaterButtonLabel = new System.Windows.Forms.Label();
            this.IceButtonLabel = new System.Windows.Forms.Label();
            this.FireButtonLabel = new System.Windows.Forms.Label();
            this.GasolineButtonLabel = new System.Windows.Forms.Label();
            this.SmokeButtonLabel = new System.Windows.Forms.Label();
            this.ToxicGasButtonLabel = new System.Windows.Forms.Label();
            this.FlammableGasButtonLabel = new System.Windows.Forms.Label();
            this.AirButtonLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.RenderPictureBox)).BeginInit();
            this.TitlebarPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TitlebarPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // RenderPictureBox
            // 
            this.RenderPictureBox.BackColor = System.Drawing.Color.Black;
            this.RenderPictureBox.Location = new System.Drawing.Point(7, 40);
            this.RenderPictureBox.Name = "RenderPictureBox";
            this.RenderPictureBox.Size = new System.Drawing.Size(1452, 480);
            this.RenderPictureBox.TabIndex = 0;
            this.RenderPictureBox.TabStop = false;
            this.RenderPictureBox.Paint += new System.Windows.Forms.PaintEventHandler(this.RenderPictureBox_Paint);
            this.RenderPictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.RenderPictureBox_MouseDown);
            this.RenderPictureBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.RenderPictureBox_MouseMove);
            this.RenderPictureBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.RenderPictureBox_MouseUp);
            // 
            // StepButton
            // 
            this.StepButton.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.StepButton.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveCaption;
            this.StepButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.StepButton.ForeColor = System.Drawing.Color.Black;
            this.StepButton.Location = new System.Drawing.Point(1322, 580);
            this.StepButton.Name = "StepButton";
            this.StepButton.Size = new System.Drawing.Size(60, 26);
            this.StepButton.TabIndex = 1;
            this.StepButton.Text = "Step";
            this.StepButton.UseVisualStyleBackColor = false;
            this.StepButton.Click += new System.EventHandler(this.StepButton_Click);
            // 
            // RunButton
            // 
            this.RunButton.BackColor = System.Drawing.Color.OliveDrab;
            this.RunButton.FlatAppearance.BorderColor = System.Drawing.Color.OliveDrab;
            this.RunButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.RunButton.ForeColor = System.Drawing.Color.Black;
            this.RunButton.Location = new System.Drawing.Point(1382, 580);
            this.RunButton.Name = "RunButton";
            this.RunButton.Size = new System.Drawing.Size(60, 26);
            this.RunButton.TabIndex = 2;
            this.RunButton.Text = "Run";
            this.RunButton.UseVisualStyleBackColor = false;
            this.RunButton.Click += new System.EventHandler(this.RunButton_Click);
            // 
            // IterationsTextBox
            // 
            this.IterationsTextBox.BackColor = System.Drawing.Color.DarkOliveGreen;
            this.IterationsTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.IterationsTextBox.Location = new System.Drawing.Point(1383, 606);
            this.IterationsTextBox.Name = "IterationsTextBox";
            this.IterationsTextBox.Size = new System.Drawing.Size(59, 13);
            this.IterationsTextBox.TabIndex = 3;
            this.IterationsTextBox.Text = "20";
            // 
            // DelayTextBox
            // 
            this.DelayTextBox.BackColor = System.Drawing.Color.Orchid;
            this.DelayTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.DelayTextBox.Location = new System.Drawing.Point(1383, 619);
            this.DelayTextBox.Name = "DelayTextBox";
            this.DelayTextBox.Size = new System.Drawing.Size(59, 13);
            this.DelayTextBox.TabIndex = 4;
            this.DelayTextBox.Text = "1";
            // 
            // InfoLabel
            // 
            this.InfoLabel.AutoSize = true;
            this.InfoLabel.BackColor = System.Drawing.Color.Black;
            this.InfoLabel.ForeColor = System.Drawing.Color.Honeydew;
            this.InfoLabel.Location = new System.Drawing.Point(1318, 527);
            this.InfoLabel.Name = "InfoLabel";
            this.InfoLabel.Size = new System.Drawing.Size(59, 13);
            this.InfoLabel.TabIndex = 5;
            this.InfoLabel.Text = "Particles: 0";
            // 
            // GenerateWorldButton
            // 
            this.GenerateWorldButton.BackColor = System.Drawing.Color.LimeGreen;
            this.GenerateWorldButton.FlatAppearance.BorderColor = System.Drawing.Color.LimeGreen;
            this.GenerateWorldButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.GenerateWorldButton.Location = new System.Drawing.Point(943, 561);
            this.GenerateWorldButton.Name = "GenerateWorldButton";
            this.GenerateWorldButton.Size = new System.Drawing.Size(79, 37);
            this.GenerateWorldButton.TabIndex = 7;
            this.GenerateWorldButton.Text = "Generate World";
            this.GenerateWorldButton.UseVisualStyleBackColor = false;
            this.GenerateWorldButton.Click += new System.EventHandler(this.GenerateWorldButton_Click);
            // 
            // PauseButton
            // 
            this.PauseButton.BackColor = System.Drawing.Color.LightSalmon;
            this.PauseButton.FlatAppearance.BorderColor = System.Drawing.Color.LightSalmon;
            this.PauseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.PauseButton.Location = new System.Drawing.Point(1322, 557);
            this.PauseButton.Name = "PauseButton";
            this.PauseButton.Size = new System.Drawing.Size(120, 23);
            this.PauseButton.TabIndex = 8;
            this.PauseButton.Text = "Pause Simulation";
            this.PauseButton.UseVisualStyleBackColor = false;
            this.PauseButton.Click += new System.EventHandler(this.PauseButton_Click);
            // 
            // ClearWorldButton
            // 
            this.ClearWorldButton.BackColor = System.Drawing.Color.Salmon;
            this.ClearWorldButton.FlatAppearance.BorderColor = System.Drawing.Color.Salmon;
            this.ClearWorldButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ClearWorldButton.Location = new System.Drawing.Point(1022, 561);
            this.ClearWorldButton.Name = "ClearWorldButton";
            this.ClearWorldButton.Size = new System.Drawing.Size(79, 37);
            this.ClearWorldButton.TabIndex = 20;
            this.ClearWorldButton.Text = "Clear World";
            this.ClearWorldButton.UseVisualStyleBackColor = false;
            this.ClearWorldButton.Click += new System.EventHandler(this.ClearWorldButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.OliveDrab;
            this.label1.Location = new System.Drawing.Point(1322, 606);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 12);
            this.label1.TabIndex = 21;
            this.label1.Text = "Ticks To Run:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Orchid;
            this.label2.Location = new System.Drawing.Point(1351, 619);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(32, 12);
            this.label2.TabIndex = 22;
            this.label2.Text = "Delay:";
            // 
            // PerformanceModeCheckBox
            // 
            this.PerformanceModeCheckBox.AutoSize = true;
            this.PerformanceModeCheckBox.ForeColor = System.Drawing.Color.White;
            this.PerformanceModeCheckBox.Location = new System.Drawing.Point(1321, 540);
            this.PerformanceModeCheckBox.Name = "PerformanceModeCheckBox";
            this.PerformanceModeCheckBox.Size = new System.Drawing.Size(116, 17);
            this.PerformanceModeCheckBox.TabIndex = 23;
            this.PerformanceModeCheckBox.Text = "Performance Mode";
            this.PerformanceModeCheckBox.UseVisualStyleBackColor = true;
            this.PerformanceModeCheckBox.CheckedChanged += new System.EventHandler(this.PerformanceModeCheckBox_CheckedChanged);
            // 
            // SaveWorldButton
            // 
            this.SaveWorldButton.BackColor = System.Drawing.Color.LimeGreen;
            this.SaveWorldButton.FlatAppearance.BorderColor = System.Drawing.Color.LimeGreen;
            this.SaveWorldButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.SaveWorldButton.Location = new System.Drawing.Point(1163, 578);
            this.SaveWorldButton.Name = "SaveWorldButton";
            this.SaveWorldButton.Size = new System.Drawing.Size(75, 27);
            this.SaveWorldButton.TabIndex = 24;
            this.SaveWorldButton.Text = "Save World";
            this.SaveWorldButton.UseVisualStyleBackColor = false;
            this.SaveWorldButton.Click += new System.EventHandler(this.SaveWorldButton_Click);
            // 
            // WorldsComboBox
            // 
            this.WorldsComboBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.WorldsComboBox.FormattingEnabled = true;
            this.WorldsComboBox.Location = new System.Drawing.Point(1163, 557);
            this.WorldsComboBox.Name = "WorldsComboBox";
            this.WorldsComboBox.Size = new System.Drawing.Size(150, 21);
            this.WorldsComboBox.TabIndex = 25;
            // 
            // LoadWorldButton
            // 
            this.LoadWorldButton.BackColor = System.Drawing.Color.MediumTurquoise;
            this.LoadWorldButton.FlatAppearance.BorderColor = System.Drawing.Color.MediumTurquoise;
            this.LoadWorldButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.LoadWorldButton.Location = new System.Drawing.Point(1238, 578);
            this.LoadWorldButton.Name = "LoadWorldButton";
            this.LoadWorldButton.Size = new System.Drawing.Size(75, 27);
            this.LoadWorldButton.TabIndex = 26;
            this.LoadWorldButton.Text = "Load World";
            this.LoadWorldButton.UseVisualStyleBackColor = false;
            this.LoadWorldButton.Click += new System.EventHandler(this.LoadWorldButton_Click);
            // 
            // TitlebarPanel
            // 
            this.TitlebarPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.TitlebarPanel.Controls.Add(this.CloseButton);
            this.TitlebarPanel.Controls.Add(this.TitlebarPictureBox);
            this.TitlebarPanel.Location = new System.Drawing.Point(0, 0);
            this.TitlebarPanel.Name = "TitlebarPanel";
            this.TitlebarPanel.Size = new System.Drawing.Size(1467, 22);
            this.TitlebarPanel.TabIndex = 27;
            this.TitlebarPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TitlebarPanel_MouseDown);
            // 
            // CloseButton
            // 
            this.CloseButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.CloseButton.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(20)))), ((int)(((byte)(20)))), ((int)(((byte)(20)))));
            this.CloseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CloseButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(100)))), ((int)(((byte)(100)))));
            this.CloseButton.Location = new System.Drawing.Point(1445, 0);
            this.CloseButton.Name = "CloseButton";
            this.CloseButton.Size = new System.Drawing.Size(22, 22);
            this.CloseButton.TabIndex = 28;
            this.CloseButton.Text = "x";
            this.CloseButton.UseVisualStyleBackColor = false;
            this.CloseButton.Click += new System.EventHandler(this.CloseButton_Click);
            // 
            // TitlebarPictureBox
            // 
            this.TitlebarPictureBox.Image = global::ParticleEngine.Properties.Resources.header;
            this.TitlebarPictureBox.Location = new System.Drawing.Point(0, 3);
            this.TitlebarPictureBox.Name = "TitlebarPictureBox";
            this.TitlebarPictureBox.Size = new System.Drawing.Size(111, 16);
            this.TitlebarPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.TitlebarPictureBox.TabIndex = 28;
            this.TitlebarPictureBox.TabStop = false;
            this.TitlebarPictureBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TitlebarPictureBox_MouseDown);
            // 
            // StopButton
            // 
            this.StopButton.BackColor = System.Drawing.Color.LightSalmon;
            this.StopButton.FlatAppearance.BorderColor = System.Drawing.Color.LightSalmon;
            this.StopButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.StopButton.Location = new System.Drawing.Point(1209, 618);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(40, 23);
            this.StopButton.TabIndex = 30;
            this.StopButton.Text = "Stop";
            this.StopButton.UseVisualStyleBackColor = false;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // StoneButtonLabel
            // 
            this.StoneButtonLabel.AutoSize = true;
            this.StoneButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.StoneButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(160)))), ((int)(((byte)(160)))), ((int)(((byte)(160)))));
            this.StoneButtonLabel.Location = new System.Drawing.Point(7, 525);
            this.StoneButtonLabel.Name = "StoneButtonLabel";
            this.StoneButtonLabel.Size = new System.Drawing.Size(57, 20);
            this.StoneButtonLabel.TabIndex = 31;
            this.StoneButtonLabel.Text = "Stone";
            this.StoneButtonLabel.Click += new System.EventHandler(this.StoneButtonLabel_Click);
            this.StoneButtonLabel.MouseEnter += new System.EventHandler(this.StoneButtonLabel_MouseEnter);
            this.StoneButtonLabel.MouseLeave += new System.EventHandler(this.StoneButtonLabel_MouseLeave);
            // 
            // SandButtonLabel
            // 
            this.SandButtonLabel.AutoSize = true;
            this.SandButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.SandButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(245)))), ((int)(((byte)(228)))), ((int)(((byte)(118)))));
            this.SandButtonLabel.Location = new System.Drawing.Point(59, 525);
            this.SandButtonLabel.Name = "SandButtonLabel";
            this.SandButtonLabel.Size = new System.Drawing.Size(51, 20);
            this.SandButtonLabel.TabIndex = 32;
            this.SandButtonLabel.Text = "Sand";
            this.SandButtonLabel.Click += new System.EventHandler(this.SandButtonLabel_Click);
            this.SandButtonLabel.MouseEnter += new System.EventHandler(this.SandButtonLabel_MouseEnter);
            this.SandButtonLabel.MouseLeave += new System.EventHandler(this.SandButtonLabel_MouseLeave);
            // 
            // DirtButtonLabel
            // 
            this.DirtButtonLabel.AutoSize = true;
            this.DirtButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DirtButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(77)))), ((int)(((byte)(54)))), ((int)(((byte)(15)))));
            this.DirtButtonLabel.Location = new System.Drawing.Point(106, 526);
            this.DirtButtonLabel.Name = "DirtButtonLabel";
            this.DirtButtonLabel.Size = new System.Drawing.Size(38, 20);
            this.DirtButtonLabel.TabIndex = 33;
            this.DirtButtonLabel.Text = "Dirt";
            this.DirtButtonLabel.Click += new System.EventHandler(this.DirtButtonLabel_Click);
            this.DirtButtonLabel.MouseEnter += new System.EventHandler(this.DirtButtonLabel_MouseEnter);
            this.DirtButtonLabel.MouseLeave += new System.EventHandler(this.DirtButtonLabel_MouseLeave);
            // 
            // GrassButtonLabel
            // 
            this.GrassButtonLabel.AutoSize = true;
            this.GrassButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.GrassButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(110)))), ((int)(((byte)(33)))));
            this.GrassButtonLabel.Location = new System.Drawing.Point(140, 526);
            this.GrassButtonLabel.Name = "GrassButtonLabel";
            this.GrassButtonLabel.Size = new System.Drawing.Size(57, 20);
            this.GrassButtonLabel.TabIndex = 34;
            this.GrassButtonLabel.Text = "Grass";
            this.GrassButtonLabel.Click += new System.EventHandler(this.GrassButtonLabel_Click);
            this.GrassButtonLabel.MouseEnter += new System.EventHandler(this.GrassButtonLabel_MouseEnter);
            this.GrassButtonLabel.MouseLeave += new System.EventHandler(this.GrassButtonLabel_MouseLeave);
            // 
            // WaterButtonLabel
            // 
            this.WaterButtonLabel.AutoSize = true;
            this.WaterButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.WaterButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(72)))), ((int)(((byte)(136)))), ((int)(((byte)(240)))));
            this.WaterButtonLabel.Location = new System.Drawing.Point(8, 543);
            this.WaterButtonLabel.Name = "WaterButtonLabel";
            this.WaterButtonLabel.Size = new System.Drawing.Size(57, 20);
            this.WaterButtonLabel.TabIndex = 35;
            this.WaterButtonLabel.Text = "Water";
            this.WaterButtonLabel.Click += new System.EventHandler(this.WaterButtonLabel_Click);
            this.WaterButtonLabel.MouseEnter += new System.EventHandler(this.WaterButtonLabel_MouseEnter);
            this.WaterButtonLabel.MouseLeave += new System.EventHandler(this.WaterButtonLabel_MouseLeave);
            // 
            // IceButtonLabel
            // 
            this.IceButtonLabel.AutoSize = true;
            this.IceButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.IceButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(120)))), ((int)(((byte)(212)))), ((int)(((byte)(240)))));
            this.IceButtonLabel.Location = new System.Drawing.Point(62, 543);
            this.IceButtonLabel.Name = "IceButtonLabel";
            this.IceButtonLabel.Size = new System.Drawing.Size(34, 20);
            this.IceButtonLabel.TabIndex = 36;
            this.IceButtonLabel.Text = "Ice";
            this.IceButtonLabel.Click += new System.EventHandler(this.IceButtonLabel_Click);
            this.IceButtonLabel.MouseEnter += new System.EventHandler(this.IceButtonLabel_MouseEnter);
            this.IceButtonLabel.MouseLeave += new System.EventHandler(this.IceButtonLabel_MouseLeave);
            // 
            // FireButtonLabel
            // 
            this.FireButtonLabel.AutoSize = true;
            this.FireButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.FireButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(191)))), ((int)(((byte)(0)))));
            this.FireButtonLabel.Location = new System.Drawing.Point(90, 543);
            this.FireButtonLabel.Name = "FireButtonLabel";
            this.FireButtonLabel.Size = new System.Drawing.Size(40, 20);
            this.FireButtonLabel.TabIndex = 37;
            this.FireButtonLabel.Text = "Fire";
            this.FireButtonLabel.Click += new System.EventHandler(this.FireButtonLabel_Click);
            this.FireButtonLabel.MouseEnter += new System.EventHandler(this.FireButtonLabel_MouseEnter);
            this.FireButtonLabel.MouseLeave += new System.EventHandler(this.FireButtonLabel_MouseLeave);
            // 
            // GasolineButtonLabel
            // 
            this.GasolineButtonLabel.AutoSize = true;
            this.GasolineButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.GasolineButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(215)))), ((int)(((byte)(219)))), ((int)(((byte)(77)))));
            this.GasolineButtonLabel.Location = new System.Drawing.Point(125, 544);
            this.GasolineButtonLabel.Name = "GasolineButtonLabel";
            this.GasolineButtonLabel.Size = new System.Drawing.Size(80, 20);
            this.GasolineButtonLabel.TabIndex = 38;
            this.GasolineButtonLabel.Text = "Gasoline";
            this.GasolineButtonLabel.Click += new System.EventHandler(this.GasolineButtonLabel_Click);
            this.GasolineButtonLabel.MouseEnter += new System.EventHandler(this.GasolineButtonLabel_MouseEnter);
            this.GasolineButtonLabel.MouseLeave += new System.EventHandler(this.GasolineButtonLabel_MouseLeave);
            // 
            // SmokeButtonLabel
            // 
            this.SmokeButtonLabel.AutoSize = true;
            this.SmokeButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.SmokeButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(180)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))));
            this.SmokeButtonLabel.Location = new System.Drawing.Point(8, 561);
            this.SmokeButtonLabel.Name = "SmokeButtonLabel";
            this.SmokeButtonLabel.Size = new System.Drawing.Size(64, 20);
            this.SmokeButtonLabel.TabIndex = 39;
            this.SmokeButtonLabel.Text = "Smoke";
            this.SmokeButtonLabel.Click += new System.EventHandler(this.SmokeButtonLabel_Click);
            this.SmokeButtonLabel.MouseEnter += new System.EventHandler(this.SmokeButtonLabel_MouseEnter);
            this.SmokeButtonLabel.MouseLeave += new System.EventHandler(this.SmokeButtonLabel_MouseLeave);
            // 
            // ToxicGasButtonLabel
            // 
            this.ToxicGasButtonLabel.AutoSize = true;
            this.ToxicGasButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.ToxicGasButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(81)))), ((int)(((byte)(97)))), ((int)(((byte)(47)))));
            this.ToxicGasButtonLabel.Location = new System.Drawing.Point(67, 562);
            this.ToxicGasButtonLabel.Name = "ToxicGasButtonLabel";
            this.ToxicGasButtonLabel.Size = new System.Drawing.Size(88, 20);
            this.ToxicGasButtonLabel.TabIndex = 40;
            this.ToxicGasButtonLabel.Text = "Toxic Gas";
            this.ToxicGasButtonLabel.Click += new System.EventHandler(this.ToxicGasButtonLabel_Click);
            this.ToxicGasButtonLabel.MouseEnter += new System.EventHandler(this.ToxicGasButtonLabel_MouseEnter);
            this.ToxicGasButtonLabel.MouseLeave += new System.EventHandler(this.ToxicGasButtonLabel_MouseLeave);
            // 
            // FlammableGasButtonLabel
            // 
            this.FlammableGasButtonLabel.AutoSize = true;
            this.FlammableGasButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.FlammableGasButtonLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(156)))), ((int)(((byte)(133)))), ((int)(((byte)(81)))));
            this.FlammableGasButtonLabel.Location = new System.Drawing.Point(149, 562);
            this.FlammableGasButtonLabel.Name = "FlammableGasButtonLabel";
            this.FlammableGasButtonLabel.Size = new System.Drawing.Size(134, 20);
            this.FlammableGasButtonLabel.TabIndex = 41;
            this.FlammableGasButtonLabel.Text = "Flammable Gas";
            this.FlammableGasButtonLabel.Click += new System.EventHandler(this.FlammableGasButtonLabel_Click);
            this.FlammableGasButtonLabel.MouseEnter += new System.EventHandler(this.FlammableGasButtonLabel_MouseEnter);
            this.FlammableGasButtonLabel.MouseLeave += new System.EventHandler(this.FlammableGasButtonLabel_MouseLeave);
            // 
            // AirButtonLabel
            // 
            this.AirButtonLabel.AutoSize = true;
            this.AirButtonLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold);
            this.AirButtonLabel.ForeColor = System.Drawing.Color.White;
            this.AirButtonLabel.Location = new System.Drawing.Point(11, 580);
            this.AirButtonLabel.Name = "AirButtonLabel";
            this.AirButtonLabel.Size = new System.Drawing.Size(31, 20);
            this.AirButtonLabel.TabIndex = 43;
            this.AirButtonLabel.Text = "Air";
            this.AirButtonLabel.Click += new System.EventHandler(this.AirButtonLabel_Click);
            this.AirButtonLabel.MouseEnter += new System.EventHandler(this.AirButtonLabel_MouseEnter);
            this.AirButtonLabel.MouseLeave += new System.EventHandler(this.AirButtonLabel_MouseLeave);
            // 
            // ParticleMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(1467, 652);
            this.Controls.Add(this.AirButtonLabel);
            this.Controls.Add(this.FlammableGasButtonLabel);
            this.Controls.Add(this.ToxicGasButtonLabel);
            this.Controls.Add(this.SmokeButtonLabel);
            this.Controls.Add(this.GasolineButtonLabel);
            this.Controls.Add(this.FireButtonLabel);
            this.Controls.Add(this.IceButtonLabel);
            this.Controls.Add(this.WaterButtonLabel);
            this.Controls.Add(this.GrassButtonLabel);
            this.Controls.Add(this.DirtButtonLabel);
            this.Controls.Add(this.SandButtonLabel);
            this.Controls.Add(this.StoneButtonLabel);
            this.Controls.Add(this.StopButton);
            this.Controls.Add(this.TitlebarPanel);
            this.Controls.Add(this.LoadWorldButton);
            this.Controls.Add(this.WorldsComboBox);
            this.Controls.Add(this.SaveWorldButton);
            this.Controls.Add(this.PerformanceModeCheckBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ClearWorldButton);
            this.Controls.Add(this.PauseButton);
            this.Controls.Add(this.GenerateWorldButton);
            this.Controls.Add(this.InfoLabel);
            this.Controls.Add(this.DelayTextBox);
            this.Controls.Add(this.IterationsTextBox);
            this.Controls.Add(this.RunButton);
            this.Controls.Add(this.StepButton);
            this.Controls.Add(this.RenderPictureBox);
            this.ForeColor = System.Drawing.Color.Black;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "ParticleMenu";
            this.Text = "particle engine";
            this.Load += new System.EventHandler(this.MainMenu_Load);
            ((System.ComponentModel.ISupportInitialize)(this.RenderPictureBox)).EndInit();
            this.TitlebarPanel.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.TitlebarPictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox RenderPictureBox;
        private System.Windows.Forms.Button StepButton;
        private System.Windows.Forms.Button RunButton;
        private System.Windows.Forms.TextBox IterationsTextBox;
        private System.Windows.Forms.TextBox DelayTextBox;
        private System.Windows.Forms.Label InfoLabel;
        private System.Windows.Forms.Button GenerateWorldButton;
        private System.Windows.Forms.Button PauseButton;
        private System.Windows.Forms.Button ClearWorldButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox PerformanceModeCheckBox;
        private System.Windows.Forms.Button SaveWorldButton;
        private System.Windows.Forms.ComboBox WorldsComboBox;
        private System.Windows.Forms.Button LoadWorldButton;
        private System.Windows.Forms.Panel TitlebarPanel;
        private System.Windows.Forms.PictureBox TitlebarPictureBox;
        private System.Windows.Forms.Button CloseButton;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.Label StoneButtonLabel;
        private System.Windows.Forms.Label SandButtonLabel;
        private System.Windows.Forms.Label DirtButtonLabel;
        private System.Windows.Forms.Label GrassButtonLabel;
        private System.Windows.Forms.Label WaterButtonLabel;
        private System.Windows.Forms.Label IceButtonLabel;
        private System.Windows.Forms.Label FireButtonLabel;
        private System.Windows.Forms.Label GasolineButtonLabel;
        private System.Windows.Forms.Label SmokeButtonLabel;
        private System.Windows.Forms.Label ToxicGasButtonLabel;
        private System.Windows.Forms.Label FlammableGasButtonLabel;
        private System.Windows.Forms.Label AirButtonLabel;
    }
}

