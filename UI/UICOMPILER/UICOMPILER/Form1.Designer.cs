namespace UICOMPILER
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.sourceCodeBox = new System.Windows.Forms.TextBox();
            this.MenusBar = new System.Windows.Forms.MenuStrip();
            this.FileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.fileNuevo = new System.Windows.Forms.ToolStripMenuItem();
            this.AbrirFile = new System.Windows.Forms.ToolStripMenuItem();
            this.GuardarFile = new System.Windows.Forms.ToolStripMenuItem();
            this.GuardarComoFile = new System.Windows.Forms.ToolStripMenuItem();
            this.Salir = new System.Windows.Forms.ToolStripMenuItem();
            this.compileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.compilarCompile = new System.Windows.Forms.ToolStripMenuItem();
            this.AyudaMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.verGramáticaAyuda = new System.Windows.Forms.ToolStripMenuItem();
            this.Output = new System.Windows.Forms.TextBox();
            this.TablaSymbolos = new System.Windows.Forms.DataGridView();
            this.Line = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Category = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Length = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Data_Type = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.in_Function = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TokensTable = new System.Windows.Forms.DataGridView();
            this.LineTokens = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Lexem = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TypeTokens = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.FileNameTitle = new System.Windows.Forms.Label();
            this.MenusBar.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TablaSymbolos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TokensTable)).BeginInit();
            this.SuspendLayout();
            // 
            // sourceCodeBox
            // 
            this.sourceCodeBox.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.sourceCodeBox.Font = new System.Drawing.Font("Franklin Gothic Demi", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.sourceCodeBox.ForeColor = System.Drawing.Color.White;
            this.sourceCodeBox.Location = new System.Drawing.Point(12, 43);
            this.sourceCodeBox.Multiline = true;
            this.sourceCodeBox.Name = "sourceCodeBox";
            this.sourceCodeBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.sourceCodeBox.Size = new System.Drawing.Size(758, 378);
            this.sourceCodeBox.TabIndex = 0;
            this.sourceCodeBox.TextChanged += new System.EventHandler(this.sourceCodeBox_TextChanged);
            // 
            // MenusBar
            // 
            this.MenusBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.FileMenu,
            this.compileMenu,
            this.AyudaMenu});
            this.MenusBar.Location = new System.Drawing.Point(0, 0);
            this.MenusBar.Name = "MenusBar";
            this.MenusBar.Size = new System.Drawing.Size(1106, 24);
            this.MenusBar.TabIndex = 1;
            this.MenusBar.Text = "menuStrip1";
            // 
            // FileMenu
            // 
            this.FileMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileNuevo,
            this.AbrirFile,
            this.GuardarFile,
            this.GuardarComoFile,
            this.Salir});
            this.FileMenu.Name = "FileMenu";
            this.FileMenu.Size = new System.Drawing.Size(37, 20);
            this.FileMenu.Text = "File";
            // 
            // fileNuevo
            // 
            this.fileNuevo.Name = "fileNuevo";
            this.fileNuevo.Size = new System.Drawing.Size(180, 22);
            this.fileNuevo.Text = "Nuevo";
            this.fileNuevo.Click += new System.EventHandler(this.fileNuevo_Click);
            // 
            // AbrirFile
            // 
            this.AbrirFile.Name = "AbrirFile";
            this.AbrirFile.Size = new System.Drawing.Size(180, 22);
            this.AbrirFile.Text = "Abrir";
            this.AbrirFile.Click += new System.EventHandler(this.AbrirFile_Click);
            // 
            // GuardarFile
            // 
            this.GuardarFile.Name = "GuardarFile";
            this.GuardarFile.Size = new System.Drawing.Size(180, 22);
            this.GuardarFile.Text = "Guardar";
            this.GuardarFile.Click += new System.EventHandler(this.GuardarFile_Click);
            // 
            // GuardarComoFile
            // 
            this.GuardarComoFile.Name = "GuardarComoFile";
            this.GuardarComoFile.Size = new System.Drawing.Size(180, 22);
            this.GuardarComoFile.Text = "Guardar Como";
            this.GuardarComoFile.Click += new System.EventHandler(this.GuardarComoFile_Click);
            // 
            // Salir
            // 
            this.Salir.Name = "Salir";
            this.Salir.Size = new System.Drawing.Size(180, 22);
            this.Salir.Text = "Salir";
            this.Salir.Click += new System.EventHandler(this.Salir_Click);
            // 
            // compileMenu
            // 
            this.compileMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.compilarCompile});
            this.compileMenu.Name = "compileMenu";
            this.compileMenu.Size = new System.Drawing.Size(64, 20);
            this.compileMenu.Text = "Compile";
            // 
            // compilarCompile
            // 
            this.compilarCompile.Name = "compilarCompile";
            this.compilarCompile.Size = new System.Drawing.Size(123, 22);
            this.compilarCompile.Text = "Compilar";
            this.compilarCompile.Click += new System.EventHandler(this.compilarCompile_Click);
            // 
            // AyudaMenu
            // 
            this.AyudaMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.verGramáticaAyuda});
            this.AyudaMenu.Name = "AyudaMenu";
            this.AyudaMenu.Size = new System.Drawing.Size(53, 20);
            this.AyudaMenu.Text = "Ayuda";
            // 
            // verGramáticaAyuda
            // 
            this.verGramáticaAyuda.Name = "verGramáticaAyuda";
            this.verGramáticaAyuda.Size = new System.Drawing.Size(146, 22);
            this.verGramáticaAyuda.Text = "Ver gramática";
            this.verGramáticaAyuda.Click += new System.EventHandler(this.verGramáticaAyuda_Click);
            // 
            // Output
            // 
            this.Output.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.Output.Location = new System.Drawing.Point(12, 427);
            this.Output.Multiline = true;
            this.Output.Name = "Output";
            this.Output.ReadOnly = true;
            this.Output.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.Output.Size = new System.Drawing.Size(1082, 111);
            this.Output.TabIndex = 2;
            // 
            // TablaSymbolos
            // 
            this.TablaSymbolos.AllowUserToAddRows = false;
            this.TablaSymbolos.AllowUserToDeleteRows = false;
            this.TablaSymbolos.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.TablaSymbolos.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.TablaSymbolos.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Line,
            this.Name,
            this.Category,
            this.Length,
            this.Data_Type,
            this.in_Function});
            this.TablaSymbolos.Location = new System.Drawing.Point(12, 544);
            this.TablaSymbolos.Name = "TablaSymbolos";
            this.TablaSymbolos.ReadOnly = true;
            this.TablaSymbolos.Size = new System.Drawing.Size(1082, 106);
            this.TablaSymbolos.TabIndex = 3;
            // 
            // Line
            // 
            this.Line.HeaderText = "Line";
            this.Line.Name = "Line";
            this.Line.ReadOnly = true;
            // 
            // Name
            // 
            this.Name.HeaderText = "Name";
            this.Name.Name = "Name";
            this.Name.ReadOnly = true;
            // 
            // Category
            // 
            this.Category.HeaderText = "Category";
            this.Category.Name = "Category";
            this.Category.ReadOnly = true;
            // 
            // Length
            // 
            this.Length.HeaderText = "Length";
            this.Length.Name = "Length";
            this.Length.ReadOnly = true;
            // 
            // Data_Type
            // 
            this.Data_Type.HeaderText = "Data Type";
            this.Data_Type.Name = "Data_Type";
            this.Data_Type.ReadOnly = true;
            // 
            // in_Function
            // 
            this.in_Function.HeaderText = "in Function";
            this.in_Function.Name = "in_Function";
            this.in_Function.ReadOnly = true;
            // 
            // TokensTable
            // 
            this.TokensTable.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.TokensTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.TokensTable.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.LineTokens,
            this.Lexem,
            this.TypeTokens});
            this.TokensTable.Location = new System.Drawing.Point(777, 27);
            this.TokensTable.Name = "TokensTable";
            this.TokensTable.Size = new System.Drawing.Size(317, 394);
            this.TokensTable.TabIndex = 4;
            this.TokensTable.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.TokensTable_CellContentClick);
            // 
            // LineTokens
            // 
            this.LineTokens.FillWeight = 60.9137F;
            this.LineTokens.HeaderText = "Line";
            this.LineTokens.Name = "LineTokens";
            this.LineTokens.ReadOnly = true;
            // 
            // Lexem
            // 
            this.Lexem.FillWeight = 172.6754F;
            this.Lexem.HeaderText = "Lexem";
            this.Lexem.Name = "Lexem";
            this.Lexem.ReadOnly = true;
            // 
            // TypeTokens
            // 
            this.TypeTokens.FillWeight = 66.41091F;
            this.TypeTokens.HeaderText = "Type";
            this.TypeTokens.Name = "TypeTokens";
            this.TypeTokens.ReadOnly = true;
            // 
            // FileNameTitle
            // 
            this.FileNameTitle.AutoSize = true;
            this.FileNameTitle.Location = new System.Drawing.Point(13, 27);
            this.FileNameTitle.Name = "FileNameTitle";
            this.FileNameTitle.Size = new System.Drawing.Size(35, 13);
            this.FileNameTitle.TabIndex = 5;
            this.FileNameTitle.Text = "label1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1106, 662);
            this.Controls.Add(this.FileNameTitle);
            this.Controls.Add(this.TokensTable);
            this.Controls.Add(this.TablaSymbolos);
            this.Controls.Add(this.Output);
            this.Controls.Add(this.sourceCodeBox);
            this.Controls.Add(this.MenusBar);
            this.MainMenuStrip = this.MenusBar;
            //this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MenusBar.ResumeLayout(false);
            this.MenusBar.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TablaSymbolos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TokensTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox sourceCodeBox;
        private System.Windows.Forms.MenuStrip MenusBar;
        private System.Windows.Forms.ToolStripMenuItem FileMenu;
        private System.Windows.Forms.TextBox Output;
        private System.Windows.Forms.DataGridView TablaSymbolos;
        private System.Windows.Forms.DataGridViewTextBoxColumn Line;
        private System.Windows.Forms.DataGridViewTextBoxColumn Name;
        private System.Windows.Forms.DataGridViewTextBoxColumn Category;
        private System.Windows.Forms.DataGridViewTextBoxColumn Length;
        private System.Windows.Forms.DataGridViewTextBoxColumn Data_Type;
        private System.Windows.Forms.DataGridViewTextBoxColumn in_Function;
        private System.Windows.Forms.DataGridView TokensTable;
        private System.Windows.Forms.ToolStripMenuItem fileNuevo;
        private System.Windows.Forms.ToolStripMenuItem AbrirFile;
        private System.Windows.Forms.ToolStripMenuItem GuardarFile;
        private System.Windows.Forms.ToolStripMenuItem GuardarComoFile;
        private System.Windows.Forms.ToolStripMenuItem Salir;
        private System.Windows.Forms.ToolStripMenuItem compileMenu;
        private System.Windows.Forms.ToolStripMenuItem compilarCompile;
        private System.Windows.Forms.ToolStripMenuItem AyudaMenu;
        private System.Windows.Forms.ToolStripMenuItem verGramáticaAyuda;
        private System.Windows.Forms.DataGridViewTextBoxColumn LineTokens;
        private System.Windows.Forms.DataGridViewTextBoxColumn Lexem;
        private System.Windows.Forms.DataGridViewTextBoxColumn TypeTokens;
        private System.Windows.Forms.Label FileNameTitle;
    }
}

