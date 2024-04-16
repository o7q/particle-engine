using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static ParticleEngine.Particle.ParticleManager;

namespace ParticleEngine.Particle.Physics.Materials
{
    public static class Dirt
    {
        public static void Calculate(int row, int column, int rowSize, int columnSize, ref ParticleManager particleWorld)
        {
            ParticleInstance self = particleWorld.particles[row, column];

            if (row - 1 > 0)
            {
                if (particleWorld.particles[row - 1, column].materialType == MaterialType.Liquid &&
                    particleWorld.particles[row, column].wetValue <= 1.0f)
                {
                    particleWorld.particles[row, column].wetValue += 0.1f;
                }

                if (particleWorld.particles[row - 1, column].material == Material.Water &&
                    particleWorld.particles[row, column].wetValue >= 0.9f)
                {
                    particleWorld.particles[row, column].material = Material.Grass;
                }
            }

            if (column - 1 > 0)
            {
                if (particleWorld.particles[row, column - 1].materialType == MaterialType.Liquid &&
                    particleWorld.particles[row, column].wetValue <= 0.5f)
                {
                    particleWorld.particles[row, column].wetValue += 0.05f;
                }
            }

            if (column < columnSize - 1)
            {
                if (particleWorld.particles[row, column + 1].materialType == MaterialType.Liquid &&
                    particleWorld.particles[row, column].wetValue <= 0.5f)
                {
                    particleWorld.particles[row, column].wetValue += 0.05f;
                }
            }

            if (row < rowSize - 1)
            {
                if (
                    (particleWorld.particles[row + 1, column].materialType == MaterialType.Gas ||
                    particleWorld.particles[row + 1, column].material == Material.Water) &&
                    particleWorld.particles[row, column].material == self.material)
                {
                    particleWorld.particles[row + 1, column] = self;
                    particleWorld.Clear(row, column);
                }
            }

            if (column > 0 && row < rowSize - 1)
            {
                if (
                    (particleWorld.particles[row + 1, column - 1].materialType == MaterialType.Liquid ||
                    particleWorld.particles[row + 1, column - 1].materialType == MaterialType.Gas) &&
                    particleWorld.particles[row, column - 1].material == Material.Air &&
                    particleWorld.particles[row, column].material == self.material)
                {

                    particleWorld.particles[row + 1, column - 1] = self;
                    particleWorld.Clear(row, column);
                }
            }

            if (column < columnSize - 1 && row < rowSize - 1)
            {
                if (
                    (particleWorld.particles[row + 1, column + 1].materialType == MaterialType.Liquid ||
                    particleWorld.particles[row + 1, column + 1].materialType == MaterialType.Gas) &&
                    particleWorld.particles[row, column + 1].material == Material.Air &&
                    particleWorld.particles[row, column].material == self.material)
                {
                    particleWorld.particles[row + 1, column + 1] = self;
                    particleWorld.Clear(row, column);
                }
            }
        }
    }
}