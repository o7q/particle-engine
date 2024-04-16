using static ParticleEngine.Particle.ParticleManager;

namespace ParticleEngine.Particle.Physics.Materials
{
    public static class Gas
    {
        public static void Calculate(int row, int column, int rowSize, int columnSize, ref ParticleManager particleWorld, ref int[,] updatedVerticalParticles)
        {
            ParticleInstance self = particleWorld.particles[row, column];

            int randomJitter = particleWorld.GenerateRandom(0, 2);

            if (row > 0)
            {
                if (
                    particleWorld.particles[row - 1, column].material == Material.Air &&
                    particleWorld.particles[row, column].material == self.material &&
                    particleWorld.particles[row, column].intValue > 1)
                {
                    particleWorld.particles[row - 1, column] = self;
                    particleWorld.particles[row - 1, column].intValue = 0;
                    updatedVerticalParticles[row - 1, column] = 1;
                    particleWorld.Clear(row, column);
                }
                else
                {
                    particleWorld.particles[row, column].intValue++;
                }
            }

            if (column > 0 && randomJitter == 0)

            {
                if (
                    particleWorld.particles[row, column - 1].material == Material.Air &&
                    particleWorld.particles[row, column].material == self.material)
                {
                    particleWorld.particles[row, column - 1] = self;
                    updatedVerticalParticles[row, column - 1] = 1;
                    particleWorld.Clear(row, column);
                }
            }

            if (column < columnSize - 1 && randomJitter == 1)
            {
                if (
                    particleWorld.particles[row, column + 1].material == Material.Air &&
                    particleWorld.particles[row, column].material == self.material)
                {
                    particleWorld.particles[row, column + 1] = self;
                    updatedVerticalParticles[row, column + 1] = 1;
                    particleWorld.Clear(row, column);
                }
            }

            particleWorld.particles[row, column].intValue++;
            if (particleWorld.particles[row, column].intValue > 5000)
            {
                particleWorld.Clear(row, column);
            }

            if (particleWorld.particles[row, column].intValue % 1000 == 0)
            {
                if (particleWorld.particles[row, column].brightness > 0.1f)
                    particleWorld.particles[row, column].brightness -= 0.1f;
            }
        }
    }
}