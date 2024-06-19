# DayzRandomContaminatedAreas
Random Contaminated Areas mod adds possibility to define random chance for spawning static hazard areas defined inside cfgeffectarea.json. Initially created for our Stalker themed server with static radiation areas to be more unpredictable but it works for any vanilla or custom area type defined via cfgeffectarea.json.

Added two new paramaters into cfgeffectarea.json:

### Chance
Float 0.0 to 1.0 meaning is percentage of occurrence (0.5 is 50%)

### ChanceGroupName
Dtring group name for grouping area that is formed form multiple areas, chance is evaluated only once as whole for group.

If Chance is omitted it defaults to 0 - always no area active.
If ChanceGroupName is omitted it defaults to "" - no group defined.
You need to have Chance defined just with first occurrence of group, all other group members inherits that chance and dice roll.

Mod is server side mod, no need to add it for client. Use just -servermod=@abRandomContaminatedAreas; on your server.

### Example:
Druganov Airfield E area have 100% chance thus will be always active, Swamps shipwreck 1a and Swamps shipwreck 1b are grouped into Swamps shipwreck 1 and have 50% chance to be active as whole group.

```
{  "AreaName": "Druganov Airfield E", 
   "Type": "SR_RadiationContaminatedArea_Static", 
   "TriggerType": "SR_RadiationContaminatedTrigger",
   "Data": { 
    "Pos": [],
    "Radius": 500,
    "PosHeight": 400,
    "NegHeight": 100,
    "InnerRingCount": 1,
    "InnerPartDist": 50,
    "OuterRingToggle": 1, 
    "OuterPartDist": 60, 
    "OuterOffset": 0, 
    "VerticalLayers": 0,
    "VerticalOffset": 0,
    "Chance": 1,
    "ParticleName": ""
    },
   "PlayerData": {
    "AroundPartName": "",
    "TinyPartName": "",
    "PPERequesterType": "PPERequester_RadiationContaminated"
   }
  },
{  "AreaName": "Swamps shipwreck 1a", 
   "Type": "SR_RadiationContaminatedArea_Static", 
   "TriggerType": "SR_RadiationContaminatedTrigger",
   "Data": { 
    "Pos": [],
    "Radius": 50,
    "PosHeight": 400,
    "NegHeight": 100,
    "InnerRingCount": 1,
    "InnerPartDist": 50,
    "OuterRingToggle": 1, 
    "OuterPartDist": 60, 
    "OuterOffset": 0, 
    "VerticalLayers": 0,
    "VerticalOffset": 0,
    "Chance": 0.5,
    "ChanceGroupName": "Swamps shipwreck 1",
    "ParticleName": ""
    },
   "PlayerData": {
    "AroundPartName": "",
    "TinyPartName": "",
    "PPERequesterType": "PPERequester_RadiationContaminated"
   }
  },
  {  "AreaName": "Swamps shipwreck 1b", 
   "Type": "SR_RadiationContaminatedArea_Static", 
   "TriggerType": "SR_RadiationContaminatedTrigger",
   "Data": { 
    "Pos": [],
    "Radius": 50,
    "PosHeight": 400,
    "NegHeight": 100,
    "InnerRingCount": 1,
    "InnerPartDist": 50,
    "OuterRingToggle": 1, 
    "OuterPartDist": 60, 
    "OuterOffset": 0, 
    "VerticalLayers": 0,
    "VerticalOffset": 0,
    "ChanceGroupName": "Swamps shipwreck 1",
    "ParticleName": ""
    },
   "PlayerData": {
    "AroundPartName": "",
    "TinyPartName": "",
    "PPERequesterType": "PPERequester_RadiationContaminated"
   }
  },
```
