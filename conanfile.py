from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.env import VirtualBuildEnv, VirtualRunEnv

class ChecoRepo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    default_options = {
        "*:shared": True,
        "gtest/*:shared": False, # GoogleTest requires specific flags to be built as shared, so we set it to False explicitly
    }

    def requirements(self):
        self.requires("qt/6.10.1")
        self.requires("gtest/1.17.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self).generate()

        tc = CMakeToolchain(self)
        tc.user_presets_path = 'build/ConanPresets.json'
        tc.generate()

        VirtualRunEnv(self).generate()
        VirtualBuildEnv(self).generate()