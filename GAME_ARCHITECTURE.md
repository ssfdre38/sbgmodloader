# Super Battle Golf - Game Architecture Analysis

Total Classes Discovered: 1127

## All Classes (GameAssembly)

### <Module>
**Methods:** 0

### AchievementData
**Methods:** 11
**Sample Methods:**
- get_Id
- set_Id
- get_SteamApiName
- set_SteamApiName
- get_HasProgressRequirement

### AchievementCollection
**Methods:** 43
**Sample Methods:**
- get_Achievements
- set_Achievements
- get_BullyDominationRequirement
- set_BullyDominationRequirement
- get_CoolheadedMinHoleCount

### AchievementId
**Methods:** 0

### AchievementsManager
**Methods:** 14
**Sample Methods:**
- Initialize
- Unlock
- SetProgress
- IncrementProgress
- IsUnlocked

### AchievementTriggerCollider
**Methods:** 3
**Sample Methods:**
- Awake
- OnTriggerEnter
- .ctor

### DummyAchievementManager
**Methods:** 10
**Sample Methods:**
- Initialize
- Unlock
- SetProgress
- IncrementProgress
- IsUnlocked

### SteamAchievementManager
**Methods:** 17
**Sample Methods:**
- Initialize
- Unlock
- SetProgress
- IncrementProgress
- IsUnlocked

### <EnsureStatsStored>d__14
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### Volume
**Methods:** 8
**Sample Methods:**
- .cctor
- GetMasterVolume
- GetMusicVolume
- GetVoiceVolume
- GetEffectsVolume

### CameraModuleType
**Methods:** 0

### CameraModule
**Methods:** 11
**Sample Methods:**
- get_Type
- get_ControlsFieldOfView
- get_FieldOfView
- GetCurrentForward
- GetCurrentRight

### CameraModuleController
**Methods:** 46
**Sample Methods:**
- get_DistanceBelowOutOfBoundsHazardSurface
- set_DistanceBelowOutOfBoundsHazardSurface
- get_CurrentModule
- get_PreviousModuleType
- get_CurrentModuleType

### <>c__DisplayClass57_0
**Methods:** 0

### <>c__DisplayClass62_0
**Methods:** 0

### <>c__DisplayClass63_0
**Methods:** 0

### GameplayCameraManager
**Methods:** 40
**Sample Methods:**
- SetForceEnabledCrtEffect
- TogglePhotoCamera
- Awake
- OnDestroy
- TransitionTo

### <AimCameraOffsetRoutine>d__30
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ReleaseSwingChargeCameraOffsetRoutine>d__31
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### LocalSpectatorCameraFollower
**Methods:** 27
**Sample Methods:**
- Awake
- OnStartServer
- OnStartClient
- OnDestroy
- OnLocalPlayerSetSpectatingTarget

### OrbitCameraModule
**Methods:** 77
**Sample Methods:**
- get_Type
- get_TrackedPoint
- set_TrackedPoint
- get_Subject
- get_Pitch

### TrackingMode
**Methods:** 0

### TrackingOffsetMode
**Methods:** 0

### <>c__DisplayClass159_0
**Methods:** 0

### <AddYawOverTimeRoutine>d__126
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <AnimateExternalFovOffset>d__138
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <AnimateExternalFovOffset>d__139
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <TransitionRollToRoutine>d__128
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### OverviewCameraModule
**Methods:** 6
**Sample Methods:**
- get_ControlsFieldOfView
- get_FieldOfView
- get_Type
- UpdateModule
- BeginSlowdown

### PhotoCameraModule
**Methods:** 13
**Sample Methods:**
- get_Active
- set_Active
- get_ControlsFieldOfView
- get_FieldOfView
- get_Type

### PostProcessingManager
**Methods:** 9
**Sample Methods:**
- Awake
- OnDestroy
- SetDistanceBelowOutOfBoundsHazardSurface
- SetDistanceBelowOutOfBoundsHazardSurfaceInternal
- OnCurrentHoleGlobalIndexChanged

### ScreenshakeType
**Methods:** 0

### ScreenshakeTypeExtensions
**Methods:** 1
**Sample Methods:**
- HasType

### ScreenshakeSettings
**Methods:** 20
**Sample Methods:**
- get_Type
- set_Type
- get_Duration
- set_Duration
- get_SmoothingSpeed

### CosmeticsUnlocksManager
**Methods:** 22
**Sample Methods:**
- add_OnCreditsUpdate
- remove_OnCreditsUpdate
- get_AllDances
- ListCosmeticsUnlocks
- ResetPlayerUnlocks

### PlayerCosmeticFaceFeature
**Methods:** 1
**Sample Methods:**
- .ctor

### PlayerCosmeticObject
**Methods:** 1
**Sample Methods:**
- .ctor

### TextureOverrideSlot
**Methods:** 0

### TextureOverride
**Methods:** 1
**Sample Methods:**
- .ctor

### ModelSlot
**Methods:** 0

### PlayerCosmetics
**Methods:** 75
**Sample Methods:**
- get_Switcher
- add_ClubCosmeticUpdated
- remove_ClubCosmeticUpdated
- Awake
- OnClubChanged

### LoadoutSlot
**Methods:** 0

### SaveData
**Methods:** 0

### Loadout
**Methods:** 5
**Sample Methods:**
- Get
- Apply
- GetVictoryDance
- <Get>g__HasSlot|13_0
- <Apply>g__HasSlot|14_0

### <>c__DisplayClass13_0
**Methods:** 0

### <>c__DisplayClass14_0
**Methods:** 0

### <Apply>d__14
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass35_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <EquipLoadout>b__0

### <EquipLoadout>d__35
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetAndEquipLoadout>d__36
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### PlayerCosmeticsMetadata
**Methods:** 4
**Sample Methods:**
- get_PersistentGuid
- IsHidden
- .ctor
- .cctor

### Variation
**Methods:** 1
**Sample Methods:**
- .ctor

### Category
**Methods:** 0

### PlayerCosmeticsObjectSwitcher
**Methods:** 5
**Sample Methods:**
- get_ModelOverride
- add_OnModelOverride
- remove_OnModelOverride
- OverrideModel
- .ctor

### <OverrideModel>d__7
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### PlayerCosmeticsSettings
**Methods:** 1
**Sample Methods:**
- .ctor

### SkinColor
**Methods:** 0

### PlayerCosmeticsSwitcher
**Methods:** 84
**Sample Methods:**
- get_CurrentHeadRuntimeKey
- set_CurrentHeadRuntimeKey
- get_CurrentHatRuntimeKey
- set_CurrentHatRuntimeKey
- get_CurrentFaceRuntimeKey

### CosmeticKey
**Methods:** 3
**Sample Methods:**
- Equals
- HasValidKey
- .ctor

### CosmeticCancellationTokenSource
**Methods:** 4
**Sample Methods:**
- Cancel
- GetLocalCancellationToken
- DisposeCancellationToken
- .ctor

### LoadedTextureOverride
**Methods:** 3
**Sample Methods:**
- UnloadTexture
- op_Implicit
- .ctor

### LoadedCosmetic
**Methods:** 2
**Sample Methods:**
- Unload
- .ctor

### <>c__DisplayClass137_0
**Methods:** 0

### <>c__DisplayClass146_0
**Methods:** 0

### <>c__DisplayClass154_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <SetBodyModel>g__UpdateTextureAndColor|0
- <SetBodyModel>g__ReleasePrev|1

### <<SetBodyModel>g__ReleasePrev|1>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<SetBodyModel>g__UpdateTextureAndColor|0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass157_0
**Methods:** 0

### <SetBodyModel>d__154
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetBrowTexture>d__143
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetCheeksTexture>d__142
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetClubModel>d__152
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetEyesTexture>d__145
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetFaceModel>d__150
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetFaceTexture>d__146
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetGolfBallModel>d__153
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetHatModel>d__149
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetHeadModel>d__148
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetLowerFaceModel>d__151
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetModelInternal>d__155
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetMouthTexture>d__144
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetTextureOverride>d__156
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### PlayerCosmeticsVictoryDanceMetadata
**Methods:** 1
**Sample Methods:**
- .ctor

### PlayerCosmeticsVictoryDances
**Methods:** 4
**Sample Methods:**
- get_Length
- GetDance
- get_Item
- .ctor

### CourseCollection
**Methods:** 4
**Sample Methods:**
- get_Courses
- set_Courses
- RuntimeInitialize
- .ctor

### CourseData
**Methods:** 22
**Sample Methods:**
- get_LocalizedName
- set_LocalizedName
- get_CategoryIcon
- set_CategoryIcon
- get_MenuBackground

### HoleCameraTransformData
**Methods:** 1
**Sample Methods:**
- .ctor

### HoleData
**Methods:** 20
**Sample Methods:**
- get_LocalizedName
- set_LocalizedName
- get_Scene
- set_Scene
- get_Par

### DifficultyLevel
**Methods:** 0

### BallDispenser
**Methods:** 33
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_IsInteractionEnabled
- get_InteractString
- Awake

### <<CmdDispenseBallFor>g__DisableInteractionTemporarily|24_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <CmdDispenseBallFor>d__24
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### CourseStarter
**Methods:** 7
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_InteractString
- get_IsInteractionEnabled
- Awake

### DrivingRangeManager
**Methods:** 12
**Sample Methods:**
- get_SpawnArea
- Awake
- OnDestroy
- RegisterBallDispenser
- DeregisterBallDispenser

### DrivingRangeSpawnArea
**Methods:** 3
**Sample Methods:**
- GetRandomSpawnPosition
- OnDrawGizmosSelected
- .ctor

### ItemDispenser
**Methods:** 23
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_IsInteractionEnabled
- get_InteractString
- Awake

### <<CmdDispenseItemFor>g__DisableInteractionTemporarily|20_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <CmdDispenseItemFor>d__20
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### MatchSetupStation
**Methods:** 4
**Sample Methods:**
- get_NextCameraButton
- PlayMenuOpenedEffectsLocalOnly
- PlayMenuOpenedEffectsLocalOnlyInternal
- .ctor

### PlayerCustomizationBuilding
**Methods:** 17
**Sample Methods:**
- OnStartServer
- InformLocalPlayerEntered
- InformLocalPlayerExited
- InformLocalPlayerEnteredInternal
- InformLocalPlayerExitedInternal

### TargetDummy
**Methods:** 15
**Sample Methods:**
- Start
- OnDestroy
- PlayHitLocalOnly
- OnWasHitByGolfSwing
- OnWasHitBySwingProjectile

### TutorialObjective
**Methods:** 0

### TutorialPromptCategory
**Methods:** 0

### TutorialPrompt
**Methods:** 0

### TutorialExtensions
**Methods:** 3
**Sample Methods:**
- HasObjective
- HasCategory
- HasPrompt

### TutorialManager
**Methods:** 37
**Sample Methods:**
- get_Settings
- get_ActiveObjective
- get_IsFinished
- add_ObjectiveChanged
- remove_ObjectiveChanged

### <>c__DisplayClass34_0
**Methods:** 0

### <>c__DisplayClass35_0
**Methods:** 0

### InfoPromptCategoryData
**Methods:** 5
**Sample Methods:**
- get_Category
- set_Category
- get_Prompts
- set_Prompts
- .ctor

### TutorialSettings
**Methods:** 16
**Sample Methods:**
- get_LookAroundRequiredDuration
- set_LookAroundRequiredDuration
- get_MoveRequiredDuration
- set_MoveRequiredDuration
- get_AimSwingRequiredDuration

### EmoteSettings
**Methods:** 1
**Sample Methods:**
- .ctor

### AllEmoteSettings
**Methods:** 6
**Sample Methods:**
- get_EmoteSettings
- set_EmoteSettings
- OnValidate
- OnEnable
- Initialize

### SpectatorEmoteSettings
**Methods:** 1
**Sample Methods:**
- .ctor

### AllSpectatorEmoteSettings
**Methods:** 6
**Sample Methods:**
- get_EmoteSettings
- set_EmoteSettings
- OnValidate
- OnEnable
- Initialize

### Entity
**Methods:** 80
**Sample Methods:**
- get_IsTree
- set_IsTree
- get_Rigidbody
- set_Rigidbody
- get_NetworkRigidbody

### <<InformInFoliage>g__MoveInFoliageRoutine|116_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <TemporarilyIgnoreCollisionsWith>d__124
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ElectromagnetEquipment
**Methods:** 5
**Sample Methods:**
- OnEnable
- OnDisable
- OnDestroy
- Activate
- .ctor

### ElectromagnetShieldManager
**Methods:** 6
**Sample Methods:**
- get_ActiveShields
- RegisterActiveShield
- DeregisterActiveShield
- RegisterActiveShieldInternal
- DeregisterActiveShieldInternal

### EquipmentType
**Methods:** 0

### Equipment
**Methods:** 5
**Sample Methods:**
- get_Type
- set_Type
- get_HasCosmetics
- set_HasCosmetics
- .ctor

### EquipmentSettings
**Methods:** 5
**Sample Methods:**
- get_Type
- set_Type
- get_Prefab
- set_Prefab
- .ctor

### EquipmentCollection
**Methods:** 5
**Sample Methods:**
- OnValidate
- OnEnable
- TryGetEquipmentSettings
- Initialize
- .ctor

### EquipmentManager
**Methods:** 7
**Sample Methods:**
- GetUnusedEquipment
- ReturnEquipment
- GetUnusedEquipmentInternal
- ReturnEquipmentInternal
- EnsurePoolParentExists

### EquipmentSwitcher
**Methods:** 20
**Sample Methods:**
- get_CurrentEquipment
- set_CurrentEquipment
- OnValidate
- Awake
- OnWillBeDestroyed

### <>c__DisplayClass15_0
**Methods:** 0

### FreezeBombEquipment
**Methods:** 3
**Sample Methods:**
- OnEnable
- SetBombMeshEnabled
- .ctor

### OrbitalLaserState
**Methods:** 0

### OrbitalLaser
**Methods:** 33
**Sample Methods:**
- OnDestroy
- OnStartServer
- OnStopServer
- OnStartClient
- OnStopClient

### <>c__DisplayClass18_0
**Methods:** 0

### OrbitalLaserEquipment
**Methods:** 2
**Sample Methods:**
- Activate
- .ctor

### OrbitalLaserManager
**Methods:** 8
**Sample Methods:**
- Awake
- OnDestroy
- ServerActivateLaser
- GetTarget
- CanTarget

### <>c__DisplayClass4_0
**Methods:** 0

### RocketDriverEquipment
**Methods:** 7
**Sample Methods:**
- get_Vfx
- set_Vfx
- OnEnable
- OnDisable
- OnDestroy

### RocketLauncherEquipment
**Methods:** 3
**Sample Methods:**
- OnEnable
- SetRocketMeshEnabled
- .ctor

### GameManager
**Methods:** 109
**Sample Methods:**
- get_AchievementsManager
- set_AchievementsManager
- get_IsSteamOverlayActive
- set_IsSteamOverlayActive
- get_HiddenUiGroups

### <<ExitToMainMenu>g__ExitGame|173_2>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c
**Methods:** 4
**Sample Methods:**
- .cctor
- .ctor
- <ExitToMainMenu>b__173_3
- <FilterProfanity>b__190_0

### <>c__DisplayClass173_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <ExitToMainMenu>g__ExitWithoutSave|0

### <>c__DisplayClass178_0
**Methods:** 0

### <>c__DisplayClass179_0
**Methods:** 0

### <>c__DisplayClass181_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <InitializeBadWords>b__1

### <OnNetworkManagerDestroyedDueToOfflineSceneTransition>d__183
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### GolfCartInfo
**Methods:** 149
**Sample Methods:**
- get_ExhaustPosition
- set_ExhaustPosition
- get_AsEntity
- set_AsEntity
- get_Movement

### <<OnPassengersChanged>g__TurnHeadlightsOnRoutine|124_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<ServerReserveDriverSeatPreNetworkSpawn>g__DestroyIfUnusedDelayed|80_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass108_0
**Methods:** 0

### <>c__DisplayClass70_0
**Methods:** 0

### <>c__DisplayClass85_0
**Methods:** 0

### <>c__DisplayClass88_0
**Methods:** 0

### <TimeOutResponsiblePlayerRoutine>d__103
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### SerializableWheelFrictionCurve
**Methods:** 1
**Sample Methods:**
- op_Implicit

### GolfCartMovement
**Methods:** 58
**Sample Methods:**
- get_SmoothedSteering
- set_SmoothedSteering
- get_SmoothedLocalAcceleration
- set_SmoothedLocalAcceleration
- get_AsEntity

### <<TryTriggerJump>g__JumpRoutine|59_4>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass56_0
**Methods:** 18
**Sample Methods:**
- .ctor
- <OnBUpdate>g__UpdateAllWheels|0
- <OnBUpdate>g__UpdateWheel|11
- <OnBUpdate>g__ApplyForwardInput|1
- <OnBUpdate>g__DisableMotorsAndBrakes|2

### <<OnBUpdate>g__StopPipeVfxDelayedRoutine|9>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass56_1
**Methods:** 0

### GolfCartMovementSettings
**Methods:** 71
**Sample Methods:**
- get_LocalCenterOfMass
- set_LocalCenterOfMass
- get_MaxForwardSpeed
- set_MaxForwardSpeed
- get_MaxBackwardSpeed

### GolfCartSeatSettings
**Methods:** 1
**Sample Methods:**
- .ctor

### GolfCartSettings
**Methods:** 36
**Sample Methods:**
- get_Prefab
- set_Prefab
- get_SeatSettings
- set_SeatSettings
- get_ExitForcedDiveSpeed

### Checkpoint
**Methods:** 11
**Sample Methods:**
- get_Order
- Awake
- OnDestroy
- OnTriggerEnter
- SetIsVisuallyActive

### CheckpointManager
**Methods:** 22
**Sample Methods:**
- OnStartClient
- OnStopClient
- RegisterCheckpoint
- DeregisterCheckpoint
- TryActivate

### <>c__DisplayClass13_0
**Methods:** 0

### <>c__DisplayClass17_0
**Methods:** 0

### CheckpointSettings
**Methods:** 11
**Sample Methods:**
- get_MaxHorizontalRespawnDistance
- set_MaxHorizontalRespawnDistance
- get_InactiveMaterial
- set_InactiveMaterial
- get_ActiveMaterial

### MatchState
**Methods:** 0

### StrokesUnderParType
**Methods:** 0

### AnnouncerLine
**Methods:** 0

### AnnouncerLineExtensions
**Methods:** 1
**Sample Methods:**
- IsMatchStateLine

### CourseManager
**Methods:** 217
**Sample Methods:**
- get_PlayerStates
- get_PlayerKnockoutStreaks
- get_PlayerDominations
- get_ServerMatchParticipants
- get_PlayerPingPerGuid

### PlayerState
**Methods:** 6
**Sample Methods:**
- get_name
- .ctor
- GetClearedState
- GetNewMatchState
- CompareTo

### PlayerPair
**Methods:** 4
**Sample Methods:**
- .ctor
- Inverse
- Equals
- GetHashCode

### <<OnMatchStateChanged>g__AwardCourseBonus|212_3>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<OnMatchStateChanged>g__ServerFinishMatchDelayed|212_1>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<PlayAnnouncerLineLocalOnlyInternal>g__PlayLineQueue|162_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c
**Methods:** 8
**Sample Methods:**
- .cctor
- .ctor
- <StartCourseInternal>b__145_0
- <RpcInformStartingCourse>b__146_0
- <EndCourseInternal>b__147_0

### <>c__DisplayClass165_0
**Methods:** 0

### <>c__DisplayClass166_0
**Methods:** 0

### <>c__DisplayClass167_0
**Methods:** 0

### <>c__DisplayClass172_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <SetPlayerSpectatorInternal>g__RespawnPlayer|0

### <<SetPlayerSpectatorInternal>g__RespawnPlayer|0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass172_1
**Methods:** 2
**Sample Methods:**
- .ctor
- <SetPlayerSpectatorInternal>b__1

### <>c__DisplayClass174_0
**Methods:** 0

### <>c__DisplayClass224_0
**Methods:** 0

### <CountDownToMatchEndRoutine>d__195
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <EndCourseInternal>d__147
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <HoleOverviewAndTeeOffCountdownRoutine>d__193
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <RpcInformEndingCourse>d__148
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <RpcInformStartingCourse>d__146
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <RpcInformStartingNextMatch>d__150
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <ServerStartNextMatch>d__149
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <StartCourseInternal>d__145
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### BallGroundData
**Methods:** 0

### BallOutOfBoundsReturnState
**Methods:** 0

### GolfBall
**Methods:** 147
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_IsGrounded
- set_IsGrounded
- get_GroundData

### FrictionMode
**Methods:** 0

### <>c__DisplayClass114_0
**Methods:** 0

### <>c__DisplayClass120_0
**Methods:** 0

### <>c__DisplayClass128_0
**Methods:** 0

### <>c__DisplayClass131_0
**Methods:** 0

### <>c__DisplayClass132_0
**Methods:** 0

### <>c__DisplayClass96_0
**Methods:** 0

### <ReturnToBoundsRoutine>d__120
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### GolfBallSettings
**Methods:** 40
**Sample Methods:**
- get_StationaryStateSpeedThreshold
- set_StationaryStateSpeedThreshold
- get_GroundFullStopMaxPitch
- set_GroundFullStopMaxPitch
- get_GroundFullRollMinPitch

### GolfTee
**Methods:** 18
**Sample Methods:**
- get_Owner
- OnStartServer
- OnStopServer
- SetOwner
- GetPlayerWorldSpawnPosition

### TeeingSpotStatus
**Methods:** 0

### TeeingSpot
**Methods:** 9
**Sample Methods:**
- get_Status
- set_Status
- get_OwningPlayerConnectionId
- set_OwningPlayerConnectionId
- ServerEnsureSpawned

### GolfTeeingPlatform
**Methods:** 20
**Sample Methods:**
- get_Settings
- get_MinPlayerCount
- get_IsActive
- Awake
- OnStartServer

### GolfTeeManager
**Methods:** 19
**Sample Methods:**
- get_ActiveTeeingPlaforms
- add_ActiveTeeingPlatformRegistered
- remove_ActiveTeeingPlatformRegistered
- RegisterTeeingPlatform
- RegisterActiveTeeingPlatform

### HitGolfTee
**Methods:** 7
**Sample Methods:**
- Awake
- OnEnable
- OnDisable
- OnDestroy
- Initialize

### SwingProjectileState
**Methods:** 0

### Hittable
**Methods:** 225
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_SwingProjectileState
- set_SwingProjectileState
- get_IsFrozen

### <<OnCollisionEnter>g__ResetResolvedCollisionVfxPairsDelayed|152_3>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<UpdateHomingWarning>g__HomingWarningUpdateRoutine|206_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass152_0
**Methods:** 0

### <>c__DisplayClass182_0
**Methods:** 0

### <>c__DisplayClass186_0
**Methods:** 4
**Sample Methods:**
- .ctor
- <HitWithItemInternal>g__ServerFreeze|0
- <HitWithItemInternal>g__CanBeFrozen|1
- <HitWithItemInternal>g__TransferHitToGolfCartPassengers|2

### <<HitWithItemInternal>g__ServerFreeze|0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### GolfHole
**Methods:** 46
**Sample Methods:**
- get_IsMainHole
- get_Settings
- TriggerHoleScoreBlast
- Start
- OnWillBeDestroyed

### <MoveFlagRoutine>d__25
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ServerOnBallScored>d__26
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### GolfHoleGreenTrigger
**Methods:** 11
**Sample Methods:**
- Awake
- OnDestroy
- OnTriggerEnter
- OnTriggerExit
- IsPointInTrigger

### GolfHoleManager
**Methods:** 12
**Sample Methods:**
- get_MainHole
- get_HasMaxReferenceDistance
- get_MaxReferenceDistance
- Awake
- OnDestroy

### GolfHoleSettings
**Methods:** 7
**Sample Methods:**
- get_MaxKnockbackDistance
- set_MaxKnockbackDistance
- get_MinKnockbackDistance
- set_MinKnockbackDistance
- get_MaxRange

### GolfHoleTrigger
**Methods:** 3
**Sample Methods:**
- Awake
- OnTriggerEnter
- .ctor

### ServerPersistentCourseData
**Methods:** 12
**Sample Methods:**
- WritePlayerStates
- WritePlayerInventories
- RegisterPlayerJoinTimestamp
- DeregisterPlayerJoinTimestamp
- TryGetPlayerInventory

### BreakableIceState
**Methods:** 0

### BreakableIce
**Methods:** 15
**Sample Methods:**
- OnDestroy
- OnStartServer
- OnStopServer
- OnStartClient
- UpdateMaterial

### Foliage
**Methods:** 4
**Sample Methods:**
- Awake
- Start
- OnDestroy
- .ctor

### LevelHazardSettings
**Methods:** 0

### HazardSettings
**Methods:** 16
**Sample Methods:**
- get_LevelHazardSettings
- set_LevelHazardSettings
- get_SwingPowerBarOutOfBoundsHazardOVerlayTexture
- set_SwingPowerBarOutOfBoundsHazardOVerlayTexture
- get_BreakableIcePristineMaterial

### LevelHazard
**Methods:** 5
**Sample Methods:**
- get_Type
- Start
- OnDestroy
- GetSize
- .ctor

### MainOutOfBoundsHazard
**Methods:** 5
**Sample Methods:**
- get_Height
- get_Type
- GetEliminationReason
- GetEliminationReasonInternal
- .ctor

### SecondaryOutOfBoundsHazard
**Methods:** 6
**Sample Methods:**
- get_Type
- Start
- OnDestroy
- GetEliminationReason
- GetSize

### DiveHittableSettings
**Methods:** 15
**Sample Methods:**
- get_CanBeHit
- set_CanBeHit
- get_MinKnockbackHitRelativeSpeed
- set_MinKnockbackHitRelativeSpeed
- get_MaxKnockbackHitRelativeSpeed

### HittableSettings
**Methods:** 13
**Sample Methods:**
- get_Swing
- set_Swing
- get_Projectile
- set_Projectile
- get_Dive

### ItemHittableSettings
**Methods:** 81
**Sample Methods:**
- get_DuelingPistolMaxKnockbackDistance
- set_DuelingPistolMaxKnockbackDistance
- get_DuelingPistolMinKnockbackDistance
- set_DuelingPistolMinKnockbackDistance
- get_DuelingPistolMaxKnockbackSpeed

### LockOnTarget
**Methods:** 8
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- Awake
- Start
- OnDestroy

### LockOnTargetManager
**Methods:** 6
**Sample Methods:**
- get_Targets
- RegisterLockOnTarget
- DeregisterLockOnTarget
- RegisterLockOnTargetInternal
- DeregisterLockOnTargetInternal

### ProjectileHittableSettings
**Methods:** 7
**Sample Methods:**
- get_CanBeHitBySwingProjectiles
- set_CanBeHitBySwingProjectiles
- get_SwingProjectileMinResultingSpeed
- set_SwingProjectileMinResultingSpeed
- get_SwingProjectileMaxResultingSpeed

### ScoreKnockbackHittableSettings
**Methods:** 13
**Sample Methods:**
- get_MinKnockbackSpeed
- set_MinKnockbackSpeed
- get_MaxKnockbackSpeed
- set_MaxKnockbackSpeed
- get_MinKnockbackAngularSpeed

### SwingHittableSettings
**Methods:** 40
**Sample Methods:**
- get_MaxPowerSwingHitSpeed
- set_MaxPowerSwingHitSpeed
- get_MaxPowerPuttHitSpeed
- set_MaxPowerPuttHitSpeed
- get_SwingHitSpinSpeed

### WindHittableSettings
**Methods:** 7
**Sample Methods:**
- get_IsAffectedByWind
- set_IsAffectedByWind
- get_WindFactor
- set_WindFactor
- get_CrossWindFactor

### ConditionalInputBuffer
**Methods:** 8
**Sample Methods:**
- get_IsActive
- set_IsActive
- .ctor
- Update
- TryUseInput

### CursorManager
**Methods:** 5
**Sample Methods:**
- get_CursorLocked
- SetCursorLock
- SetCursorForceUnlocked
- ApplyCursorLock
- .ctor

### FullDurationInputBuffer
**Methods:** 8
**Sample Methods:**
- get_IsActive
- set_IsActive
- .ctor
- Update
- TryUseInput

### GameControls
**Methods:** 30
**Sample Methods:**
- get_asset
- .ctor
- Finalize
- Dispose
- get_bindingMask

### GameplayActions
**Methods:** 23
**Sample Methods:**
- .ctor
- get_Move
- get_Jump
- get_Aim
- get_Swing

### GolfCartDriverActions
**Methods:** 15
**Sample Methods:**
- .ctor
- get_Accelerate
- get_Brake
- get_Steer
- get_Jump

### GolfCartSharedActions
**Methods:** 12
**Sample Methods:**
- .ctor
- get_Exit
- get_DiveOut
- Get
- Enable

### HotkeysActions
**Methods:** 21
**Sample Methods:**
- .ctor
- get_Hotkey1
- get_Hotkey2
- get_Hotkey3
- get_Hotkey4

### SpectateActions
**Methods:** 12
**Sample Methods:**
- .ctor
- get_CyclePreviousPlayer
- get_CycleNextPlayer
- Get
- Enable

### IngameActions
**Methods:** 14
**Sample Methods:**
- .ctor
- get_ShowScoreboard
- get_Pause
- get_OpenChat
- get_ToggleEmoteMenu

### VoiceChatActions
**Methods:** 11
**Sample Methods:**
- .ctor
- get_PushToTalk
- Get
- Enable
- Disable

### CameraActions
**Methods:** 11
**Sample Methods:**
- .ctor
- get_Look
- Get
- Enable
- Disable

### RadialMenuActions
**Methods:** 12
**Sample Methods:**
- .ctor
- get_Select
- get_Cancel
- Get
- Enable

### UIActions
**Methods:** 22
**Sample Methods:**
- .ctor
- get_Navigate
- get_Submit
- get_Cancel
- get_Point

### VoteActions
**Methods:** 12
**Sample Methods:**
- .ctor
- get_Yes
- get_No
- Get
- Enable

### IGameplayActions
**Methods:** 13
**Sample Methods:**
- OnMove
- OnJump
- OnAim
- OnSwing
- OnUseItem

### IGolfCartDriverActions
**Methods:** 5
**Sample Methods:**
- OnAccelerate
- OnBrake
- OnSteer
- OnJump
- OnHonk

### IGolfCartSharedActions
**Methods:** 2
**Sample Methods:**
- OnExit
- OnDiveOut

### IHotkeysActions
**Methods:** 11
**Sample Methods:**
- OnHotkey1
- OnHotkey2
- OnHotkey3
- OnHotkey4
- OnHotkey5

### ISpectateActions
**Methods:** 2
**Sample Methods:**
- OnCyclePreviousPlayer
- OnCycleNextPlayer

### IIngameActions
**Methods:** 4
**Sample Methods:**
- OnShowScoreboard
- OnPause
- OnOpenChat
- OnToggleEmoteMenu

### IVoiceChatActions
**Methods:** 1
**Sample Methods:**
- OnPushToTalk

### ICameraActions
**Methods:** 1
**Sample Methods:**
- OnLook

### IRadialMenuActions
**Methods:** 2
**Sample Methods:**
- OnSelect
- OnCancel

### IUIActions
**Methods:** 12
**Sample Methods:**
- OnNavigate
- OnSubmit
- OnCancel
- OnPoint
- OnClick

### IVoteActions
**Methods:** 2
**Sample Methods:**
- OnYes
- OnNo

### HeldConditionalInputBuffer
**Methods:** 9
**Sample Methods:**
- get_IsActive
- set_IsActive
- .ctor
- Update
- TryUseInput

### IInputBuffer
**Methods:** 5
**Sample Methods:**
- get_IsActive
- Update
- TryUseInput
- Cancel
- OnDestroy

### ActionState
**Methods:** 0

### InputIcon
**Methods:** 2
**Sample Methods:**
- TryMergeWith
- .ctor

### MergeData
**Methods:** 0

### InputIconCollection
**Methods:** 13
**Sample Methods:**
- get_Device
- RebuildLookupIfNeeded
- OnValidate
- OnEnable
- OnDisable

### InputIconsSets
**Methods:** 5
**Sample Methods:**
- OnValidate
- OnEnable
- GetIconSet
- Initialize
- .ctor

### InputIconsSet
**Methods:** 5
**Sample Methods:**
- GetIcon
- GetIconRichTextTag
- TryMerge
- TryMerge
- .ctor

### InputMode
**Methods:** 0

### InputOverride
**Methods:** 0

### InputModeExtensions
**Methods:** 3
**Sample Methods:**
- HasMode
- HasOverride
- DisablesUiInputModule

### InputManager
**Methods:** 66
**Sample Methods:**
- get_Controls
- get_CurrentDeviceType
- set_CurrentDeviceType
- get_CurrentMode
- set_CurrentMode

### DeviceType
**Methods:** 0

### <>c__DisplayClass76_0
**Methods:** 0

### ManualConditionalInputBuffer
**Methods:** 8
**Sample Methods:**
- get_IsActive
- set_IsActive
- .ctor
- Update
- TryUseInput

### DrivingRangeNextCameraButton
**Methods:** 7
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_IsInteractionEnabled
- get_InteractString
- LocalPlayerInteract

### IInteractable
**Methods:** 4
**Sample Methods:**
- get_AsEntity
- get_IsInteractionEnabled
- get_InteractString
- LocalPlayerInteract

### MenuOpenInteraction
**Methods:** 18
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_IsInteractionEnabled
- get_InteractString
- Awake

### Menu
**Methods:** 0

### TargetReticlePosition
**Methods:** 1
**Sample Methods:**
- .ctor

### AudioSettings
**Methods:** 376
**Sample Methods:**
- get_ItemBoxCollectedEvent
- set_ItemBoxCollectedEvent
- get_BallInHoleEvent
- set_BallInHoleEvent
- get_FootstepEvent

### FreezeBomb
**Methods:** 25
**Sample Methods:**
- Awake
- Start
- OnWillBeDestroyed
- OnStartServer
- OnStopServer

### <>c__DisplayClass21_0
**Methods:** 0

### FreezeBombIceBlock
**Methods:** 8
**Sample Methods:**
- Awake
- OnDestroy
- Initialize
- PlayBreakVfxLocalOnly
- InformReturnedToPool

### <>c__DisplayClass5_0
**Methods:** 0

### FreezeBombManager
**Methods:** 7
**Sample Methods:**
- GetUnusedIceBlock
- ReturnIceBlock
- GetUnusedIceBlockInternal
- ReturnIceBlockInternal
- .ctor

### FreezeBombPlatform
**Methods:** 13
**Sample Methods:**
- OnStartServer
- OnDestroy
- OnMeshIndexChanged
- OnIsShakingChanged
- .ctor

### <<OnStartServer>g__DisappearDelayed|7_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ItemCollection
**Methods:** 8
**Sample Methods:**
- get_Count
- OnValidate
- OnEnable
- Initialize
- GetItemAtIndex

### ItemNonAimingUse
**Methods:** 0

### ItemAirhornReaction
**Methods:** 0

### ItemData
**Methods:** 38
**Sample Methods:**
- get_Type
- set_Type
- get_Prefab
- set_Prefab
- get_DroppedLocalRotationEuler

### ItemPool
**Methods:** 8
**Sample Methods:**
- get_SpawnChances
- get_TotalSpawnChanceWeight
- OnValidate
- GetSpawnChanceWeight
- UpdateTotalWeight

### ItemSpawnChance
**Methods:** 0

### ItemSettings
**Methods:** 470
**Sample Methods:**
- get_CoffeeDrinkEffectStartFrames
- set_CoffeeDrinkEffectStartFrames
- get_CoffeeTotalFrames
- set_CoffeeTotalFrames
- get_CoffeeEffectDuration

### ItemSpawner
**Methods:** 34
**Sample Methods:**
- Awake
- OnDestroy
- OnStartServer
- OnStopServer
- OnTriggerEnter

### ItemSpawnerSettings
**Methods:** 21
**Sample Methods:**
- get_ItemPools
- get_ItemPoolsDefaults
- get_AheadOfBallItemPool
- get_AheadOfBallItemPoolDefaults
- get_RespawnTime

### ItemPoolData
**Methods:** 1
**Sample Methods:**
- CompareTo

### ItemSpawnerVisuals
**Methods:** 11
**Sample Methods:**
- get_EffectSourcePosition
- get_HasBox
- Awake
- SetIsTaken
- SetFill

### ItemSpawnerVisualType
**Methods:** 0

### ItemType
**Methods:** 0

### ItemTypeExtensions
**Methods:** 1
**Sample Methods:**
- TryGetEliminationReason

### LandmineArmType
**Methods:** 0

### Landmine
**Methods:** 47
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_Owner
- set_Owner
- get_IsArmed

### <<ServerArmWhenStationary>g__ArmWhenStationaryRoutine|33_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass32_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <ServerArmDelayed>g__ShouldArm|0
- <ServerArmDelayed>g__ArmDelayedRoutine|1

### <<ServerArmDelayed>g__ArmDelayedRoutine|1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ServerExplodeDelayed>d__40
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### UpdateLandmineTransformsJob
**Methods:** 1
**Sample Methods:**
- Execute

### SetUpLandmineOverlapChecksJob
**Methods:** 1
**Sample Methods:**
- Execute

### LandmineManager
**Methods:** 8
**Sample Methods:**
- Awake
- OnDestroy
- RegisterArmedLandmine
- DeregisterArmedLandmine
- RegisterArmedLandmineInternal

### LandmineInstance
**Methods:** 0

### PhysicalItem
**Methods:** 23
**Sample Methods:**
- get_RemainingUses
- set_RemainingUses
- get_AsEntity
- set_AsEntity
- get_ItemType

### Rocket
**Methods:** 40
**Sample Methods:**
- get_IsPlayingHomingWarning
- set_IsPlayingHomingWarning
- Awake
- Start
- OnWillBeDestroyed

### <<UpdateHomingWarning>g__HomingWarningUpdateRoutine|31_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### ThrownUsedItemType
**Methods:** 0

### ThrownUsedItem
**Methods:** 13
**Sample Methods:**
- get_AsEntity
- set_AsEntity
- get_Type
- get_Rigidbody
- OnValidate

### <<OnEnable>g__TemporarilyIgnoreCollisionsWith|16_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ThrownUsedItemManager
**Methods:** 8
**Sample Methods:**
- Awake
- GetUnusedThrownItem
- ReturnThrownItem
- GetUnusedThrownItemInternal
- ReturnThrownItemInternal

### ThrownUsedRocketDriver
**Methods:** 7
**Sample Methods:**
- get_IsRocketActive
- set_IsRocketActive
- OnDisable
- OnDestroy
- OnFixedBUpdate

### BallOutOfBoundsTrigger
**Methods:** 4
**Sample Methods:**
- Awake
- OnTriggerEnter
- OnTriggerExit
- .ctor

### BallOutOfBoundsTriggerManager
**Methods:** 9
**Sample Methods:**
- OnDestroy
- RegisterOverlap
- DeregisterOverlap
- IsBallInOutOfBoundsTrigger
- RegisterOverlapInternal

### BoundsJobHelper
**Methods:** 7
**Sample Methods:**
- DoesCurveRequiresSplittingForWindingAngle
- GetCurveWindingAngleRad
- GetBezierTotalWindingAngleRad
- IsInOutOfBoundsHazard
- IsInOrOverLevelHazard

### <>c__DisplayClass3_0
**Methods:** 0

### <>c__DisplayClass4_0
**Methods:** 0

### FindApproximateNearestPointOnCurvesJob
**Methods:** 1
**Sample Methods:**
- Execute

### FindNearestCurveJob
**Methods:** 1
**Sample Methods:**
- Execute

### FindApproximateNearestPointsOnCurveSegmentsJob
**Methods:** 1
**Sample Methods:**
- Execute

### FindNearestCurveSegmentPointJob
**Methods:** 1
**Sample Methods:**
- Execute

### GetBezierWindingAnglesForSinglePointJob
**Methods:** 1
**Sample Methods:**
- Execute

### ProcessSinglePointWindingAnglesJob
**Methods:** 1
**Sample Methods:**
- Execute

### PrepareBoundsStateUpdateJob
**Methods:** 1
**Sample Methods:**
- Execute

### UpdateLevelBoundTrackerTransformsJob
**Methods:** 1
**Sample Methods:**
- Execute

### UpdateOutOfBoundsHazardStateJob
**Methods:** 1
**Sample Methods:**
- Execute

### GetBezierWindingAnglesJob
**Methods:** 1
**Sample Methods:**
- Execute

### GetBezierWindingAnglesFilteredJob
**Methods:** 1
**Sample Methods:**
- Execute

### GetWindingNumbersFromAnglesJob
**Methods:** 1
**Sample Methods:**
- Execute

### ProcessGreenBoundsUpdateResultsJob
**Methods:** 1
**Sample Methods:**
- Execute

### ProcessLevelBoundsUpdateResultsJob
**Methods:** 2
**Sample Methods:**
- Execute
- <Execute>g__ApplyState|4_0

### <>c__DisplayClass4_0
**Methods:** 0

### ProcessBoundsCheckResultsJob
**Methods:** 1
**Sample Methods:**
- Execute

### BoundsState
**Methods:** 0

### LevelBoundsTrackingType
**Methods:** 0

### LevelBoundsTrackingTypeExtensions
**Methods:** 1
**Sample Methods:**
- HasType

### BoundsStateExtensions
**Methods:** 3
**Sample Methods:**
- IsInOutOfBoundsHazard
- IsInOrOverOutOfBoundsHazard
- HasState

### BoundsManager
**Methods:** 36
**Sample Methods:**
- get_SecondaryOutOfBoundsHazardInstances
- get_LevelHazardInstances
- add_UpdateFinished
- remove_UpdateFinished
- Awake

### SecondaryOutOfBoundsHazardInstance
**Methods:** 1
**Sample Methods:**
- .ctor

### LevelHazardInstance
**Methods:** 1
**Sample Methods:**
- .ctor

### BoundsTrackerInstance
**Methods:** 0

### TrackerOutOfBoundsHazardState
**Methods:** 1
**Sample Methods:**
- .ctor

### NearestPointOnCurve
**Methods:** 0

### JumpPad
**Methods:** 23
**Sample Methods:**
- get_Collider
- Awake
- OnDestroy
- OnStartServer
- OnCollisionStayTriggered

### JumpType
**Methods:** 0

### JumpSettings
**Methods:** 1
**Sample Methods:**
- get_Default

### <>c__DisplayClass21_0
**Methods:** 0

### JumpPadCollider
**Methods:** 6
**Sample Methods:**
- add_OnCollisionStayTriggered
- remove_OnCollisionStayTriggered
- get_Collider
- Awake
- OnCollisionStay

### JumpPadTrigger
**Methods:** 5
**Sample Methods:**
- add_OnTriggerStayTriggered
- remove_OnTriggerStayTriggered
- Awake
- OnTriggerStay
- .ctor

### AutomaticOutOfBoundsBehaviour
**Methods:** 0

### LevelBoundsTracker
**Methods:** 47
**Sample Methods:**
- get_AuthoritativeBoundsState
- get_LocalBoundsState
- set_LocalBoundsState
- get_CurrentOutOfBoundsHazardWorldHeightLocalOnly
- set_CurrentOutOfBoundsHazardWorldHeightLocalOnly

### <<Start>g__RegisterPlayerWhenReady|45_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass61_0
**Methods:** 0

### LevelBoundsTrackerNetworker
**Methods:** 26
**Sample Methods:**
- get_BoundsState
- get_IsOnGreen
- add_BoundsStateChanged
- remove_BoundsStateChanged
- add_IsOnGreenChanged

### LevelBoundsTrackerSettings
**Methods:** 17
**Sample Methods:**
- get_ServerOnly
- set_ServerOnly
- get_DrivingRangeAutomaticOutOfBoundsBehaviour
- set_DrivingRangeAutomaticOutOfBoundsBehaviour
- get_MatchAutomaticOutOfBoundsBehaviour

### LevelBoundsWall
**Methods:** 5
**Sample Methods:**
- Awake
- OnDestroy
- OnBUpdate
- .ctor
- .cctor

### TerrainAddition
**Methods:** 4
**Sample Methods:**
- get_TerrainLayer
- Awake
- OnDestroy
- .ctor

### OutOfBoundsHazard
**Methods:** 0

### LevelHazardType
**Methods:** 0

### OutOfBoundsHazardExtensions
**Methods:** 1
**Sample Methods:**
- GetEliminationReason

### TerrainLayer
**Methods:** 0

### TerrainManager
**Methods:** 30
**Sample Methods:**
- get_Settings
- get_Terrains
- get_TerrainSize
- get_SpatiallyHashedJobsTerrains
- get_AllTerrainLayerWeights

### JobsTerrain
**Methods:** 11
**Sample Methods:**
- .ctor
- GetDominantLayerIndexAt
- GetHeightAt
- WorldPointToEffectiveLocalPoint2d
- ClampLocalPoint2d

### <>c__DisplayClass44_0
**Methods:** 0

### BClientAuthenticator
**Methods:** 17
**Sample Methods:**
- SetVersionGuid
- PrintGuid
- CopyGuid
- OnStartServer
- OnStopServer

### AuthenticationResponse
**Methods:** 0

### ClientCanceledAuthenticationMessage
**Methods:** 0

### IsPasswordRequiredRequestMessage
**Methods:** 0

### IsPasswordRequiredResponseMessage
**Methods:** 0

### AuthenticationRequestMessage
**Methods:** 0

### AuthenticationResponseMessage
**Methods:** 0

### <>c__DisplayClass19_0
**Methods:** 5
**Sample Methods:**
- .ctor
- <OnServerAuthenticationRequestMessage>g__WaitForFriendshipConfirm|0
- <OnServerAuthenticationRequestMessage>g__AcceptRequest|1
- <OnServerAuthenticationRequestMessage>g__DenyRequest|2
- <OnServerAuthenticationRequestMessage>g__DisconnectClient|3

### <<OnServerAuthenticationRequestMessage>g__DisconnectClient|3>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<OnServerAuthenticationRequestMessage>g__WaitForFriendshipConfirm|0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass19_1
**Methods:** 3
**Sample Methods:**
- .ctor
- <OnServerAuthenticationRequestMessage>b__4
- <OnServerAuthenticationRequestMessage>g__OnFriendshipConfirm|5

### <>c__DisplayClass23_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <OnClientIsPasswordRequiredResponseMessage>g__Connect|0
- <OnClientIsPasswordRequiredResponseMessage>g__Cancel|1

### <ClientCancelAuthentication>d__25
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### TransportType
**Methods:** 0

### DisconnectReason
**Methods:** 0

### LobbyMode
**Methods:** 0

### BNetworkManager
**Methods:** 148
**Sample Methods:**
- get_ClientAuthenticator
- set_ClientAuthenticator
- get_IsChangingScene
- get_IsShuttingDown
- set_IsShuttingDown

### <<OpenSteamLobby>g__CreateLobby|157_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<OpenSteamLobby>g__SetLobbyPingLocation|157_1>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c
**Methods:** 3
**Sample Methods:**
- .cctor
- .ctor
- <ConnectToServer>b__179_0

### <>c__DisplayClass135_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <OnServerAddPlayer>g__AddPlayerToDrivingRange|0
- <OnServerAddPlayer>g__AddPlayerToHole|1

### <<OnServerAddPlayer>g__AddPlayerToHole|1>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass135_1
**Methods:** 2
**Sample Methods:**
- .ctor
- <OnServerAddPlayer>g__GetPlayerSpawnData|2

### <<OnServerAddPlayer>g__GetPlayerSpawnData|2>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass151_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <ConnectToSteamLobby>g__ConnectFromMainMenu|0

### <>c__DisplayClass179_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <ConnectToServer>g__CancelConnection|1

### <ConnectToServer>d__179
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <JoinSteamLobby>d__163
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <OnServerAddPlayer>d__135
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <OpenSteamLobby>d__157
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <PollSteamPlayerRelationships>d__120
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <ServerDisconnectClientWithMessage>d__175
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <StopHostWithDisconnectMessage>d__122
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### MaxPlayersUpdatedMessage
**Methods:** 0

### SetPlayerGuidMessage
**Methods:** 0

### DisconnectReasonMessage
**Methods:** 0

### SetStandardCourseMessage
**Methods:** 0

### SetNonStandardCourseMessage
**Methods:** 0

### StartMatchMessage
**Methods:** 0

### RemotePlayerDisconnectMessage
**Methods:** 0

### TriggerNetworkClientToServerExceptionMessage
**Methods:** 0

### RequestNetworkServerToClientExceptionMessage
**Methods:** 0

### TriggerNetworkServerToClientExceptionMessage
**Methods:** 0

### ServerRequestFriendCheckMessage
**Methods:** 0

### ClientFriendCheckConfirmationMessage
**Methods:** 0

### PhysicsManager
**Methods:** 53
**Sample Methods:**
- get_Settings
- get_TerrainAdditionLayerPerColliderId
- get_JumpPadsByCollider
- Awake
- Start

### PredictedContact
**Methods:** 1
**Sample Methods:**
- .ctor

### ColliderType
**Methods:** 0

### RigidbodyType
**Methods:** 0

### <>c__DisplayClass58_0
**Methods:** 0

### EliminationData
**Methods:** 0

### EliminationSettings
**Methods:** 7
**Sample Methods:**
- get_EliminationResponsibilityDuration
- set_EliminationResponsibilityDuration
- OnValidate
- OnEnable
- Initialize

### KnockoutData
**Methods:** 0

### KnockoutSettings
**Methods:** 5
**Sample Methods:**
- OnValidate
- OnEnable
- Initialize
- TryGetKnockoutData
- .ctor

### Foot
**Methods:** 0

### VictoryDance
**Methods:** 0

### LossAnimation
**Methods:** 0

### Emote
**Methods:** 0

### FootExtensions
**Methods:** 1
**Sample Methods:**
- Opposite

### PlayerAnimatorIo
**Methods:** 72
**Sample Methods:**
- get_ShouldGolfCartBriefcaseBeSplit
- set_ShouldGolfCartBriefcaseBeSplit
- get_AimingYawOffset
- get_SpineStraighteningWeight
- add_Footstep

### <AnimateKnockounHitFlinch>d__143
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <BlendLayerRoutine>d__142
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <TransitionFloatRoutine>d__140
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### FootstepAudioMaterial
**Methods:** 0

### AudioHitObjectType
**Methods:** 0

### PlayerAudio
**Methods:** 168
**Sample Methods:**
- Awake
- OnDestroy
- OnStartServer
- PlayFootstepLocalOnly
- PlayJumpForAllClients

### <>c__DisplayClass41_0
**Methods:** 0

### <>c__DisplayClass49_0
**Methods:** 0

### <>c__DisplayClass70_0
**Methods:** 0

### PlayerMatchResolution
**Methods:** 0

### PlayerMatchResolutionExtensions
**Methods:** 1
**Sample Methods:**
- IsResolved

### EliminationReason
**Methods:** 0

### PlayerGolfer
**Methods:** 228
**Sample Methods:**
- get_PlayerInfo
- set_PlayerInfo
- get_IsInitialized
- get_OwnBall
- get_LocalPlayerLatestImmediateEliminationReason

### SwingDistanceEstimation
**Methods:** 1
**Sample Methods:**
- .ctor

### TerrainLayerNormalizedSwingPower
**Methods:** 2
**Sample Methods:**
- get_Invalid
- IsInvalid

### TerrainLayerNormalizedSwingPowerComparer
**Methods:** 1
**Sample Methods:**
- Compare

### <>c__DisplayClass189_0
**Methods:** 0

### <>c__DisplayClass203_0
**Methods:** 0

### <>c__DisplayClass206_0
**Methods:** 0

### <>c__DisplayClass228_0
**Methods:** 0

### <SwingRoutine>d__203
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### PlayerId
**Methods:** 34
**Sample Methods:**
- get_PlayerInfo
- set_PlayerInfo
- get_Guid
- get_PlayerName
- get_PlayerNameNoRichText

### GolfCartSeat
**Methods:** 4
**Sample Methods:**
- get_Invalid
- .ctor
- IsValid
- IsDriver

### PlayerTextPopupType
**Methods:** 0

### PlayerInfo
**Methods:** 323
**Sample Methods:**
- get_HipBone
- set_HipBone
- get_Spine1Bone
- set_Spine1Bone
- get_ChestBone

### <<PopUpInternal>g__ExecuteQueuedPopupsRoutine|269_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass240_0
**Methods:** 4
**Sample Methods:**
- .ctor
- <SetEmoteToPlay>g__EmoteRoutine|0
- <SetEmoteToPlay>g__CanEmote|1
- <SetEmoteToPlay>g__DoesEmoteQualifyforSweetMovesAchievement|2

### <<SetEmoteToPlay>g__EmoteRoutine|0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass248_0
**Methods:** 0

### <>c__DisplayClass294_0
**Methods:** 0

### <>c__DisplayClass305_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <LocalPlayerUpdateIsElectromagnetShieldActive>g__ShouldBeActive|0
- <LocalPlayerUpdateIsElectromagnetShieldActive>g__ElectromagnetShieldRoutine|1

### <<LocalPlayerUpdateIsElectromagnetShieldActive>g__ElectromagnetShieldRoutine|1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass323_0
**Methods:** 0

### PlayerInput
**Methods:** 103
**Sample Methods:**
- get_Controls
- get_IsHoldingAimSwing
- set_IsHoldingAimSwing
- get_IsHoldingChargeSwing
- set_IsHoldingChargeSwing

### <>c__DisplayClass49_0
**Methods:** 0

### PlayerInteractableTargeter
**Methods:** 19
**Sample Methods:**
- get_CurrentTargetEntity
- set_CurrentTargetEntity
- get_HasTarget
- get_FirstTargetInteracable
- get_CurrentTargetReticlePosition

### InteractableHit
**Methods:** 4
**Sample Methods:**
- .ctor
- CompareAgainst
- IsBetterThan
- .cctor

### <>c__DisplayClass31_0
**Methods:** 0

### PlayerInteractor
**Methods:** 4
**Sample Methods:**
- Awake
- TryInteract
- .ctor
- <TryInteract>g__CanInteract|2_0

### InventorySlot
**Methods:** 2
**Sample Methods:**
- get_Empty
- .ctor

### ItemUseId
**Methods:** 5
**Sample Methods:**
- .ctor
- IsValid
- Equals
- GetHashCode
- .cctor

### ItemUseType
**Methods:** 0

### PlayerInventory
**Methods:** 257
**Sample Methods:**
- get_PlayerInfo
- set_PlayerInfo
- get_CurrentItemUse
- set_CurrentItemUse
- get_ItemUseTimestamp

### ThrownItemHand
**Methods:** 0

### <<PlaceGolfCartRoutine>g__WaitToEnterPlacedGolfCartRoutine|168_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<TryUseSpringBoots>g__UseSpringBootsRoutine|126_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass108_0
**Methods:** 0

### <>c__DisplayClass120_0
**Methods:** 0

### <>c__DisplayClass121_0
**Methods:** 7
**Sample Methods:**
- .ctor
- <TryUseItem>g__GetItemUseRoutine|0
- <TryUseItem>g__FlourishItem|1
- <TryUseItem>g__FlourishRoutine|2
- <TryUseItem>g__ShouldPlayEffects|4

### <<TryUseItem>g__FlourishRoutine|2>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass121_1
**Methods:** 0

### <>c__DisplayClass185_0
**Methods:** 0

### <>c__DisplayClass188_0
**Methods:** 0

### <>c__DisplayClass198_0
**Methods:** 0

### <>c__DisplayClass205_0
**Methods:** 0

### <>c__DisplayClass219_0
**Methods:** 0

### <ActivateElectromagnetRoutine>d__174
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ActivateOrbitalLaserRoutine>d__176
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <BlowAirhornRoutine>d__167
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <DrinkCoffeeRoutine>d__163
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <PlaceGolfCartRoutine>d__168
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <PlantLandmineRoutine>d__172
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ShootDuelingPistolRoutine>d__164
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ShootElephantGunRoutine>d__165
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ShootFreezeBombRoutine>d__178
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <ShootRocketLauncherRoutine>d__166
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <TossLandmineRoutine>d__173
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### PlayerGroundData
**Methods:** 0

### JumpType
**Methods:** 0

### StatusEffect
**Methods:** 0

### KnockoutType
**Methods:** 0

### DivingState
**Methods:** 0

### DiveType
**Methods:** 0

### RespawnState
**Methods:** 0

### GolfCartExitType
**Methods:** 0

### StatusEffectExtensions
**Methods:** 1
**Sample Methods:**
- HasEffect

### DiveTypeExtensions
**Methods:** 1
**Sample Methods:**
- IsElephantGunDive

### KnockoutState
**Methods:** 0

### KnockoutRecoveryType
**Methods:** 0

### GroundTerrainType
**Methods:** 0

### RespawnTarget
**Methods:** 0

### PlayerMovement
**Methods:** 366
**Sample Methods:**
- get_PlayerInfo
- set_PlayerInfo
- get_RawMoveVectorMagnitude
- set_RawMoveVectorMagnitude
- get_MoveVectorMagnitude

### KnockedOutVfxData
**Methods:** 2
**Sample Methods:**
- .ctor
- get_None

### KnockOutImmunity
**Methods:** 2
**Sample Methods:**
- Get
- Reset

### <<AddSpeedBoost>g__AddSpeedBoostAtEndOfFrame|326_1>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<InformEnteringGolfCart>g__TimeOutGolfCartBeingEnteredRoutine|267_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<InformExitedGolfCart>g__TemporarilyIgnoreKnockoutsFrom|271_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<PlayKnockoutBlockedEffectInternal>g__PlayEffectAtEndOfFrame|241_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<RecoverFromKnockout>g__KnockoutRecoveryRoutine|316_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass227_0
**Methods:** 0

### <>c__DisplayClass234_0
**Methods:** 0

### <>c__DisplayClass251_0
**Methods:** 4
**Sample Methods:**
- .ctor
- <LocalPlayerBeginRespawn>g__RespawnRoutine|0
- <LocalPlayerBeginRespawn>g__TeleportToRespawnPosition|1
- <LocalPlayerBeginRespawn>g__PlayRespawnEffectsForAllClients|2

### <<LocalPlayerBeginRespawn>g__RespawnRoutine|0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass270_0
**Methods:** 0

### <>c__DisplayClass318_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <StartKnockoutImmunity>g__KnockoutImmunityRoutine|0
- <StartKnockoutImmunity>g__IsStillInPlayerAgressionImmunity|1

### <<StartKnockoutImmunity>g__KnockoutImmunityRoutine|0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass344_0
**Methods:** 0

### <>c__DisplayClass364_0
**Methods:** 0

### <BlendStrafeStrengthRoutine>d__333
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <LocalPlayerUpdateVisibilityDelayed>d__334
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### PlayerOcclusion
**Methods:** 6
**Sample Methods:**
- IsOccluded
- TimeSinceVisible
- SetInstanceId
- OnEnable
- OnDisable

### PlayerOcclusionManager
**Methods:** 10
**Sample Methods:**
- Awake
- OnDestroy
- RegisterInstance
- DeregisterInstance
- IsOccluded

### State
**Methods:** 0

### SetupRaycastsJob
**Methods:** 1
**Sample Methods:**
- Execute

### UpdateOcclusion
**Methods:** 1
**Sample Methods:**
- Execute

### PlayerShaderDataHelper
**Methods:** 2
**Sample Methods:**
- SetPlayerIndex
- SetPlayerShaderIndexOnRenderers

### PlayerShaderDataManager
**Methods:** 11
**Sample Methods:**
- Awake
- OnDestroy
- Update
- PreCull
- GetPlayerShaderIndex

### PlayerSpectator
**Methods:** 77
**Sample Methods:**
- get_PlayerInfo
- set_PlayerInfo
- get_IsSpectating
- get_TargetPlayer
- set_TargetPlayer

### <<StartSpectatingDelayed>g__SpectateDelayedRoutine|58_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass55_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <CycleNextTargetDelayed>g__SpectateDelayedRoutine|0

### <<CycleNextTargetDelayed>g__SpectateDelayedRoutine|0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass68_0
**Methods:** 4
**Sample Methods:**
- .ctor
- <TryGetCycleTarget>g__TryGetPlayerTarget|0
- <TryGetCycleTarget>g__TryGetBallTarget|1
- <TryGetCycleTarget>b__2

### PlayerVfx
**Methods:** 16
**Sample Methods:**
- get_PlayerInfo
- OnEnable
- OnDisable
- Awake
- OnWillBeDestroyed

### PlayerVoiceChat
**Methods:** 22
**Sample Methods:**
- InitializeStatics
- SetPlayerVolume
- SetIsPlayerMuted
- UpdateInstancePersistentPlayerStatus
- GetPlayerStatus

### PersistentPlayerStatus
**Methods:** 5
**Sample Methods:**
- get_Default
- Write
- Read
- UpdateTimestamp
- IsDefault

### TerrainGrassRenderer
**Methods:** 13
**Sample Methods:**
- OnEnable
- OnDisable
- UpdateRenderParams
- ScheduleCameraJobs
- LateUpdate

### Tile
**Methods:** 0

### GetValidTilesJob
**Methods:** 4
**Sample Methods:**
- Execute
- distanceToPlane
- isPointAbovePlane
- isInsideFrustum

### GenerateBatchJob
**Methods:** 1
**Sample Methods:**
- Execute

### LodBatchJobData
**Methods:** 4
**Sample Methods:**
- .ctor
- ScheduleJob
- Render
- Dispose

### <>c__DisplayClass25_0
**Methods:** 0

### TerrainGrassRendererSettings
**Methods:** 1
**Sample Methods:**
- .ctor

### LodData
**Methods:** 1
**Sample Methods:**
- .ctor

### FuzzySettings
**Methods:** 1
**Sample Methods:**
- .ctor

### RimlightSettings
**Methods:** 0

### SsprPlane
**Methods:** 1
**Sample Methods:**
- .ctor

### ScreenSpacePlanarReflections
**Methods:** 16
**Sample Methods:**
- Awake
- Start
- OnEnable
- OnDisable
- OnDestroy

### SsprPlaneObject
**Methods:** 3
**Sample Methods:**
- Awake
- Update
- .ctor

### BInputSettings
**Methods:** 15
**Sample Methods:**
- get_DefaultBufferDuration
- set_DefaultBufferDuration
- get_InteractBufferDuration
- set_InteractBufferDuration
- get_MinNonPuttPitch

### CameraGameplaySettings
**Methods:** 40
**Sample Methods:**
- get_IntoSwingAimTransitionDuration
- set_IntoSwingAimTransitionDuration
- get_OutOfSwingAimTransitionDuration
- set_OutOfSwingAimTransitionDuration
- get_SwingAimVerticalTrackingOffset

### GolfSettings
**Methods:** 134
**Sample Methods:**
- get_BallPrefab
- set_BallPrefab
- get_TeeBallLocalSpawnHeight
- set_TeeBallLocalSpawnHeight
- get_TeePostHitSizeCurve

### LayerSettings
**Methods:** 97
**Sample Methods:**
- get_StationaryBallLayer
- set_StationaryBallLayer
- get_DynamicBallLayer
- set_DynamicBallLayer
- get_HittablesLayer

### MatchSettings
**Methods:** 67
**Sample Methods:**
- get_HoleOverviewInitialBlankDuration
- set_HoleOverviewInitialBlankDuration
- get_HoleOverviewHoleNameDuration
- set_HoleOverviewHoleNameDuration
- get_HoleOverviewFinalBlankDuration

### ParSpeedrunTime
**Methods:** 1
**Sample Methods:**
- CompareTo

### ComebackBonus
**Methods:** 0

### OutOfBoundsHazardSettings
**Methods:** 7
**Sample Methods:**
- get_Type
- set_Type
- get_SwingPowerBarColor
- set_SwingPowerBarColor
- get_SwingPowerBarOutOfBoundsOverlayColor

### PhysicsSettings
**Methods:** 23
**Sample Methods:**
- get_PlayerMaterial
- set_PlayerMaterial
- get_PlayerKnockedOutMaterial
- set_PlayerKnockedOutMaterial
- get_PlayerDivingMaterial

### PlayerInventorySettings
**Methods:** 5
**Sample Methods:**
- get_MaxItems
- set_MaxItems
- get_DropItemVerticalOffset
- set_DropItemVerticalOffset
- .ctor

### PlayerMovementSettings
**Methods:** 110
**Sample Methods:**
- get_DefaultMoveSpeed
- set_DefaultMoveSpeed
- get_WalkMoveSpeed
- set_WalkMoveSpeed
- get_SwingAimingSpeed

### PlayerTargetingSettings
**Methods:** 7
**Sample Methods:**
- get_SearchConeDistance
- set_SearchConeDistance
- get_SearchConeAperture
- set_SearchConeAperture
- get_SearchConeBaseDiameter

### TeeingPlatformSettings
**Methods:** 14
**Sample Methods:**
- get_TeePrefab
- set_TeePrefab
- get_TeeVerticalOffset
- set_TeeVerticalOffset
- get_MaxTeeCount

### TerrainLayerSettings
**Methods:** 49
**Sample Methods:**
- get_Layer
- set_Layer
- get_LayerAsset
- set_LayerAsset
- get_SwingPowerBarColor

### JobsPhysicsData
**Methods:** 1
**Sample Methods:**
- .ctor

### TerrainSettings
**Methods:** 10
**Sample Methods:**
- get_Layers
- set_Layers
- get_OutOfBoundsHazards
- set_OutOfBoundsHazards
- get_JobsBallTerrainCollisionMaterialPerTerrainLayer

### TextHighlight
**Methods:** 0

### UiSettings
**Methods:** 53
**Sample Methods:**
- get_UnknownItemIcon
- set_UnknownItemIcon
- get_LoadingScreenBackgroundColor
- set_LoadingScreenBackgroundColor
- get_TextHighlightColor

### AheadOfBallMessage
**Methods:** 9
**Sample Methods:**
- Awake
- Show
- Hide
- ShowInternal
- HideInternal

### <<FadeTo>g__FadeRoutine|14_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### SpeedBoostWheelUi
**Methods:** 7
**Sample Methods:**
- Awake
- OnDestroy
- OnLateBUpdate
- AnimateVisibilityRoutine
- .ctor

### <AnimateVisibilityRoutine>d__9
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### BallStatusMessage
**Methods:** 16
**Sample Methods:**
- get_ReturnedMessage
- Awake
- OnDestroy
- SetReturned
- Clear

### Status
**Methods:** 0

### <<FadeTo>g__FadeRoutine|20_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<SetDisplayedStatus>g__ClearReturnedMessageDelayed|16_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ColorOverlay
**Methods:** 18
**Sample Methods:**
- get_IsActive
- get_IsFading
- Awake
- SetColor
- ShowInstantly

### <FadeToInternal>d__20
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ConnectionWarningUi
**Methods:** 3
**Sample Methods:**
- Awake
- Update
- .ctor

### <>c
**Methods:** 4
**Sample Methods:**
- .cctor
- .ctor
- <Update>b__6_0
- <Update>b__6_1

### CurrencyDisplay
**Methods:** 6
**Sample Methods:**
- OnEnable
- OnDisable
- OnCurrencyUpdate
- Timeout
- OnAnimationCreditsUpdate

### <>c
**Methods:** 4
**Sample Methods:**
- .cctor
- .ctor
- <OnCurrencyUpdate>b__12_0
- <Timeout>b__13_0

### <Timeout>d__13
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### FirstToHoleWinsMessageUi
**Methods:** 10
**Sample Methods:**
- Awake
- Start
- OnDestroy
- TryDisplay
- OnCurrentHoleCourseIndexChanged

### <<TryDisplay>g__DisplayRoutine|9_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<TryDisplay>g__FadeRoutine|9_2>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### FullScreenMessage
**Methods:** 25
**Sample Methods:**
- get_Instance
- get_IsDisplayingAnyMessage
- get_IsDisplayingError
- get_InputFieldText
- Awake

### ButtonEntry
**Methods:** 1
**Sample Methods:**
- .ctor

### <<ActiveSceneChanged>g__AssertFocusDelayed|24_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<ShowInternal>g__EnableInputs|34_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### GameplayScreenspaceUiCanvas
**Methods:** 2
**Sample Methods:**
- get_Canvas
- .ctor

### GameVersionLabel
**Methods:** 3
**Sample Methods:**
- GetVersion
- Awake
- .ctor

### HoleInfoUi
**Methods:** 16
**Sample Methods:**
- get_IsVisible
- Awake
- Start
- OnDestroy
- UpdateAll

### <<FadeAway>g__FadeAwayRoutine|23_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### HoleOverviewCameraUi
**Methods:** 19
**Sample Methods:**
- OnStartClient
- Show
- Hide
- SetState
- ShowInternal

### State
**Methods:** 0

### <<OnIsVisibleChanged>g__FadeToRoutine|15_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass16_0
**Methods:** 0

### HoleProgressBarPlayerEntryUi
**Methods:** 16
**Sample Methods:**
- get_NormalizedProgress
- set_NormalizedProgress
- get_IsLocalPlayer
- Awake
- OnDestroy

### HoleProgressBarUi
**Methods:** 32
**Sample Methods:**
- Awake
- Start
- OnDestroy
- UpdateStrokes
- IncrementStrokes

### <<SetStrokes>g__FadeRoutine|20_2>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<SetStrokes>g__ShowStrokesRoutine|20_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass28_0
**Methods:** 0

### HotkeyMode
**Methods:** 0

### Hotkeys
**Methods:** 62
**Sample Methods:**
- get_SelectedIndex
- get_CurrentMode
- add_ModeChanged
- remove_ModeChanged
- Awake

### <<UpdateInventoryPitchVisibility>g__FadeToRoutine|59_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass55_0
**Methods:** 0

### <>c__DisplayClass69_0
**Methods:** 0

### <UpdateGolfClubIcon>d__37
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### HotkeyUi
**Methods:** 16
**Sample Methods:**
- get_RectTransform
- Awake
- Initialize
- ShowButtonPrompt
- HideButtonPrompt

### <AnimateSelectionRoutine>d__29
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### ButtonPrompt
**Methods:** 5
**Sample Methods:**
- Initialize
- OnEnable
- OnDisable
- UpdatePrompt
- .ctor

### ButtonPromptExplicit
**Methods:** 4
**Sample Methods:**
- OnEnable
- OnDisable
- UpdateIcon
- .ctor

### ButtonPromptManager
**Methods:** 5
**Sample Methods:**
- GetButtonPrompt
- ReturnButtonPrompt
- GetButtonPromptInternal
- ReturnButtonPromptInternal
- .ctor

### Type
**Methods:** 0

### HudManager
**Methods:** 6
**Sample Methods:**
- Show
- Hide
- ShowInternal
- HideInternal
- AnimateVisibilityRoutine

### <AnimateVisibilityRoutine>d__6
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### RestartPrompt
**Methods:** 11
**Sample Methods:**
- Awake
- OnDestroy
- CanBePressed
- ShouldBeVisible
- UpdateLabel

### <>c
**Methods:** 4
**Sample Methods:**
- .cctor
- .ctor
- <Update>b__15_0
- <Update>b__15_1

### InfoFeed
**Methods:** 95
**Sample Methods:**
- get_Player0Color
- get_Player1Color
- get_IconSettings
- get_MessageDuration
- get_MessageSlideInDuration

### IMessageData
**Methods:** 0

### KnockoutMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### EliminationMessaqeData
**Methods:** 1
**Sample Methods:**
- .ctor

### SelfKnockoutMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### SelfEliminationMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### FinishedHoleMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### ScoredOnDrivingRangeMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### StrokesMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### ChipInMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### SpeedrunMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### DominatingMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### RevengeMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### ComebackMessageData
**Methods:** 1
**Sample Methods:**
- .ctor

### InfoFeedIconType
**Methods:** 0

### InfoFeedIconSettings
**Methods:** 5
**Sample Methods:**
- OnValidate
- OnEnable
- Initialize
- TryGetIcon
- .ctor

### Icon
**Methods:** 0

### InfoFeedMessage
**Methods:** 26
**Sample Methods:**
- get_IsFadingOut
- set_IsFadingOut
- Awake
- Initialize
- OnUpdate

### <>c__DisplayClass18_0
**Methods:** 0

### <FadeOut>d__20
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SlideIn>d__19
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### LabelOverflowScroll
**Methods:** 5
**Sample Methods:**
- Awake
- OnDisable
- Update
- Reset
- .ctor

### LoadingScreen
**Methods:** 15
**Sample Methods:**
- get_IsVisible
- get_IsFadingScreenIn
- get_IsFadingScreenOut
- Awake
- OnDestroy

### <<HideInternal>g__HideRoutine|29_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<ShowInternal>g__ShowRoutine|28_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### LockOnTargetUi
**Methods:** 7
**Sample Methods:**
- Awake
- OnLateUpdate
- SetTarget
- .ctor
- <OnLateUpdate>g__UpdatePosition|5_0

### LockOnTargetUiManager
**Methods:** 17
**Sample Methods:**
- Awake
- OnDestroy
- AddTarget
- RemoveTarget
- ClearTargets

### MatchEndCountdown
**Methods:** 27
**Sample Methods:**
- get_DisplayedTime
- Awake
- Show
- Hide
- EnterOvertime

### <<Pop>g__PopRoutine|24_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### CreditsRoll
**Methods:** 4
**Sample Methods:**
- OnEnable
- Update
- ResetScroll
- .ctor

### LobbyBrowser
**Methods:** 55
**Sample Methods:**
- get_IsActive
- get_DefaultEntryColor
- get_SelectedEntryColor
- get_settingsPath
- Awake

### FriendInfo
**Methods:** 18
**Sample Methods:**
- get_SteamFriend
- set_SteamFriend
- get_SteamLobby
- set_SteamLobby
- .ctor

### LobbyCmp
**Methods:** 2
**Sample Methods:**
- Compare
- .ctor

### SortMode
**Methods:** 0

### Lobby
**Methods:** 23
**Sample Methods:**
- get_SteamLobby
- set_SteamLobby
- get_Entry
- set_Entry
- get_Ping

### FilterSettings
**Methods:** 1
**Sample Methods:**
- .ctor

### <<RefreshLobbiesInternal>g__UpdateLobbies|79_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<RefreshLobbiesInternal>g__UpdateOnlinePlayers|79_1>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass58_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <Awake>b__8

### <>c__DisplayClass70_0
**Methods:** 0

### <>c__DisplayClass76_0
**Methods:** 0

### <>c__DisplayClass82_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <AddLobby>b__0
- <AddLobby>b__1

### <QuickRefresh>d__74
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <QuickRefreshInternal>d__77
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <RefreshInternal>d__76
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <RefreshLobbiesInternal>d__79
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <WaitForLobbyRefresh>d__80
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### LobbyEntryUi
**Methods:** 6
**Sample Methods:**
- Awake
- OnControllerSelected
- Initialize
- RefreshLobby
- SetIsSelected

### MainMenu
**Methods:** 18
**Sample Methods:**
- Awake
- Start
- OnDestroy
- OpenDiscord
- StartHost

### <<Start>g__ConnectToPresetLobby|23_1>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<Start>g__TimeOutIntro|23_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c
**Methods:** 3
**Sample Methods:**
- .cctor
- .ctor
- <StartHost>b__26_0

### <StartHost>d__26
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### MainMenuButton
**Methods:** 9
**Sample Methods:**
- Awake
- OnDestroy
- OnPointerEnter
- OnPointerExit
- OnDisable

### LocAdjustment
**Methods:** 0

### MatchSetupCoursesTab
**Methods:** 3
**Sample Methods:**
- OnEnable
- ResetHoleScrollRects
- .ctor

### MatchSetupHole
**Methods:** 18
**Sample Methods:**
- Start
- OnControllerSubmit
- Update
- OnDisable
- Swap

### MatchSetupMenu
**Methods:** 88
**Sample Methods:**
- get_CustomCourseData
- set_CustomCourseData
- get_RandomCourseData
- set_RandomCourseData
- get_IsActive

### SelectableChildIndexCmp
**Methods:** 2
**Sample Methods:**
- Compare
- .ctor

### ServerValues
**Methods:** 1
**Sample Methods:**
- .ctor

### <>c
**Methods:** 3
**Sample Methods:**
- .cctor
- .ctor
- <SortInactiveHoles>b__90_0

### <>c__DisplayClass80_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <InitializeCourses>b__4

### <>c__DisplayClass96_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <LoadValues>b__4

### <>c__DisplayClass98_0
**Methods:** 0

### MatchSetupPlayer
**Methods:** 26
**Sample Methods:**
- get_Guid
- get_isLocalPlayer
- Awake
- OnEnable
- OnDisable

### <>c__DisplayClass35_0
**Methods:** 0

### MatchSetupRules
**Methods:** 74
**Sample Methods:**
- get_CurrentPreset
- add_UpdateItemSpawnersLoc
- remove_UpdateItemSpawnersLoc
- add_RulesPopulated
- remove_RulesPopulated

### ItemPoolId
**Methods:** 1
**Sample Methods:**
- Get

### Rule
**Methods:** 0

### RuleCategory
**Methods:** 0

### Preset
**Methods:** 0

### <<OnItemLayoutSet>g__UpdateNavigationDelayed|119_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c
**Methods:** 4
**Sample Methods:**
- .cctor
- .ctor
- <Initialize>b__66_4
- <Initialize>b__66_5

### <>c__DisplayClass106_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <InitSlider>b__0

### <>c__DisplayClass107_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <InitDropdownOnOff>b__0

### <>c__DisplayClass108_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <InitDropdown>b__0

### <>c__DisplayClass66_0
**Methods:** 7
**Sample Methods:**
- .ctor
- <Initialize>b__0
- <Initialize>b__1
- <Initialize>b__2
- <Initialize>b__3

### <>c__DisplayClass66_1
**Methods:** 2
**Sample Methods:**
- .ctor
- <Initialize>g__UpdateLocString|8

### <>c__DisplayClass66_2
**Methods:** 3
**Sample Methods:**
- .ctor
- <Initialize>b__9
- <Initialize>b__10

### <>c__DisplayClass70_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <UpdateCurrentItemPool>b__0
- <UpdateCurrentItemPool>b__1

### <>c__DisplayClass77_0
**Methods:** 0

### MenuTabs
**Methods:** 9
**Sample Methods:**
- Awake
- Update
- CycleTabLeft
- CycleTabRight
- WrapIndex

### <>c__DisplayClass8_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <Awake>b__0

### <AnimateButton>d__15
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### PauseMenu
**Methods:** 41
**Sample Methods:**
- get_IsPaused
- get_ResumeButton
- add_Paused
- remove_Paused
- add_Unpaused

### <>c__DisplayClass72_0
**Methods:** 0

### <>c__DisplayClass77_0
**Methods:** 0

### PauseMenuPlayerEntry
**Methods:** 31
**Sample Methods:**
- get_CurrentPlayerGuid
- set_CurrentPlayerGuid
- get_IsLocalPlayer
- Awake
- OnDisable

### <>c__DisplayClass47_0
**Methods:** 10
**Sample Methods:**
- .ctor
- <AssignPlayer>b__0
- <AssignPlayer>b__1
- <AssignPlayer>g__OnSetOwnVolume|2
- <AssignPlayer>g__RefreshMutedToggle|3

### PlayerCustomizationCosmeticButton
**Methods:** 1
**Sample Methods:**
- .ctor

### PlayerCustomizationMenu
**Methods:** 95
**Sample Methods:**
- get_IsActive
- add_OnOpened
- remove_OnOpened
- add_OnClosed
- remove_OnClosed

### NavigationMode
**Methods:** 0

### MetadataCmp
**Methods:** 2
**Sample Methods:**
- Compare
- .ctor

### MetadataReference
**Methods:** 2
**Sample Methods:**
- Dispose
- .ctor

### PersistentData
**Methods:** 4
**Sample Methods:**
- HasAcknowledgedCosmetic
- AcknowledgeCosmetic
- IsValid
- .ctor

### <<LoadCategories>g__LoadMetadata|94_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass100_0
**Methods:** 1
**Sample Methods:**
- .ctor

### <>c__DisplayClass100_1
**Methods:** 2
**Sample Methods:**
- .ctor
- <UpdateColors>b__0

### <>c__DisplayClass101_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <InitSkinColors>b__0

### <>c__DisplayClass112_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <UpdateOwnershipWarnings>b__0
- <UpdateOwnershipWarnings>b__1

### <>c__DisplayClass113_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <UpdateOwnershipWarnings>b__0
- <UpdateOwnershipWarnings>b__1

### <>c__DisplayClass114_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <UpdateOwnershipWarningsInternal>g__OnBuy|0

### <>c__DisplayClass72_0
**Methods:** 0

### <>c__DisplayClass72_1
**Methods:** 2
**Sample Methods:**
- .ctor
- <UpdateCategoryUnequipWarning>b__1

### <>c__DisplayClass76_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <UpdateLoadoutToggles>b__0

### <>c__DisplayClass96_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <UpdateDanceButtons>b__1

### <>c__DisplayClass98_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <UpdateCosmeticsButtons>b__1

### <>c__DisplayClass99_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <UpdateButtonCost>b__0
- <UpdateButtonCost>b__1

### <>c__DisplayClass99_1
**Methods:** 2
**Sample Methods:**
- .ctor
- <UpdateButtonCost>b__2

### <LoadCategories>d__94
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <RegisterBUpdateDelayed>d__81
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetBodyModel>d__123
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetBrowsTexture>d__126
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetCheeksTexture>d__127
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetClubModel>d__120
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetEyesTexture>d__125
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetFaceModel>d__121
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetGolfBallModel>d__128
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetHairModel>d__119
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetHatModel>d__117
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetHeadModel>d__118
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetLoadout>d__75
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetLowerFaceModel>d__122
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SetMouthTexture>d__124
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <StressTest>d__67
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### RadialMenuMode
**Methods:** 0

### RadialMenu
**Methods:** 44
**Sample Methods:**
- get_WasOpenThisOrLastFrame
- add_OnSelected
- remove_OnSelected
- get_Size
- get_OptionSettings

### <<HideInternal>g__HideRoutine|50_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass49_0
**Methods:** 4
**Sample Methods:**
- .ctor
- <TryShowInternal>g__ShowRoutine|0
- <TryShowInternal>b__1
- <TryShowInternal>b__2

### <<TryShowInternal>g__ShowRoutine|0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass62_0
**Methods:** 0

### RadialMenuOptionSettings
**Methods:** 22
**Sample Methods:**
- get_Material
- set_Material
- get_SpacingWidth
- set_SpacingWidth
- get_HighlightAnimationDuration

### RadialMenuOptionUi
**Methods:** 16
**Sample Methods:**
- get_RectTransform
- set_RectTransform
- get_SelectionIndex
- set_SelectionIndex
- Awake

### <<SetIsHighlighted>g__AnimateHighlightRoutine|26_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### RadialMenuUi
**Methods:** 9
**Sample Methods:**
- get_Options
- Awake
- OnDestroy
- OnWillChangeScene
- ClearOptions

### ReorderableList
**Methods:** 13
**Sample Methods:**
- get_Current
- set_Current
- add_OnElementMoved
- remove_OnElementMoved
- Awake

### <AnimateRoutine>d__18
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ReorderableListElement
**Methods:** 15
**Sample Methods:**
- get_Button
- get_CurrentParent
- add_OnAssignedToParent
- remove_OnAssignedToParent
- add_OnSelected

### ActionRebindOption
**Methods:** 13
**Sample Methods:**
- Initialize
- SetVerticalNavigationTarget
- SetVerticalNavigationTarget
- SetAsSelectableNavigationDownTarget
- GetLocalizedBindingName

### RebindButton
**Methods:** 0

### <>c__DisplayClass16_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <SetupRebindButton>b__0
- <SetupRebindButton>b__1

### ControlRebindSettings
**Methods:** 4
**Sample Methods:**
- OnValidate
- OnEnable
- Initialize
- .ctor

### MapActionPair
**Methods:** 0

### ControlsRebind
**Methods:** 22
**Sample Methods:**
- get_RebindCanceledTimestamp
- set_RebindCanceledTimestamp
- Awake
- OnEnable
- OnDisable

### <>c__DisplayClass20_0
**Methods:** 5
**Sample Methods:**
- .ctor
- <PerformRebind>g__CleanUp|0
- <PerformRebind>b__1
- <PerformRebind>b__2
- <PerformRebind>g__CompleteSuccess|3

### <<PerformRebind>g__CleanUp|0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c__DisplayClass21_0
**Methods:** 0

### <>c__DisplayClass22_0
**Methods:** 4
**Sample Methods:**
- .ctor
- <HandleOverlap>g__Override|1
- <HandleOverlap>g__Cancel|2
- <HandleOverlap>g__Complete|3

### DropdownOption
**Methods:** 14
**Sample Methods:**
- get_captionText
- get_Localized
- get_Interactable
- set_Interactable
- get_OptionsCount

### DropdownSelectableCancel
**Methods:** 2
**Sample Methods:**
- Awake
- .ctor

### IGameSettings
**Methods:** 1
**Sample Methods:**
- Initialize

### GameSettings
**Methods:** 6
**Sample Methods:**
- get_All
- Initialize
- ApplyAndSave
- SaveWithoutApplying
- SaveInputBindings

### AudioSettings
**Methods:** 39
**Sample Methods:**
- get_MasterVolume
- set_MasterVolume
- get_MusicVolume
- set_MusicVolume
- get_SfxVolume

### InputMode
**Methods:** 0

### Device
**Methods:** 0

### GraphicsSettings
**Methods:** 34
**Sample Methods:**
- get_MSAA
- set_MSAA
- get_VSync
- set_VSync
- get_FpsLimit

### Quality
**Methods:** 0

### GeneralSettings
**Methods:** 33
**Sample Methods:**
- get_ScreenshakeFactor
- set_ScreenshakeFactor
- get_FlashingEffects
- set_FlashingEffects
- get_ShowNameTags

### ButtonPromptVisibility
**Methods:** 0

### DistanceUnit
**Methods:** 0

### SpeedUnit
**Methods:** 0

### ControlSettings
**Methods:** 5
**Sample Methods:**
- get_Camera
- get_Mouse
- get_Controller
- Initialize
- .ctor

### AxisSetting
**Methods:** 2
**Sample Methods:**
- ScaleInput
- .ctor

### TutorialProgress
**Methods:** 9
**Sample Methods:**
- get_Version
- set_Version
- get_CompletedObjectives
- get_CompletedPrompts
- Initialize

### AllSettings
**Methods:** 8
**Sample Methods:**
- get_Audio
- get_Graphics
- get_General
- get_Controls
- get_TutorialProgress

### SettingsMenu
**Methods:** 26
**Sample Methods:**
- Start
- UpdateTooltips
- OnEnable
- RefreshAudioDevices
- SetShadowQuality

### <>c__DisplayClass49_0
**Methods:** 10
**Sample Methods:**
- .ctor
- <Start>b__9
- <Start>b__10
- <Start>b__11
- <Start>b__12

### <>c__DisplayClass49_1
**Methods:** 10
**Sample Methods:**
- .ctor
- <Start>b__18
- <Start>b__19
- <Start>b__20
- <Start>b__21

### <>c__DisplayClass49_2
**Methods:** 10
**Sample Methods:**
- .ctor
- <Start>b__27
- <Start>b__28
- <Start>b__29
- <Start>b__30

### <>c__DisplayClass49_3
**Methods:** 9
**Sample Methods:**
- .ctor
- <Start>b__36
- <Start>b__37
- <Start>b__38
- <Start>b__39

### <>c__DisplayClass52_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <RefreshAudioDevices>b__0
- <RefreshAudioDevices>b__1

### SliderOption
**Methods:** 20
**Sample Methods:**
- get_Slider
- get_label
- get_value
- set_value
- set_valueWithoutNotify

### ToggleOption
**Methods:** 6
**Sample Methods:**
- get_isOn
- set_isOn
- Initialize
- SetIsOn
- OnValueChanged

### UiFadeEnable
**Methods:** 5
**Sample Methods:**
- Awake
- OnDisable
- Update
- SetActive
- .ctor

### UiMouseFollow
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### UiTooltip
**Methods:** 14
**Sample Methods:**
- add_HoverChanged
- remove_HoverChanged
- RegisterTooltip
- DeregisterTooltip
- OverrideText

### NameTagManager
**Methods:** 10
**Sample Methods:**
- get_PlayerNameTagSettings
- get_BallNameTagSettings
- get_SpectatorNameTagSettings
- GetUnusedNameTag
- ReturnNameTag

### NameTagUi
**Methods:** 10
**Sample Methods:**
- Awake
- Initialize
- LateUpdate
- SetName
- .ctor

### NameTagUiSettings
**Methods:** 26
**Sample Methods:**
- get_FadeStartDistance
- set_FadeStartDistance
- get_FadeEndDistance
- set_FadeEndDistance
- get_MinTextSize

### SelectableActiveMode
**Methods:** 0

### ControllerSelectable
**Methods:** 43
**Sample Methods:**
- get_IsInteractableSelf
- set_IsInteractableSelf
- get_AsSlider
- set_AsSlider
- get_AsDropdown

### GridNavigationGroup
**Methods:** 13
**Sample Methods:**
- InsertRow
- InsertRowsFrom
- UpdateNavigation
- .ctor
- <UpdateNavigation>g__FindNavigationLeftTarget|5_0

### Row
**Methods:** 2
**Sample Methods:**
- CreateBlankRow
- .ctor

### Element
**Methods:** 1
**Sample Methods:**
- .ctor

### MenuNavigation
**Methods:** 25
**Sample Methods:**
- get_ShouldShowVirtualKeyboard
- add_OnExitEvent
- remove_OnExitEvent
- SendExitEvent
- OnEnable

### NavigationDirection
**Methods:** 0

### <>c__DisplayClass26_0
**Methods:** 0

### <>c__DisplayClass26_1
**Methods:** 0

### <Reselect>d__23
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### SingleAxisNavigationGroup
**Methods:** 6
**Sample Methods:**
- Awake
- OnEnable
- OnTransformChildrenChanged
- OnValidate
- UpdateNavigation

### Axis
**Methods:** 0

### UiSfx
**Methods:** 12
**Sample Methods:**
- OnPointerClick
- OnPointerEnter
- Start
- OnEnable
- ShouldSupressSfx

### Type
**Methods:** 0

### NextMatchCountdown
**Methods:** 28
**Sample Methods:**
- get_NextMatchCountdownMessage
- get_CourseEndedCountdownMessage
- Awake
- OnDestroy
- Show

### OutOfBoundsMessage
**Methods:** 18
**Sample Methods:**
- get_UnformattedMessage
- Awake
- OnDestroy
- Show
- Hide

### <<ForceHideTemporarilyInternal>g__ForceHideTemporarilyRoutine|20_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<UpdateVisibility>g__FadeRoutine|22_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### PlayerIconManager
**Methods:** 7
**Sample Methods:**
- GetPlayerIconFromSteamId
- GetPlayerIcon
- GetPlayerIcon
- GetPlayerIconInternal
- OnDestroy

### IconSize
**Methods:** 0

### <>c__DisplayClass6_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <GetPlayerIconInternal>g__LoadIconAsync|0

### <<GetPlayerIconInternal>g__LoadIconAsync|0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ReticleManager
**Methods:** 12
**Sample Methods:**
- Awake
- SetDuelingPistol
- SetElephantGun
- SetRocketLauncher
- SetFreezeBomb

### Scoreboard
**Methods:** 27
**Sample Methods:**
- get_ScoredIcon
- get_EliminatedIcon
- get_IsVisible
- get_HostLocalizedString
- get_FakePlayers

### <<UpdateVisibility>g__AnimateVisibilityRoutine|47_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <MarkDirty>d__48
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ScoreboardEntry
**Methods:** 9
**Sample Methods:**
- PopulateWith
- Update
- .ctor
- <PopulateWith>g__UpdateStatus|29_0
- <PopulateWith>g__GetMatchScore|29_1

### <>c__DisplayClass29_0
**Methods:** 0

### ScoreboardStat
**Methods:** 2
**Sample Methods:**
- Initialize
- .ctor

### SharedUiHidingGroups
**Methods:** 3
**Sample Methods:**
- get_HidingGroups
- set_HidingGroups
- .ctor

### SpectatorButtonPrompts
**Methods:** 10
**Sample Methods:**
- Awake
- OnDestroy
- Show
- Hide
- OnBUpdate

### SwingPitchUi
**Methods:** 16
**Sample Methods:**
- Awake
- OnDestroy
- SetPitch
- SetPitchInternal
- MoveToCenter

### <FadeToRoutine>d__23
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <MoveToDefaultPositionRoutine>d__22
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### SwingPowerBarUi
**Methods:** 27
**Sample Methods:**
- Awake
- OnDestroy
- SetNormalizedPower
- SetFlagIcon
- HideFlagIcon

### SwingTrajectoryPreview
**Methods:** 13
**Sample Methods:**
- Awake
- OnDestroy
- SetIsEnabled
- SetData
- SetIsLockedOn

### TargetReticleUi
**Methods:** 5
**Sample Methods:**
- Awake
- LateUpdate
- AnimateVisibilityRoutine
- .ctor
- <LateUpdate>g__ShouldBeVisible|7_0

### <AnimateVisibilityRoutine>d__8
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### TeeOffCountdown
**Methods:** 26
**Sample Methods:**
- Awake
- Show
- Hide
- SetRemainingTime
- ShowInternal

### <<ApplyVisibility>g__HideRoutine|14_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### TextChatManager
**Methods:** 20
**Sample Methods:**
- OnStartClient
- OnStopClient
- SendChatMessage
- GetPlayerFromConnection
- CmdSendMessageInternal

### TextChatMessageUi
**Methods:** 5
**Sample Methods:**
- OnDestroy
- Initialize
- OnBUpdate
- UpdateAlpha
- .ctor

### TextChatUi
**Methods:** 16
**Sample Methods:**
- get_IsOpen
- Awake
- OnDestroy
- Update
- UpdateButtonPrompt

### <OnMessageSubmit>d__27
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <UpdateButtonPromptAlpha>d__28
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### TextPopupManager
**Methods:** 9
**Sample Methods:**
- get_DefaultPopupSettings
- get_PenaltyPopupSettings
- GetUnusedPopup
- ReturnPopup
- GetUnusedPopupInternal

### TextPopupUi
**Methods:** 12
**Sample Methods:**
- add_Disappeared
- remove_Disappeared
- Awake
- Initialize
- LateUpdate

### TextPopupUiSettings
**Methods:** 34
**Sample Methods:**
- get_Color
- set_Color
- get_FadeStartDistance
- set_FadeStartDistance
- get_FadeEndDistance

### TutorialObjectiveUi
**Methods:** 15
**Sample Methods:**
- get_DisplayedObjective
- add_ObjectiveTextUpdated
- remove_ObjectiveTextUpdated
- Awake
- SetObjective

### <<FadeTextTo>g__FadeToRoutine|21_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<FadeTo>g__FadeToRoutine|20_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <<SetObjectiveInternal>g__UpdateObjectiveAnimatedRoutine|19_1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### TutorialPromptUi
**Methods:** 20
**Sample Methods:**
- get_IsFadingOut
- Awake
- OnDestroy
- SetPrompt
- SetPromptNormalizedProgress

### <<FadeTo>g__FadeToRoutine|29_0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### <>c__DisplayClass23_0
**Methods:** 6
**Sample Methods:**
- .ctor
- <SetPromptInternal>g__UpdatePromptAnimated|0
- <SetPromptInternal>g__UpdatePromptAnimatedRoutine|1
- <SetPromptInternal>g__UpdatePromptText|2
- <SetPromptInternal>g__UpdateTitleText|3

### <<SetPromptInternal>g__UpdatePromptAnimatedRoutine|1>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### UiHidingGroup
**Methods:** 0

### UiVisibilityController
**Methods:** 20
**Sample Methods:**
- get_DesiredAlpha
- set_DesiredAlpha
- get_IsHidden
- SetHidingGroupOverride
- RefreshHidingGroups

### <AnimateAlpha>d__27
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### CanvasAspectWidthScaler
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### CharacterPreview
**Methods:** 7
**Sample Methods:**
- Initialize
- Refresh
- SetPreviewEnabled
- Update
- OnDestroy

### ControllerInputReselect
**Methods:** 14
**Sample Methods:**
- Start
- OnEnable
- OnDisable
- ResetLastSelectable
- IsOnTop

### <>c
**Methods:** 3
**Sample Methods:**
- .cctor
- .ctor
- <IsOnTop>b__11_0

### <TryReselectSelectable>d__12
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### LocalizedWidth
**Methods:** 4
**Sample Methods:**
- Awake
- OnDestroy
- OnLocaleChanged
- .ctor

### LocAdjustment
**Methods:** 0

### NavigationLayout
**Methods:** 5
**Sample Methods:**
- Awake
- Update
- IsSelectableValid
- .ctor
- <Update>b__5_0

### Direction
**Methods:** 0

### <>c
**Methods:** 3
**Sample Methods:**
- .cctor
- .ctor
- <Awake>b__4_0

### RectMaxWidth
**Methods:** 6
**Sample Methods:**
- OnEnable
- OnDisable
- SetDirty
- SetLayoutHorizontal
- SetLayoutVertical

### ScrollRectControllerInput
**Methods:** 5
**Sample Methods:**
- OnEnable
- OnDisable
- Update
- RefreshMovementType
- .ctor

### ScrollViewSnap
**Methods:** 7
**Sample Methods:**
- Awake
- SetSteps
- Update
- MoveLeft
- MoveRight

### SetLayoutInformer
**Methods:** 7
**Sample Methods:**
- add_SetLayoutHorizontalCalled
- remove_SetLayoutHorizontalCalled
- add_SetLayoutVerticalCalled
- remove_SetLayoutVerticalCalled
- SetLayoutHorizontal

### VoiceChatIndicatorHud
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### VoiceChatIndicatorsHud
**Methods:** 5
**Sample Methods:**
- Start
- Update
- EnsureCapacity
- .ctor
- <Update>g__UpdateIcon|5_0

### VoteKickManager
**Methods:** 45
**Sample Methods:**
- get_CanVotekick
- get_CanKickOrVotekick
- get_CanKick
- get_NormalizedProgress
- get_YesVotes

### Vote
**Methods:** 0

### VoteResults
**Methods:** 0

### <>c__DisplayClass35_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <BeginKickInternal>b__0
- <BeginKickInternal>b__1

### <>c__DisplayClass36_0
**Methods:** 3
**Sample Methods:**
- .ctor
- <CmdRequestVoteKick>g__VotekickRoutine|0
- <CmdRequestVoteKick>g__IsOnCooldown|1

### <<CmdRequestVoteKick>g__VotekickRoutine|0>d
**Methods:** 6
**Sample Methods:**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### VoteKickUi
**Methods:** 11
**Sample Methods:**
- Start
- OnDestroy
- Show
- Hide
- UpdateValues

### WindInfoUi
**Methods:** 15
**Sample Methods:**
- Start
- OnDestroy
- OnLateBUpdate
- UpdateArrowScrollEffect
- OnUpdateWindInfo

### WindInfoUISettings
**Methods:** 1
**Sample Methods:**
- .ctor

### WorldspaceIconManager
**Methods:** 17
**Sample Methods:**
- get_ObjectiveIcon
- get_BallDispenserIcon
- get_BallIcon
- get_HoleIcon
- get_HomingWarningIcon

### WorldspaceIconUi
**Methods:** 18
**Sample Methods:**
- Awake
- OnEnable
- OnDisable
- Initialize
- LateUpdate

### WorldspaceIconUiSettings
**Methods:** 35
**Sample Methods:**
- get_LocalOffset
- set_LocalOffset
- get_WorldOffset
- set_WorldOffset
- get_FadeStartDistance

### GraphicsOptions
**Methods:** 3
**Sample Methods:**
- Initialize
- SetVSync
- .ctor

### InstantiationUtility
**Methods:** 2
**Sample Methods:**
- InstantiateInactive
- InstantiateInactive

### BGui
**Methods:** 25
**Sample Methods:**
- SetCamera
- SetColor
- DrawRect
- DrawRect
- DrawRect

### ColorScope
**Methods:** 2
**Sample Methods:**
- .ctor
- Dispose

### BackgroundColorScope
**Methods:** 2
**Sample Methods:**
- .ctor
- Dispose

### ContentColorScope
**Methods:** 2
**Sample Methods:**
- .ctor
- Dispose

### <>c
**Methods:** 3
**Sample Methods:**
- .cctor
- .ctor
- <.cctor>b__31_0

### MouseUtility
**Methods:** 5
**Sample Methods:**
- SetMouseScreenPosition
- SetMouseWorldPosition
- SetMouseViewportPosition
- ClampScreenPosition
- SetMouseScreenPositionInternal

### IReturnableToPool
**Methods:** 1
**Sample Methods:**
- ReturnToPool

### IPoolable`1
**Methods:** 1
**Sample Methods:**
- SetPool

### ObjectPool`1
**Methods:** 17
**Sample Methods:**
- get_IsDisposed
- get_PrefabLoaded
- set_PrefabLoaded
- get_Prefab
- .ctor

### <LoadPrefab>d__20
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### BUpdate
**Methods:** 14
**Sample Methods:**
- RegisterCallback
- DeregisterCallback
- Initialize
- OnApplicationQuit
- HookUpdateLoop

### InvokeRepeatingInstance
**Methods:** 1
**Sample Methods:**
- .ctor

### OnUpdate
**Methods:** 0

### OnFixedUpdate
**Methods:** 0

### OnPreLateUpdate
**Methods:** 0

### OnLateUpdate
**Methods:** 0

### <>c__DisplayClass17_0
**Methods:** 2
**Sample Methods:**
- .ctor
- <CancelInvoke>b__0

### IAnyBUpdateCallback
**Methods:** 0

### IBUpdateCallback
**Methods:** 1
**Sample Methods:**
- OnBUpdate

### BUpdateCallback
**Methods:** 3
**Sample Methods:**
- .ctor
- Dispose
- OnBUpdate

### IFixedBUpdateCallback
**Methods:** 1
**Sample Methods:**
- OnFixedBUpdate

### FixedBUpdateCallback
**Methods:** 3
**Sample Methods:**
- .ctor
- Dispose
- OnFixedBUpdate

### IPostFixedBUpdateCallback
**Methods:** 1
**Sample Methods:**
- OnPostFixedBUpdate

### PostFixedBUpdateCallback
**Methods:** 3
**Sample Methods:**
- .ctor
- Dispose
- OnPostFixedBUpdate

### ILateBUpdateCallback
**Methods:** 1
**Sample Methods:**
- OnLateBUpdate

### LateBUpdateCallback
**Methods:** 3
**Sample Methods:**
- .ctor
- Dispose
- OnLateBUpdate

### IPreLateBUpdateCallback
**Methods:** 1
**Sample Methods:**
- OnPreLateBUpdate

### PreLateBUpdateCallback
**Methods:** 3
**Sample Methods:**
- .ctor
- Dispose
- OnPreLateBUpdate

### AmbientVfx
**Methods:** 8
**Sample Methods:**
- get_VfxType
- Initialize
- DisableVfx
- Start
- OnDestroy

### AmbientVfxManager
**Methods:** 21
**Sample Methods:**
- Awake
- OnDestroy
- OnEnable
- OnDisable
- OnBUpdate

### AmbientVfxDistanceJob
**Methods:** 1
**Sample Methods:**
- Execute

### AmbientVfxSettings
**Methods:** 3
**Sample Methods:**
- get_ActivationRadiusSqr
- OnEnable
- .ctor

### AmbientVfxData
**Methods:** 1
**Sample Methods:**
- .ctor

### AmbientVfxType
**Methods:** 0

### BallVfxSettings
**Methods:** 6
**Sample Methods:**
- get_PuttingTrail
- get_Launch
- get_Hit
- get_WinStart
- get_WinEnd

### PuttingTrail
**Methods:** 9
**Sample Methods:**
- Awake
- Update
- Initialize
- BeforeTeleport
- AfterTeleport

### BezierSpline
**Methods:** 13
**Sample Methods:**
- get_Nodes
- OnDrawGizmos
- OnValidate
- UpdateNodeList
- GetFrontHandleWorldPos

### OrientedPoint
**Methods:** 1
**Sample Methods:**
- .ctor

### SplineSequence
**Methods:** 3
**Sample Methods:**
- get_Splines
- GetTrackingPoint
- .ctor

### SplineTracker
**Methods:** 9
**Sample Methods:**
- get_TrackingMode
- get_PointInterpolation
- get_NormalizedInterpolation
- Start
- Update

### SplineTrackingMode
**Methods:** 0

### TrackablePath
**Methods:** 2
**Sample Methods:**
- GetTrackingPoint
- .ctor

### KnockedOutStar
**Methods:** 4
**Sample Methods:**
- Initialize
- SetColored
- Destroy
- .ctor

### KnockedOutVfx
**Methods:** 5
**Sample Methods:**
- get_AsPoolable
- Initialize
- SetColoredStarCount
- .ctor
- <Initialize>g__GetOrCreateKnockedOutStar|8_0

### KnockOutVfxColorSettings
**Methods:** 2
**Sample Methods:**
- GetData
- .ctor

### KnockOutVfxColorData
**Methods:** 1
**Sample Methods:**
- .ctor

### KnockOutVfxColor
**Methods:** 0

### KnockOutVfxVisuals
**Methods:** 3
**Sample Methods:**
- get_CurrentColor
- SetColor
- .ctor

### RespawnVfx
**Methods:** 8
**Sample Methods:**
- get_AsPoolable
- OnEnable
- PlayAnimation
- SetHeightErosion
- PlayingAnimation

### <PlayingAnimation>d__22
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <PlayingMeshGeneration>d__23
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <PlayingSpawnParticles>d__24
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ClubVfxSettings
**Methods:** 2
**Sample Methods:**
- get_Hit
- .ctor

### CourseWindVfx
**Methods:** 2
**Sample Methods:**
- SetInterpolation
- .ctor

### CourseWindVfxSettings
**Methods:** 2
**Sample Methods:**
- ApplySettings
- .ctor

### ExplosionDecalSpawner
**Methods:** 6
**Sample Methods:**
- OnEnable
- OnDisable
- OnParticlesPlayed
- GetExplosionRange
- SpawnDecal

### TerrainExplosionDecal
**Methods:** 6
**Sample Methods:**
- OnEnable
- Awake
- RandomizeTexture
- Update
- GetMaterials

### DuelingPistolVfx
**Methods:** 5
**Sample Methods:**
- SetMuzzleEffectsEnabled
- SetPoints
- PlayingTracer
- SetTracerWidthMultiplier
- .ctor

### <PlayingTracer>d__5
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### GolfCartFlagPoleVfx
**Methods:** 8
**Sample Methods:**
- OnEnable
- OnDisable
- Start
- SetForwardLean
- SetIsFrozen

### GolfCartTireTrailVfx
**Methods:** 10
**Sample Methods:**
- get_ShouldPlay
- OnEnable
- OnDisable
- Start
- SetEmitting

### GolfCartVfx
**Methods:** 17
**Sample Methods:**
- get_ArePipeVfxPlaying
- set_ArePipeVfxPlaying
- get_HeadlightsAreOn
- Awake
- SetLocalVelocity

### HittableVfxSettings
**Methods:** 13
**Sample Methods:**
- get_CollisionVfx
- set_CollisionVfx
- get_CollisionMinimumSpeed
- set_CollisionMinimumSpeed
- get_CollisionMinimumAlignment

### ProjectileTrail
**Methods:** 14
**Sample Methods:**
- Awake
- OnDestroy
- Initialize
- SetIsSuppressed
- BeforeTeleport

### VfxDistanceScalerSettings
**Methods:** 6
**Sample Methods:**
- get_MinimumScale
- get_MaximumScale
- get_MinimumDistanceSqr
- get_MaximumDistanceSqr
- get_Easing

### FrozenEntityVfx
**Methods:** 2
**Sample Methods:**
- SetScale
- .ctor

### IceBreakableFloorVfx
**Methods:** 2
**Sample Methods:**
- SetData
- .ctor

### IceBreakableVfxParticleData
**Methods:** 1
**Sample Methods:**
- .ctor

### IceCracksRandomizer
**Methods:** 2
**Sample Methods:**
- OnEnable
- .ctor

### AirhornActivationVfx
**Methods:** 4
**Sample Methods:**
- OnEnable
- OnDisable
- OnLateBUpdate
- .ctor

### AirhornPlayerTriggeredVfx
**Methods:** 3
**Sample Methods:**
- get_AsPoolableParticleSystem
- SetItemTriggered
- .ctor

### ThrownUsedItemMaterialHandler
**Methods:** 7
**Sample Methods:**
- OnEnable
- UpdateRenderers
- SetGrayscaleEnabled
- SetGrayscaleValue
- AnimatingGrayscale

### <AnimatingGrayscale>d__9
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### MineVfx
**Methods:** 9
**Sample Methods:**
- OnEnable
- OnDisable
- OnBUpdate
- UpdateEmissionColor
- Arm

### PlayerMovementVfx
**Methods:** 13
**Sample Methods:**
- Initialize
- OnLeftFootstep
- OnRightFootstep
- SetIsWadingInWater
- SetWadingWaterWorldHeight

### PlayerStateVfx
**Methods:** 4
**Sample Methods:**
- PlaySpeedBoostEffects
- StopSpeedBoostEffects
- SetSpeedUpVfxHidden
- .ctor

### CrtScreen
**Methods:** 1
**Sample Methods:**
- .ctor

### CrtScreenRenderer
**Methods:** 2
**Sample Methods:**
- Render
- .ctor

### CrtScreenController
**Methods:** 11
**Sample Methods:**
- Awake
- SetCrtScreenEnabled
- SetBulgeEnabled
- SetAberrationEnabled
- SetScanlineEnabled

### PostProcessingFog
**Methods:** 1
**Sample Methods:**
- .ctor

### PostProcessingFogRenderer
**Methods:** 2
**Sample Methods:**
- Render
- .ctor

### ImpactFrame
**Methods:** 2
**Sample Methods:**
- IsEnabledAndSupported
- .ctor

### ImpactFrameRenderer
**Methods:** 2
**Sample Methods:**
- Render
- .ctor

### ImpactFrameController
**Methods:** 5
**Sample Methods:**
- Start
- SetImpactFrameEnabled
- PlayImpactFrame
- PlayingImpactFrame
- .ctor

### <PlayingImpactFrame>d__7
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### BallDispenserVfx
**Methods:** 6
**Sample Methods:**
- get_BloatPartADuration
- Start
- UpdateBloatMultiplier
- UpdateBloatSourcePos
- Dispensing

### <Dispensing>d__15
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### CoffeeDispenserVfx
**Methods:** 7
**Sample Methods:**
- Awake
- OnEnable
- OnDisable
- OnBUpdate
- Dispensing

### <Dispensing>d__15
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### DoorVfx
**Methods:** 3
**Sample Methods:**
- Open
- .ctor
- .cctor

### DoorRotationDirection
**Methods:** 0

### DrivingRangeStaticCamera
**Methods:** 13
**Sample Methods:**
- get_IsActive
- get_IsRendering
- Awake
- OnDestroy
- SetCameraActive

### DrivingRangeStaticCameraManager
**Methods:** 27
**Sample Methods:**
- get_IsCycleNextButtonEnabled
- Awake
- OnDestroy
- OnStartServer
- OnStartClient

### <<CmdCycleNextCameraForAllClientsInternal>g__DisableCycleButtonTemporarily|17_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <<OnStartClient>g__Initialize|14_0>d
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <>c
**Methods:** 3
**Sample Methods:**
- .cctor
- .ctor
- <OnStartClient>b__14_1

### FreezeBombPlatformVfx
**Methods:** 3
**Sample Methods:**
- OnEnable
- SetShaking
- .ctor

### JumpPadVfx
**Methods:** 6
**Sample Methods:**
- Awake
- Update
- CheckForDifference
- OnActivated
- .ctor

### PlayerCustomizeBuildingVfx
**Methods:** 3
**Sample Methods:**
- get_OpenDoorsCooldown
- TryOpenDoors
- .ctor

### SpectatorEmote
**Methods:** 0

### SpectatorCameraVfx
**Methods:** 6
**Sample Methods:**
- Awake
- SetTalking
- SetTalkingIntensity
- PlayEmote
- .ctor

### RocketDriverEquipmentVfx
**Methods:** 6
**Sample Methods:**
- OnEnable
- Start
- OnStartedAiming
- SetOvercharged
- SetThrusterPower

### RocketDriverThrusterVfxData
**Methods:** 1
**Sample Methods:**
- .ctor

### SpringBootsSpringVfx
**Methods:** 5
**Sample Methods:**
- OnEnable
- OnDisable
- OnBUpdate
- UpdateLength
- .ctor

### SwingSlashVfx
**Methods:** 4
**Sample Methods:**
- SetData
- SetData
- SetDataInternal
- .ctor

### SwingSlashVfxSettings
**Methods:** 2
**Sample Methods:**
- GetSwingSlashData
- .ctor

### SwingSlashVfxData
**Methods:** 1
**Sample Methods:**
- .ctor

### TrailVfx
**Methods:** 5
**Sample Methods:**
- get_IsPlaying
- set_IsPlaying
- SetPlaying
- Clear
- .ctor

### AirhornTargetIndicator
**Methods:** 10
**Sample Methods:**
- OnEnable
- OnDisable
- OnDestroy
- Start
- SetTarget

### AirhornTargetState
**Methods:** 0

### DominatedVfx
**Methods:** 7
**Sample Methods:**
- OnEnable
- OnDisable
- OnLateBUpdate
- Spawn
- GetTargetPosition

### <Despawn>d__12
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### FirstPlaceCrownVfx
**Methods:** 7
**Sample Methods:**
- OnEnable
- OnDisable
- OnLateBUpdate
- Spawn
- GetTargetPosition

### <Despawn>d__12
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### MainMenuBackgroundHandler
**Methods:** 8
**Sample Methods:**
- Start
- SetScenariosActive
- SetOverlayCanvasAlpha
- ShuffleScenarios
- Playing

### <DelayingOverlayFadeIn>d__11
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <Playing>d__10
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <SettingOverlayShown>d__12
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### MainMenuScenario
**Methods:** 4
**Sample Methods:**
- get_CameraTransform
- Playing
- SetActive
- .ctor

### <Playing>d__5
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### RivalryVfx
**Methods:** 7
**Sample Methods:**
- OnEnable
- OnDisable
- OnLateBUpdate
- Spawn
- GetTargetPosition

### <Despawn>d__11
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### AlignToVelocity
**Methods:** 3
**Sample Methods:**
- OnEnable
- Update
- .ctor

### DestroyByTime
**Methods:** 4
**Sample Methods:**
- set_TimeToTake
- OnEnable
- DestroyObject
- .ctor

### DisableByTime
**Methods:** 3
**Sample Methods:**
- OnEnable
- DisableObject
- .ctor

### FollowRigidbody
**Methods:** 4
**Sample Methods:**
- OnDisable
- SetTarget
- Update
- .ctor

### FollowTarget
**Methods:** 4
**Sample Methods:**
- OnEnable
- OnDisable
- OnBUpdate
- .ctor

### ForceRotation
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### LookAtCamera
**Methods:** 4
**Sample Methods:**
- OnEnable
- Update
- UpdateRotation
- .ctor

### LookAtTarget
**Methods:** 5
**Sample Methods:**
- SetLookAtTarget
- Update
- UpdateRotation
- .ctor
- .cctor

### PlayVfxOnKeyPress
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### PolygonMovement
**Methods:** 3
**Sample Methods:**
- Update
- GetPositionInPolygon
- .ctor

### PoolableParticleSystem
**Methods:** 20
**Sample Methods:**
- get_IsPlaying
- add_ParticlesPlayed
- remove_ParticlesPlayed
- add_ParticlesStopped
- remove_ParticlesStopped

### <RegisterToPoolWhenFinished>d__26
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### Rotator
**Methods:** 4
**Sample Methods:**
- Start
- Update
- Rotate
- .ctor

### Shake
**Methods:** 5
**Sample Methods:**
- get_ShakeFactor
- set_ShakeFactor
- Start
- Update
- .ctor

### CameraShakeType
**Methods:** 0

### ValueRamp
**Methods:** 4
**Sample Methods:**
- SetIncreasing
- Update
- GetValue
- ForceValue

### VelocityScaler
**Methods:** 3
**Sample Methods:**
- Start
- Update
- .ctor

### VfxDistanceScaler
**Methods:** 4
**Sample Methods:**
- OnEnable
- Update
- UpdateVfx
- .ctor

### VfxManager
**Methods:** 97
**Sample Methods:**
- ServerPlayPooledVfxForAllClients
- ClientPlayPooledVfxForAllClients
- PlayPooledVfxLocalOnly
- PlayPooledVfxLocalOnly
- ServerPlayPooledVfxForAllClientsInternal

### GunShotHitVfxData
**Methods:** 2
**Sample Methods:**
- .ctor
- GetHitPoint

### <>c__DisplayClass19_0
**Methods:** 0

### VfxPersistentData
**Methods:** 8
**Sample Methods:**
- get_DefaultBallVfxSettings
- get_DefaultSwingSlashVfxSettings
- Awake
- OnDestroy
- TryGetPooledVfx

### VfxPoolSettings
**Methods:** 4
**Sample Methods:**
- get_BasePath
- get_Extension
- get_Pools
- .ctor

### VfxPoolData
**Methods:** 1
**Sample Methods:**
- .ctor

### VfxTerrainMaterial
**Methods:** 0

### VfxType
**Methods:** 0

### VoiceChatVfx
**Methods:** 12
**Sample Methods:**
- get_AsPoolable
- OnEnable
- TryInitializeCamera
- Start
- SetPlaying

### VoiceChatVfxSettings
**Methods:** 17
**Sample Methods:**
- get_VolumeRange
- set_VolumeRange
- get_LifetimeRange
- set_LifetimeRange
- get_BurstCountRange

### MouthCameraThreshold
**Methods:** 0

### BubbleVfxMaterialHandler
**Methods:** 3
**Sample Methods:**
- OnEnable
- Update
- .ctor

### AirhornVfxTester
**Methods:** 6
**Sample Methods:**
- Start
- Update
- OnArmAirhorn
- OnActivateAirhorn
- HideIndicators

### BallDispenserVfxTester
**Methods:** 3
**Sample Methods:**
- Update
- Dispensing
- .ctor

### <Dispensing>d__4
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### BubbleVfxTester
**Methods:** 3
**Sample Methods:**
- OnEnable
- Update
- .ctor

### CheckpointVfxTester
**Methods:** 4
**Sample Methods:**
- Start
- Update
- SetCheckpointActive
- .ctor

### CoffeeDispenserVfxTester
**Methods:** 3
**Sample Methods:**
- Update
- Dispensing
- .ctor

### <Dispensing>d__4
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### DominatedVfxTester
**Methods:** 6
**Sample Methods:**
- Start
- Update
- Spawn
- Despawn
- Despawning

### <Despawning>d__8
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### DuelingPistolVfxTester
**Methods:** 6
**Sample Methods:**
- Start
- Update
- Shoot
- PlayingTracer
- SetTracerWidth

### <PlayingTracer>d__9
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### FirstPlaceCrownVfxTester
**Methods:** 6
**Sample Methods:**
- Start
- Update
- Spawn
- Despawn
- Despawning

### <Despawning>d__8
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### GolfCartVfxTester
**Methods:** 9
**Sample Methods:**
- Update
- TryPlayImpact
- PlayingImpact
- TryJump
- Jumping

### <Jumping>d__20
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <PlayingImpact>d__18
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ImpactFrameTester
**Methods:** 5
**Sample Methods:**
- Start
- Update
- GetRandomLocation
- Explode
- .ctor

### <Explode>d__9
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### JumpPadVfxTester
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### KnockedOutVfxTester
**Methods:** 8
**Sample Methods:**
- Start
- Update
- KnockOut
- PlayingVfx
- Clear

### <PlayingShield>d__14
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <PlayingVfx>d__11
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### MineVfxTester
**Methods:** 7
**Sample Methods:**
- Start
- Update
- Burrow
- ToggleArmedState
- SetArmedState

### <Explode>d__13
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### OrbitalLaserVfxTester
**Methods:** 6
**Sample Methods:**
- Start
- Update
- PlayingSequence
- PlayingImpactFrame
- PlayingCameraShake

### <PlayingCameraShake>d__18
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <PlayingImpactFrame>d__17
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### <PlayingSequence>d__16
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### OutOfBoundsWallVfxTester
**Methods:** 4
**Sample Methods:**
- Start
- Update
- SetWallActive
- .ctor

### PostHitSpinTester
**Methods:** 3
**Sample Methods:**
- Update
- SimulatingHit
- .ctor

### <SimulatingHit>d__6
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### RespawnVfxTester
**Methods:** 3
**Sample Methods:**
- Update
- PlayRespawnVfx
- .ctor

### RivalryVfxTester
**Methods:** 6
**Sample Methods:**
- Start
- Update
- Spawn
- Despawn
- Despawning

### <Despawning>d__8
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### RocketDriverEquipmentVfxTester
**Methods:** 4
**Sample Methods:**
- Update
- OnSliderValueChanged
- OnToggleValueChanged
- .ctor

### RocketLauncherVfxTester
**Methods:** 4
**Sample Methods:**
- Start
- Update
- PlayingSequence
- .ctor

### <PlayingSequence>d__15
**Methods:** 2
**Sample Methods:**
- MoveNext
- SetStateMachine

### ShopVfxTester
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### ShotgunVfxTester
**Methods:** 4
**Sample Methods:**
- Start
- Update
- Shoot
- .ctor

### SpectatorCameraVfxTester
**Methods:** 4
**Sample Methods:**
- Awake
- Update
- TryEmote
- .ctor

### SpeedUpVfxTester
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### SplineWallGenerator
**Methods:** 1
**Sample Methods:**
- .ctor

### SpringBootsTester
**Methods:** 3
**Sample Methods:**
- Start
- Update
- .ctor

### SwingSlashVfxTester
**Methods:** 3
**Sample Methods:**
- Update
- PlaySlash
- .ctor

### TargetDummyVfxTester
**Methods:** 3
**Sample Methods:**
- Update
- Hit
- .ctor

### UiFollowTransformTester
**Methods:** 2
**Sample Methods:**
- Update
- .ctor

### VoiceChatVfxTester
**Methods:** 4
**Sample Methods:**
- Start
- Update
- SetTestInterpolation
- .ctor

### WindManager
**Methods:** 43
**Sample Methods:**
- get_CurrentWindDirection
- get_Wind
- get_CurrentWindSpeed
- get_MinPossibleWindSpeed
- get_MaxPossibleWindSpeed

### WindType
**Methods:** 0

### WindAudioAmbienceType
**Methods:** 0

### WindSpeedRange
**Methods:** 1
**Sample Methods:**
- .ctor

### WindSettings
**Methods:** 2
**Sample Methods:**
- OnValidate
- .ctor

### UnitySourceGeneratedAssemblyMonoScriptTypes_v1
**Methods:** 2
**Sample Methods:**
- Get
- .ctor

### MonoScriptData
**Methods:** 0

### Overthrown.LevelEditor.ShortcutBase
**Methods:** 5
**Sample Methods:**
- OnEnable
- OnDisable
- Update
- OnShortcutPressed
- .ctor

### Overthrown.LevelEditor.ShortcutButton
**Methods:** 2
**Sample Methods:**
- OnShortcutPressed
- .ctor

### UnityEngine.InputSystem.Processors.VectorSensitivityScale
**Methods:** 4
**Sample Methods:**
- Process
- Register
- .cctor
- .ctor

### UnityEngine.InputSystem.Interactions.PressAndRepeatInteraction
**Methods:** 7
**Sample Methods:**
- .cctor
- RegisterInteraction
- Process
- OnUpdate
- Reset

### Brimstone.BallDistanceJobs.CalculateFirstGroundHitDistancesJob
**Methods:** 1
**Sample Methods:**
- Execute

### Brimstone.BallDistanceJobs.CalculateGroundRollStopDistancesJob
**Methods:** 1
**Sample Methods:**
- Execute

### Brimstone.BallDistanceJobs.ProcessDistanceEstimationsJob
**Methods:** 3
**Sample Methods:**
- Execute
- ShouldSearchForDesiredDistance
- AddOrSetTerrainLayerNormalizedSwingPower

### <PrivateImplementationDetails>
**Methods:** 1
**Sample Methods:**
- ThrowSwitchExpressionException

### __StaticArrayInitTypeSize=12
**Methods:** 0

### __StaticArrayInitTypeSize=24
**Methods:** 0

### __StaticArrayInitTypeSize=72
**Methods:** 0

### __StaticArrayInitTypeSize=16600
**Methods:** 0

### __StaticArrayInitTypeSize=24384
**Methods:** 0

### Mirror.GeneratedNetworkCode
**Methods:** 205
**Sample Methods:**
- _Read_Mirror.TimeSnapshotMessage
- _Write_Mirror.TimeSnapshotMessage
- _Read_Mirror.ReadyMessage
- _Write_Mirror.ReadyMessage
- _Read_Mirror.NotReadyMessage

### __JobReflectionRegistrationOutput__15695277335665486751
**Methods:** 2
**Sample Methods:**
- CreateJobReflectionData
- EarlyInit


## Game Mode Classes

### .TrackingMode
**Assembly:** GameAssembly

**Methods (0):**

### .TrackingOffsetMode
**Assembly:** GameAssembly

**Methods (0):**

### .ScreenshakeSettings
**Assembly:** GameAssembly

**Methods (20):**
- get_Type
- set_Type
- get_Duration
- set_Duration
- get_SmoothingSpeed

### .ModelSlot
**Assembly:** GameAssembly

**Methods (0):**

### .<OverrideModel>d__7
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .PlayerCosmeticsSettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .<<SetBodyModel>g__ReleasePrev|1>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<<SetBodyModel>g__UpdateTextureAndColor|0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetBodyModel>d__154
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetClubModel>d__152
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetFaceModel>d__150
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetGolfBallModel>d__153
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetHatModel>d__149
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetHeadModel>d__148
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetLowerFaceModel>d__151
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetModelInternal>d__155
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .MatchSetupStation
**Assembly:** GameAssembly

**Methods (4):**
- get_NextCameraButton
- PlayMenuOpenedEffectsLocalOnly
- PlayMenuOpenedEffectsLocalOnlyInternal
- .ctor

### .TutorialSettings
**Assembly:** GameAssembly

**Methods (16):**
- get_LookAroundRequiredDuration
- set_LookAroundRequiredDuration
- get_MoveRequiredDuration
- set_MoveRequiredDuration
- get_AimSwingRequiredDuration

### .EmoteSettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .AllEmoteSettings
**Assembly:** GameAssembly

**Methods (6):**
- get_EmoteSettings
- set_EmoteSettings
- OnValidate
- OnEnable
- Initialize

### .SpectatorEmoteSettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .AllSpectatorEmoteSettings
**Assembly:** GameAssembly

**Methods (6):**
- get_EmoteSettings
- set_EmoteSettings
- OnValidate
- OnEnable
- Initialize

### .EquipmentSettings
**Assembly:** GameAssembly

**Methods (5):**
- get_Type
- set_Type
- get_Prefab
- set_Prefab
- .ctor

### .GolfCartMovementSettings
**Assembly:** GameAssembly

**Methods (71):**
- get_LocalCenterOfMass
- set_LocalCenterOfMass
- get_MaxForwardSpeed
- set_MaxForwardSpeed
- get_MaxBackwardSpeed

### .GolfCartSeatSettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .GolfCartSettings
**Assembly:** GameAssembly

**Methods (36):**
- get_Prefab
- set_Prefab
- get_SeatSettings
- set_SeatSettings
- get_ExitForcedDiveSpeed

### .CheckpointSettings
**Assembly:** GameAssembly

**Methods (11):**
- get_MaxHorizontalRespawnDistance
- set_MaxHorizontalRespawnDistance
- get_InactiveMaterial
- set_InactiveMaterial
- get_ActiveMaterial

### .MatchState
**Assembly:** GameAssembly

**Methods (0):**

### .<<OnMatchStateChanged>g__AwardCourseBonus|212_3>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<<OnMatchStateChanged>g__ServerFinishMatchDelayed|212_1>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<CountDownToMatchEndRoutine>d__195
**Assembly:** GameAssembly

**Methods (6):**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### .<RpcInformStartingNextMatch>d__150
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<ServerStartNextMatch>d__149
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .FrictionMode
**Assembly:** GameAssembly

**Methods (0):**

### .GolfBallSettings
**Assembly:** GameAssembly

**Methods (40):**
- get_StationaryStateSpeedThreshold
- set_StationaryStateSpeedThreshold
- get_GroundFullStopMaxPitch
- set_GroundFullStopMaxPitch
- get_GroundFullRollMinPitch

### .GolfHoleSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_MaxKnockbackDistance
- set_MaxKnockbackDistance
- get_MinKnockbackDistance
- set_MinKnockbackDistance
- get_MaxRange

### .LevelHazardSettings
**Assembly:** GameAssembly

**Methods (0):**

### .HazardSettings
**Assembly:** GameAssembly

**Methods (16):**
- get_LevelHazardSettings
- set_LevelHazardSettings
- get_SwingPowerBarOutOfBoundsHazardOVerlayTexture
- set_SwingPowerBarOutOfBoundsHazardOVerlayTexture
- get_BreakableIcePristineMaterial

### .DiveHittableSettings
**Assembly:** GameAssembly

**Methods (15):**
- get_CanBeHit
- set_CanBeHit
- get_MinKnockbackHitRelativeSpeed
- set_MinKnockbackHitRelativeSpeed
- get_MaxKnockbackHitRelativeSpeed

### .HittableSettings
**Assembly:** GameAssembly

**Methods (13):**
- get_Swing
- set_Swing
- get_Projectile
- set_Projectile
- get_Dive

### .ItemHittableSettings
**Assembly:** GameAssembly

**Methods (81):**
- get_DuelingPistolMaxKnockbackDistance
- set_DuelingPistolMaxKnockbackDistance
- get_DuelingPistolMinKnockbackDistance
- set_DuelingPistolMinKnockbackDistance
- get_DuelingPistolMaxKnockbackSpeed

### .ProjectileHittableSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_CanBeHitBySwingProjectiles
- set_CanBeHitBySwingProjectiles
- get_SwingProjectileMinResultingSpeed
- set_SwingProjectileMinResultingSpeed
- get_SwingProjectileMaxResultingSpeed

### .ScoreKnockbackHittableSettings
**Assembly:** GameAssembly

**Methods (13):**
- get_MinKnockbackSpeed
- set_MinKnockbackSpeed
- get_MaxKnockbackSpeed
- set_MaxKnockbackSpeed
- get_MinKnockbackAngularSpeed

### .SwingHittableSettings
**Assembly:** GameAssembly

**Methods (40):**
- get_MaxPowerSwingHitSpeed
- set_MaxPowerSwingHitSpeed
- get_MaxPowerPuttHitSpeed
- set_MaxPowerPuttHitSpeed
- get_SwingHitSpinSpeed

### .WindHittableSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_IsAffectedByWind
- set_IsAffectedByWind
- get_WindFactor
- set_WindFactor
- get_CrossWindFactor

### .InputMode
**Assembly:** GameAssembly

**Methods (0):**

### .InputModeExtensions
**Assembly:** GameAssembly

**Methods (3):**
- HasMode
- HasOverride
- DisablesUiInputModule

### .AudioSettings
**Assembly:** GameAssembly

**Methods (376):**
- get_ItemBoxCollectedEvent
- set_ItemBoxCollectedEvent
- get_BallInHoleEvent
- set_BallInHoleEvent
- get_FootstepEvent

### .ItemSettings
**Assembly:** GameAssembly

**Methods (470):**
- get_CoffeeDrinkEffectStartFrames
- set_CoffeeDrinkEffectStartFrames
- get_CoffeeTotalFrames
- set_CoffeeTotalFrames
- get_CoffeeEffectDuration

### .ItemSpawnerSettings
**Assembly:** GameAssembly

**Methods (21):**
- get_ItemPools
- get_ItemPoolsDefaults
- get_AheadOfBallItemPool
- get_AheadOfBallItemPoolDefaults
- get_RespawnTime

### .JumpSettings
**Assembly:** GameAssembly

**Methods (1):**
- get_Default

### .LevelBoundsTrackerSettings
**Assembly:** GameAssembly

**Methods (17):**
- get_ServerOnly
- set_ServerOnly
- get_DrivingRangeAutomaticOutOfBoundsBehaviour
- set_DrivingRangeAutomaticOutOfBoundsBehaviour
- get_MatchAutomaticOutOfBoundsBehaviour

### .LobbyMode
**Assembly:** GameAssembly

**Methods (0):**

### .StartMatchMessage
**Assembly:** GameAssembly

**Methods (0):**

### .EliminationSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_EliminationResponsibilityDuration
- set_EliminationResponsibilityDuration
- OnValidate
- OnEnable
- Initialize

### .KnockoutSettings
**Assembly:** GameAssembly

**Methods (5):**
- OnValidate
- OnEnable
- Initialize
- TryGetKnockoutData
- .ctor

### .PlayerMatchResolution
**Assembly:** GameAssembly

**Methods (0):**

### .PlayerMatchResolutionExtensions
**Assembly:** GameAssembly

**Methods (1):**
- IsResolved

### .TerrainGrassRendererSettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .FuzzySettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .RimlightSettings
**Assembly:** GameAssembly

**Methods (0):**

### .BInputSettings
**Assembly:** GameAssembly

**Methods (15):**
- get_DefaultBufferDuration
- set_DefaultBufferDuration
- get_InteractBufferDuration
- set_InteractBufferDuration
- get_MinNonPuttPitch

### .CameraGameplaySettings
**Assembly:** GameAssembly

**Methods (40):**
- get_IntoSwingAimTransitionDuration
- set_IntoSwingAimTransitionDuration
- get_OutOfSwingAimTransitionDuration
- set_OutOfSwingAimTransitionDuration
- get_SwingAimVerticalTrackingOffset

### .GolfSettings
**Assembly:** GameAssembly

**Methods (134):**
- get_BallPrefab
- set_BallPrefab
- get_TeeBallLocalSpawnHeight
- set_TeeBallLocalSpawnHeight
- get_TeePostHitSizeCurve

### .LayerSettings
**Assembly:** GameAssembly

**Methods (97):**
- get_StationaryBallLayer
- set_StationaryBallLayer
- get_DynamicBallLayer
- set_DynamicBallLayer
- get_HittablesLayer

### .MatchSettings
**Assembly:** GameAssembly

**Methods (67):**
- get_HoleOverviewInitialBlankDuration
- set_HoleOverviewInitialBlankDuration
- get_HoleOverviewHoleNameDuration
- set_HoleOverviewHoleNameDuration
- get_HoleOverviewFinalBlankDuration

### .OutOfBoundsHazardSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_Type
- set_Type
- get_SwingPowerBarColor
- set_SwingPowerBarColor
- get_SwingPowerBarOutOfBoundsOverlayColor

### .PhysicsSettings
**Assembly:** GameAssembly

**Methods (23):**
- get_PlayerMaterial
- set_PlayerMaterial
- get_PlayerKnockedOutMaterial
- set_PlayerKnockedOutMaterial
- get_PlayerDivingMaterial

### .PlayerInventorySettings
**Assembly:** GameAssembly

**Methods (5):**
- get_MaxItems
- set_MaxItems
- get_DropItemVerticalOffset
- set_DropItemVerticalOffset
- .ctor

### .PlayerMovementSettings
**Assembly:** GameAssembly

**Methods (110):**
- get_DefaultMoveSpeed
- set_DefaultMoveSpeed
- get_WalkMoveSpeed
- set_WalkMoveSpeed
- get_SwingAimingSpeed

### .PlayerTargetingSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_SearchConeDistance
- set_SearchConeDistance
- get_SearchConeAperture
- set_SearchConeAperture
- get_SearchConeBaseDiameter

### .TeeingPlatformSettings
**Assembly:** GameAssembly

**Methods (14):**
- get_TeePrefab
- set_TeePrefab
- get_TeeVerticalOffset
- set_TeeVerticalOffset
- get_MaxTeeCount

### .TerrainLayerSettings
**Assembly:** GameAssembly

**Methods (49):**
- get_Layer
- set_Layer
- get_LayerAsset
- set_LayerAsset
- get_SwingPowerBarColor

### .TerrainSettings
**Assembly:** GameAssembly

**Methods (10):**
- get_Layers
- set_Layers
- get_OutOfBoundsHazards
- set_OutOfBoundsHazards
- get_JobsBallTerrainCollisionMaterialPerTerrainLayer

### .UiSettings
**Assembly:** GameAssembly

**Methods (53):**
- get_UnknownItemIcon
- set_UnknownItemIcon
- get_LoadingScreenBackgroundColor
- set_LoadingScreenBackgroundColor
- get_TextHighlightColor

### .HotkeyMode
**Assembly:** GameAssembly

**Methods (0):**

### .InfoFeedIconSettings
**Assembly:** GameAssembly

**Methods (5):**
- OnValidate
- OnEnable
- Initialize
- TryGetIcon
- .ctor

### .MatchEndCountdown
**Assembly:** GameAssembly

**Methods (27):**
- get_DisplayedTime
- Awake
- Show
- Hide
- EnterOvertime

### .SortMode
**Assembly:** GameAssembly

**Methods (0):**

### .FilterSettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .MatchSetupCoursesTab
**Assembly:** GameAssembly

**Methods (3):**
- OnEnable
- ResetHoleScrollRects
- .ctor

### .MatchSetupHole
**Assembly:** GameAssembly

**Methods (18):**
- Start
- OnControllerSubmit
- Update
- OnDisable
- Swap

### .MatchSetupMenu
**Assembly:** GameAssembly

**Methods (88):**
- get_CustomCourseData
- set_CustomCourseData
- get_RandomCourseData
- set_RandomCourseData
- get_IsActive

### .MatchSetupPlayer
**Assembly:** GameAssembly

**Methods (26):**
- get_Guid
- get_isLocalPlayer
- Awake
- OnEnable
- OnDisable

### .MatchSetupRules
**Assembly:** GameAssembly

**Methods (74):**
- get_CurrentPreset
- add_UpdateItemSpawnersLoc
- remove_UpdateItemSpawnersLoc
- add_RulesPopulated
- remove_RulesPopulated

### .NavigationMode
**Assembly:** GameAssembly

**Methods (0):**

### .<SetBodyModel>d__123
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetClubModel>d__120
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetFaceModel>d__121
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetGolfBallModel>d__128
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetHairModel>d__119
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetHatModel>d__117
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetHeadModel>d__118
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetLowerFaceModel>d__122
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .RadialMenuMode
**Assembly:** GameAssembly

**Methods (0):**

### .RadialMenuOptionSettings
**Assembly:** GameAssembly

**Methods (22):**
- get_Material
- set_Material
- get_SpacingWidth
- set_SpacingWidth
- get_HighlightAnimationDuration

### .ControlRebindSettings
**Assembly:** GameAssembly

**Methods (4):**
- OnValidate
- OnEnable
- Initialize
- .ctor

### .IGameSettings
**Assembly:** GameAssembly

**Methods (1):**
- Initialize

### .GameSettings
**Assembly:** GameAssembly

**Methods (6):**
- get_All
- Initialize
- ApplyAndSave
- SaveWithoutApplying
- SaveInputBindings

### .AudioSettings
**Assembly:** GameAssembly

**Methods (39):**
- get_MasterVolume
- set_MasterVolume
- get_MusicVolume
- set_MusicVolume
- get_SfxVolume

### .InputMode
**Assembly:** GameAssembly

**Methods (0):**

### .GraphicsSettings
**Assembly:** GameAssembly

**Methods (34):**
- get_MSAA
- set_MSAA
- get_VSync
- set_VSync
- get_FpsLimit

### .GeneralSettings
**Assembly:** GameAssembly

**Methods (33):**
- get_ScreenshakeFactor
- set_ScreenshakeFactor
- get_FlashingEffects
- set_FlashingEffects
- get_ShowNameTags

### .ControlSettings
**Assembly:** GameAssembly

**Methods (5):**
- get_Camera
- get_Mouse
- get_Controller
- Initialize
- .ctor

### .AllSettings
**Assembly:** GameAssembly

**Methods (8):**
- get_Audio
- get_Graphics
- get_General
- get_Controls
- get_TutorialProgress

### .SettingsMenu
**Assembly:** GameAssembly

**Methods (26):**
- Start
- UpdateTooltips
- OnEnable
- RefreshAudioDevices
- SetShadowQuality

### .NameTagUiSettings
**Assembly:** GameAssembly

**Methods (26):**
- get_FadeStartDistance
- set_FadeStartDistance
- get_FadeEndDistance
- set_FadeEndDistance
- get_MinTextSize

### .SelectableActiveMode
**Assembly:** GameAssembly

**Methods (0):**

### .NextMatchCountdown
**Assembly:** GameAssembly

**Methods (28):**
- get_NextMatchCountdownMessage
- get_CourseEndedCountdownMessage
- Awake
- OnDestroy
- Show

### .TextPopupUiSettings
**Assembly:** GameAssembly

**Methods (34):**
- get_Color
- set_Color
- get_FadeStartDistance
- set_FadeStartDistance
- get_FadeEndDistance

### .WindInfoUISettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .WorldspaceIconUiSettings
**Assembly:** GameAssembly

**Methods (35):**
- get_LocalOffset
- set_LocalOffset
- get_WorldOffset
- set_WorldOffset
- get_FadeStartDistance

### .AmbientVfxSettings
**Assembly:** GameAssembly

**Methods (3):**
- get_ActivationRadiusSqr
- OnEnable
- .ctor

### .BallVfxSettings
**Assembly:** GameAssembly

**Methods (6):**
- get_PuttingTrail
- get_Launch
- get_Hit
- get_WinStart
- get_WinEnd

### .SplineTrackingMode
**Assembly:** GameAssembly

**Methods (0):**

### .KnockOutVfxColorSettings
**Assembly:** GameAssembly

**Methods (2):**
- GetData
- .ctor

### .ClubVfxSettings
**Assembly:** GameAssembly

**Methods (2):**
- get_Hit
- .ctor

### .CourseWindVfxSettings
**Assembly:** GameAssembly

**Methods (2):**
- ApplySettings
- .ctor

### .HittableVfxSettings
**Assembly:** GameAssembly

**Methods (13):**
- get_CollisionVfx
- set_CollisionVfx
- get_CollisionMinimumSpeed
- set_CollisionMinimumSpeed
- get_CollisionMinimumAlignment

### .VfxDistanceScalerSettings
**Assembly:** GameAssembly

**Methods (6):**
- get_MinimumScale
- get_MaximumScale
- get_MinimumDistanceSqr
- get_MaximumDistanceSqr
- get_Easing

### .SwingSlashVfxSettings
**Assembly:** GameAssembly

**Methods (2):**
- GetSwingSlashData
- .ctor

### .VfxPoolSettings
**Assembly:** GameAssembly

**Methods (4):**
- get_BasePath
- get_Extension
- get_Pools
- .ctor

### .VoiceChatVfxSettings
**Assembly:** GameAssembly

**Methods (17):**
- get_VolumeRange
- set_VolumeRange
- get_LifetimeRange
- set_LifetimeRange
- get_BurstCountRange

### .WindSettings
**Assembly:** GameAssembly

**Methods (2):**
- OnValidate
- .ctor


## Weapon Classes

### .ItemDispenser
**Assembly:** GameAssembly

**Methods (23):**
- get_AsEntity
- set_AsEntity
- get_IsInteractionEnabled
- get_InteractString
- Awake

### .<<CmdDispenseItemFor>g__DisableInteractionTemporarily|20_0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<CmdDispenseItemFor>d__20
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .RocketLauncherEquipment
**Assembly:** GameAssembly

**Methods (3):**
- OnEnable
- SetRocketMeshEnabled
- .ctor

### .SwingProjectileState
**Assembly:** GameAssembly

**Methods (0):**

### .<<HitWithItemInternal>g__ServerFreeze|0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .ItemHittableSettings
**Assembly:** GameAssembly

**Methods (81):**
- get_DuelingPistolMaxKnockbackDistance
- set_DuelingPistolMaxKnockbackDistance
- get_DuelingPistolMinKnockbackDistance
- set_DuelingPistolMinKnockbackDistance
- get_DuelingPistolMaxKnockbackSpeed

### .ProjectileHittableSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_CanBeHitBySwingProjectiles
- set_CanBeHitBySwingProjectiles
- get_SwingProjectileMinResultingSpeed
- set_SwingProjectileMinResultingSpeed
- get_SwingProjectileMaxResultingSpeed

### .ItemCollection
**Assembly:** GameAssembly

**Methods (8):**
- get_Count
- OnValidate
- OnEnable
- Initialize
- GetItemAtIndex

### .ItemNonAimingUse
**Assembly:** GameAssembly

**Methods (0):**

### .ItemAirhornReaction
**Assembly:** GameAssembly

**Methods (0):**

### .ItemData
**Assembly:** GameAssembly

**Methods (38):**
- get_Type
- set_Type
- get_Prefab
- set_Prefab
- get_DroppedLocalRotationEuler

### .ItemPool
**Assembly:** GameAssembly

**Methods (8):**
- get_SpawnChances
- get_TotalSpawnChanceWeight
- OnValidate
- GetSpawnChanceWeight
- UpdateTotalWeight

### .ItemSpawnChance
**Assembly:** GameAssembly

**Methods (0):**

### .ItemSettings
**Assembly:** GameAssembly

**Methods (470):**
- get_CoffeeDrinkEffectStartFrames
- set_CoffeeDrinkEffectStartFrames
- get_CoffeeTotalFrames
- set_CoffeeTotalFrames
- get_CoffeeEffectDuration

### .ItemSpawner
**Assembly:** GameAssembly

**Methods (34):**
- Awake
- OnDestroy
- OnStartServer
- OnStopServer
- OnTriggerEnter

### .ItemSpawnerSettings
**Assembly:** GameAssembly

**Methods (21):**
- get_ItemPools
- get_ItemPoolsDefaults
- get_AheadOfBallItemPool
- get_AheadOfBallItemPoolDefaults
- get_RespawnTime

### .ItemPoolData
**Assembly:** GameAssembly

**Methods (1):**
- CompareTo

### .ItemSpawnerVisuals
**Assembly:** GameAssembly

**Methods (11):**
- get_EffectSourcePosition
- get_HasBox
- Awake
- SetIsTaken
- SetFill

### .ItemSpawnerVisualType
**Assembly:** GameAssembly

**Methods (0):**

### .ItemType
**Assembly:** GameAssembly

**Methods (0):**

### .ItemTypeExtensions
**Assembly:** GameAssembly

**Methods (1):**
- TryGetEliminationReason

### .PhysicalItem
**Assembly:** GameAssembly

**Methods (23):**
- get_RemainingUses
- set_RemainingUses
- get_AsEntity
- set_AsEntity
- get_ItemType

### .ThrownUsedItemType
**Assembly:** GameAssembly

**Methods (0):**

### .ThrownUsedItem
**Assembly:** GameAssembly

**Methods (13):**
- get_AsEntity
- set_AsEntity
- get_Type
- get_Rigidbody
- OnValidate

### .ThrownUsedItemManager
**Assembly:** GameAssembly

**Methods (8):**
- Awake
- GetUnusedThrownItem
- ReturnThrownItem
- GetUnusedThrownItemInternal
- ReturnThrownItemInternal

### .ThrownUsedRocketDriver
**Assembly:** GameAssembly

**Methods (7):**
- get_IsRocketActive
- set_IsRocketActive
- OnDisable
- OnDestroy
- OnFixedBUpdate

### .ItemUseId
**Assembly:** GameAssembly

**Methods (5):**
- .ctor
- IsValid
- Equals
- GetHashCode
- .cctor

### .ItemUseType
**Assembly:** GameAssembly

**Methods (0):**

### .ThrownItemHand
**Assembly:** GameAssembly

**Methods (0):**

### .<<TryUseItem>g__FlourishRoutine|2>d
**Assembly:** GameAssembly

**Methods (6):**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### .<ShootElephantGunRoutine>d__165
**Assembly:** GameAssembly

**Methods (6):**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### .<ShootRocketLauncherRoutine>d__166
**Assembly:** GameAssembly

**Methods (6):**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### .ItemPoolId
**Assembly:** GameAssembly

**Methods (1):**
- Get

### .<<OnItemLayoutSet>g__UpdateNavigationDelayed|119_0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .ProjectileTrail
**Assembly:** GameAssembly

**Methods (14):**
- Awake
- OnDestroy
- Initialize
- SetIsSuppressed
- BeforeTeleport

### .ThrownUsedItemMaterialHandler
**Assembly:** GameAssembly

**Methods (7):**
- OnEnable
- UpdateRenderers
- SetGrayscaleEnabled
- SetGrayscaleValue
- AnimatingGrayscale

### .GunShotHitVfxData
**Assembly:** GameAssembly

**Methods (2):**
- .ctor
- GetHitPoint

### .RocketLauncherVfxTester
**Assembly:** GameAssembly

**Methods (4):**
- Start
- Update
- PlayingSequence
- .ctor

### .ShotgunVfxTester
**Assembly:** GameAssembly

**Methods (4):**
- Start
- Update
- Shoot
- .ctor


## Character Classes

### .CameraModuleController
**Assembly:** GameAssembly

**Methods (46):**
- get_DistanceBelowOutOfBoundsHazardSurface
- set_DistanceBelowOutOfBoundsHazardSurface
- get_CurrentModule
- get_PreviousModuleType
- get_CurrentModuleType

### .PlayerCosmeticFaceFeature
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .PlayerCosmeticObject
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .PlayerCosmetics
**Assembly:** GameAssembly

**Methods (75):**
- get_Switcher
- add_ClubCosmeticUpdated
- remove_ClubCosmeticUpdated
- Awake
- OnClubChanged

### .LoadoutSlot
**Assembly:** GameAssembly

**Methods (0):**

### .Loadout
**Assembly:** GameAssembly

**Methods (5):**
- Get
- Apply
- GetVictoryDance
- <Get>g__HasSlot|13_0
- <Apply>g__HasSlot|14_0

### .<EquipLoadout>d__35
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<SetAndEquipLoadout>d__36
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .PlayerCosmeticsMetadata
**Assembly:** GameAssembly

**Methods (4):**
- get_PersistentGuid
- IsHidden
- .ctor
- .cctor

### .PlayerCosmeticsObjectSwitcher
**Assembly:** GameAssembly

**Methods (5):**
- get_ModelOverride
- add_OnModelOverride
- remove_OnModelOverride
- OverrideModel
- .ctor

### .PlayerCosmeticsSettings
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .SkinColor
**Assembly:** GameAssembly

**Methods (0):**

### .PlayerCosmeticsSwitcher
**Assembly:** GameAssembly

**Methods (84):**
- get_CurrentHeadRuntimeKey
- set_CurrentHeadRuntimeKey
- get_CurrentHatRuntimeKey
- set_CurrentHatRuntimeKey
- get_CurrentFaceRuntimeKey

### .PlayerCosmeticsVictoryDanceMetadata
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .PlayerCosmeticsVictoryDances
**Assembly:** GameAssembly

**Methods (4):**
- get_Length
- GetDance
- get_Item
- .ctor

### .DrivingRangeSpawnArea
**Assembly:** GameAssembly

**Methods (3):**
- GetRandomSpawnPosition
- OnDrawGizmosSelected
- .ctor

### .PlayerCustomizationBuilding
**Assembly:** GameAssembly

**Methods (17):**
- OnStartServer
- InformLocalPlayerEntered
- InformLocalPlayerExited
- InformLocalPlayerEnteredInternal
- InformLocalPlayerExitedInternal

### .<<ServerReserveDriverSeatPreNetworkSpawn>g__DestroyIfUnusedDelayed|80_0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<TimeOutResponsiblePlayerRoutine>d__103
**Assembly:** GameAssembly

**Methods (6):**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### .PlayerState
**Assembly:** GameAssembly

**Methods (6):**
- get_name
- .ctor
- GetClearedState
- GetNewMatchState
- CompareTo

### .PlayerPair
**Assembly:** GameAssembly

**Methods (4):**
- .ctor
- Inverse
- Equals
- GetHashCode

### .<<SetPlayerSpectatorInternal>g__RespawnPlayer|0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .ItemSpawnChance
**Assembly:** GameAssembly

**Methods (0):**

### .ItemSpawner
**Assembly:** GameAssembly

**Methods (34):**
- Awake
- OnDestroy
- OnStartServer
- OnStopServer
- OnTriggerEnter

### .ItemSpawnerSettings
**Assembly:** GameAssembly

**Methods (21):**
- get_ItemPools
- get_ItemPoolsDefaults
- get_AheadOfBallItemPool
- get_AheadOfBallItemPoolDefaults
- get_RespawnTime

### .ItemSpawnerVisuals
**Assembly:** GameAssembly

**Methods (11):**
- get_EffectSourcePosition
- get_HasBox
- Awake
- SetIsTaken
- SetFill

### .ItemSpawnerVisualType
**Assembly:** GameAssembly

**Methods (0):**

### .<<Start>g__RegisterPlayerWhenReady|45_0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<<OnServerAddPlayer>g__AddPlayerToHole|1>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<<OnServerAddPlayer>g__GetPlayerSpawnData|2>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<OnServerAddPlayer>d__135
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<PollSteamPlayerRelationships>d__120
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .MaxPlayersUpdatedMessage
**Assembly:** GameAssembly

**Methods (0):**

### .SetPlayerGuidMessage
**Assembly:** GameAssembly

**Methods (0):**

### .RemotePlayerDisconnectMessage
**Assembly:** GameAssembly

**Methods (0):**

### .PlayerAnimatorIo
**Assembly:** GameAssembly

**Methods (72):**
- get_ShouldGolfCartBriefcaseBeSplit
- set_ShouldGolfCartBriefcaseBeSplit
- get_AimingYawOffset
- get_SpineStraighteningWeight
- add_Footstep

### .PlayerAudio
**Assembly:** GameAssembly

**Methods (168):**
- Awake
- OnDestroy
- OnStartServer
- PlayFootstepLocalOnly
- PlayJumpForAllClients

### .PlayerMatchResolution
**Assembly:** GameAssembly

**Methods (0):**

### .PlayerMatchResolutionExtensions
**Assembly:** GameAssembly

**Methods (1):**
- IsResolved

### .PlayerGolfer
**Assembly:** GameAssembly

**Methods (228):**
- get_PlayerInfo
- set_PlayerInfo
- get_IsInitialized
- get_OwnBall
- get_LocalPlayerLatestImmediateEliminationReason

### .PlayerId
**Assembly:** GameAssembly

**Methods (34):**
- get_PlayerInfo
- set_PlayerInfo
- get_Guid
- get_PlayerName
- get_PlayerNameNoRichText

### .PlayerTextPopupType
**Assembly:** GameAssembly

**Methods (0):**

### .PlayerInfo
**Assembly:** GameAssembly

**Methods (323):**
- get_HipBone
- set_HipBone
- get_Spine1Bone
- set_Spine1Bone
- get_ChestBone

### .<<LocalPlayerUpdateIsElectromagnetShieldActive>g__ElectromagnetShieldRoutine|1>d
**Assembly:** GameAssembly

**Methods (6):**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### .PlayerInput
**Assembly:** GameAssembly

**Methods (103):**
- get_Controls
- get_IsHoldingAimSwing
- set_IsHoldingAimSwing
- get_IsHoldingChargeSwing
- set_IsHoldingChargeSwing

### .PlayerInteractableTargeter
**Assembly:** GameAssembly

**Methods (19):**
- get_CurrentTargetEntity
- set_CurrentTargetEntity
- get_HasTarget
- get_FirstTargetInteracable
- get_CurrentTargetReticlePosition

### .PlayerInteractor
**Assembly:** GameAssembly

**Methods (4):**
- Awake
- TryInteract
- .ctor
- <TryInteract>g__CanInteract|2_0

### .PlayerInventory
**Assembly:** GameAssembly

**Methods (257):**
- get_PlayerInfo
- set_PlayerInfo
- get_CurrentItemUse
- set_CurrentItemUse
- get_ItemUseTimestamp

### .PlayerGroundData
**Assembly:** GameAssembly

**Methods (0):**

### .RespawnState
**Assembly:** GameAssembly

**Methods (0):**

### .RespawnTarget
**Assembly:** GameAssembly

**Methods (0):**

### .PlayerMovement
**Assembly:** GameAssembly

**Methods (366):**
- get_PlayerInfo
- set_PlayerInfo
- get_RawMoveVectorMagnitude
- set_RawMoveVectorMagnitude
- get_MoveVectorMagnitude

### .<<LocalPlayerBeginRespawn>g__RespawnRoutine|0>d
**Assembly:** GameAssembly

**Methods (6):**
- .ctor
- System.IDisposable.Dispose
- MoveNext
- System.Collections.Generic.IEnumerator<System.Object>.get_Current
- System.Collections.IEnumerator.Reset

### .<LocalPlayerUpdateVisibilityDelayed>d__334
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .PlayerOcclusion
**Assembly:** GameAssembly

**Methods (6):**
- IsOccluded
- TimeSinceVisible
- SetInstanceId
- OnEnable
- OnDisable

### .PlayerOcclusionManager
**Assembly:** GameAssembly

**Methods (10):**
- Awake
- OnDestroy
- RegisterInstance
- DeregisterInstance
- IsOccluded

### .PlayerShaderDataHelper
**Assembly:** GameAssembly

**Methods (2):**
- SetPlayerIndex
- SetPlayerShaderIndexOnRenderers

### .PlayerShaderDataManager
**Assembly:** GameAssembly

**Methods (11):**
- Awake
- OnDestroy
- Update
- PreCull
- GetPlayerShaderIndex

### .PlayerSpectator
**Assembly:** GameAssembly

**Methods (77):**
- get_PlayerInfo
- set_PlayerInfo
- get_IsSpectating
- get_TargetPlayer
- set_TargetPlayer

### .PlayerVfx
**Assembly:** GameAssembly

**Methods (16):**
- get_PlayerInfo
- OnEnable
- OnDisable
- Awake
- OnWillBeDestroyed

### .PlayerVoiceChat
**Assembly:** GameAssembly

**Methods (22):**
- InitializeStatics
- SetPlayerVolume
- SetIsPlayerMuted
- UpdateInstancePersistentPlayerStatus
- GetPlayerStatus

### .PersistentPlayerStatus
**Assembly:** GameAssembly

**Methods (5):**
- get_Default
- Write
- Read
- UpdateTimestamp
- IsDefault

### .PlayerInventorySettings
**Assembly:** GameAssembly

**Methods (5):**
- get_MaxItems
- set_MaxItems
- get_DropItemVerticalOffset
- set_DropItemVerticalOffset
- .ctor

### .PlayerMovementSettings
**Assembly:** GameAssembly

**Methods (110):**
- get_DefaultMoveSpeed
- set_DefaultMoveSpeed
- get_WalkMoveSpeed
- set_WalkMoveSpeed
- get_SwingAimingSpeed

### .PlayerTargetingSettings
**Assembly:** GameAssembly

**Methods (7):**
- get_SearchConeDistance
- set_SearchConeDistance
- get_SearchConeAperture
- set_SearchConeAperture
- get_SearchConeBaseDiameter

### .HoleProgressBarPlayerEntryUi
**Assembly:** GameAssembly

**Methods (16):**
- get_NormalizedProgress
- set_NormalizedProgress
- get_IsLocalPlayer
- Awake
- OnDestroy

### .<<RefreshLobbiesInternal>g__UpdateOnlinePlayers|79_1>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .MatchSetupPlayer
**Assembly:** GameAssembly

**Methods (26):**
- get_Guid
- get_isLocalPlayer
- Awake
- OnEnable
- OnDisable

### .PauseMenuPlayerEntry
**Assembly:** GameAssembly

**Methods (31):**
- get_CurrentPlayerGuid
- set_CurrentPlayerGuid
- get_IsLocalPlayer
- Awake
- OnDisable

### .PlayerCustomizationCosmeticButton
**Assembly:** GameAssembly

**Methods (1):**
- .ctor

### .PlayerCustomizationMenu
**Assembly:** GameAssembly

**Methods (95):**
- get_IsActive
- add_OnOpened
- remove_OnOpened
- add_OnClosed
- remove_OnClosed

### .<SetLoadout>d__75
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .ControllerSelectable
**Assembly:** GameAssembly

**Methods (43):**
- get_IsInteractableSelf
- set_IsInteractableSelf
- get_AsSlider
- set_AsSlider
- get_AsDropdown

### .PlayerIconManager
**Assembly:** GameAssembly

**Methods (7):**
- GetPlayerIconFromSteamId
- GetPlayerIcon
- GetPlayerIcon
- GetPlayerIconInternal
- OnDestroy

### .<<GetPlayerIconInternal>g__LoadIconAsync|0>d
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .UiVisibilityController
**Assembly:** GameAssembly

**Methods (20):**
- get_DesiredAlpha
- set_DesiredAlpha
- get_IsHidden
- SetHidingGroupOverride
- RefreshHidingGroups

### .CharacterPreview
**Assembly:** GameAssembly

**Methods (7):**
- Initialize
- Refresh
- SetPreviewEnabled
- Update
- OnDestroy

### .ControllerInputReselect
**Assembly:** GameAssembly

**Methods (14):**
- Start
- OnEnable
- OnDisable
- ResetLastSelectable
- IsOnTop

### .ScrollRectControllerInput
**Assembly:** GameAssembly

**Methods (5):**
- OnEnable
- OnDisable
- Update
- RefreshMovementType
- .ctor

### .RespawnVfx
**Assembly:** GameAssembly

**Methods (8):**
- get_AsPoolable
- OnEnable
- PlayAnimation
- SetHeightErosion
- PlayingAnimation

### .<PlayingSpawnParticles>d__24
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .ExplosionDecalSpawner
**Assembly:** GameAssembly

**Methods (6):**
- OnEnable
- OnDisable
- OnParticlesPlayed
- GetExplosionRange
- SpawnDecal

### .AirhornPlayerTriggeredVfx
**Assembly:** GameAssembly

**Methods (3):**
- get_AsPoolableParticleSystem
- SetItemTriggered
- .ctor

### .PlayerMovementVfx
**Assembly:** GameAssembly

**Methods (13):**
- Initialize
- OnLeftFootstep
- OnRightFootstep
- SetIsWadingInWater
- SetWadingWaterWorldHeight

### .PlayerStateVfx
**Assembly:** GameAssembly

**Methods (4):**
- PlaySpeedBoostEffects
- StopSpeedBoostEffects
- SetSpeedUpVfxHidden
- .ctor

### .CrtScreenController
**Assembly:** GameAssembly

**Methods (11):**
- Awake
- SetCrtScreenEnabled
- SetBulgeEnabled
- SetAberrationEnabled
- SetScanlineEnabled

### .ImpactFrameController
**Assembly:** GameAssembly

**Methods (5):**
- Start
- SetImpactFrameEnabled
- PlayImpactFrame
- PlayingImpactFrame
- .ctor

### .PlayerCustomizeBuildingVfx
**Assembly:** GameAssembly

**Methods (3):**
- get_OpenDoorsCooldown
- TryOpenDoors
- .ctor

### .<Despawn>d__12
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<Despawn>d__12
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<Despawn>d__11
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<Despawning>d__8
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .<Despawning>d__8
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

### .RespawnVfxTester
**Assembly:** GameAssembly

**Methods (3):**
- Update
- PlayRespawnVfx
- .ctor

### .<Despawning>d__8
**Assembly:** GameAssembly

**Methods (2):**
- MoveNext
- SetStateMachine

