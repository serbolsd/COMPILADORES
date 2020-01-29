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
        List<String> Token = new List<String>();
        List<String> symboltab = new List<String>();
        String str;
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
                sourceCodeBox.Text = data.Replace("\r\n", "\n").Replace("\n", Environment.NewLine);
                sourceData = sourceCodeBox.Text;
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
            TokensTable.Rows.Clear();
            TablaSymbolos.Rows.Clear();
        }

        private void compilarCompile_Click(object sender, EventArgs e)
        {
            Output.Text = "";
            TokensTable.Rows.Clear();
            TablaSymbolos.Rows.Clear();
            String [] compileOutput = compilador.compileProgram(sourceCodeBox.Text);
            // Output.Lines = compileOutput;
            Output.Text = compileOutput[0];
            if (compileOutput[2] != null)
            {
                Output.Text += "\r\n";
                //textBox2.Text += "\n\r";
                Output.Text += compileOutput[2];
            }
            else
            {
                Output.Text += "\r\n";
                //textBox2.Text += "\n\r";
                Output.Text += "no se detectaron errores";
            }
            String tokens = compileOutput[1];
            if (tokens != null)
            {
                for (int i = 0; i < tokens.Length; i++)
                {

                    if (tokens[i] != '\n')
                    {
                        str += tokens[i];
                        //i++;
                    }
                    if (tokens[i + 1] == '\n')
                    {
                        Token.Add(str);
                        str = "";
                        i++;
                    }
                    if (Token.Count == 3)
                    {
                        TokensTable.Rows.Add(Token[0], Token[1], Token[2]);

                        Token.Clear();
                    }
                }
            }
            String symbolTable = compileOutput[3];
            if (symbolTable != null)
            {
                for (int i = 0; i < symbolTable.Length; i++)
                {

                    if (symbolTable[i] != '\n')
                    {
                        str += symbolTable[i];
                        //i++;
                    }
                    if (symbolTable[i + 1] == '\n')
                    {
                        symboltab.Add(str);
                        str = "";
                        i++;
                    }
                    if (symboltab.Count == 6)
                    {
                        TablaSymbolos.Rows.Add(symboltab[0], symboltab[1], symboltab[2], symboltab[3], symboltab[4], symboltab[5]);

                        symboltab.Clear();
                    }
                }
            }
        }

        private void verGramáticaAyuda_Click(object sender, EventArgs e)
        {

        }

        private void sourceCodeBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
