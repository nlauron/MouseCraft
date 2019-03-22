#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
uniform vec3 color;
uniform mat4 transform;
uniform mat4 invTransform;
uniform int textureID;

out vec3 fragNormal;
out vec2 fragTexCoord;
out vec3 fragPos;

void main()
{
    vec4 pos = transform * vec4(position, 1.0);
    fragPos = pos.xyz;
    fragNormal = (invTransform * vec4(normal, 1.0)).xyz;
    fragTexCoord = texCoord;
    gl_Position = pos;
}