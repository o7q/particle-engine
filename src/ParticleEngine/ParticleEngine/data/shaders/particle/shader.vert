attribute vec2 position;
varying vec2 texCoord;
uniform vec2 texSize;
uniform vec2 resolution;
uniform vec2 translation;
uniform float zoom;

void main()
{
    // Calculate aspect ratio
    float aspect = (resolution.x / resolution.y) * (texSize.y / texSize.x);
    vec2 scaledPosition = position;

    // Scale position to maintain aspect ratio
    if (aspect < 1.0)
    {
        scaledPosition = scaledPosition / vec2(1.0, 1.0 / aspect);
    }
    else
    {
        scaledPosition = scaledPosition / vec2(aspect, 1.0);
    }

    scaledPosition += (translation * vec2(-1.0, 1.0)) / resolution;
    scaledPosition *= zoom;
    
    // Assign scaled position to gl_Position
    gl_Position = vec4(scaledPosition, 0.0, 1.0);

    // Flip texture vertically
    texCoord = position * vec2(1.0, -1.0);
}