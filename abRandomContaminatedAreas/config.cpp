class CfgPatches
{
	class abRandomContaminatedAreas
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class abRandomContaminatedAreas
	{
		type="mod";
		dependencies[] = {"World"};
		
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]={"abRandomContaminatedAreas/scripts/4_world"};
			};
		};
	};
};