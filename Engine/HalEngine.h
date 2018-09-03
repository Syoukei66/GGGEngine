#pragma once

#include "Moniker.h"

//Activity
#include "BaseActivity.h"

//Allocator
#include "PoolAllocator.h"

//Component
#include "GameComponent.h"
//--Camera
#include "Camera.h"
//----2D
#include "Camera2D.h"
#include "Camera2D_MultiTarget.h"
//----3D
#include "Camera3D.h"
#include "Camera3D_LookAt.h"
#include "Camera3D_Transformed.h"
//--Collision
//----2D
#include "Collider2D.h"
#include "Collision2D.h"
//----3D
#include "Collider3D.h"
#include "Collision3D.h"
//--GameObject
#include "GameObject.h"
#include "GameObjectRenderState.h"
#include "GameObjectRenderQueue.h"
#include "Transform.h"
//----2D
#include "GameObject2D.h"
#include "Transform2D.h"
//------Modifier
#include "EntityModifier.h"
#include "EntityModifierAttribute.h"
#include "EntityModifierFactory.h"
#include "EntityModifierManager.h"
//------Sprite
#include "AnimatedSprite.h"
#include "LoopSprite.h"
#include "Sprite.h"
//------Spine
#include "SkeletonAnimation.h"
//----3D
#include "GameObject3D.h"
#include "Transform3D.h"
#include "Transform3DRotator.h"
//------Model
#include "Model.h"
#include "ModelNode.h"
//------Primitive
#include "AnimatedSprite3D.h"
#include "Cube3D.h"
#include "Plane3D.h"
#include "Sprite3D.h"
//--Light
//--rcMaterial
#include "Material.h"
#include "ShaderProperties.h"
//--Mesh
#include "Mesh.h"
#include "MeshResource.h"
//----Builder
#include "MeshBuilder.h"
#include "MeshBuilder_Cube.h"
#include "MeshBuilder_Plane.h"
#include "MeshBuilder_Sprite.h"
//----Factory
#include "MeshFactory_Cube.h"
#include "MeshFactory_Plane.h"
#include "MeshFactory_Sprite.h"
//--Renderer
#include "AnimatedSpriteRenderer.h"
#include "MeshRenderer.h"
#include "Renderer.h"
#include "SpriteRenderer.h"
//Director
#include "Director.h"

//ThirdPirty
//--Eigen
#include "Eigen\Core.h"
#include "Eigen\Geometry.h"
//--imgui
#include "imgui/imgui.h"
#include "imgui_ja_gryph_ranges.h"

//Engine
#include "Engine.h"
#include "EngineInitializeSetting.h"
#include "EngineOption.h"
//--Input
#include "AnalogInput.h"
#include "DigitalInput.h"
#include "EngineInput.h"
#include "InputDevice.h"
#include "InputDeviceManager.h"

//Input
#include "InputManager.h"
#include "InputSetting.h"

//Native
#include "../Core/NativeProcess.h"
#include "../Core/NativeAssert.h"
#include "../Core/NativeType.h"
//--Objects
#include "../Core/NativeObject.h"
#include "../Core/NativeShader.h"
#include "../Core/NativeShader.h"
//----Buffer
#include "../Core/NativeIndexBuffer.h"
#include "../Core/NativeVertexBuffer.h"

//Asset
#include "AssetContainer.h"
#include "LoadProgressCounter.h"
#include "AssetManager.h"
//Resource
//--Texture
#include "../Core/RenderBuffer.h"
#include "../Core/Texture.h"
#include "RenderTexture.h"
#include "TextureSource.h"
//----Atlas
#include "TextureAtlas.h"
#include "TextureAtlasLoader.h"
//--Model
#include "StaticModelResource.h"
//--Particle
#include "ParticleData.h"
#include "ParticleDataManager.h"
#include "ParticleSystem.h"

//Scene
#include "Scene.h"
#include "SceneTransitioner.h"
//--Event
//----EngineInput
#include "EngineInputEvent.h"
//----Update
#include "UpdateEvent.h"

//Structure
#include "../Core/BlendFunction.h"
//--Color
#include "../Core/Color.h"
#include "../Core/Gradient.h"
//--Math
#include "../Core/Geometry.h"
#include "../Core/Quaternion.h"
#include "../Core/Vector2.h"
#include "../Core/Vector3.h"
#include "../Core/Vector4.h"
#include "../Core/Matrix4x4.h"
//--rcTextureRegion
#include "ITextureRegion.h"
#include "TextureRegion.h"
#include "TiledTextureRegion.h"

//Util
#include "../Core/Bresenham.h"
#include "../Core/GraphicsConstants.h"
#include "../Core/MathConstants.h"
#include "Util.h"
//--Random
#include "RandomGenerator.h"
//--Noise
#include "PerlinNoiseGenerator.h"
//--EasingFunction
#include "../Core/EasingFunction.h"
#include "../Core/EasingFunctionManager.h"
//--Singleton
#include "Singleton.h"


#include "../Asset/CSVData.h"
#include "../Asset/JsonData.h"
#include "../Asset/SpineData.h"
#include <spine\spine.h>