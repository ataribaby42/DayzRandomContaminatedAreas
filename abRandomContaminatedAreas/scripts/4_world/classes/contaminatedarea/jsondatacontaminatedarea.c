modded class JsonDataAreaData : Managed
{
	ref array<float> Pos;
	float Radius;
	float PosHeight;
	float NegHeight;
	int InnerRingCount;
	int InnerPartDist;
	bool OuterRingToggle;
	int OuterPartDist;
	int OuterOffset;
	int VerticalLayers;
	int VerticalOffset;
	float Chance; //ataribaby added chance parameter
	string ChanceGroupName; //ataribaby added chance group parameter
	string ParticleName; 
};