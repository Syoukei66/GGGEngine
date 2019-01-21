#pragma once

/*!
 * @brief AssetLoader�̃C���^�[�t�F�[�X
 * ���C���h�J�[�h�ȃe���v���[�g���`�ł��Ȃ��̂ŁA
 * AssetManager����Ăяo�������@�\������
 * �܂Ƃ߂��C���^�[�t�F�[�X�Ƃ��Đ؂�o�����B
 */
class IAssetLoader
{
  friend class AssetManager;
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~IAssetLoader() {}

  // =================================================================
  // Methods
  // =================================================================
protected:
  virtual void UnloadCache() = 0;

public:
  virtual bool IsMapped() const = 0;
  virtual T_UINT32 GetUniqueID() const = 0;
  virtual T_UINT32 GetSize() const = 0;

};

/*!
 * @brief �A�Z�b�g�����[�h����N���X�B
 * ���[�h�����C���X�^���X���L���b�V�����Ă���ׁA
 * �����񃍁[�h���s����̂�h���ł���B
 */
template<class Asset_>
class AssetLoader : public IAssetLoader
{
  GG_NO_COPYABLE(AssetLoader);

  friend class AssetManager;
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  AssetLoader(T_UINT32 uid, const std::string& path, const SharedRef<Asset_>& data)
    : unique_id_(uid)
    , path_("Asset/" + path)
    , cache_(data)
  {
    //�{���̓A�[�J�C�u�t�@�C������擾����
    this->size_ = 1;
    this->cache_->SetUniqueId(uid);
  }

  AssetLoader(T_UINT32 uid, const std::string& path)
    : unique_id_(uid)
    , path_("Asset/" + path)
    , cache_()
  {
    //�{���̓A�[�J�C�u�t�@�C������擾����
    this->size_ = 1;
  }

  virtual ~AssetLoader()
  {
    this->UnloadCache();
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  operator SharedRef<Asset_>() const
  {
    return this->CreateFromFile();
  }

  operator SharedRef<const Asset_>() const
  {
    return this->CreateFromFile();
  }

  SharedRef<Asset_> CreateFromFile() const
  {
    AssetLoader<Asset_>* self = const_cast<AssetLoader<Asset_>*>(this);
    if (!self->cache_)
    {
      self->cache_ = Asset_::CreateFromFile(self->path_.c_str());
      self->cache_->SetUniqueId(this->unique_id_);
      GG_ASSERT(self->cache_, "Asset�̃��[�h�Ɏ��s���܂���");
    }
    return self->cache_;
  }

  //void CreateFromFileAsync(std::function<void(Asset_*)> func, T_UINT8 priority)
  //{
  //  if (this->cache_)
  //  {
  //    this->cache_->Retain();
  //    func(this->cache_);
  //    return;
  //  }
  //  this->cache_ = this->LoadProcess(this->path_);
  //  func(this->cache_);
  //}

  GG_INLINE void UnloadCache() override
  {
    this->cache_ = nullptr;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE bool IsMapped() const override
  {
    return (bool)this->cache_;
  }

  GG_INLINE T_UINT32 GetUniqueID() const override
  {
    return this->unique_id_;
  }

  GG_INLINE T_UINT32 GetSize() const override
  {
    return this->size_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  T_UINT32 unique_id_;
  std::string path_;
  T_UINT32 size_;
  SharedRef<Asset_> cache_;
  
};
