# crazyclock
The main idea of this project is arduino clock with flexible second time.
This would allow to speed up or slow down the time.

## Local Development

### Unit Tests

For unit tests of C code we use [GoogleTest](https://github.com/google/googletest/) with [Bazel](https://google.github.io/googletest/quickstart-bazel.html).

### VS Code

For VS Code with [C/C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
you need to update the settings to [Format Curly Braces on Same Line](https://stackoverflow.com/a/69560647/1823545):

1. Press `ctlr + ,`
2. Search for `C_Cpp.clang_format_fallback`
3. Just change the value in the textfield from `Visual Studio` to `LLVM`
