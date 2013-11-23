using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Runtime.InteropServices;
// mp3 재생을 위한 추가

namespace NoteEditor
{
    class Fmod
    {
        // DLLImport to Initialize FMOD
        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_Create")]
        private static extern int FMOD_System_Create(ref IntPtr fmodSystem);
        // FMOD_RESULT F_API FMOD_System_Create (FMOD_SYSTEM **system);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_Release")]
        private static extern int FMOD_System_Release(ref IntPtr fmodSystem);
        // FMOD_RESULT F_API FMOD_System_Release (FMOD_SYSTEM *system); 

        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_Init")]
        private static extern int FMOD_System_Init(IntPtr fmodSystem, int maxChannels, uint flags, IntPtr extraDriverData);
        // FMOD_RESULT F_API FMOD_System_Init (FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_CreateSound")]
        private static extern int FMOD_System_CreateSound(IntPtr fmodSystem, String soundName, int mode, IntPtr info, ref IntPtr sound);
        // FMOD_RESULT F_API FMOD_System_CreateSound (FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);

        // FMOD_RESULT F_API FMOD_Sound_Release (FMOD_SOUND *sound);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_System_PlaySound")]
        private static extern int FMOD_System_PlaySound(IntPtr fmodSystem, int channelId, IntPtr sound, bool paused, ref IntPtr chan);
        // FMOD_RESULT F_API FMOD_System_PlaySound (FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_Channel_Stop")]
        private static extern int FMOD_Channel_Stop(IntPtr chan);
        // FMOD_RESULT F_API FMOD_Channel_Stop (FMOD_CHANNEL *channel);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_Channel_SetPosition")]
        private static extern int FMOD_Channel_SetPosition(IntPtr chan, uint position, uint postype);
        // FMOD_RESULT F_API FMOD_Channel_SetPosition (FMOD_CHANNEL *channel, unsigned int position, FMOD_TIMEUNIT postype);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_Channel_GetPosition")]
        private static extern int FMOD_Channel_GetPosition(IntPtr chan, ref uint position, uint postype);
        // FMOD_RESULT F_API FMOD_Channel_GetPosition (FMOD_CHANNEL *channel, unsigned int *position, FMOD_TIMEUNIT postype);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_Sound_GetLength")]
        private static extern int FMOD_Sound_GetLength(IntPtr sound, ref uint length, uint postype);
        // FMOD_RESULT F_API FMOD_Sound_GetLength (FMOD_SOUND *sound, unsigned int *length, FMOD_TIMEUNIT lengthtype);

        [DllImport("fmodex.dll", EntryPoint = "FMOD_Channel_GetSpectrum")]
        private static extern int FMOD_Channel_GetSpectrum(IntPtr chan, float[] spectrumArray, int numValues, int channelOffset, int windowType);
        // FMOD_RESULT F_API FMOD_Channel_GetSpectrum (FMOD_CHANNEL *channel, float *spectrumarray, int numvalues, int channeloffset, FMOD_DSP_FFT_WINDOW windowtype);

        // FMOD_RESULT F_API FMOD_Channel_SetMute (FMOD_CHANNEL *channel, FMOD_BOOL mute);

        // FMOD_RESULT F_API FMOD_Channel_SetPaused (FMOD_CHANNEL *channel, FMOD_BOOL paused);

        // FMOD_RESULT F_API FMOD_Channel_GetPaused (FMOD_CHANNEL *channel, FMOD_BOOL *paused);

        private IntPtr fmodSystem;
        private IntPtr sound;
        private IntPtr chan;
        private IntPtr info;
        private IntPtr nullptr;

        public int System_Create()
        {
            int errorResult = FMOD_System_Create(ref fmodSystem);
            
            if (errorResult != 0)
                return errorResult;

            errorResult = FMOD_System_Init(fmodSystem, 2, 0, nullptr);

            if (errorResult != 0)
                FMOD_System_Release(ref fmodSystem);
            
            return errorResult;
        }

        public int CreateSound(String fileName)
        {
            return FMOD_System_CreateSound(fmodSystem, fileName, 0, info, ref sound);
        }

        public int PlaySound()
        {
            return FMOD_System_PlaySound(fmodSystem, -1, sound, false, ref chan);
        }

        public int StopSound()
        {
            return FMOD_Channel_Stop(chan);
        }

        public int GetPosition(ref uint position)
        {
            return FMOD_Channel_GetPosition(chan, ref position, 1);
        }

        public int SetPosition(uint position)
        {
            return FMOD_Channel_SetPosition(chan, position, 1);
        }

        public uint GetLength()
        {
            uint length = 0;
            int errorResult = FMOD_Sound_GetLength(sound, ref length, 1);

            if (errorResult != 0)
                length = 0;

            return length;
        }

        public int GetLoud(ref uint leftLoud, ref uint rightLoud)
        {
            float[] spectrumArrayLeft = new float[64];
            float[] spectrumArrayRight = new float[64];

            leftLoud = 0;
            rightLoud = 0;

            int errorResult = FMOD_Channel_GetSpectrum(chan, spectrumArrayLeft, 64, 0, 0);
            if (errorResult != 0)
            {
                errorResult += 10000;
            }

            errorResult = FMOD_Channel_GetSpectrum(chan, spectrumArrayRight, 64, 1, 0);
            if (errorResult != 0)
            {
                errorResult += 10000;
            }

            for (int i = 0; i < 64; ++i)
            {
                leftLoud += (spectrumArrayLeft[i] > 0) ? (uint) (spectrumArrayLeft[i] * 25) : 0;
                rightLoud += (spectrumArrayRight[i] > 0) ? (uint) (spectrumArrayRight[i] * 25) : 0;
            }

            if (leftLoud == 0)
                leftLoud += rightLoud;
            if (rightLoud == 0)
                rightLoud += leftLoud;

            return errorResult;
        }

    }
}
