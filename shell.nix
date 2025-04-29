{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = [
    pkgs.qt6.full
    pkgs.cmake
    pkgs.gcc
    pkgs.git
    pkgs.xkeyboard_config
    pkgs.vulkan-headers
  ];

  buildInputs = [
    pkgs.qt6.full
    pkgs.xkeyboard_config
    pkgs.libxkbcommon
  ];

  shellHook = ''
    export QT_PLUGIN_PATH=${pkgs.qt6.qtbase}/lib/qt-6/plugins
  '';
}
