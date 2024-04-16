using System;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Threading.Tasks;
using System.Diagnostics;

using ParticleEngine.Particle;
using static ParticleEngine.Tools.Forms;
using static ParticleEngine.Tools.Strings;
using static ParticleEngine.World.WorldGenerator;
using static ParticleEngine.Particle.ParticleManager;
using static ParticleEngine.Particle.ParticleRenderer;
using ParticleEngine.Scripts.Particle.Physics;
using System.Drawing;

namespace ParticleEngine
{

    public partial class ParticleMenu : Form
    {
        bool simulate = false;
        bool stopFiniteSim = false;

        const int particleSize = 3;
        const int rowSize = 480 / particleSize;
        const int columnSize = 1452 / particleSize;

        ParticleManager particleWorld = new ParticleManager(rowSize, columnSize);

        public ParticleMenu()
        {
            InitializeComponent();
        }

        Material selectedMaterial = Material.Air;
        MaterialType selectedMateralState = MaterialType.Gas;

        private void MainMenu_Load(object sender, EventArgs e)
        {
            Directory.CreateDirectory("worlds");

            foreach (string world in Directory.GetFiles("worlds"))
            {
                WorldsComboBox.Items.Add(Path.GetFileNameWithoutExtension(world));
            }

            simulate = true;
            Task.Run(() => RunInfiniteSim(1));

            selectedMaterial = Material.Sand;
            selectedMateralState = MaterialType.Solid;

            RenderPictureBox.Invalidate();
        }

        private void RenderPictureBox_Paint(object sender, PaintEventArgs e)
        {
            int result = RenderParticles(e, ref particleWorld, rowSize, columnSize, particleSize, PerformanceModeCheckBox.Checked);

            InfoLabel.Text = "Particles: " + result;
        }

        private void StepButton_Click(object sender, EventArgs e)
        {
            Step();
        }

        private void Step()
        {
            PhysicsManager.Step(rowSize, columnSize, ref particleWorld);

            RenderPictureBox.Invalidate();
        }

        private void RunButton_Click(object sender, EventArgs e)
        {
            int iterations = int.Parse(IterationsTextBox.Text);
            double delay = double.Parse(DelayTextBox.Text);

            Task.Run(() => RunFiniteSim(iterations, delay));
        }

        private void RunFiniteSim(int iterations, double delay)
        {
            for (int i = 0; i < iterations; i++)
            {
                if (stopFiniteSim)
                {
                    stopFiniteSim = false;
                    return;
                }
                
                WaitPrecise(delay);

                Step();
            }
        }

        private void RunInfiniteSim(double delay)
        {
            while (true)
            {
                if (simulate)
                {
                    WaitPrecise(delay);
                    Step();
                }
            }
        }

        private static void WaitPrecise(double durationMiliseconds)
        {
            var durationTicks = Math.Round((durationMiliseconds / 1000) * Stopwatch.Frequency);
            var sw = Stopwatch.StartNew();

            while (sw.ElapsedTicks < durationTicks)
            {

            }
        }

        private void GenerateNoiseButton_Click(object sender, EventArgs e)
        {
            particleWorld.particles = GenerateWorld(rowSize, columnSize);
            RenderPictureBox.Invalidate();
        }

        bool mouseDown = false;
        private void RenderPictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            mouseDown = true;
        }

        private void RenderPictureBox_MouseUp(object sender, MouseEventArgs e)
        {
            mouseDown = false;
        }

        private void RenderPictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (mouseDown && rowSize - 1 > e.Y / particleSize && e.Y / particleSize > 0 && columnSize - 1 > e.X / particleSize && e.X / particleSize > 0)
            {
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize - 1].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize - 1].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize - 1].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize + 1].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize + 1].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize, e.X / particleSize - 1].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize, e.X / particleSize - 1].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize, e.X / particleSize].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize, e.X / particleSize].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize, e.X / particleSize + 1].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize, e.X / particleSize + 1].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize + 1, e.X / particleSize - 1].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize + 1, e.X / particleSize - 1].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize + 1, e.X / particleSize].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize + 1, e.X / particleSize].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                particleWorld.particles[e.Y / particleSize + 1, e.X / particleSize + 1].material = selectedMaterial;
                particleWorld.particles[e.Y / particleSize + 1, e.X / particleSize + 1].materialType = selectedMateralState;
                particleWorld.particles[e.Y / particleSize - 1, e.X / particleSize].brightness = particleWorld.GenerateRandom(75, 100) / (float)100;

                RenderPictureBox.Invalidate();
            }
        }

        private void PauseButton_Click(object sender, EventArgs e)
        {
            if (simulate)
            {
                simulate = false;
                PauseButton.Text = "Resume Simulation";
            }
            else
            {
                simulate = true;
                PauseButton.Text = "Pause Simulation";
            }
        }

        private void AirButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Air;
            selectedMateralState = MaterialType.Gas;
        }

        private void StoneButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Stone;
            selectedMateralState = MaterialType.Solid;
        }

        private void SandButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Sand;
            selectedMateralState = MaterialType.Solid;
        }

        private void DirtButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Dirt;
            selectedMateralState = MaterialType.Solid;
        }

        private void GrassButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Grass;
            selectedMateralState = MaterialType.Solid;
        }

        private void WaterButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Water;
            selectedMateralState = MaterialType.Liquid;
        }

        private void GasolineButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Gasoline;
            selectedMateralState = MaterialType.Liquid;
        }

        private void FireButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Fire;
            selectedMateralState = MaterialType.Solid;
        }

        private void IceButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Ice;
            selectedMateralState = MaterialType.Liquid;
        }

        private void SmokeButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Smoke;
            selectedMateralState = MaterialType.Gas;
        }

        private void ToxicGasButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.ToxicGas;
            selectedMateralState = MaterialType.Gas;
        }

        private void FlammableGasButton_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.FlammableGas;
            selectedMateralState = MaterialType.Gas;
        }

        private void GenerateWorldButton_Click(object sender, EventArgs e)
        {
            particleWorld.particles = GenerateWorld(rowSize, columnSize);
            RenderPictureBox.Invalidate();
        }

        private void ClearWorldButton_Click(object sender, EventArgs e)
        {
            ClearWorld();
            RenderPictureBox.Invalidate();
        }

        private void ClearWorld()
        {
            for (int row = 0; row < rowSize; row++)
            {
                for (int column = 0; column < columnSize; column++)
                {
                    particleWorld.Clear(row, column);
                }
            }
        }

        private void PerformanceModeCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            RenderPictureBox.Invalidate();
        }

        private void SaveWorldButton_Click(object sender, EventArgs e)
        {
            simulate = false;
            PauseButton.Text = "Resume Simulation";

            StringBuilder sb = new StringBuilder();

            sb.Append(rowSize.ToString()).Append(',');
            sb.Append(columnSize.ToString());
            sb.Append('/');

            for (int row = 0; row < rowSize; row++)
            {
                for (int column = 0; column < columnSize; column++)
                {
                    sb.Append(particleWorld.particles[row, column].material).Append(',');
                    sb.Append(particleWorld.particles[row, column].materialType).Append(',');
                    sb.Append(particleWorld.particles[row, column].wetValue).Append(',');
                    sb.Append(particleWorld.particles[row, column].brightness).Append(',');
                    sb.Append(particleWorld.particles[row, column].intValue);
                    sb.Append('/');
                }
            }
            sb.Length--;

            File.WriteAllBytes("worlds\\" + WorldsComboBox.Text + ".world", CompressString(sb.ToString()));

            WorldsComboBox.Items.Clear();
            foreach (string world in Directory.GetFiles("worlds"))
            {
                WorldsComboBox.Items.Add(Path.GetFileNameWithoutExtension(world));
            }
        }

        private void LoadWorldButton_Click(object sender, EventArgs e)
        {
            simulate = false;
            PauseButton.Text = "Resume Simulation";

            string[] world = DecompressString(File.ReadAllBytes("worlds\\" + WorldsComboBox.Text + ".world")).Split('/');
            string[] sizeSettings = world[0].Split(',');
            int rows = int.Parse(sizeSettings[0]);
            int columns = int.Parse(sizeSettings[1]);

            int row = 0;
            int column = 0;

            ClearWorld();

            for (int i = 1; i < world.Length; i++)
            {
                if (column > columns - 1)
                {
                    column = 0;
                    row++;
                }

                string[] particle = world[i].Split(',');
                for (int j = 0; j < particle.Length; j++)
                {
                    particleWorld.particles[row, column].material = (Material)Enum.Parse(typeof(Material), particle[0]);
                    particleWorld.particles[row, column].materialType = (MaterialType)Enum.Parse(typeof(MaterialType), particle[1]);
                    particleWorld.particles[row, column].wetValue = float.Parse(particle[2]);
                    particleWorld.particles[row, column].brightness = float.Parse(particle[3]);
                    particleWorld.particles[row, column].intValue = int.Parse(particle[4]);
                }
                column++;
            }

            RenderPictureBox.Invalidate();
        }

        private void TitlebarPictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            MoveForm(Handle, e);
        }

        private void TitlebarPanel_MouseDown(object sender, MouseEventArgs e)
        {
            MoveForm(Handle, e);
        }

        private void CloseButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            stopFiniteSim = true;
        }

        private void StoneButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Stone;
            selectedMateralState = MaterialType.Solid;
        }

        private void SandButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Sand;
            selectedMateralState = MaterialType.Solid;
        }

        private void DirtButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Dirt;
            selectedMateralState = MaterialType.Solid;
        }

        private void GrassButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Grass;
            selectedMateralState = MaterialType.Solid;
        }

        private void WaterButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Water;
            selectedMateralState = MaterialType.Liquid;
        }

        private void IceButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Ice;
            selectedMateralState = MaterialType.Solid;
        }

        private void FireButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Fire;
            selectedMateralState = MaterialType.Liquid;
        }

        private void GasolineButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Gasoline;
            selectedMateralState = MaterialType.Liquid;
        }

        private void SmokeButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Smoke;
            selectedMateralState = MaterialType.Gas;
        }

        private void ToxicGasButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.ToxicGas;
            selectedMateralState = MaterialType.Gas;
        }

        private void FlammableGasButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.FlammableGas;
            selectedMateralState = MaterialType.Gas;
        }

        private void AirButtonLabel_Click(object sender, EventArgs e)
        {
            selectedMaterial = Material.Air;
            selectedMateralState = MaterialType.Gas;
        }

        private void StoneButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            StoneButtonLabel.ForeColor = Color.White;
        }

        private void StoneButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            StoneButtonLabel.ForeColor = Color.FromArgb(0, 160, 160, 160);
        }

        private void SandButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            SandButtonLabel.ForeColor = Color.White;
        }

        private void SandButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            SandButtonLabel.ForeColor = Color.FromArgb(0, 245, 228, 118);
        }

        private void DirtButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            DirtButtonLabel.ForeColor = Color.White;
        }

        private void DirtButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            DirtButtonLabel.ForeColor = Color.FromArgb(0, 77, 54, 15);
        }

        private void GrassButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            GrassButtonLabel.ForeColor = Color.White;
        }

        private void GrassButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            GrassButtonLabel.ForeColor = Color.FromArgb(0, 60, 110, 33);
        }

        private void WaterButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            WaterButtonLabel.ForeColor = Color.White;
        }

        private void WaterButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            WaterButtonLabel.ForeColor = Color.FromArgb(0, 72, 136, 240);
        }

        private void IceButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            IceButtonLabel.ForeColor = Color.White;
        }

        private void IceButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            IceButtonLabel.ForeColor = Color.FromArgb(0, 120, 212, 240);
        }

        private void FireButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            FireButtonLabel.ForeColor = Color.White;
        }

        private void FireButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            FireButtonLabel.ForeColor = Color.FromArgb(0, 255, 191, 0);
        }

        private void GasolineButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            GasolineButtonLabel.ForeColor = Color.White;
        }

        private void GasolineButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            GasolineButtonLabel.ForeColor = Color.FromArgb(0, 215, 219, 77);
        }

        private void SmokeButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            SmokeButtonLabel.ForeColor = Color.White;
        }

        private void SmokeButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            SmokeButtonLabel.ForeColor = Color.FromArgb(0, 180, 180, 180);
        }

        private void ToxicGasButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            ToxicGasButtonLabel.ForeColor = Color.White;
        }

        private void ToxicGasButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            ToxicGasButtonLabel.ForeColor = Color.FromArgb(0, 81, 97, 47);
        }

        private void FlammableGasButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            FlammableGasButtonLabel.ForeColor = Color.White;
        }

        private void FlammableGasButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            FlammableGasButtonLabel.ForeColor = Color.FromArgb(0, 156, 133, 81);
        }

        private void AirButtonLabel_MouseEnter(object sender, EventArgs e)
        {
            AirButtonLabel.ForeColor = Color.White;
        }

        private void AirButtonLabel_MouseLeave(object sender, EventArgs e)
        {
            AirButtonLabel.ForeColor = Color.FromArgb(0, 255, 255, 255);
        }
    }
}