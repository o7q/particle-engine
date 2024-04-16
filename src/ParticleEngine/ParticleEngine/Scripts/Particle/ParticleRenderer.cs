using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static ParticleEngine.Particle.ParticleManager;

namespace ParticleEngine.Particle
{
    public static class ParticleRenderer
    {
        public static int RenderParticles(PaintEventArgs e, ref ParticleManager particleWorld, int rowSize, int columnSize, int particleSize, bool performanceMode)
        {
            Graphics graphics = e.Graphics;

            SolidBrush drawBrush = new SolidBrush(Color.FromArgb(255, 255, 255, 255));

            int particleCount = 0;

            for (int row = 0; row < rowSize; row++)
            {
                for (int column = 0; column < columnSize; column++)
                {
                    int a = 0;
                    int r = 0;
                    int g = 0;
                    int b = 0;

                    bool draw = false;

                    float brightnessColor = particleWorld.particles[row, column].brightness;
                    float wetnessColor = particleWorld.particles[row, column].wetValue + 1;
                    switch (particleWorld.particles[row, column].material)
                    {
                        case Material.Stone:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(160 * brightnessColor);
                                g = (int)(160 * brightnessColor);
                                b = (int)(160 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 160;
                                g = 160;
                                b = 160;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.Sand:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(245 / wetnessColor * brightnessColor);
                                g = (int)(228 / wetnessColor * brightnessColor);
                                b = (int)(118 / wetnessColor * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 245;
                                g = 228;
                                b = 118;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.Sandstone:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(189 * brightnessColor);
                                g = (int)(176 * brightnessColor);
                                b = (int)(91 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 189;
                                g = 176;
                                b = 91;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.Dirt:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(77 / wetnessColor * brightnessColor);
                                g = (int)(54 / wetnessColor * brightnessColor);
                                b = (int)(15 / wetnessColor * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 77;
                                g = 54;
                                b = 15;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.Grass:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(60 * brightnessColor);
                                g = (int)(110 * brightnessColor);
                                b = (int)(33 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 60;
                                g = 110;
                                b = 33;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.RedFlower:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(255 * brightnessColor);
                                g = (int)(59 * brightnessColor);
                                b = (int)(59 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 255;
                                g = 59;
                                b = 59;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.PinkFlower:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(246 * brightnessColor);
                                g = (int)(122 * brightnessColor);
                                b = (int)(255 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 246;
                                g = 122;
                                b = 255;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.YellowFlower:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(255 * brightnessColor);
                                g = (int)(222 * brightnessColor);
                                b = (int)(92 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 255;
                                g = 222;
                                b = 92;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.BlueFlower:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(84 * brightnessColor);
                                g = (int)(178 * brightnessColor);
                                b = (int)(255 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 84;
                                g = 178;
                                b = 255;
                            }
                            particleCount++;
                            draw = true;
                            break;

                        case Material.Water:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(72 * brightnessColor);
                                g = (int)(136 * brightnessColor);
                                b = (int)(240 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 72;
                                g = 136;
                                b = 240;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.Gasoline:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(215 * brightnessColor);
                                g = (int)(219 * brightnessColor);
                                b = (int)(77 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 215;
                                g = 219;
                                b = 77;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.Fire:
                            if (!performanceMode)
                            {
                                double fireFlicker = particleWorld.GenerateRandom(5, 10) / (double)10;
                                a = 255;
                                r = (int)(255 * fireFlicker);
                                g = (int)(191 * fireFlicker);
                                b = (int)(0 * fireFlicker);
                            }
                            else
                            {
                                a = 255;
                                r = 255;
                                g = 191;
                                b = 0;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.Ice:
                            if (!performanceMode)
                            {
                                a = 255;
                                r = (int)(120 * brightnessColor);
                                g = (int)(212 * brightnessColor);
                                b = (int)(240 * brightnessColor);
                            }
                            else
                            {
                                a = 255;
                                r = 120;
                                g = 212;
                                b = 240;
                            }
                            particleCount++;
                            draw = true;
                            break;

                        case Material.Smoke:
                            if (!performanceMode)
                            {
                                a = 150;
                                r = (int)(180 * brightnessColor);
                                g = (int)(180 * brightnessColor);
                                b = (int)(180 * brightnessColor);
                            }
                            else
                            {
                                a = 150;
                                r = 180;
                                g = 180;
                                b = 180;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.ToxicGas:
                            if (!performanceMode)
                            {
                                a = 150;
                                r = (int)(81 * brightnessColor);
                                g = (int)(97 * brightnessColor);
                                b = (int)(47 * brightnessColor);
                            }
                            else
                            {
                                a = 150;
                                r = 81;
                                g = 97;
                                b = 47;
                            }
                            particleCount++;
                            draw = true;
                            break;
                        case Material.FlammableGas:
                            if (!performanceMode)
                            {
                                a = 150;
                                r = (int)(156 * brightnessColor);
                                g = (int)(133 * brightnessColor);
                                b = (int)(81 * brightnessColor);
                            }
                            else
                            {
                                a = 150;
                                r = 156;
                                g = 133;
                                b = 81;
                            }
                            particleCount++;
                            draw = true;
                            break;
                    }

                    if (draw)
                    {
                        drawBrush.Color = Color.FromArgb(a, r, g, b);
                        graphics.FillRectangle(drawBrush, column * particleSize, row * particleSize, particleSize, particleSize);
                    }
                }
            }

            return particleCount;
        }
    }
}