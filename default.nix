with ( import ( builtins.fetchGit {
  url = "https://github.com/NixOS/nixpkgs";
  rev = "f480f9d09e4b4cf87ee6151eba068197125714de";
  ref = "nixpkgs-unstable";
} ) {} );
callPackage ./package.nix {}
