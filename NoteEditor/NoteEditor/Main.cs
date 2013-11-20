using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NoteEditor
{
    public partial class Main : Form
    {
        string mp3FileName = string.Empty;
       
        int errorResult = 0;
        Fmod fmod = new Fmod();
        
        public Main()
        {
            InitializeComponent();
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            
        }

        private void 불러오기ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            string fileName = string.Empty;

            using (OpenFileDialog dlg = new OpenFileDialog())
            {
                dlg.InitialDirectory = AppDomain.CurrentDomain.BaseDirectory; // + "\\Music\\";
                dlg.Filter = "mp3 파일 (*.mp3)|*.mp3|모든 파일 (*.*)|*.*";
                dlg.FilterIndex = 1;
                dlg.RestoreDirectory = true;
 
                if (dlg.ShowDialog() != DialogResult.OK)
                {
                    return;
                }
                mp3FileName = dlg.FileName;
                mp3Label.Text = "음원 파일 : " + mp3FileName;

                // 재생 코드
                errorResult = fmod.System_Create();
                mp3Label.Text += "\r\n\rSystem Create Result : " + errorResult;

                errorResult = fmod.createSound(mp3FileName);
                mp3Label.Text += "           Sound Load Result : " + errorResult;

                errorResult = fmod.stopSound();
                mp3Label.Text += "\r\nSound Stop Result : " + errorResult;

                errorResult = fmod.playSound();
                mp3Label.Text += "           Sound Play Result : " + errorResult;

                errorResult = fmod.seekPosition(12000);
                mp3Label.Text += "\r\nData Seek Result : " + errorResult;

            }
            // FilenameTextbox.Text = openFileDialog1.FileName;
            // button3.Enabled = true; // So you dont play no file. lol
            
        }

        private void 종료ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
