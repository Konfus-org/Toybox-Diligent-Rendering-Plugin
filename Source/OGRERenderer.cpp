#include "OGRERenderer.h"
#include <OGRE-Next/OgreRenderSystem.h>
#include <OGRE-Next/OgreStringConverter.h> // For converting handles to string
#include <OGRE-Next/OgreConfigFile.h>
#include <OGRE-Next/OgreResourceGroupManager.h>
#include <OGRE-Next/OgreSceneManager.h>
#include <OGRE-Next/OgreCamera.h>
#include <OGRE-Next/OgreViewport.h>
#include <OGRE-Next/OgreWindow.h>

namespace OGRERendering
{
    OGRERenderer::OGRERenderer()
    {
        _ogreRoot = OGRE_NEW Ogre::Root();
        SetApi(Tbx::GraphicsApi::OpenGl);
        _ogreRoot->initialise(false);
        _ogreSceneManager = _ogreRoot->createSceneManager(Ogre::SceneType::ST_GENERIC, 1);

        // Load resources (e.g., from resources.cfg)
        //Ogre::ConfigFile cf;
        //cf.load("resources.cfg");

        //Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
        //while (secIt.hasMoreElements())
        //{
        //    Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
        //    Ogre::ConfigFile::SettingsMultiMap::iterator it;
        //    for (it = settings->begin(); it != settings->end(); ++it)
        //    {
        //        Ogre::String locType = it->first;
        //        Ogre::String name = it->second;
        //        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
        //            name, locType, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        //    }
        //}

        // Basic Ogre setup (similar to previous tutorial)
        //mOgreCamera = mOgreSceneManager->createCamera("MainCamera");
        //mOgreCamera->setPosition(0, 5, 10);
        //mOgreCamera->lookAt(0, 0, 0);
        //mOgreCamera->setNearClipDistance(0.1f);
        //mOgreCamera->setFarClipDistance(1000.0f);

        // Initialise all resource groups (loads meshes, textures etc.)
        //Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(false);

        //// Add some content
        //Ogre::Entity* sinbadEntity = mOgreSceneManager->createEntity("Sinbad.mesh");
        //Ogre::SceneNode* node = mOgreSceneManager->getRootSceneNode()->createChildSceneNode();
        //node->attachObject(sinbadEntity);
        //node->setPosition(0, 0, -5);

        //// Add a basic light
        //Ogre::Light* light = mOgreSceneManager->createLight("MainLight");
        //Ogre::SceneNode* lightNode = mOgreSceneManager->getRootSceneNode()->createChildSceneNode();
        //lightNode->attachObject(light);
        //lightNode->setPosition(0, 10, 15);
        //light->setType(Ogre::Light::LT_DIRECTIONAL);
        //light->setDirection(Ogre::Vector3(0, -1, -1).normalisedCopy());
        //light->setDiffuseColour(1.0f, 1.0f, 1.0f);
        //light->setSpecularColour(1.0f, 1.0f, 1.0f);
    }

    void OGRERenderer::ProcessData(const Tbx::RenderData& data)
    {
        const auto& command = data.GetCommand();
        const auto& payload = data.GetPayload();
        switch (command)
        {
            case Tbx::RenderCommand::None:
            {
                TBX_VERBOSE("OpenGl Renderer: Processing none cmd...");
                break;
            }
            case Tbx::RenderCommand::Clear:
            {
                TBX_VERBOSE("OpenGl Renderer: Processing clear cmd...");

                const auto& color = std::any_cast<const Tbx::Color&>(payload);
                Clear(color);
                break;
            }
            case Tbx::RenderCommand::CompileMaterial:
            {
                TBX_VERBOSE("OpenGl Renderer: Processing compile material cmd...");

                const auto& material = std::any_cast<const Tbx::Material&>(payload);
                CompileShader(material.GetShader());
                break;
            }
            case Tbx::RenderCommand::UploadMaterialsTextures:
            {
                TBX_VERBOSE("OpenGl Renderer: Processing upload material textures cmd...");

                const auto& material = std::any_cast<const Tbx::Material&>(payload);

                int textureSlot = 0;
                for (const auto& texture : material.GetTextures())
                {
                    UploadTexture(texture, textureSlot);
                    textureSlot++;
                }
                break;
            }
            case Tbx::RenderCommand::UploadMaterialShaderData:
            {
                TBX_VERBOSE("OpenGl Renderer: Processing upload material data cmd...");

                const auto& shaderData = std::any_cast<const Tbx::ShaderData&>(payload);
                UploadShaderData(shaderData);
                break;
            }
            case Tbx::RenderCommand::SetMaterial:
            {
                TBX_VERBOSE("OpenGl Renderer: Processing set material cmd...");

                const auto& material = std::any_cast<const Tbx::Material&>(payload);
                SetMaterial(material);
                break;
            }
            case Tbx::RenderCommand::RenderMesh:
            {
                TBX_VERBOSE("OpenGl Renderer: Processing mesh cmd...");

                const auto& mesh = std::any_cast<const Tbx::Mesh&>(payload);
                Draw(mesh);
                break;
            }
            default:
            {
                TBX_ASSERT(false, "Unknown render command type.");
                break;
            }
        }
    }

    void OGRERenderer::SetContext(const std::weak_ptr<Tbx::IRenderSurface>& context)
    {
        _renderSurface = context.lock()->GetNativeHandle();

        // Call initialise with `false` to prevent Ogre from creating a new window

        // This is crucial: tell OGRE not to create its own window by passing 'false'
        // and provide the external window handle in miscParams.
        auto miscParams = Ogre::NameValuePairList();
        miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(_renderSurface);

        // Create the RenderWindow using your external handle
        _ogreRenderSurface = _ogreRoot->createRenderWindow(
            "OgreRenderWindow", context.lock()->GetSize().Width, context.lock()->GetSize().Height, false, &miscParams);
    }

    void OGRERenderer::SetViewport(const Tbx::Size& size)
    {
        _viewportSize = size;
    }

    void OGRERenderer::SetResolution(const Tbx::Size& size)
    {
        _resolution = size;
    }

    void OGRERenderer::SetVSyncEnabled(bool enabled)
    {
        _vsyncEnabled = enabled;
    }

    void OGRERenderer::UploadTexture(const Tbx::Texture& texture, Tbx::uint slot)
    {
    }

    void OGRERenderer::CompileShader(const Tbx::Shader& shader)
    {
    }

    void OGRERenderer::UploadShaderData(const Tbx::ShaderData& data)
    {
    }

    void OGRERenderer::SetApi(Tbx::GraphicsApi api)
    {
        Ogre::RenderSystem* rs = nullptr;

        if (api == Tbx::GraphicsApi::DX12)
        {
#ifdef TBX_PLATFORM_WINDOWS

#else
            TBX_ASSERT(false, "DirectX is only supported on Windows devices!");
#endif
        }
        else if (api == Tbx::GraphicsApi::OpenGl)
        {
            rs = _ogreRoot->getRenderSystemByName("OpenGL 3+ Rendering Subsystem");
            if (!rs)
            {
                TBX_ASSERT(false, "Failed to init OGRE render system!");
                return;
            }
        }

        _ogreRoot->setRenderSystem(rs);
    }

    void OGRERenderer::Flush()
    {
    }

    void OGRERenderer::Clear(const Tbx::Color& color)
    {
    }

    void OGRERenderer::BeginDraw()
    {
    }

    void OGRERenderer::EndDraw()
    {
    }

    void OGRERenderer::SetMaterial(const Tbx::Material& material)
    {
    }

    void OGRERenderer::Draw(const Tbx::Mesh& mesh)
    {
    }

    void OGRERenderer::Redraw()
    {
    }
}
