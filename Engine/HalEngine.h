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
    #include "Transform.h"
//----2D
      #include "GameObject2D.h"
      #include "GameObject2DRenderState.h"
      #include "Transform2D.h"
//------Modifier
        #include "EntityModifier.h"
        #include "EntityModifierAttribute.h"
        #include "EntityModifierFactory.h"
        #include "EntityModifierManager.h"
//------Shape
        #include "Shape.h"
//--------Sprite
          #include "AnimatedSprite.h"
          #include "LoopSprite.h"
          #include "Sprite.h"
//----------TextureRegion
            #include "ITextureRegion.h"
            #include "LoopTextureRegion.h"
            #include "TextureRegion.h"
            #include "TiledTextureRegion.h"
//----3D
      #include "GameObject3D.h"
      #include "GameObject3DRenderState.h"
      #include "Transform3D.h"
      #include "Transform3DRotator.h"
//------Model
        #include "Model.h"
        #include "ModelNode.h"
//------Primitive
        #include "AnimatedSprite3D.h"
        #include "Cube3D.h"
        #include "Line3D.h"
        #include "MeshField.h"
        #include "Plane3D.h"
        #include "Primitive3D.h"
        #include "Shape.h"
        #include "Sprite3D.h"
        #include "Triangle3D.h"
//----Material
      #include "Material.h"
//----Mesh
      #include "Mesh.h"
      #include "MeshMaterial.h"
//------Materials
        #include "MeshMaterial_Cube.h"
        #include "MeshMaterial_Plane.h"
//----VBO
      #include "IVertexBufferObject.h"
//------2D
        #include "SpriteVertexBufferObject.h"
//------3D
        #include "VertexBufferObject_Primitive3D_Cube.h"
        #include "VertexBufferObject_Primitive3D_Line.h"
        #include "VertexBufferObject_Primitive3D_MeshField.h"
        #include "VertexBufferObject_Primitive3D_Plane.h"
        #include "VertexBufferObject_Primitive3D_Triangle.h"
        #include "VertexBufferObject_Sprite3D.h"
//--Light
    #include "Light.h"
//--Mesh

//Director
  #include "Director.h"

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
  #include "INativeProcess_Graphics.h"
  #include "INativeProcess_IO.h"
  #include "INativeProcess_Time.h"
  #include "NativeMethod.h"
  #include "NativeObjectFactory.h"
  #include "NativeType.h"
//--Objects
    #include "NativeIndexBuffer.h"
    #include "NativeMatrix.h"
    #include "NativeMatrixStack.h"
    #include "NativeVertexBuffer.h"
    #include "NativeModel.h"
    #include "NativeObject.h"
    #include "NativeShader.h"
    #include "NativeTexture.h"

//Resource
  #include "EngineAsset.h"
//--File
    #include "FileResource.h"
    #include "ResourceLoader.h"
//----Model
      #include "ModelData.h"
//----CSV
      #include "CSVData.h"
      #include "CSVResource.h"
      #include "CSVTokenizer.h"
//----Json
      #include "JsonParser.h"
//----Fbx
      #include "FbxData.h"
      #include "FbxMeshMaterial.h"
      #include "FbxNodeData.h"
      #include "FbxResource.h"

//----Particle
      #include "ParticleData.h"
      #include "ParticleDataLoader.h"
      #include "ParticleDataManager.h"
      #include "ParticleSystem.h"
//----Spine
      #include "AttachmentVertexes.h"
      #include "EngineAttachmentLoader.h"
      #include "SkeletonAnimation.h"
      #include "SpineData.h"
      #include "SpineDataManager.h"
      #include "SpineResource.h"
//------c
        #include <spine\spine.h>
//----Texture
      #include "Texture.h"
//------Atlas
        #include "TextureAtlas.h"
        #include "TextureAtlasLoader.h"
//--Pool
    #include "EngineResourcePool.h"
    #include "LoadProgressCounter.h"
    #include "ResourcePool.h"
    #include "UserResourcePool.h"

//Scene
  #include "Scene.h"
  #include "SceneTransitioner.h"
//--Event
//----EngineInput
      #include "EngineInputEvent.h"
//----Update
      #include "UpdateEvent.h"

//Structure
  #include "BlendFunction.h"
  #include "Color.h"
  #include "Geometry.h"
  #include "Quaternion.h"
  #include "Vertex.h"

//Util
  #include "Bresenham.h"
  #include "MathConstants.h"
  #include "Util.h"
//--EasingFunction
    #include "EasingFunction.h"
    #include "EasingFunctionManager.h"
//--Singleton
    #include "Singleton.h"
