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
        // DLLImport to Initialize FMOD
        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_Create")]
        public static extern int FMOD_System_Create(ref IntPtr fmodSystem);
        // FMOD_RESULT F_API FMOD_System_Create (FMOD_SYSTEM **system);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_Init")]
        public static extern int FMOD_System_Init (IntPtr fmodSystem, int maxChannels, uint flags, IntPtr extraDriverData);
        // FMOD_RESULT F_API FMOD_System_Init (FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_CreateSound")]
        public static extern int FMOD_System_CreateSound (IntPtr fmodSystem, String soundName, int mode, IntPtr info, ref IntPtr sound);
        // FMOD_RESULT F_API FMOD_System_CreateSound (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_PlaySound")]
        public static extern int FMOD_System_PlaySound( IntPtr fmodSystem, int channelId, IntPtr sound, bool paused, ref IntPtr channel);

        // FMOD_RESULT F_API FMOD_System_PlaySound (FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);


        string mp3FileName = string.Empty;
        IntPtr fmodSystem;
        IntPtr info;
        IntPtr sound;
        IntPtr nullptr;
        IntPtr chan;
        int errorResult = 0;
        
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
                errorResult = FMOD_System_Create(ref fmodSystem);
                mp3Label.Text += "\r\n\rSystem Create Result : " + errorResult;

                errorResult = FMOD_System_Init(fmodSystem, 2, 0, nullptr);
                mp3Label.Text += "\r\nSystem Initialize Result : " + errorResult;

                errorResult = FMOD_System_CreateSound(fmodSystem, mp3FileName, 0, info, ref sound);
                mp3Label.Text += "\r\nSound Load Result : " + errorResult;

                errorResult = FMOD_System_PlaySound(fmodSystem, -1, sound, false, ref chan);
                mp3Label.Text += "\r\nSound Play Result : " + errorResult;

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
