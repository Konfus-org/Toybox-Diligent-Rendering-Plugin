project "Diligent Renderer"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    RegisterDynamicPlugin("Diligent Renderer")

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

    }
    links
    {
    }