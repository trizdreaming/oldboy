using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace NoteEditor
{
    public partial class Main : Form
    {
        string mp3FileName = string.Empty;
       
        int errorResult = 0;
        Fmod fmod = new Fmod();
        Thread timeThread;
        uint playingTime = 0;
        
        public Main()
        {
            InitializeComponent();
            timeThread = new Thread(CountPlayingTime);
            timeThread.Start();
        }

        public delegate void SetTextCallback(string message);

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
                if (errorResult != 0)
                {
                    mp3Label.Text = "Fmod 시스템 생성 실패 : " + errorResult;
                }

                errorResult = fmod.CreateSound(mp3FileName);
                if (errorResult != 0)
                {
                    mp3Label.Text = "사운드 로딩 실패 : " + errorResult;
                }

                errorResult = fmod.StopSound();

            }
        }

        private void CountPlayingTime()
        {
            while (true)
            {
                fmod.GetPosition(ref playingTime);
                // timeLabel.Text = "재생 시간 : " + playingTime + "ms";
                SetText("재생 시간 : " + playingTime + "ms");
            }
        }

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.timeLabel.InvokeRequired)
            {
                try
                {
                    SetTextCallback d = new SetTextCallback(SetText);
                    this.Invoke(d, new object[] { text });
                }
                catch
                {
                    if (timeThread.IsAlive)
                    {
                        timeThread.Abort();
                    }
                }
                
            }
            else
            {
                this.timeLabel.Text = text;
            }
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

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            errorResult = fmod.StopSound();
            errorResult = fmod.PlaySound();

            if (errorResult != 0)
            {
                mp3Label.Text = "음악 재생 실패 : " + errorResult;
            }
        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            errorResult = fmod.StopSound();
            playingTime = 0;
            // timeLabel.Text = "재생 시간 : " + playingTime + "ms";
        }
    }
}
