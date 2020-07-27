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
    options = {"gtest": ["1.7.0", "1.8.1", "1.10.0"], "openssl": ["1.0.2n", "1.0.2s", "1.1.1g"]}
    default_options = {"gtest":"1.10.0", "openssl":"1.1.1g"}
    exports_sources = "*"

    def build_requirements(self):
        if self.options.gtest == "1.7.0":
            self.build_requires("gtest/1.7.0@systelab/stable")
        elif self.options.gtest == "1.8.1":
            self.build_requires("gtest/1.8.1")
        else:
            self.build_requires("gtest/1.10.0")

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