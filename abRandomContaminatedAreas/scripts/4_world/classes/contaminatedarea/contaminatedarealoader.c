//ataribaby added ChanceGroupData
class ChanceGroupData : Managed
{
	string GroupName;
	float Chance;
	float SelectedChance;
	bool Active;
};
	
modded class EffectAreaLoader
{
	//ataribaby added GetChanceGroup
	static ChanceGroupData GetChanceGroup(string name, ref array<ref ChanceGroupData> groups)
	{
		for (int i = 0; i < groups.Count(); i++)
		{
			if(name == groups[i].GroupName)
			{
				return groups[i];
			}
		}
		
		return null;
	}
	
	override static void CreateZones()
	{
		JsonDataContaminatedAreas effectAreaData;
		
		// We confirm the contaminated area configuration file exists in mission folder
		if ( !FileExist( m_Path ) )
		{
			// We fallback to check in data and notify user file was not found in mission
			PrintToRPT("[WARNING] :: [EffectAreaLoader CreateZones] :: No contaminated area file found in MISSION folder, your path is " + m_Path + " Attempting DATA folder"); // If the path is invalid, we warn the user
			
			m_Path = "";
			GetGame().GetWorldName( m_Path );
			m_Path = string.Format("dz/worlds/%1/ce/cfgeffectarea.json", m_Path );
			
			if ( !FileExist( m_Path ) )
			{
				PrintToRPT("[WARNING] :: [EffectAreaLoader CreateZones] :: No contaminated area file found in DATA folder, your path is " + m_Path); // If the path is invalid, we warn the user
				return; // Nothing could be read, just end here
			}
		}
		
		// We load the data from file, in case of failure we notify user
		effectAreaData = EffectAreaLoader.GetData();
		if ( effectAreaData )
		{
			// Now that we have extracted the data we go through every declared area
			//Debug.Log("Contaminated area JSON contains : " + effectAreaData.Areas.Count());

			//ataribaby added ChanceGroups
			ref array<ref ChanceGroupData> chanceGroups = new array<ref ChanceGroupData>;
			
			for ( int i = 0; i < effectAreaData.Areas.Count(); i++ )
			{
				//ataribaby added logic start
				JsonDataAreaData data = effectAreaData.Areas.Get(i).Data;
				float chance = data.Chance;
				string chanceGroupName = data.ChanceGroupName 
				float dice = Math.RandomFloat01();
				bool active = false;
				
				if(chanceGroupName != "")
				{
					ChanceGroupData testGroup = GetChanceGroup(chanceGroupName, chanceGroups);
					
					if(testGroup == null)
					{
						ChanceGroupData groupToAdd = new ChanceGroupData();
						groupToAdd.GroupName = chanceGroupName;
						groupToAdd.Chance = chance;
						groupToAdd.SelectedChance = dice;
						groupToAdd.Active = dice <= chance;
						chanceGroups.Insert(groupToAdd);						
						active = groupToAdd.Active;
						Print("[Random Contaminated Area] Added new group '" + chanceGroupName + "'");
						Print("[Random Contaminated Area] Name: " + effectAreaData.Areas.Get(i).AreaName + ", Active: " + active + ", Pos: " + Vector( data.Pos[0], data.Pos[1], data.Pos[2] ) + ", Radius: " + data.Radius + ", Chance: " + groupToAdd.Chance + ", ChanceGroup: '" + groupToAdd.GroupName + "', Selected RNG Chance: " + groupToAdd.SelectedChance);
					}
					else
					{
						active = testGroup.Active;
						Print("[Random Contaminated Area] Got already existing group '" + chanceGroupName + "'");
						Print("[Random Contaminated Area] Name: " + effectAreaData.Areas.Get(i).AreaName + ", Active: " + active + ", Pos: " + Vector( data.Pos[0], data.Pos[1], data.Pos[2] ) + ", Radius: " + data.Radius + ", Chance: " + testGroup.Chance + ", ChanceGroup: '" + testGroup.GroupName + "', Selected RNG Chance: " + testGroup.SelectedChance);
					}
				}
				else
				{
					active = dice <= chance;
					Print("[Random Contaminated Area] Name: " + effectAreaData.Areas.Get(i).AreaName + ", Active: " + active + ", Pos: " + Vector( data.Pos[0], data.Pos[1], data.Pos[2] ) + ", Radius: " + data.Radius + ", Chance: " + chance + ", Selected RNG Chance: " + dice);
				}
				//ataribaby added logic start end
				
				if (active) //ataribaby added conditions
				{
					EffectAreaParams params = new EffectAreaParams();
					
					// We feed in all relevant data
					params.m_ParamName = effectAreaData.Areas.Get( i ).AreaName;
					string areaType = effectAreaData.Areas.Get( i ).Type;
					params.m_ParamTriggerType = effectAreaData.Areas.Get( i ).TriggerType;
					//ataribaby commented out
					//JsonDataAreaData data = effectAreaData.Areas.Get( i ).Data;
					
					// World level area data ( Trigger info, world particles, etc... )
					vector pos = Vector( data.Pos[0], data.Pos[1], data.Pos[2] );
					params.m_ParamRadius = data.Radius;
					params.m_ParamPosHeight = data.PosHeight;
					params.m_ParamNegHeight = data.NegHeight;
					params.m_ParamInnerRings = data.InnerRingCount;
					params.m_ParamInnerSpace = data.InnerPartDist;
					params.m_ParamOuterToggle = data.OuterRingToggle;
					params.m_ParamOuterSpace = data.OuterPartDist;
					params.m_ParamOuterOffset = data.OuterOffset;
					params.m_ParamVertLayers = data.VerticalLayers;
					params.m_ParamVerticalOffset = data.VerticalOffset;
					string particleName = data.ParticleName;
					
					// Local level area data ( Player particles and PPE )
					JsonDataPlayerData playerData = effectAreaData.Areas.Get( i ).PlayerData;
					string aroundPartName = playerData.AroundPartName;
					string tinyPartName = playerData.TinyPartName;
					string ppeRequesterType = playerData.PPERequesterType;
					
					// Conversion of particle name to ID for synchronization and loading
					if (particleName != "")
						params.m_ParamPartId = ParticleList.GetParticleID( particleName );
					
					if (aroundPartName != "")
						params.m_ParamAroundPartId = ParticleList.GetParticleID( aroundPartName );
					
					if (tinyPartName != "")
						params.m_ParamTinyPartId = ParticleList.GetParticleID( tinyPartName );
					
					params.m_ParamPpeRequesterType = ppeRequesterType;

					EffectArea newZone; // Zones MUST inherit from EffectArea
					
					// We snap item position to ground before creating if specified Y is 0
					if ( pos[1] == 0 )
					{
						pos[1] = GetGame().SurfaceRoadY( pos[0], pos[2] );
						Class.CastTo( newZone, GetGame().CreateObjectEx( areaType, pos, ECE_PLACE_ON_SURFACE ) );
					}
					else
						Class.CastTo( newZone, GetGame().CreateObjectEx( areaType, pos, ECE_NONE ) );
					
					// We created a new zone, we feed in the data to finalize setup
					if ( newZone )
						newZone.SetupZoneData( params );
					else
						Error("[WARNING] :: [EffectAreaLoader CreateZones] :: Cast failed, are you sure your class ( 'Type:' ) inherits from EffectArea and that there are no Typos?");
				}
			}
		}
		else
			Error("[WARNING] :: [EffectAreaLoader CreateZones] :: Data could not be read, please check data and syntax"); // Most JSON related errors should be handled, but we have an extra check in case data could not be read
	}
}