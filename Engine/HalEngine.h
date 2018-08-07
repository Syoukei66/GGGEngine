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
//--Material
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
//--Cereal
    #include "CerealIO.h"

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
  #include "../Common/NativeProcess.h"
  #include "../Common/NativeAssert.h"
  #include "../Common/NativeType.h"
//--Objects
    #include "../Common/NativeObject.h"
    #include "../Common/NativeShader.h"
    #include "../Common/NativeShader.h"
//----Buffer
      #include "../Common/NativeIndexBuffer.h"
      #include "../Common/NativeVertexBuffer.h"

//Asset
  #include "EngineAsset.h"
//--File
    #include "FileResource.h"
    #include "ResourceLoader.h"
//----CSV
      #include "CSVData.h"
      #include "CSVResource.h"
      #include "CSVTokenizer.h"
//----Json
      #include "JsonData.h"
      #include "JsonParser.h"
      #include "JsonResource.h"
//----Model
      #include "ModelData.h"
      #include "ModelResource.h"
//----Particle
      #include "ParticleData.h"
      #include "ParticleDataLoader.h"
      #include "ParticleDataManager.h"
      #include "ParticleSystem.h"
//----Shader
      #include "ShaderResource.h"
//----Spine
      #include "AttachmentVertexes.h"
      #include "EngineAttachmentLoader.h"
      #include "SkeletonAnimation.h"
      #include "SpineData.h"
      #include "SpineDataManager.h"
      #include "SpineResource.h"
//----Sound
      #include "SoundResource.h"
//------c
        #include <spine\spine.h>
//----Texture
      #include "TextureResource.h"
//------Atlas
        #include "TextureAtlas.h"
        #include "TextureAtlasLoader.h"
//--Pool
    #include "EngineResourcePool.h"
    #include "LoadProgressCounter.h"
    #include "ResourcePool.h"
    #include "UserResourcePool.h"
//Resource
//--Texture
    #include "../Common/RenderBuffer.h"
    #include "../Common/Texture.h"
    #include "RenderTexture.h"
    #include "TextureSource.h"
//Scene
  #include "Scene.h"
  #include "SceneTransitioner.h"
//--Event
//----EngineInput
      #include "EngineInputEvent.h"
//----Update
      #include "UpdateEvent.h"

//Structure
  #include "../Common/BlendFunction.h"
//--Color
    #include "../Common/Color.h"
    #include "../Common/Gradient.h"
//--Math
    #include "../Common/Geometry.h"
    #include "../Common/Quaternion.h"
    #include "../Common/Vector2.h"
    #include "../Common/Vector3.h"
    #include "../Common/Vector4.h"
    #include "../Common/Matrix4x4.h"
//--TextureRegion
    #include "ITextureRegion.h"
    #include "TextureRegion.h"
    #include "TiledTextureRegion.h"

//Util
  #include "../Common/Bresenham.h"
  #include "../Common/GraphicsConstants.h"
  #include "../Common/MathConstants.h"
  #include "Util.h"
//--Random
    #include "RandomGenerator.h"
//--Noise
    #include "PerlinNoiseGenerator.h"
//--EasingFunction
    #include "../Common/EasingFunction.h"
    #include "../Common/EasingFunctionManager.h"
//--Singleton
    #include "Singleton.h"
