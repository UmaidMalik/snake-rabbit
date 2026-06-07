#version 100

precision mediump float;

uniform sampler2D texture0;
uniform float uTime;

varying vec2 fragTexCoord;

void main()
{
    vec2 uv = fragTexCoord;

    float scanline =
        sin((uv.y + uTime * 0.5) * 800.0) * 0.04;

    float offset = 1.0 / 200.0;

    float rCol =
        texture2D(texture0, uv + vec2(offset, 0.0)).r;

    float gCol =
        texture2D(texture0, uv).g;

    float bCol =
        texture2D(texture0, uv - vec2(offset, 0.0)).b;

    vec3 color = vec3(rCol, gCol, bCol);
    color -= scanline;

    gl_FragColor = vec4(color, 1.0);
}