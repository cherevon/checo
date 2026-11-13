from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.env import VirtualBuildEnv, VirtualRunEnv

class ChecoRepo(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    default_options = {
        "*:shared": False,
        "qt/*:shared": True, # Qt's license requires shared libraries
        "qt/*:with_pq": False,
    }

    def requirements(self):
        self.requires("gtest/1.17.0")
        self.requires("qt/6.12.0")

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