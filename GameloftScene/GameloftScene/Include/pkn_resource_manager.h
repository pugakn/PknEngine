#pragma once
#include "pkn_prerequiites.h"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "pkn_module.h"
namespace pugaknSDK {
  class Resource {
  public:
    virtual ~Resource() {};
  };
  class ResourceFactory {
  public:
    virtual void Init() = 0;
    virtual Resource* Load(std::string path, std::string extraPath = "") = 0;
    virtual bool IsCompatible(std::string ext) = 0;
    virtual std::shared_ptr<Resource> GetDefaultResource() { return m_defaultResource; }

    explicit ResourceFactory() = default;
    ResourceFactory(ResourceFactory&&) = default;
    ResourceFactory(const ResourceFactory&) = delete;
    ResourceFactory& operator=(const ResourceFactory&) = delete;
    virtual ~ResourceFactory() = default;
  protected:
    std::shared_ptr<Resource> m_defaultResource;
  };

  class ResourceManager : public Module<ResourceManager> {
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

    static SharedResource LoadResource(std::string path,std::string extraPath = "");
    static bool IsLoaded(std::string path);
  private:
    std::vector<FactoryPtr> m_foctories;
    std::unordered_map<std::string, SharedResource> m_resources;

  private:
    //Private constructor as this is a Module class
    friend class Module<ResourceManager>;
    ResourceManager() = default;
  };
}