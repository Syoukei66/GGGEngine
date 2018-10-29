#pragma once

#include <spine/AtlasAttachmentLoader.h>

//TODO:アセット管理の変更に合わせていつか修正する
class EngineAttachmentLoader
{
public:
  EngineAttachmentLoader(spAtlas* atlas);

public:
  spAttachmentLoader super;
  spAtlasAttachmentLoader* atlas_attachment_loader_;
};

