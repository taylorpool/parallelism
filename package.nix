{ lib, stdenv, cmake, ninja }:
stdenv.mkDerivation {
  pname = "parallelism";
  version = "0.1.0";

  src = ./.;

  nativeBuildInputs = [
    cmake
    ninja
  ];

  propagatedBuildInputs = [
  ];
}
