#pragma once

namespace BlendFunction
{

enum BlendMode
{
  BL_ZERO,
  BL_ONE,
  BL_SRCCLR,
  BL_INVSRCCLR,
  BL_SRCALPHA,
  BL_INVSRCALPHA,
  BL_DSTCLR,
  BL_INVDSTCLR,
  BL_DSTALPHA,
  BL_INVDSTALPHA,
  BL_NOBLEND,

  BL_DATANUM = BL_NOBLEND,
};

static const BlendMode BLEND_DEFAULT_SRC = BL_SRCALPHA;
static const BlendMode BLEND_DEFAULT_DST = BL_INVSRCALPHA;

static const BlendMode BLEND_ADD_SRC = BL_SRCALPHA;
static const BlendMode BLEND_ADD_DST = BL_ONE;

static const BlendMode BLEND_SUB_SRC = BL_SRCALPHA;
static const BlendMode BLEND_SUB_DST = BL_ONE;

static const BlendMode BLEND_MUL_SRC = BL_DSTCLR;
static const BlendMode BLEND_MUL_DST = BL_INVSRCALPHA;

static const BlendMode BLEND_SCREEN_SRC = BL_ONE;
static const BlendMode BLEND_SCREEN_DST = BL_INVSRCALPHA;


}