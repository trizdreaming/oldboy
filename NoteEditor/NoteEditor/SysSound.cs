using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
namespace NoteEditor
{
    class SysSound
    {
        [DllImport("winmm.dll")]
        public static extern int waveOutGetVolume(IntPtr hwo, out uint dwVolume);

        [DllImport("winmm.dll")]
        public static extern int waveOutSetVolume(IntPtr hwo, uint dwVolume);


        public uint GetSystemVolume()
        {
            // By the default set the volume to 0
            uint CurrVol = 0;
            // At this point, CurrVol gets assigned the volume
            waveOutGetVolume(IntPtr.Zero, out CurrVol);
            // Calculate the volume
            //ushort CalcVol = (ushort)(CurrVol & 0x0000ffff);

            return CurrVol;
        }

        public void SetSystemVolume(uint NewVolume)
        {
            //int NewVolume = 50;
            // Set the same volume for both the left and the right channels
            uint NewVolumeAllChannels = ((NewVolume & 0x0000ffff) | (NewVolume << 16));
            // Set the volume
            waveOutSetVolume(IntPtr.Zero, NewVolumeAllChannels);
        }
    }
}
