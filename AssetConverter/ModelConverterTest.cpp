
//
////=============================================================================
//// MaterialPropertyData
////=============================================================================
//template <typename T>
//void ModelComparator::Compare(ModelMaterialPropertyData<T>* a, ModelMaterialPropertyData<T>* b)
//{
//  PushState("Name"); Compare(a->name, b->name); PopState();
//  PushState("Value"); Compare(a->value, b->value); PopState();
//}
//
//template<typename T>
//void ModelComparator::AddMessage(T a, T b)
//{
//  AddMessage(std::to_string(a), std::to_string(b));
//}

//
////=============================================================================
//// MeshData
////=============================================================================
////void ModelComparator::Compare(StaticModelMeshData* a, StaticModelMeshData* b)
////{
////  using namespace Graphics;
////
////  PushState("VertexFormat"); Compare(a->vertex_format_, b->vertex_format_); PopState();
////  PushState("VertexSize"); Compare(a->vertex_size_, b->vertex_size_); PopState();
////  PushState("VertexCount"); Compare(a->vertex_count_, b->vertex_count_); PopState();
////  PushState("PolygonCount"); Compare(a->polygon_count_, b->polygon_count_); PopState();
////
////  for (T_UINT32 i = 0; i < a->vertex_count_;)
////  {
////    //Position
////    if (a->vertex_format_ & V_ATTR_POSITION)
////    {
////      PushState("Position");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_POSITION); PopState();
////      PopState();
////      i += V_ATTRSIZE_POSITION;
////    }
////
////    //Normal
////    if (a->vertex_format_ & V_ATTR_NORMAL)
////    {
////      PushState("Normal");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_NORMAL); PopState();
////      PopState();
////      i += V_ATTRSIZE_NORMAL;
////    }
////
////    //UV
////    if (a->vertex_format_ & V_ATTR_UV)
////    {
////      PushState("Uv");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_UV); PopState();
////      PopState();
////      i += V_ATTRSIZE_UV;
////    }
////
////    //UV2
////    if (a->vertex_format_ & V_ATTR_UV2)
////    {
////      PushState("Uv2");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_UV2); PopState();
////      PopState();
////      i += V_ATTRSIZE_UV2;
////    }
////
////    //UV3
////    if (a->vertex_format_ & V_ATTR_UV3)
////    {
////      PushState("Uv3");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_UV3); PopState();
////      PopState();
////      i += V_ATTRSIZE_UV3;
////    }
////
////    //UV4
////    if (a->vertex_format_ & V_ATTR_UV4)
////    {
////      PushState("Uv4");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_UV4); PopState();
////      PopState();
////      i += V_ATTRSIZE_UV4;
////    }
////
////    //Tangent
////    if (a->vertex_format_ & V_ATTR_TANGENT)
////    {
////      PushState("Tangent");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_TANGENT); PopState();
////      PopState();
////      i += V_ATTRSIZE_TANGENT;
////    }
////
////    //Color
////    if (a->vertex_format_ & V_ATTR_COLOR)
////    {
////      PushState("Color");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_COLOR); PopState();
////      PopState();
////      i += V_ATTRSIZE_COLOR;
////    }
////
////    //BoneWeight
////    if (a->vertex_format_ & V_ATTR_BONE_WEIGHTS)
////    {
////      PushState("BoneWeight");
////      PushState(std::to_string(i)); Compare(&a->vertices_[i], &b->vertices_[i], V_ATTRSIZE_BONE_WEIGHTS); PopState();
////      PopState();
////      i += V_ATTRSIZE_BONE_WEIGHTS;
////    }
////
////  }
////
////  PushState("IndexCount"); Compare(a->index_count_, b->index_count_); PopState();
////  PushState("Indices");
////  for (T_UINT32 i = 0; i < a->index_count_; ++i)
////  {
////    PushState(std::to_string(i)); Compare(a->indices_[i], b->indices_[i]); PopState();
////  }
////  PopState();
////
////  PushState("SubmeshCount"); Compare(a->submesh_count_, b->submesh_count_); PopState();
////  PushState("SubmeshIndexCounts"); 
////  for (T_UINT8 i = 0; i < a->submesh_count_; ++i)
////  {
////    PushState(std::to_string(i)); Compare(a->submesh_index_counts_[i], b->submesh_index_counts_[i]); PopState();
////  }
////  PopState();
////  
////  PushState("Bounds"); Compare(a->bounds_, b->bounds_); PopState();
////
////  PushState("BindPoseCount"); Compare(a->bind_pose_count_, b->bind_pose_count_); PopState();
////  PushState("BindPoses");
////  for (T_UINT8 i = 0; i < a->bind_pose_count_; ++i)
////  {
////    PushState(std::to_string(i)); Compare(a->bind_poses_[i], b->bind_poses_[i]); PopState();
////  }
////  PopState();
////}
//
////=============================================================================
//// TextureData
////=============================================================================
//void ModelComparator::Compare(ModelTextureData* a, ModelTextureData* b)
//{
//  PushState("Path"); Compare(a->path_, b->path_); PopState();
//  PushState("Mapping"); Compare(a->mapping_, b->mapping_); PopState();
//  PushState("UvIndex"); Compare(a->uv_index_, b->uv_index_); PopState();
//  PushState("Blend"); Compare(a->blend_, b->blend_); PopState();
//  PushState("Op"); Compare(a->op_, b->op_); PopState();
//  PushState("MapMode"); Compare(a->map_mode_, b->map_mode_); PopState();
//}
//
////=============================================================================
//// MaterialData
////=============================================================================
//void ModelComparator::Compare(ModelMaterialData* a, ModelMaterialData* b)
//{
//  PushState("TextureCount");
//  for (T_UINT32 i = 0; i < ModelTextureData::TEX_TYPE_DATANUM; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->texture_counts_[i], b->texture_counts_[i]); PopState();
//  }
//  PopState();
//
//  PushState("TextureData");
//  for (T_UINT32 i = 0; i < ModelTextureData::TEX_TYPE_DATANUM; ++i)
//  {
//    PushState(std::to_string(i));
//    for (T_UINT32 j = 0; j < a->texture_counts_[i]; ++j)
//    {
//      PushState(std::to_string(i)); Compare(a->texture_datas_[i][j], b->texture_datas_[i][j]); PopState();
//    }
//    PopState();
//  }
//  PopState();
//
//  //bool
//  PushState("BoolPropertyCount"); Compare(a->bool_property_count_, b->bool_property_count_); PopState();
//  PushState("BoolProperty");
//  for (T_UINT32 i = 0; i < a->bool_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->bool_properties_[i], b->bool_properties_[i]); PopState();
//  }
//  PopState();
//
//  //int
//  PushState("IntPropertyCount"); Compare(a->int_property_count_, b->int_property_count_); PopState();
//  PushState("IntProperty");
//  for (T_UINT32 i = 0; i < a->int_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->int_properties_[i], b->int_properties_[i]); PopState();
//  }
//  PopState();
//
//  //float
//  PushState("FloatPropertyCount"); Compare(a->float_property_count_, b->float_property_count_); PopState();
//  PushState("FloatProperty");
//  for (T_UINT32 i = 0; i < a->float_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->float_properties_[i], b->float_properties_[i]); PopState();
//  }
//  PopState();
//
//  //vec2
//  PushState("Vec2PropertyCount"); Compare(a->vec2_property_count_, b->vec2_property_count_); PopState();
//  PushState("Vec2Property");
//  for (T_UINT32 i = 0; i < a->vec2_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->vec2_properties_[i], b->vec2_properties_[i]); PopState();
//  }
//  PopState();
//
//  //vec3
//  PushState("Vec3PropertyCount"); Compare(a->vec3_property_count_, b->vec3_property_count_); PopState();
//  PushState("Vec3Property");
//  for (T_UINT32 i = 0; i < a->vec3_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->vec3_properties_[i], b->vec3_properties_[i]); PopState();
//  }
//  PopState();
//
//  //vec4
//  PushState("Vec4PropertyCount"); Compare(a->vec4_property_count_, b->vec4_property_count_); PopState();
//  PushState("Vec4Property");
//  for (T_UINT32 i = 0; i < a->vec4_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->vec4_properties_[i], b->vec4_properties_[i]); PopState();
//  }
//  PopState();
//
//  //color
//  PushState("ColorPropertyCount"); Compare(a->color_property_count_, b->color_property_count_); PopState();
//  PushState("ColorProperty");
//  for (T_UINT32 i = 0; i < a->color_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->color_properties_[i], b->color_properties_[i]); PopState();
//  }
//  PopState();
//
//  //matrix
//  PushState("MatrixPropertyCount"); Compare(a->matrix_property_count_, b->matrix_property_count_); PopState();
//  PushState("MatrixProperty");
//  for (T_UINT32 i = 0; i < a->matrix_property_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->matrix_properties_[i], b->matrix_properties_[i]); PopState();
//  }
//  PopState();
//
//}
//
////=============================================================================
//// NodeData
////=============================================================================
////void ModelComparator::Compare(StaticModelNodeData* a, StaticModelNodeData* b)
////{
////  PushState("Transate"); Compare(a->translation_, b->translation_); PopState();
////  PushState("Scale"); Compare(a->scaling_, b->scaling_); PopState();
////  PushState("Rotation"); Compare(a->rotation_, b->rotation_); PopState();
////
////  PushState("SubmeshCount"); Compare(a->submesh_count_, b->submesh_count_); PopState();
////
////  PushState("SubmeshData");
////  for (T_UINT32 i = 0; i < a->submesh_count_; ++i)
////  {
////    PushState(std::to_string(i));
////    PushState("MeshIndex"); Compare(a->mesh_indices_[i], b->mesh_indices_[i]); PopState();
////    PushState("SubmeshIndex"); Compare(a->submesh_indices_[i], b->submesh_indices_[i]); PopState();
////    PushState("MaterialIndex"); Compare(a->material_indices_[i], b->material_indices_[i]); PopState();
////    PopState();
////  }
////  PopState();
////
////  PushState("ChildCount"); Compare(a->child_count_, b->child_count_); PopState();
////  PushState("Children");
////  for (T_UINT32 i = 0; i < a->child_count_; ++i)
////  {
////    PushState(std::to_string(i)); Compare(a->children_[i], b->children_[i]); PopState();
////  }
////  PopState();
////}
//
////=============================================================================
//// ModelNodeData
////=============================================================================
//void ModelComparator::Compare(StaticModelData* a, StaticModelData* b)
//{
//  PushState("VertexFormat"); Compare(a->vertex_format_, b->vertex_format_); PopState();
//  PushState("VertexSize"); Compare(a->vertex_size_, b->vertex_size_); PopState();
//
//  PushState("VertexCount"); Compare(a->vertex_count_, b->vertex_count_); PopState();
//  PushState("Vertices");
//  for (T_UINT32 i = 0; i < a->vertex_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->vertices_[i], b->vertices_[i]); PopState();
//  }
//  PopState();
//
//  PushState("PolygonCount"); Compare(a->polygon_count_, b->polygon_count_); PopState();
//
//  PushState("IndexCount"); Compare(a->index_count_, b->index_count_); PopState();
//  PushState("Indices");
//  for (T_UINT32 i = 0; i < a->index_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->indices_[i], b->indices_[i]); PopState();
//  }
//  PopState();
//
//  PushState("SubmeshCount"); Compare(a->submesh_count_, b->submesh_count_); PopState();
//  PushState("SubmeshIndexCounts");
//  for (T_UINT32 i = 0; i < a->submesh_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->submesh_index_counts_[i], b->submesh_index_counts_[i]); PopState();
//  }
//  PopState();
//
//  PushState("Bounds"); Compare(a->bounds_, b->bounds_); PopState();
//
//  PushState("MaterialCount"); Compare(a->material_count_, b->material_count_); PopState();
//  PushState("Materials");
//  for (T_UINT32 i = 0; i < a->material_count_; ++i)
//  {
//    PushState(std::to_string(i)); Compare(a->materials_[i], b->materials_[i]); PopState();
//  }
//  PopState();
//}
