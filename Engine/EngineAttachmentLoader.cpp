#include "EngineAttachmentLoader.h"

#include <spine/extension.h>
#include "AttachmentVertexes.h"

static unsigned short quadTriangles[6] = { 0, 1, 2, 2, 3, 0 };

spAttachment* EngineAttachmentLoader_createAttachment(spAttachmentLoader* loader, spSkin* skin, spAttachmentType type,
  const char* name, const char* path) {
  EngineAttachmentLoader* self = SUB_CAST(EngineAttachmentLoader, loader);
  return spAttachmentLoader_createAttachment(SUPER(self->atlas_attachment_loader_), skin, type, name, path);
}

void EngineAttachmentLoader_configureAttachment(spAttachmentLoader* loader, spAttachment* attachment) {
  attachment->attachmentLoader = loader;

  if (attachment->type != SP_ATTACHMENT_REGION)
  {
    //RegionˆÈŠO‚Í–¢‘Î‰ž
    return;
  }
  spRegionAttachment* region_attachment = SUB_CAST(spRegionAttachment, attachment);
  spAtlasRegion* region = (spAtlasRegion*)region_attachment->rendererObject;
  AttachmentVertexes* attachment_vertexes = new AttachmentVertexes((TextureResource*)region->page->rendererObject, 4);
  Vertex::VCT* vertexes = attachment_vertexes->vertexes_;
  for (int i = 0, ii = 0; i < 4; ++i, ii += 2) {
    vertexes[i].uv[0] = region_attachment->uvs[ii];
    vertexes[i].uv[1] = region_attachment->uvs[ii + 1];
  }
  region_attachment->rendererObject = attachment_vertexes;
}

void EngineAttachmentLoader_disposeAttachment(spAttachmentLoader* loader, spAttachment* attachment) {
  if (attachment->type != SP_ATTACHMENT_REGION)
  {
    //RegionˆÈŠO‚Í–¢‘Î‰ž
    return;
  }
  spRegionAttachment* region_attachment = SUB_CAST(spRegionAttachment, attachment);
  delete (AttachmentVertexes*)region_attachment->rendererObject;
}

void EngineAttachmentLoader_dispose(spAttachmentLoader* loader) {
 EngineAttachmentLoader* self = SUB_CAST(EngineAttachmentLoader, loader);
  spAttachmentLoader_dispose(SUPER_CAST(spAttachmentLoader, self->atlas_attachment_loader_));
  _spAttachmentLoader_deinit(loader);
}

EngineAttachmentLoader::EngineAttachmentLoader(spAtlas* atlas)
{
  _spAttachmentLoader_init(
    &this->super,
    EngineAttachmentLoader_dispose,
    EngineAttachmentLoader_createAttachment,
    EngineAttachmentLoader_configureAttachment,
    EngineAttachmentLoader_disposeAttachment
  );
  this->atlas_attachment_loader_ = spAtlasAttachmentLoader_create(atlas);
}
