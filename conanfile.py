from conans import ConanFile, CMake, tools

class PatternsConan(ConanFile):
    name = "Patterns"
    description = "C++ REST API framework"
    url = "https://github.com/systelab/cpp-patterns"
    homepage = "https://github.com/systelab/cpp-patterns"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "patterns", "c++")
    license = "MIT"
    generators = "cmake_find_package"
    settings = "os", "compiler", "build_type", "arch"
    options = {"gtest": ["1.15.0"]}
    default_options = {"gtest":"1.15.0"}
    exports_sources = "*"

    def build_requirements(self):
        self.build_requires("gtest/1.15.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst=("bin/%s" % self.settings.build_type), src="bin")
        self.copy("*.dylib*", dst=("bin/%s" % self.settings.build_type), src="lib")
        self.copy("*.so*", dst=("bin/%s" % self.settings.build_type), src="lib")

    def package(self):
        self.copy("*.h", dst="include/Patterns", src="src/Patterns")
        self.copy("*Patterns.lib", dst="lib", keep_path=False)
        self.copy("*Patterns.pdb", dst="lib", keep_path=False)
        self.copy("*Patterns.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)