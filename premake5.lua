project "Diligent Renderer"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    files
    {
        "./**.hpp",
        "./**.cpp",
        "./**.h",
        "./**.c",
        "./**.md",
        "./**.lua",
        "./**.txt",
        "./**.plugin"
    }
    includedirs
    {
        "./Source",
        _MAIN_SCRIPT_DIR .. "/Dependencies/DiligentEngine"
    }
    links
    {
        "DiligentFX"
    }

    RegisterDynamicPlugin("Diligent Renderer")