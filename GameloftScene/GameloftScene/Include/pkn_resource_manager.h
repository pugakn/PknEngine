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
    /**
    * Allocate memory and initialize ResourceFactory if needed 
    */
    virtual void Init() = 0;
    /**
    * Load
    */
    virtual Resource* Load(std::string path, std::string extraPath = "") = 0;
    /**
    * Load
    */
    virtual bool IsCompatible(std::string ext) = 0;
    /**
    * Returns a default resource for the type of resource
    * (Used when the resource couldn´t be found)
    */
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
  public:
    /**
    * Resources path
    */
    static const std::string ASSETS_PATH;
    static const std::string TEXTURES_PATH;
    static const std::string SHADERS_PATH;
    static const std::string MODELS_PATH;
  private:
    using FactoryPtr = std::unique_ptr<ResourceFactory>;
  public:
    using SharedResource = std::shared_ptr<Resource>;
    /**
    * Create all the resources factories
    */
    static void Init();
    /**
    * Deallocate memory
    */
    static void Destroy();
    /**
    * 
    */
    static SharedResource GetResource(std::string path);

    /**
    *
    */
    template <typename T>
    static std::shared_ptr<T> GetResourceT(std::string path) {
      return std::dynamic_pointer_cast<T>(GetResource(path));
    }

    /**
    *
    */
    static SharedResource LoadResource(std::string path,std::string extraPath = "");
    /**
    *
    */
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