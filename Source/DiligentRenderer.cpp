#include "DiligentRenderer.h"

namespace DiligentRendering
{
    DiligentRenderer::DiligentRenderer()
    {
    }

    void DiligentRenderer::ProcessData(const Tbx::RenderData& data)
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

    void DiligentRenderer::SetContext(const std::weak_ptr<Tbx::IRenderSurface>& context)
    {
        _renderSurface = context.lock()->GetNativeHandle();
    }

    void DiligentRenderer::SetViewport(const Tbx::Size& size)
    {
        _viewportSize = size;
    }

    void DiligentRenderer::SetResolution(const Tbx::Size& size)
    {
        _resolution = size;
    }

    void DiligentRenderer::SetVSyncEnabled(bool enabled)
    {
        _vsyncEnabled = enabled;
    }

    void DiligentRenderer::UploadTexture(const Tbx::Texture& texture, Tbx::uint slot)
    {
    }

    void DiligentRenderer::CompileShader(const Tbx::Shader& shader)
    {
    }

    void DiligentRenderer::UploadShaderData(const Tbx::ShaderData& data)
    {
    }

    void DiligentRenderer::SetApi(Tbx::GraphicsApi api)
    {
    }

    void DiligentRenderer::Flush()
    {
    }

    void DiligentRenderer::Clear(const Tbx::Color& color)
    {
    }

    void DiligentRenderer::BeginDraw()
    {
    }

    void DiligentRenderer::EndDraw()
    {
    }

    void DiligentRenderer::SetMaterial(const Tbx::Material& material)
    {
    }

    void DiligentRenderer::Draw(const Tbx::Mesh& mesh)
    {
    }

    void DiligentRenderer::Redraw()
    {
    }
}
