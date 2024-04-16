using System;
using static ParticleEngine.Particle.ParticleManager;

namespace ParticleEngine.World
{
    public static class WorldGenerator
    {
        const int groundLayerSmooth = 30;
        const int groundHeight = -30;
        const int caveAmount = 20;
        const int caveMinLength = 200;
        const int caveMaxLength = 10000;
        const int caveGroundLevelDistance = 10;

        public static ParticleInstance[,] GenerateWorld(int rows, int columns)
        {
            Random random = new Random();

            int[,] noisyWorld = new int[rows, columns];
            int[,] convolutedWorld = new int[rows, columns];

            int[] noisyGroundLayer = new int[columns];
            int[] convolutedGroundLayer = new int[columns];

            double[] groundLayerKernel = { 0.1, 0.2, 0.4, 0.2, 0.1 };

            for (int i = 0; i < columns; i++)
            {
                noisyGroundLayer[i] = random.Next(256) / groundLayerSmooth - groundHeight;

                bool shouldGenMountain = random.Next(101) < 2;
                if (shouldGenMountain)
                {
                    int mountainStart = random.Next(columns - 1);
                    int mountainEnd = random.Next(mountainStart, columns - 1);

                    for (int j = mountainStart; j < mountainEnd; j++)
                    {
                        noisyGroundLayer[j] = random.Next(100);
                    }
                }
            }

            for (int i = 0; i < columns; i++)
            {
                double groundLayerConvolution = 0;

                for (int j = 0; j < groundLayerKernel.Length; j++)
                {
                    int colIndex = Math.Min(i + j, columns - 1);

                    groundLayerConvolution += noisyGroundLayer[colIndex] * groundLayerKernel[j];
                }

                convolutedGroundLayer[i] = (int)groundLayerConvolution;
            }

            double[,] worldSmoothKernel = new double[10, 10];

            for (int row = 0; row < 10; row++)
            {
                for (int column = 0; column < 10; column++)
                {
                    worldSmoothKernel[row, column] = 0.015;
                }
            }

            int[] heightmapColors = { 152, 194, 232 };
            for (int row = 0; row < rows - 1; row++)
            {
                for (int column = 0; column < columns - 1; column++)
                {
                    noisyWorld[row, column] = random.Next(256);
                }
            }

            for (int row = 0; row < rows - 1; row++)
            {
                for (int column = 0; column < columns - 1; column++)
                {
                    double worldSmoothConvolution = 0;
                    for (int kernel_row = 0; kernel_row < worldSmoothKernel.GetLength(0); kernel_row++)
                    {
                        for (int kernel_column = 0; kernel_column < worldSmoothKernel.GetLength(1); kernel_column++)
                        {
                            int rowIndex = Math.Min(
                                    Math.Max(row + kernel_row - worldSmoothKernel.GetLength(0) / 2, 0),
                                    rows - 1
                                );
                            int colIndex = Math.Min(
                                    Math.Max(column + kernel_column - worldSmoothKernel.GetLength(1) / 2, 0),
                                    columns - 1
                                );
                            worldSmoothConvolution += noisyWorld[rowIndex, colIndex] * worldSmoothKernel[kernel_row, kernel_column];
                        }
                    }

                    convolutedWorld[row, column] = (int)worldSmoothConvolution;
                }
            }

            ParticleInstance[,] world = new ParticleInstance[rows, columns];
            int[,] quantizedConvolutedNoise = new int[rows, columns];

            for (int row = 0; row < rows - 1; row++)
            {
                for (int column = 0; column < columns - 1; column++)
                {
                    double closestDistance = double.MaxValue;
                    int closestIndex = 0;

                    for (int i = 0; i < heightmapColors.Length; i++)
                    {
                        double distance = Math.Sqrt(Math.Pow(convolutedWorld[row, column] - heightmapColors[i], 2));

                        if (distance < closestDistance)
                        {
                            closestDistance = distance;
                            closestIndex = i;
                        }
                    }

                    quantizedConvolutedNoise[row, column] = heightmapColors[closestIndex];

                    switch (quantizedConvolutedNoise[row, column])
                    {
                        case 152:
                            world[row, column].material = Material.Stone;
                            world[row, column].materialType = MaterialType.Solid;
                            world[row, column].brightness = random.Next(9, 11) / (float)10;
                            break;

                        case 194:
                            world[row, column].material = Material.Dirt;
                            world[row, column].materialType = MaterialType.Solid;
                            world[row, column].brightness = random.Next(9, 11) / (float)10;
                            break;

                        case 232:
                            world[row, column].material = Material.Water;
                            world[row, column].materialType = MaterialType.Liquid;
                            world[row, column].brightness = random.Next(9, 11) / (float)10;
                            break;
                    }
                }
            }

            // cut out terrain
            for (int column = 0; column < columns - 1; column++)
            {
                int bumboclat = convolutedGroundLayer[column];

                int bumboclat2 = Math.Min(bumboclat, rows);

                for (int row = bumboclat2 - 1; row >= 0; row--)
                {
                    world[row, column].material = Material.Air;
                    world[row, column].materialType = MaterialType.Gas;
                    world[row, column].brightness = random.Next(9, 11) / (float)10;
                }
            }

            // generate caves
            for (int i = 0; i < caveAmount; i++)
            {
                int x = random.Next(columns);
                int y = rows - 1;

                for (int j = 0; j < random.Next(caveMinLength, caveMaxLength); j++)
                {
                    int direction = random.Next(4);

                    if (y < -groundHeight + caveGroundLevelDistance && -groundHeight + caveGroundLevelDistance < rows - 1)
                        y++;

                    switch (direction)
                    {
                        case 0:
                            if (x < columns - 1)
                            {
                                world[y, x].material = Material.ToxicGas;
                                world[y, x].materialType = MaterialType.Gas;
                                world[y, x].brightness = random.Next(9, 11) / (float)10;
                                x++;
                            }
                            break;
                        case 1:
                            if (x > 0)
                            {
                                world[y, x].material = Material.ToxicGas;
                                world[y, x].materialType = MaterialType.Gas;
                                world[y, x].brightness = random.Next(9, 11) / (float)10;
                                x--;
                            }
                            break;
                        case 2:
                            if (y < rows - 1)
                            {
                                world[y, x].material = Material.ToxicGas;
                                world[y, x].materialType = MaterialType.Gas;
                                world[y, x].brightness = random.Next(9, 11) / (float)10;
                                y++;
                            }
                            break;
                        case 3:
                            if (y > 0)
                            {
                                world[y, x].material = Material.ToxicGas;
                                world[y, x].materialType = MaterialType.Gas;
                                world[y, x].brightness = random.Next(9, 11) / (float)10;
                                y--;
                            }
                            break;
                    }

                    if (y > 0)
                    {
                        world[y - 1, x].material = Material.Smoke;
                        world[y - 1, x].materialType = MaterialType.Gas;
                        world[y - 1, x].brightness = random.Next(9, 11) / (float)10;
                    }
                }
            }

            return world;
        }
    }
}