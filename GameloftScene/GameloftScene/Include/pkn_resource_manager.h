#pragma once
#include "pkn_prerequiites.h"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
namespace pugaknSDK {
  class Resource {
  public:
    virtual ~Resource() {};
  };
  class ResourceFactory {
  public:
    virtual void Init() = 0;
    virtual Resource* Load(std::string path) = 0;
    virtual bool IsCompatible(std::string ext) = 0;
    virtual std::shared_ptr<Resource> GetDefaultResource() { return m_defaultResource; }
    virtual ~ResourceFactory() {};
  protected:
    std::shared_ptr<Resource> m_defaultResource;
  };

  class ResourceManager {
  private:
    using FactoryPtr = std::unique_ptr<ResourceFactory>;
  public:
    using SharedResource = std::shared_ptr<Resource>;
    static void Init();
    static void Destroy();
    static SharedResource GetResource(std::string path);

    template <typename T>
    static std::shared_ptr<T> GetResourceT(std::string path) {
      return std::dynamic_pointer_cast<T>(GetResource(path));
    }

    static SharedResource LoadResource(std::string path);
    static bool IsLoaded(std::string path);
  private:
    static ResourceManager* Instance();
    static ResourceManager* m_instance;

    std::vector<FactoryPtr> m_foctories;
    std::unordered_map<std::string, SharedResource> m_resources;
  };
}