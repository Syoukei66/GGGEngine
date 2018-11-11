#include "EntryScene.h"
#include <Windows.h>
#include <Native/Windows/Activity/WindowsActivity.h>

// =================================================================
// Methods from Scene
// =================================================================
void EntryScene::OnLoad()
{
  this->path_.resize(1000);
}

void EntryScene::OnUnload()
{
}

void EntryScene::OnShow(ISceneShowListener* listener)
{
}

void EntryScene::OnHide(ISceneHideListener* listener)
{
}

void EntryScene::Update()
{
  if (this->open_file_dialog_)
  {
    OPENFILENAME ofn = OPENFILENAME();
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = SharedRef<WindowsActivity>::StaticCast(Application::GetMainActivity())->GetWindowHandle();
    ofn.lpstrFile = &this->path_[0];
    ofn.nMaxFile = sizeof(this->path_[0]) * this->path_.size();
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
    {

    }
    this->open_file_dialog_ = false;
  }

  ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiSetCond_Once);
  ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f), ImGuiSetCond_Once);

  ImGui::Begin("EntryMenu");

  ImGui::Text(u8"ファイル名");
  ImGui::InputText("", &this->path_[0], this->path_.size());
  this->open_file_dialog_ |= ImGui::Button(u8"開く");

  ImGui::End();
}
