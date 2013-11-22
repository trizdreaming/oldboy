using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
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
        uint totalTime = 0;
        
        public Main()
        {
            InitializeComponent();
            timeThread = new Thread(CountPlayingTime);
            timeThread.Start();

            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.DoubleBuffer, true);

            Paint += new PaintEventHandler(TestDraw);
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            Graphics g = pe.Graphics;
            g.SmoothingMode = SmoothingMode.HighQuality;
            // g.TranslateTransform(0, 0);

            DrawPosition(g);

            base.OnPaint(pe);
        }
        
        public delegate void SetTextCallback(string message);

        protected void TestDraw(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawRectangle(Pens.Green, 10, 100, 760, 20);
        }

        protected void DrawPosition(Graphics g)
        {
            if (totalTime < 1)
            {
                g.FillRectangle(new SolidBrush(Color.WhiteSmoke), 11, 101, 758, 18);
                return;
            }
            int tempTotal = (int)totalTime + 1;
            int totalLength = (int)((758) * playingTime / tempTotal);

            g.FillRectangle(new SolidBrush(Color.Red), 11, 101, totalLength, 18);
        }
        
        protected void DrawPosition(object sender, PaintEventArgs e)
        {
            if (totalTime < 1)
            {
                e.Graphics.FillRectangle(new SolidBrush(Color.WhiteSmoke), 11, 101, 759, 19);
                return;
            }
            int tempTotal = (int)totalTime + 1;
            int totalLength = (int)(759 * playingTime / tempTotal);

            e.Graphics.FillRectangle(new SolidBrush(Color.Red), 11, 101, totalLength, 19);
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
                totalTime = fmod.GetLength();
            }
        }

        private void CountPlayingTime()
        {
            while (true)
            {
                fmod.GetPosition(ref playingTime);
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

                    this.Invalidate();
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
        }

        private void Main_Load(object sender, EventArgs e)
        {

        }
    }
}
