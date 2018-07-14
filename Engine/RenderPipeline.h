#pragma once

#include "RenderState.h"

class RenderPipeline
{
public:
  /*
     カリング成功パラメーター
     　・Renderer
       ・ソート条件となるデータ

     カリング失敗パラメーター
     　・Renderer
       ・カリング失敗した条件　⇒　カリングは直前の失敗条件で失敗する可能性が高いので

  　１．描画リストのラスタライズ処理

      整列とカリングの為にキャッシュを取っておきたい
 
      カリング成功/失敗リスト　⇒　レンダラの数だけ領域を確保

      レンダラの更新を探知　⇒　更新されない場合はカリングをスキップ
    　  １つもレンダラが更新されなかった場合はカリングも整列もスキップし直接描画

      カリング処理
  　    [カリング失敗リスト]でのカリング　⇒　成功があれば[追加カリング成功リスト]へ
  　    [カリング成功リスト]でのカリング　⇒　失敗があれば[追加カリング失敗リスト]へ
      並列処理が行えるのでは

      [追加カリング成功リスト]の内容を[カリング成功リスト]へ追加
      [追加カリング失敗リスト]の内容を[カリング失敗リスト]へ追加

    ２．描画処理
      
      高ダイナミックレンジ（HDR） vs 低ダイナミックレンジ（LDR）
      リニアワークフロー vs ガンマワークフロー
      マルチサンプルアンチエイリアシング vs ポストプロセスアンチエイリアシング
      物理ベースレンダリングマテリアル vs 通常のマテリアル
      ライティングあり vs ライティングなし
      ライティングの手法
      シャドーイングの手法
      
      ソート条件
      ライトプローブやライトマップの設定
      バッチングやインスタンシングの使用有無
      現在のドローコールにどのシェーダーパスを使用するか

      などを記述

      [カリング成功リスト]をソート条件を基にソート
      [カリング成功リスト]で描画を行う
      
    ３．ポストプロセス
      
      レンダーターゲットはRenderStateから取得可能
      RenderTargetがnullptrの場合は無効もしくは警告


  */
protected:
  enum FrustumCullingFailureKind
  {
    CULL_FRUSUTUM_FAILED_NEAR,
    CULL_FRUSUTUM_FAILED_LEFT,
    CULL_FRUSUTUM_FAILED_RIGHT,
    CULL_FRUSUTUM_FAILED_TOP,
    CULL_FRUSUTUM_FAILED_BOTTOM,
    CULL_FRUSUTUM_FAILED_FAR,
    CULL_FRUSUTUM_SUCCESS,
  };

  struct SuccessCache
  {
    Renderer* renderer_;
    T_FLOAT distance_;
  };

  struct FailureCache
  {
    Renderer* renderer_;
    bool enabled_failed_;
    bool material_failed_;
    bool layer_id_failed_;
    FrustumCullingFailureKind fustum_failed_;
    bool occlusion_failed_;
  };

private:
  std::vector<SuccessCache> successes_;
  std::vector<FailureCache> failures_;

};
