# SnakeSFML

## How to run (Visual Studio)

1. Download [SFML-2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1/)
2. In project properties:
   - Put `<sfml-install-path>/include` to C/C++ > General > Additional Include Directiories
   - Put `<sfml-install-path>/lib` to Linker > General > Additional Library Directories
3. If You don't use my `.vcxproj` file:
   Add libraries to Linker > Input > Additional Dependencies:
   - For **Debug**:
     - `sfml-graphics-d.lib`
     - `sfml-window-d.lib`
     - `sfml-system-d.lib`
   - For **Release**:
     - `sfml-graphics.lib`
     - `sfml-window.lib`
     - `sfml-system.lib`
4. Add DLLs to Your application folder:
   - If built with **Debug** configuration:
     - `sfml-graphics-d-2.dll`
     - `sfml-system-d-2.dll`
     - `sfml-window-d-2.dll`
   - If built with **Release** configuration:
     - `sfml-graphics-2.dll`
     - `sfml-system-2.dll`
     - `sfml-window-2.dll`
    
## How to use

1. Create `Game` object of demanded size `x`, `y`.
2. Call `Gane::Start()` on Your `Game` object.
