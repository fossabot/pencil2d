# Build Options

## Commonly Used Options

These are options you might want to pass to QMake when configuring your build.

- `-spec …`: Used to specify the platform and compiler of the build. There is no comprehensive list of available options, but usually you will only need the ones mentioned in our build guides ([macOS](docs/build_mac.md), [Linux](docs/build_linux.md), [Windows](docs/build_win.md))
- `QMAKE_CXX=…`: Used to overwrite the C++ compiler binary
- `CONFIG+=release` / `CONFIG+=debug`: Indicates that the build is meant for release or development, respectively. On non-Windows systems `CONFIG+=release` is the default, while on Windows, both a release and a development build are generated by default
- `CONFIG+=NIGHTLY`: Marks the build as a nightly build
- `CONFIG+=GIT`: Signifies that the git command line program is available and causes information about the current state of the repository to be included in the build. Currently this does nothing without `CONFIG+=NIGHTLY`
- `DEFINES+=QT_NO_DEBUG_OUTPUT`: Disables debug output on the terminal
- `DEFINES+=PENCIL2D_RELEASE`: Marks the build as a released version of Pencil2D

Please note that there is little benefit in using `CONFIG+=NIGHTLY` or `CONFIG+=GIT` in development builds; in fact these options might prevent build acceleration tools such as ccache from working properly.

## Common Build Configurations

- Development builds: `CONFIG+=debug`
- Nightly builds: `CONFIG+=release CONFIG+=NIGHTLY CONFIG+=GIT`
- Release builds: `CONFIG+=release DEFINES+=QT_NO_DEBUG_OUTPUT DEFINES+=PENCIL2D_RELEASE`