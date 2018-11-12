#pragma once

class URI;
class AssetEntity;

class EntryScene : public Scene
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(EntryScene);
  GG_CREATE_FUNC(EntryScene) { return Scene::Init(); }

  // =================================================================
  // Methods from Scene
  // =================================================================
public:
  virtual void OnLoad() override;
  virtual void OnUnload() override;
  virtual void OnShow(ISceneShowListener* listener) override;
  virtual void OnHide(ISceneHideListener* listener) override;
  virtual void Update() override;

  // =================================================================
  // Methods
  // =================================================================
private:
  void ShowViewer(const URI& uri);

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<char> path_;
  bool open_file_dialog_;
  AssetEntity* selected_entity_;

};