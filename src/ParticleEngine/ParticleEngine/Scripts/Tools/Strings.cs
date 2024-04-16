using System.IO;
using System.IO.Compression;
using System.Text;

namespace ParticleEngine.Tools
{
    public static class Strings
    {
        public static byte[] CompressString(string inputString)
        {
            try
            {
                byte[] sourceFileBytes = Encoding.UTF8.GetBytes(inputString);

                using (MemoryStream compressedMemoryStream = new MemoryStream())
                {
                    using (GZipStream compressionStream = new GZipStream(compressedMemoryStream, CompressionMode.Compress))
                    {
                        compressionStream.Write(sourceFileBytes, 0, sourceFileBytes.Length);
                    }

                    byte[] compressedData = compressedMemoryStream.ToArray();

                    return compressedData;
                }
            }
            catch
            {
                return Encoding.UTF8.GetBytes("");
            }
        }

        public static string DecompressString(byte[] compressedString)
        {
            try
            {
                using (MemoryStream compressedMemoryStream = new MemoryStream(compressedString))
                {
                    using (MemoryStream decompressedMemoryStream = new MemoryStream())
                    {
                        using (GZipStream decompressionStream = new GZipStream(compressedMemoryStream, CompressionMode.Decompress))
                        {
                            decompressionStream.CopyTo(decompressedMemoryStream);
                        }

                        byte[] decompressedBytes = decompressedMemoryStream.ToArray();
                        return Encoding.UTF8.GetString(decompressedBytes);
                    }
                }
            }
            catch
            {
                return "";
            }
        }
    }
}
