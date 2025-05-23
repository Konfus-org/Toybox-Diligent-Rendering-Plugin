#pragma once
#include <Tbx/Core/Rendering/IRenderer.h>
#include <OGRE-Next/OgreRoot.h>

namespace OGRERendering
{
    class OGRERenderer : public Tbx::IRenderer
    {
    public:
        OGRERenderer();
        ~OGRERenderer() override = default;

        void ProcessData(const Tbx::RenderData& data) final;

        void Flush() final;
        void Clear(const Tbx::Color& color) final;

        void BeginDraw() final;
        void EndDraw() final;

        void Draw(const Tbx::Mesh& mesh) final;
        void Redraw() final;

        void CompileShader(const Tbx::Shader& shader) final;
        void UploadTexture(const Tbx::Texture& texture, Tbx::uint slot) final;
        void UploadShaderData(const Tbx::ShaderData& data) final;

        void SetApi(Tbx::GraphicsApi api) final;
        void SetMaterial(const Tbx::Material& material) final;
        void SetContext(const std::weak_ptr<Tbx::IRenderSurface>& context) final;
        void SetViewport(const Tbx::Size& size) final;
        void SetResolution(const Tbx::Size& size) final;
        void SetVSyncEnabled(bool enabled) final;

        Tbx::Size GetViewportSize() const { return _viewportSize; }

    private:
        Ogre::Root* _ogreRoot = nullptr;
        Ogre::Window* _ogreRenderSurface = nullptr;
        Ogre::SceneManager* _ogreSceneManager = nullptr;

        Tbx::NativeHandle _renderSurface = -1;
        Tbx::Size _resolution = {0, 0};
        Tbx::Vector2I _viewportPos = { 0, 0 };
        Tbx::Size _viewportSize = { 0, 0 };

        bool _vsyncEnabled = true;
    };
}

