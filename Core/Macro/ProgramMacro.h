#pragma once

#ifndef NDEBUG
#define GG_INLINE inline
#define GG_FORCE_INLINE inline
#else
/*!
* @brief �R���p�C���ˑ��̃C�����C���B
* �����s�̊֐��ȂǁA�C�����C�����s�����ǂ�����
* �g�p�p�x����R���p�C���ɔ��肵�Ă��炤�ۂɎg�p����
*/
#define GG_INLINE inline

/*!
* @brief �����I�ȃC�����C���B
* �P�s�̊֐��ȂǂɎg�p����
*/
#define GG_FORCE_INLINE __forceinline

#endif
