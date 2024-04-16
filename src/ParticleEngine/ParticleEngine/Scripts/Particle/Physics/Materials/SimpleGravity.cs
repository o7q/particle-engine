using static ParticleEngine.Particle.ParticleManager;

namespace ParticleEngine.Particle.Physics.Materials
{
    public static class SimpleGravity
    {
        public static void Calculate(int row, int column, int rowSize, int columnSize, ref ParticleManager particleWorld)
        {
            ParticleInstance self = particleWorld.particles[row, column];

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
        }
    }
}