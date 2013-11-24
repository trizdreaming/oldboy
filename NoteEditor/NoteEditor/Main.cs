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
        static uint MAX_BLOCK = 760;

        string mp3FileName = string.Empty;
        int errorResult = 0;
        Fmod fmod = new Fmod();
        Thread timeThread, loudThread;
        uint playingTime = 0;
        uint totalTime = 0;
        uint leftLoud = 0;
        uint rightLoud = 0;
        uint[] leftLoudTable = new uint[MAX_BLOCK];
        uint[] rightLoudTable = new uint[MAX_BLOCK];
        uint delta = 0;
        Brush whiteBrush = new SolidBrush(Color.WhiteSmoke);
        Brush greenBrush = new SolidBrush(Color.Green);


        // 시스템의 소리를 컨트롤함
        SysSound sysSound = new SysSound();
        uint sysSoundTemp = 0;

        public Main()
        {
            InitializeComponent();
            
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.DoubleBuffer, true);

            Paint += new PaintEventHandler(TestDraw);
            
            errorResult = fmod.System_Create();
            if (errorResult != 0)
            {
                mp3Label.Text = "Fmod 시스템 생성 실패 : " + errorResult;
            }

            timeThread = new Thread(CountPlayingTime);
            timeThread.Start();
        }

        protected override void OnPaint(PaintEventArgs pe)
        {
            Graphics g = pe.Graphics;
            g.SmoothingMode = SmoothingMode.HighQuality;
            
            DrawPosition(g);
            DrawGraphs(g);

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
                g.FillRectangle(whiteBrush, 11, 101, 759, 18);
                return;
            }
            int tempTotal = (int)totalTime + 1;
            int totalLength = (int)((759) * playingTime / tempTotal);

            g.FillRectangle(greenBrush, 11, 101, totalLength, 18);
        }

        protected void DrawGraphs(Graphics g)
        {
            for (int i = 0; i < MAX_BLOCK; ++i)
            {
                if (i == (int)(760 * playingTime / (totalTime + 1)))
                {
                    g.DrawLine(Pens.Black, new PointF(10 + i, 140), new PointF(10 + i, 260));
                }
                else if (i < (int)(760 * playingTime / (totalTime + 1)))
                {
                    g.DrawLine(Pens.OrangeRed, new PointF(10 + i, 200), new PointF(10 + i, 200 - ((leftLoudTable[i] > 50) ? 50 : leftLoudTable[i])));
                    g.DrawLine(Pens.PaleVioletRed, new PointF(10 + i, 200), new PointF(10 + i, 200 + ((leftLoudTable[i] > 50) ? 50 : leftLoudTable[i])));
                }
                else
                {
                    g.DrawLine(Pens.BlueViolet, new PointF(10 + i, 200), new PointF(10 + i, 200 - ((leftLoudTable[i] > 50) ? 50 : leftLoudTable[i])));
                    g.DrawLine(Pens.DeepSkyBlue, new PointF(10 + i, 200), new PointF(10 + i, 200 + ((leftLoudTable[i] > 50) ? 50 : leftLoudTable[i])));
                }
                
            }
        }

        protected void DrawPosition(object sender, PaintEventArgs e)
        {
            if (totalTime < 1)
            {
                e.Graphics.FillRectangle(new SolidBrush(Color.WhiteSmoke), 11, 101, 760, 19);
                return;
            }
            int totalLength = (int)(760 * playingTime / (totalTime + 1));

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
                
                errorResult = fmod.CreateSound(mp3FileName);
                if (errorResult != 0)
                {
                    mp3Label.Text = "사운드 로딩 실패 : " + errorResult;
                }

                errorResult = fmod.StopSound();
                totalTime = fmod.GetLength();

                delta = (uint)(totalTime / MAX_BLOCK);

                errorResult = fmod.PlaySound();

                for (int i = 0; i < MAX_BLOCK; ++i)
                {
                    leftLoudTable[i] = 0;
                    rightLoudTable[i] = 0;
                }

                //sysSoundTemp = 4294967295;
                sysSoundTemp = sysSound.GetSystemVolume();
                sysSound.SetSystemVolume(0);

                loudThread = new Thread(CalcLoud);
                loudThread.Start();
            }
        }
        
        private void CalcLoud()
        {
            
            uint i = 0;
            while (i < MAX_BLOCK )
            {
                fmod.SetPosition(i * delta);
                fmod.GetLoud(ref leftLoud, ref rightLoud);

                leftLoudTable[i] = leftLoud;
                rightLoudTable[i++] = rightLoud;
                playingTime = i * delta;
                Thread.Sleep(20);
                this.Invalidate();
            }
            errorResult = fmod.StopSound();
            Thread.Sleep(200);
            sysSound.SetSystemVolume(sysSoundTemp);
        }

        private void CountPlayingTime()
        {
            while (true)
            {
                int result = 0;
                fmod.GetPosition(ref playingTime);
                result = fmod.GetLoud(ref leftLoud, ref rightLoud);
                SetTimeLabel("재생 시간 : " + playingTime + "ms    소리 크기 - L : " + leftLoud + " R : " + rightLoud + " 에러 검출 : " + result);
            }
        }

        private void SetTimeLabel(string text)
        {
            if (this.timeLabel.InvokeRequired)
            {
                try
                {
                    SetTextCallback d = new SetTextCallback(SetTimeLabel);
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

        private void loudTableLabel_Click(object sender, EventArgs e)
        {
        }

        private void button1_Click_1(object sender, EventArgs e)
        {

        }
    }
}
