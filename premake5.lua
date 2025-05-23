project "The Forge Rendering"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"
    ignoredefaultlibraries { "MSVCRT" }
    externalwarnings "Off"

    targetdir ("../../" .. OutputTargetPluginDir .. "")
    objdir    ("../../" .. OutputIntermediatePluginDir .. "")

    files
    {
        "./**.h",
        "./**.c",
        "./**.hpp",
        "./**.cpp"
    }

    includedirs
    {
        "./Source"
    }

    ToyboxPluginConfigs()
    RegisterPlugin("The Forge Rendering")