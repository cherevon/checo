from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.env import VirtualBuildEnv, VirtualRunEnv

class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("qt/6.10.1")

    def build_requirements(self):
        self.tool_requires("qt/6.10.1")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self).generate()

        tc = CMakeToolchain(self)
        tc.user_presets_path = 'build/ConanPresets.json'
        tc.generate()

        VirtualRunEnv(self).generate()
        VirtualBuildEnv(self).generate()