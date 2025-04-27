from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout


class Task2Recipe(ConanFile):
    name = "task2"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def configure(self):
        if not self.settings.build_type:
            self.settings.build_type = "Release"

    def requirements(self):
        self.requires("gtest/1.16.0")
        self.requires("raylib/5.5")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
