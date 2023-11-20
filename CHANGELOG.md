# SpaRcle Blog 

### These are changes that were made during the last week.

## Week №3 - 2023-11-16
```
GitHub {
    Added prototype version of contribution guidelines.
}

Linux {
    Started implementing Linux support.
    Implemented stacktrace which takes all needed information from reading the Engine's binary file.
    Currently working on implementation of X11 window and compilation of scripts.
}

Readme {
    Added CI build statistics.
    Added commit activity and discord badges.
}

CI {
    MainCI.yml was created. It now handles #SR_CI_LINUX and #SR_CI_WINDOWS macroses in commit description.
    Depending on it, MainCI runs either Linux build or Windows build (or both).

    Implemented IssuesCI.yml, this stage is ran after the builds
    and it creates an issue if build failed. Ex. ||https://github.com/SpaRcle-Studio/SREngine/issues/70||

    This workflow also handles #SR_CLOSE() macros which can take several issue IDs as arguments
    and if builds were successful, it closes them.
    (because standard GitHub's "closes #id" syntax closes issues only after merging in master branch)
}

Bugs {
    Fixed several multi-threading issues -> fixed singleton multi-instance under GCC compiler.
}

TypeTraits {
    Implemented easy-to-use component properties system.
}

Physics {
    Improved internal rigidbody implementation.
}

Security {
    Fixed possible OS command injection. Our CodeFactor score is now A+ :)
}

UI {
    Implemented sliced image feature.
}

Submodules {
    Several updates in EvoVulkan and other SpaRcle submodules.
}

StringAtom {
    StringAtom was implemented.
    Shaders and materials now use it instead of std::string.
}

SRSL {
    Added syntax highlighting configuration file for SRSL in CLion.

    P.S. SRSL stands for SpaRcle Engine Shader Language.
}
```