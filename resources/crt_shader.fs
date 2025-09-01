#version 330

uniform sampler2D texture0;
uniform float uTime;
in vec2 fragTexCoord;
out vec4 finalColor;

void main() {
    vec2 uv = fragTexCoord;

    // Screen curvature
    // uv = uv * 2.0 - 1.0;
    // uv *= vec2(1.1, 1.1);
    // float r = dot(uv, uv);
    // uv = uv * (1.0 + r * 0.1);
    // uv = (uv + 1.0) / 2.0;


    // Scanlines
    //float scanline = sin(uv.y * 800.0) * 0.04;
    float scanline = sin((uv.y + uTime * 0.5) * 800.0) * 0.04;

    // Color offset simulation (very subtle here)
    float offset = 1.0 / 300.0;
    float rCol = texture(texture0, uv + vec2(offset, 0.0)).r;
    float gCol = texture(texture0, uv).g;
    float bCol = texture(texture0, uv - vec2(offset, 0.0)).b;

    vec3 color = vec3(rCol, gCol, bCol);

    // Combine with scanlines
    color -= scanline;

    finalColor = vec4(color, 1.0);
}