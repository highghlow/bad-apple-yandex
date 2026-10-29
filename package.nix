{ stdenv }:

stdenv.mkDerivation {
  pname = "bapple-yandex";
  version = "0.1";

  src = ./.;
}
