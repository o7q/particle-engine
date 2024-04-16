using System;
using System.Drawing;

namespace ParticleEngine.Particle
{
    public class ParticleManager
    {
        public enum Material
        {
            Air,

            Stone,
            Sand,
            Sandstone,
            Dirt,
            Grass,
            RedFlower,
            PinkFlower,
            YellowFlower,
            BlueFlower,

            Water,
            Gasoline,
            Fire,
            Ice,

            Smoke,
            ToxicGas,
            FlammableGas
        }

        public enum MaterialType
        {
            Solid,
            Liquid,
            Gas
        }

        public struct ParticleInstance
        {
            public Material material;
            public MaterialType materialType;
            public Color colorMultiplier;
            public float wetValue;
            public float brightness;
            public int intValue;
        }

        public ParticleInstance[,] particles;
        private Random random;
        private int randomCount = 0;

        public ParticleManager(int rows, int columns)
        {
            particles = new ParticleInstance[rows, columns];
            random = new Random();

            for (int row = 0; row < rows; row++)
            {
                for (int col = 0; col < columns; col++)
                {
                    Clear(row, col);
                }
            }
        }

        public void Clear(int row, int col)
        {
            particles[row, col].material = Material.Air;
            particles[row, col].materialType = MaterialType.Gas;
            particles[row, col].wetValue = 0.0f;
            particles[row, col].brightness = 1.0f;
            particles[row, col].intValue = 0;
        }

        public int GenerateRandom(int start, int end)
        {
            int randomNumber = random.Next(start, end);
            if (randomCount > 1000000)
            {
                random = new Random();
                randomCount = 0;
            }
            randomCount++;

            return randomNumber;
        }
    }
}