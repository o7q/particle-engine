precision mediump float;

varying vec2 texCoord;
uniform sampler2D tex;

void main()
{
    gl_FragColor = texture2D(tex, (texCoord + 1.0) / 2.0); // Remap texture coordinates to range from 0 to 1
}