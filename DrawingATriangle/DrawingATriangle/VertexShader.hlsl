cbuffer ConstantBuffer
{
    float3 Offset;
};


struct VOut
{
    float4 position : SV_Position;
    float4 color : COLOR;
};



//vertex shader
VOut main(float4 position : POSITION, float4 color : COLOR)
{
    VOut output;
    output.position = position;
    output.position.x += Offset.x;
    output.position.y += Offset.y;
    output.position.xy *= Offset.z;
    output.color = color;
    

    return output;
}