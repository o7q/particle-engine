using static ParticleEngine.Particle.ParticleManager;

namespace ParticleEngine.Particle.Physics.Materials
{
    public static class Liquid
    {
        public static void Calculate(int row, int column, int rowSize, int columnSize, ref ParticleManager particleWorld)
        {
            ParticleInstance self = particleWorld.particles[row, column];

            if (row < rowSize - 1)
            {
                if (
                    (particleWorld.particles[row + 1, column].material == Material.Air ||
                    particleWorld.particles[row + 1, column].materialType == MaterialType.Gas) &&
                    particleWorld.particles[row, column].material == self.material)
                {
                    particleWorld.particles[row + 1, column] = self;
                    particleWorld.Clear(row, column);
                }
            }

            if (column > 0)
            {
                if (
                    (particleWorld.particles[row, column - 1].material == Material.Air ||
                    particleWorld.particles[row, column - 1].materialType == MaterialType.Gas) &&
                    particleWorld.particles[row, column].material == self.material)
                {
                    particleWorld.particles[row, column - 1] = self;
                    particleWorld.Clear(row, column);
                }
            }

            if (column < columnSize - 1)
            {
                if (
                    (particleWorld.particles[row, column + 1].material == Material.Air ||
                    particleWorld.particles[row, column + 1].materialType == MaterialType.Gas) &&
                    particleWorld.particles[row, column].material == self.material)
                {
                    particleWorld.particles[row, column + 1] = self;
                    particleWorld.Clear(row, column);
                }
            }
        }
    }
}