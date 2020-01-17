using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Reflection;
using System.Resources;
using System.Diagnostics;
using System.Management;
using System.Windows.Forms;

namespace UICOMPILER
{
    public partial class Form1 : Form
    {
        Compiler.Manager compilador;
        string actualFile="";
        string sourceData="";

        public Form1()
        {
            InitializeComponent();
            FileNameTitle.Text = "";
            compilador = new Compiler.Manager();
        }
        private void saveChanges()
        {
            if (sourceCodeBox.Text != "" && sourceData != sourceCodeBox.Text)
            {
                string mesg = "¿desea guardar los cambios?";
                string name = "CompilerUI";
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                DialogResult result = MessageBox.Show(mesg, name, buttons);
                if (result == DialogResult.Yes)
                {
                    FileSave();
                }
            }
        }
        private void FileSaveAs()
        {
            SaveFileDialog guardarComo = new SaveFileDialog();
            guardarComo.Filter = "Text File|*.txt|CPP File|*.cpp";
            guardarComo.Title = "Guardar Como...";
            guardarComo.FileName = actualFile;
            if(guardarComo.ShowDialog()==DialogResult.OK)
            {
                using (StreamWriter Data = new StreamWriter(guardarComo.OpenFile()))
                {
                    string text = sourceCodeBox.Text;
                    sourceData = text;
                    Data.Write(text);
                    Data.Close();
                }
                actualFile = guardarComo.FileName;
                FileNameTitle.Text = Path.GetFileName(guardarComo.FileName);
            }
        }
        private void FileSave()
        {
            if (File.Exists(actualFile))
            {
                TextWriter file= new StreamWriter(actualFile);
                file.Write(sourceCodeBox.Text);
                sourceData = sourceCodeBox.Text;
                file.Close();
            }
            else
            {
                FileSaveAs();
            }
        }
        private void OpenFile()
        {
            saveChanges();
            OpenFileDialog archivo = new OpenFileDialog();
            if (archivo.ShowDialog() == DialogResult.OK)
            {
                actualFile = archivo.FileName;
                string data = File.ReadAllText(archivo.FileName);
                sourceCodeBox.Text = data;
                sourceData = data;
                FileNameTitle.Text = Path.GetFileName(archivo.FileName);
                //label4.Text = Path.GetFileName(archivo.FileName);
                //dataGridView1.Rows.Clear();
                //dataGridView2.Rows.Clear();

            }
        }
        private void NewFile()
        {
            saveChanges();
            // Do something
            SaveFileDialog newFile = new SaveFileDialog();
            newFile.Filter = "Text File|*.txt|CPP File|*.cpp";
            newFile.Title = "New File...";
            if (newFile.ShowDialog() == DialogResult.OK)
            {
                using (StreamWriter Data = new StreamWriter(newFile.OpenFile()))
                {
                    Data.Write("");
                    sourceData = "";
                    Data.Close();
                }
                actualFile = newFile.FileName;
                FileNameTitle.Text = Path.GetFileName(newFile.FileName);
                clear();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void TokensTable_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void fileNuevo_Click(object sender, EventArgs e)
        {
            NewFile();
        }

        private void AbrirFile_Click(object sender, EventArgs e)
        {
            OpenFile();
        }

        private void GuardarFile_Click(object sender, EventArgs e)
        {
            FileSave();
        }

        private void GuardarComoFile_Click(object sender, EventArgs e)
        {
            FileSaveAs();
        }

        private void Salir_Click(object sender, EventArgs e)
        {
            if (sourceCodeBox.Text != "")
            {
                FileSave();
            }
            if (System.Windows.Forms.Application.MessageLoop)
            {
                // WinForms app
                System.Windows.Forms.Application.Exit();
            }
            else
            {
                // Console app
                System.Environment.Exit(1);
            }
        }

        private void clear()
        {
            sourceCodeBox.Text = "";
            Output.Text = "";
        }

        private void compilarCompile_Click(object sender, EventArgs e)
        {
            clear();
            String [] compileOutput = compilador.compileProgram(sourceCodeBox.Text);
            Output.Lines = compileOutput;
        }

        private void verGramáticaAyuda_Click(object sender, EventArgs e)
        {

        }

        private void sourceCodeBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
