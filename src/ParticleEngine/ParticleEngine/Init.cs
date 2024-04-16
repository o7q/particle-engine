using System;
using System.Windows.Forms;

namespace ParticleEngine
{
    internal static class Init
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new ParticleMenu());
        }
    }
}