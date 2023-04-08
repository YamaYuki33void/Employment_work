
struct InputData{
	
	int i[100];

};

struct OutData{
	
    int i[100];
};

StructuredBuffer<InputData> Buffer0 : register(t1);
RWStructuredBuffer<OutData> BufferOut : register(u1);

[numthreads(1, 1, 1)]
void CS( uint3 DTid : SV_DispatchThreadID )
{
    BufferOut[0].i[DTid.x] = Buffer0[0].i[DTid.x] * 20;
}
