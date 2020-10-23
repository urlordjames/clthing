{ pkgs ? import (fetchTarball https://github.com/nixos/nixpkgs/archive/nixos-20.09.tar.gz) {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    gcc
    cmake
    gnumake
    rocm-opencl-runtime
  ];
}
