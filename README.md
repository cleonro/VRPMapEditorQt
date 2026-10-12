# VRPMapEditorQt

A Qt Widgets application for editing vehicle-routing maps and generating routes.
The project now builds with CMake and requires **Qt 6.10.1 or newer**. The former
Visual Studio project targeted Qt 4.8.0.

## Requirements

- CMake 3.24 or newer.
- A C++17-capable compiler compatible with your Qt kit.
- Qt 6.10.1 or newer, including Widgets, Network, OpenGL, and OpenGL Widgets.
- Desktop OpenGL development libraries and a driver supporting OpenGL 2.1.
- Ninja for the supplied presets, or another CMake generator.
- Qt Test when `BUILD_TESTING=ON` (the default).

Networking and PNG decoding use Qt. Legacy curl, DevIL, GLUT, and OpenSSL
binaries and unused dependency headers are no longer bundled, and GLU is not
required.

## Build on Linux

Set `QT_ROOT` to the Qt **kit directory**, which contains `lib/cmake/Qt6`, then use
the presets from the repository root:

```sh
export QT_ROOT="$HOME/Qt/6.10.1/gcc_64"
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
../build_Debug/VRPMapEditorQt
```

The Debug and Release presets build in `../build_Debug` and `../build_Release`,
respectively, outside the project directory.

Use `release` in place of `debug` for an optimized build. With a compatible Qt
development package installed in a system location, `QT_ROOT` can be omitted.

The equivalent configure and build commands without presets are:

```sh
cmake -S . -B ../build_Debug -G Ninja \
  -DCMAKE_PREFIX_PATH=/path/to/Qt/6.10.1/gcc_64 \
  -DCMAKE_BUILD_TYPE=Debug
cmake --build ../build_Debug
```

## Build on Windows

Install an x64 Qt kit matching your compiler. For an MSVC kit, run the following
in its x64 Developer PowerShell with CMake and Ninja available:

```powershell
$env:QT_ROOT = "C:/Qt/6.10.1/msvc2022_64"
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
../build_Debug/VRPMapEditorQt.exe
```

Open the root `CMakeLists.txt` in Qt Creator, or open the repository folder in
Visual Studio with CMake support. Generated Visual Studio solutions are also
supported:

```powershell
cmake -S . -B ../build_VS -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_PREFIX_PATH=C:/Qt/6.10.1/msvc2022_64
cmake --build ../build_VS --config Release
```

On Windows, run the application with the selected Qt kit's `bin` directory on
`PATH`, or install a deployed copy:

```powershell
cmake --install ../build_VS --config Release --prefix ../install
../install/bin/VRPMapEditorQt.exe
```

The install step uses Qt's deployment script to copy required Qt runtime files
on supported platforms. CMake runs `moc`, `uic`, and `rcc`; generated files stay
in the build directory.

## Google Maps access

Set `GOOGLE_MAPS_API_KEY` in the application's environment to enable background
map downloads and Google's Directions requests. Without it, local editing and
saved maps remain available, and Google requests are skipped. Requests use HTTPS.

Google requires API access configured in the associated cloud project; see the
[Maps Static API setup](https://developers.google.com/maps/documentation/maps-static/get-api-key)
and [Directions API (Legacy) setup](https://developers.google.com/maps/documentation/directions/get-api-key).
The existing XML Directions integration still uses the legacy service, so its
availability depends on your Google project. Live Google requests were not part
of migration verification.

## Tests and file compatibility

`ctest` runs regression tests for the existing sample map, the 32-bit route
length field, UTF-8 node names, portable math, local HTTP responses, malformed
Directions responses, and cooperative worker shutdown. The HTTP tests need
permission to listen on a loopback socket, but use no external services.

To also run the rendering smoke test on a machine with a desktop display:

```sh
cmake --preset debug -DVRPMAPEDITOR_TEST_OPENGL=ON
cmake --build --preset debug
ctest --preset debug
```

The renderer requests desktop OpenGL 2.1 to support the existing fixed-function
drawing code. OpenGL ES and core-only contexts are not supported by this renderer.
The smoke test checks rendering, grid toggling, texture upload, and window shutdown.
Build with `-DBUILD_TESTING=OFF` if Qt Test is not installed.

Map loading and saving explicitly use `QDataStream::Qt_4_8`. The existing
`qtsavetest.vrpm` fixture round-trips byte-for-byte under Qt 6.10.1, and route
counts remain 32-bit even in a 64-bit build.

The migration was built and tested on Linux with Qt 6.10.1. The Windows build
instructions and deployment have not been verified on a Windows host.
