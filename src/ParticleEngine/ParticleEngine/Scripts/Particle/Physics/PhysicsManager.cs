using ParticleEngine.Particle;
using ParticleEngine.Particle.Physics.Materials;
using static ParticleEngine.Particle.ParticleManager;

namespace ParticleEngine.Scripts.Particle.Physics
{
    public class PhysicsManager
    {
        public static int[,] updatedVerticalParticles;

        public static void Step(int rowSize, int columnSize, ref ParticleManager particleWorld)
        {
            if (updatedVerticalParticles == null)
                updatedVerticalParticles = new int[rowSize, columnSize];

            for (int row = rowSize - 1; row >= 0; row--)
            {
                for (int column = columnSize - 1; column >= 0; column--)
                {
                    if (updatedVerticalParticles[row, column] == 1)
                    {
                        updatedVerticalParticles[row, column] = 0;
                        continue;
                    }

                    switch (particleWorld.particles[row, column].material)
                    {
                        case Material.Air:
                            break;
                        case Material.Sand:
                            Sand.Calculate(row, column, rowSize, columnSize, ref particleWorld);
                            break;
                        case Material.RedFlower:
                        case Material.PinkFlower:
                        case Material.YellowFlower:
                        case Material.BlueFlower:
                            SimpleGravity.Calculate(row, column, rowSize, columnSize, ref particleWorld);
                            break;
                        case Material.Grass:
                            Grass.Calculate(row, column, rowSize, columnSize, ref particleWorld);
                            break;
                        case Material.Dirt:
                            Dirt.Calculate(row, column, rowSize, columnSize, ref particleWorld);
                            break;
                        case Material.Water:
                        case Material.Gasoline:
                            Liquid.Calculate(row, column, rowSize, columnSize, ref particleWorld);
                            break;
                        case Material.Fire:
                            Fire.Calculate(row, column, rowSize, columnSize, ref particleWorld);
                            break;
                        case Material.Ice:
                            Ice.Calculate(row, column, rowSize, columnSize, ref particleWorld);
                            break;
                        case Material.Smoke:
                        case Material.ToxicGas:
                        case Material.FlammableGas:
                            Gas.Calculate(row, column, rowSize, columnSize, ref particleWorld, ref updatedVerticalParticles);
                            break;
                    }
                }
            }
        }
    }
}