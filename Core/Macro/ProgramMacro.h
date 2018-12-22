#pragma once

#ifndef NDEBUG
#define GG_INLINE inline
#define GG_FORCE_INLINE inline
#else
/*!
* @brief コンパイラ依存のインライン。
* 複数行の関数など、インラインを行うかどうかを
* 使用頻度からコンパイラに判定してもらう際に使用する
*/
#define GG_INLINE inline

/*!
* @brief 強制的なインライン。
* １行の関数などに使用する
*/
#define GG_FORCE_INLINE __forceinline

#endif
