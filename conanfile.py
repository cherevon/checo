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

    def build_requirements(self):
        self.tool_requires("qt/6.10.1")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self).generate()

        buildEnv = VirtualBuildEnv(self)
        buildEnv.generate()

        runEnv = VirtualRunEnv(self)
        runEnv.generate()

        tc = CMakeToolchain(self)
        tc.user_presets_path = 'build/ConanPresets.json'
        # Combine the build and run environments into a single environment to be able to run Qt tools during the build
        tc.presets_build_environment = buildEnv.environment().compose_env(runEnv.environment())
        tc.generate()