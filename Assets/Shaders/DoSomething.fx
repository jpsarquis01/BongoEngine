// simple shader that takes a position and renders the shape as yellow

// define expected vertex data
struct VS_INPUT
{
    float3 position : POSITIONT;
};

// Output of vertes function that gets interpoated through the rasterizer and used in pixel function
struct VS_OUTPUT
{
    float4 position : SV_Position;
};

// Vertex function, applies effects to vertex
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    return output;
}

// Pixel function, interpolated screen position of the pixel, what color it should be
float4 PS(VS_OUTPUT input) : SV_Traget
{
    return float4(1, 1, 0, 1); // yellow
}