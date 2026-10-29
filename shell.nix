{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = [
    (pkgs.python3.withPackages (p: with p; [
      opencv4Full
    ]))
  ];
}
