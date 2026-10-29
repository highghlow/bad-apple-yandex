{
  description = "Bad Apple Yandex";

  inputs = {
    nixpkgs.url = "https://channels.nixos.org/nixpkgs-unstable/nixexprs.tar.zst";
  };

  outputs = inputs: {
    packages.aarch64-linux.bapple =
      let
        pkgs = (import inputs.nixpkgs {
          crossSystem = "aarch64-linux";
          localSystem = "x86_64-linux";
        }).pkgsStatic;
      in pkgs.callPackage ./package.nix {};
  };
}
