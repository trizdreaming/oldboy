using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Runtime.InteropServices;
// mp3 재생을 위한 추가

namespace NoteEditor
{
    public partial class Main : Form
    {
        // C코드로 작성된 DLL을 부르기 위함
        // C#에서 지원하는게 아니므로 네이티브 코드에서 작성된 코드를 활용
        [DllImport("winmm.dll")]
        // DLL 속에 있는 이 메소드를 사용하겠다.
        // 헤더파일(.h)에서 제공해 주는 것만 사용
        private static extern long mciSendString(string strCommand, StringBuilder strReturn, int iReturnLength, IntPtr hwndCallback);

        string mp3FileName = string.Empty;

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
                mciSendString("close MediaFile", null, 0, IntPtr.Zero);
                mciSendString("open \"" + mp3FileName + "\" type mpegvideo alias MediaFile", null, 0, IntPtr.Zero);
                mciSendString("play MediaFile", null, 0, IntPtr.Zero);
         
                // tbxFilePath.Text = mp3FileName;
                // 추가 한 파일 경로(및 이름)를 보여줌
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
